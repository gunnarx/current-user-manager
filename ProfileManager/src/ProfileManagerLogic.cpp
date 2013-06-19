/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/

#include "ProfileManagerLogic.h"
#include <stdlib.h>
#include <fstream>

using namespace std;

uint64_t const ProfileManagerLogic::checksumKey = static_cast<uint64_t>(rand()); // Stupid one time pad for one life cycle

//externalSession bytes 0x cs cs is is ci ci si si
//legend: cs=checksum, is=internal session, ci = clientId, si = seatId


short ProfileManagerLogic::calcChecksum(uint64_t externalSession) {
   unsigned short retVal = 0xffff; // Invalid checksum
   if (externalSession <= 0xffffffffffff) {
      // "Calculate" checksum by simply XOR with key, then mod 0xfffe and add 1 to avoid result 0
      // Hence checksum value will be between 0 and 0xff excluding both boundaries
      retVal = ((externalSession ^ checksumKey) % 0xfffe) + 1;
   }
   return retVal;
}


bool ProfileManagerLogic::checksumValid(uint64_t value) {
   bool bRet = false;
   short calculatedChecksum = calcChecksum(value & 0xffffffffffff);
   if (calculatedChecksum == static_cast<short>(value >> 48)) {
      bRet = true;
   }
   return bRet;
}


uint64_t ProfileManagerLogic::getExternalSession(int internalSession, int clientId, int seatId) {
   uint64_t session = ((uint64_t)internalSession & (uint64_t)0xffff) << 32 | (clientId & 0xffff) << 16 | (seatId & 0xffff);
   session = session | ((uint64_t)calcChecksum(session) << 48);
   return session;
}


int ProfileManagerLogic::getClientId(uint64_t externalSession) {
   return (externalSession >> 16) & 0xffff;
}


int ProfileManagerLogic::getInternalSession(uint64_t externalSession) {
   return (externalSession >> 32) & 0xffff;
}


int ProfileManagerLogic::getSeatId(uint64_t exernalSession) {
   return exernalSession & 0xffff;
}


ProfileManagerLogic::ProfileManagerLogic(ProfileManagerLog& log, CommonApiProfileManagerIntf& clientSend)
: mCfg(0)
, mSeats(0)
, mNumOfSeats(-1)
, mInternalSession(0)
, mLog(&log)
, mClientSend(&clientSend)
, mCtrlConsumer(0)
{
}


void ProfileManagerLogic::readCfgFromFile(){
   mCfg = new CProfileManagerCfg();
   unsigned int version;
   unsigned int numOfCfgs;
   fstream cfgFile("profile_manager_cfg", ios::in | ios::binary);
   cfgFile.read((char*)&version, sizeof(unsigned int));
   cfgFile.read((char*)&(mCfg->mDefaultDepLevel), sizeof(int));
   cfgFile.read((char*)&(mCfg->mDefaultTimeOutMs), sizeof(unsigned int));
   cfgFile.read((char*)&(mCfg->mNumOfSeats), sizeof(unsigned int));
   cfgFile.read((char*)&numOfCfgs, sizeof(unsigned int));
   for (int i = 0; i < numOfCfgs; i++) {
      CProfileManagerCfg::ClientCfg ccfg;
      unsigned int nameLen;
      cfgFile.read((char*)&nameLen, sizeof(unsigned int));
      char name[nameLen+1];
      name[nameLen] = 0;
      cfgFile.read(name, nameLen);
      ccfg.mAppName = name;
      cfgFile.read((char*)&(ccfg.mSeatId), sizeof(unsigned int));
      cfgFile.read((char*)&(ccfg.mDepLevel), sizeof(int));
      cfgFile.read((char*)&(ccfg.mTimeOutMs), sizeof(int));
      mCfg->mClientCfgs.push_back(ccfg);
   }
   cfgFile.close();
}


void ProfileManagerLogic::registerMe(CProfileManagerCtrlConsumer& consumer, CProfileManagerCfg* cfg)
{
   mCtrlConsumer = &consumer;
   mCfg = cfg;
   if (mCfg == 0) {
      readCfgFromFile();
   }
   mNumOfSeats = mCfg->mNumOfSeats;
   mSeats = new Seat[mNumOfSeats];
   for (int seatIt = 0; seatIt < mNumOfSeats; seatIt++) {
      Seat* s = &(mSeats[seatIt]);
      s->mSeatId = seatIt;
      s->mUserId = -1;
      s->mNextUserId = -1;
      s->mDepLevelIndex = 0;
      s->mStatus = eNoUser;
      s->mInternalSession = 0;
   }
   for (vector<CProfileManagerCfg::ClientCfg>::iterator cfgIt = mCfg->mClientCfgs.begin(); cfgIt != mCfg->mClientCfgs.end(); cfgIt++) {
      int32_t depLevel = (*cfgIt).mDepLevel;
      if (depLevel >= 0) {
         bool inserted = false;
         vector<int32_t>::iterator depIt = mDepLevels.begin();
         for (; depIt != mDepLevels.end(); depIt++) {
            if (*depIt == depLevel) {
               inserted = true;
               break;
            } else if (*depIt > depLevel) {
               inserted = true;
               (void)mDepLevels.insert(depIt, depLevel);
               break;
            }
         }
         if (!inserted) {
            mDepLevels.push_back(depLevel);
         }
      }
   }
}


/**
 * Overloaded function for identification plugins to call to set a new user. Currently not thread safe!
 * @param seatId ID of seat where new user was detected.
 * @param userId Id of user that was detected on given seat.
 */
void ProfileManagerLogic::setUser(u_int32_t seatId, u_int32_t userId) {
   Seat* s = &(mSeats[seatId]);
   s->mNextUserId = userId;

   if (s->mStatus != eNoUser) {
      s->mStatus = eStopping;
   }

   sendStop(seatId, -1);
   sendNextLevelStop(seatId);

   if (checkNextUserPending(*s)){
      if (sendDetected(seatId, -1) == 0 || sendNextLevelDetected(seatId) == 0) {
         s->mStatus = eUser;
      }
   }
}

void ProfileManagerLogic::unsetUser(u_int32_t seatId){
   //TBD
}


void ProfileManagerLogic::timeOutAction(uint64_t timeOutSessionId, ETimeOutAction timeOutAction){
   //TBD
}


ProfileManagerLogic::~ProfileManagerLogic() {
}


/**
 * Returns true if each client of the given seat and dependency level has the expected client state
 * @param clientStatus  expected state
 * @param s             seat to be examined
 * @param depLevel      only examine clients belonging to this dependency level
 * @return              false: There exist a client, which matches the dependency level, that differs from the expected state
 */
bool ProfileManagerLogic::checkStatus(EClientStatus clientState, Seat const &s, int depLevel) {
   vector<ProfileManagerClient>::const_iterator clientIt;
   for (clientIt = s.mClientList.begin(); clientIt != s.mClientList.end(); clientIt++) {
      ProfileManagerClient const * c = &(*clientIt);
      if ( (c->mClientCurrentStatus != eNotRegistered && c->mClientDepLevel == depLevel) &&
           (c->mClientCurrentStatus != clientState || c->mCurrentInternalSession != s.mInternalSession)) {
         return false;
      }
   }
   return true;
}


/**
 * Construct external Session for given seat and client
 * @return Session as seen in ProfileManager.fidl
 */
uint64_t ProfileManagerLogic::getExternalSession(Seat const &seat, ProfileManagerClient const &client) {
   return getExternalSession(seat.mInternalSession, client.mClientId, seat.mSeatId);
}


/**
 * Send a sync signal to all registered clients for a given seat
 * @param seatId  Seat for which to send signal
 * @return Number of signals send
 */
int ProfileManagerLogic::sendSync(int seatId) {
   int numOfSendMsgs = 0;
   Seat* s = &(mSeats[seatId]);
   vector<ProfileManagerClient>::iterator clientIt;
   for (clientIt = s->mClientList.begin(); clientIt != s->mClientList.end(); clientIt++) {
      ProfileManagerClient * c = &(*clientIt);
      if (c->mClientCurrentStatus != eNotRegistered) {
         mClientSend->sendSynchronizedUser(c->mClientSelector, seatId, s->mUserId, getExternalSession(*s, *c));
         c->mClientCurrentStatus = eSynced;
         numOfSendMsgs++;
      }
   }
   return numOfSendMsgs;
}


/**
 * Send a detected signal to all registered client for the given seat and dependency Level
 * @param seatId
 * @param depLevel
 * @return Number if signals send
 */
int ProfileManagerLogic::sendDetected(int seatId, int depLevel) {
   int numOfSendMsgs = 0;
   Seat* s = &(mSeats[seatId]);

   mCtrlConsumer->onStateChangeStart(s->mUserId, seatId, depLevel, CProfileManagerCtrlConsumer::eConfirm, s->mInternalSession);

   for (vector<ProfileManagerClient>::iterator clientIt = s->mClientList.begin(); clientIt != s->mClientList.end(); clientIt++) {
      ProfileManagerClient * c = &(*clientIt);
      if (c->mClientCurrentStatus != eNotRegistered && c->mClientDepLevel == depLevel) {
         mClientSend->sendDetectedUser(c->mClientSelector, seatId, s->mUserId, getExternalSession(*s, *c));
         c->mClientCurrentStatus = eDetected;
         c->mCurrentInternalSession = s->mInternalSession;
         numOfSendMsgs++;
      }
   }

   //if (numOfSendMsgs == 0) {
      mCtrlConsumer->onStateChangeStop(s->mUserId, seatId, depLevel, CProfileManagerCtrlConsumer::eConfirm, s->mInternalSession);
   //}

   return numOfSendMsgs;
}


/**
 * Send a stop signal to all registered client for the given seat and dependency Level
 * @param seatId
 * @param depLevel
 * @return Number if signals send
 */
int ProfileManagerLogic::sendStop(int seatId, int depLevel) {
   int numOfSendMsgs = 0;
   Seat* s = &(mSeats[seatId]);

   mCtrlConsumer->onStateChangeStart(s->mUserId, seatId, depLevel, CProfileManagerCtrlConsumer::eStopped, s->mInternalSession);


   for (vector<ProfileManagerClient>::iterator clientIt = s->mClientList.begin(); clientIt != s->mClientList.end(); clientIt++) {
      ProfileManagerClient * c = &(*clientIt);
      if (c->mClientCurrentStatus != eNotRegistered && c->mClientCurrentStatus != eStop &&
          c->mClientCurrentStatus != eStopped && c->mClientDepLevel == depLevel) {
         mClientSend->sendStop(c->mClientSelector, seatId, getExternalSession(*s, *c));
         c->mClientCurrentStatus = eStop;
         c->mCurrentInternalSession = s->mInternalSession;
         numOfSendMsgs++;
      }
   }

   if (numOfSendMsgs == 0 ) {
      mCtrlConsumer->onStateChangeStop(s->mUserId, seatId, depLevel, CProfileManagerCtrlConsumer::eStopped, s->mInternalSession);
   }
   return numOfSendMsgs;
}


/**
 * triggers logic due to client registration
 * @param clientSelector   Connection Id used to address the client later via given IPC mechanism
 * @param appID            String identifier (unique per seat), that is needed to find the correct client configuration
 * @param seatID           Seat to register onto
 */
void ProfileManagerLogic::receiveRegister(ClientSelector clientSelector, std::string appID, int seatID) {
   ProfileManagerClient* c = 0;
   if (seatID > 0 && seatID < mNumOfSeats) {
      Seat* s = &(mSeats[seatID]);

      // Check if client is already registered, or has been registered before on this seat
      for (vector<ProfileManagerClient>::iterator clientIt = s->mClientList.begin(); clientIt != s->mClientList.end(); clientIt++) {
         ProfileManagerClient * foundClient = &(*clientIt);
         if (foundClient->mClientName.compare(appID) == 0) {
            c = foundClient;
            break;
         }
      }

      // If client was not yet registered, check what configuration needs to be applied
      if (c == 0) {
         CProfileManagerCfg::ClientCfg* cfgClient = 0;
         for (vector<CProfileManagerCfg::ClientCfg>::iterator cfgClientIt = mCfg->mClientCfgs.begin(); cfgClientIt != mCfg->mClientCfgs.end(); cfgClientIt++) {
            CProfileManagerCfg::ClientCfg * foundClient = &(*cfgClientIt);
            if ((foundClient->mSeatId == -1 || foundClient->mSeatId == seatID) && foundClient->mAppName.compare(appID) == 0) {
               cfgClient = foundClient;
               break;
            }
         }
         ProfileManagerClient newClient;
         newClient.mClientCurrentStatus = eStopped;
         if (cfgClient == 0) {
            newClient.mClientDepLevel = -1;
         } else {
            newClient.mClientDepLevel = cfgClient->mDepLevel;
         }
         newClient.mClientId = s->mClientList.size();
         newClient.mClientName = appID;
         newClient.mClientSelector = clientSelector;
         newClient.mCurrentInternalSession = -1;
         s->mClientList.push_back(newClient);
         c = &(s->mClientList.back());
      }

      // Check if the seat currently has an active user, or is in the process of having an active user
      // If yes send detected signal to client (adhering to dependency level).
      c->mCurrentInternalSession = s->mInternalSession;
      if (s->mStatus == eStarting || s->mStatus == eUser) {
         if (c->mClientDepLevel > -1) {
            mLog->log(PROFILEMAMAGERLOG_LEVEL_WARNING, "ProfileManager: Client with dependencies registered while user is active!");
         }
         if (s->mDepLevelIndex >= (int)mDepLevels.size() || mDepLevels[s->mDepLevelIndex] >= c->mClientDepLevel) {
            mClientSend->sendDetectedUser(c->mClientSelector, seatID, s->mUserId, getExternalSession(*s, *c));
            c->mClientCurrentStatus = eDetected;
         }
      }

      mCtrlConsumer->onClientRegister(seatID, appID);
   }
}


/**
 * triggers logic due to client unregestering
 * @param clientSelector   Connection Id used to address the client later via given IPC mechanism
 * @param appID            String identifier (unique per seat), that is needed to find the correct client configuration
 * @param seatID           Seat to unregister from
 */
void ProfileManagerLogic::receiveUnregister(ClientSelector clientSelector, std::string appID, int seatID) {
   if (seatID > 0 && seatID < mNumOfSeats) {
      Seat* s = &(mSeats[seatID]);
      // Check if client is already registered, or has been registered before on this seat
      for (vector<ProfileManagerClient>::iterator clientIt = s->mClientList.begin(); clientIt != s->mClientList.end(); clientIt++) {
         ProfileManagerClient * foundClient = &(*clientIt);
         if (foundClient->mClientName.compare(appID) == 0) {
            foundClient->mClientCurrentStatus = eNotRegistered;
            mCtrlConsumer->onClientUnregister(seatID, appID);
            break;
         }
      }
   }
}


/**
 * Sends detected signal to clients with a set dependency level. Automatically skips dependency levels,
 * where no clients are registered
 * @param seatId
 * @return number of send detected signals
 */
int ProfileManagerLogic::sendNextLevelDetected(int seatId){
   Seat* s = &(mSeats[seatId]);
   int ctr = 0;

   while (ctr == 0 && (unsigned int)s->mDepLevelIndex < mDepLevels.size()) {
      ctr = sendDetected(seatId, mDepLevels[s->mDepLevelIndex]);
      s->mDepLevelIndex++;
   }

   return ctr;
}


/**
 * Sends stop signal to clients with a set dependency level. Automatically skips dependency levels,
 * where no clients are registered
 * @param seatId
 * @return
 */
int ProfileManagerLogic::sendNextLevelStop(int seatId){
   int ctr = 0;
   Seat* s = &(mSeats[seatId]);
   while (ctr == 0 && s->mDepLevelIndex > 0) {
      s->mDepLevelIndex--;
      ctr = sendStop(seatId, mDepLevels[s->mDepLevelIndex]);
   }
   return ctr;
}


/**
 * triggers logic due to received confirmation
 * @param externalSession
 */
void ProfileManagerLogic::receiveConfirm(uint64_t externalSession) {
   if (!checksumValid(externalSession)) {
      return;
   }

   int internalSession = getInternalSession(externalSession);
   int seatId = getSeatId(externalSession);

   if (seatId >= 0 && seatId < mNumOfSeats && mSeats[seatId].mInternalSession == internalSession) {
      Seat* s = &(mSeats[seatId]);
      int clientId = getClientId(externalSession);
      if (clientId >= 0 && clientId < (int)s->mClientList.size()) {
         // Check if confirmation is valid. For dependent clients, check if next dependency level shall be triggered
         ProfileManagerClient *c = &(s->mClientList[clientId]);
         if (c->mCurrentInternalSession == internalSession && c->mClientCurrentStatus == eDetected) {
            c->mClientCurrentStatus = eConfirmed;
            if (c->mClientDepLevel >= 0 && c->mClientDepLevel < mDepLevels[s->mDepLevelIndex]) {
               if (checkStatus(eConfirmed, *s, c->mClientDepLevel)) {
                  mCtrlConsumer->onStateChangeStop(s->mUserId, seatId, c->mClientDepLevel, CProfileManagerCtrlConsumer::eConfirm, s->mInternalSession);
                  sendNextLevelDetected(seatId);
               }
            }
         }
         // If all clients have confirmed, send sync signal to clients. Special case (eUser): Clients which register
         // during an active user and confirm the detected signal still should get a sync confirmation signal,
         // other clients should not be affected
         bool allConfirmed = true;
         switch (s->mStatus) {
         case eStarting:
            for (vector<ProfileManagerClient>::const_iterator clientIt = s->mClientList.begin(); clientIt != s->mClientList.end(); clientIt++) {
               ProfileManagerClient const * c = &(*clientIt);
               if (c->mClientCurrentStatus != eNotRegistered && (c->mClientCurrentStatus != eConfirmed || c->mCurrentInternalSession != s->mInternalSession)) {
                  allConfirmed = false;
                  break;
               }
            }
            if (allConfirmed) {
               s->mStatus = eUser;
               sendSync(seatId);
            }
            break;
         case eUser:
            c->mClientCurrentStatus = eSynced;
            mClientSend->sendSynchronizedUser(c->mClientSelector, seatId, s->mUserId, getExternalSession(*s, *c));
            break;
         default:
            break;
         }
      }
   }
}


/**
 * triggers logic due to received stopped signal
 * @param externalSession
 */
void ProfileManagerLogic::receiveStopped(uint64_t externalSession) {
   if (!checksumValid(externalSession)) {
      return;
   }

   int internalSession = getInternalSession(externalSession);
   int seatId = getSeatId(externalSession);

   if (seatId >= 0 && seatId < mNumOfSeats && mSeats[seatId].mInternalSession == internalSession) {
      // Check if stopped is valid. For dependent clients, check if next dependency level shall be triggered
      Seat* s = &(mSeats[seatId]);
      int clientId = getClientId(externalSession);
      if (clientId >= 0 && (unsigned int)clientId < s->mClientList.size()) {
         ProfileManagerClient *c = &(s->mClientList[getClientId(externalSession)]);
         if (c->mCurrentInternalSession == internalSession && c->mClientCurrentStatus == eStop) {
            c->mClientCurrentStatus = eStopped;
            if (checkStatus(eStopped, *s, c->mClientDepLevel)) {
               mCtrlConsumer->onStateChangeStop(s->mUserId, seatId, c->mClientDepLevel, CProfileManagerCtrlConsumer::eStopped, s->mInternalSession);
               if (c->mClientDepLevel >= 0 && c->mClientDepLevel == mDepLevels[s->mDepLevelIndex]) {
                  sendNextLevelStop(seatId);
               }
            }
         }
      }
      // Check if after all clients have stopped, if a new user should be activated
      if (checkNextUserPending(*s)){
         if (sendDetected(seatId, -1) == 0 || sendNextLevelDetected(seatId) == 0) {
            s->mStatus = eUser;
         }
      }
   }
}


/**
 * Returns true, if detected signals should send out, because a new user was detected.
 * @param s seat to examine if a new use was detected.
 * @return false: no new user was detected or stopping the previous is still active
 */
bool ProfileManagerLogic::checkNextUserPending(Seat &s){
   if (s.mNextUserId == s.mUserId) {
      return false;
   }
   for (vector<ProfileManagerClient>::const_iterator clientIt = s.mClientList.begin(); clientIt != s.mClientList.end(); clientIt++) {
      ProfileManagerClient const * c = &(*clientIt);
      if (c->mClientCurrentStatus != eNotRegistered && c->mClientCurrentStatus != eStopped) {
         return false;
      }
   }

   s.mUserId = s.mNextUserId;
   if (s.mNextUserId < 0) {
      s.mStatus = eNoUser;
      return false;
   }

   s.mInternalSession++;
   s.mStatus = eStarting;
   return true;
}



