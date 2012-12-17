/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/

#ifndef PROFILEMANAGERLOGIC_H_
#define PROFILEMANAGERLOGIC_H_

#define PROFILEMANGERLOGIC_UNCONFIRMED -2

#include <string>
#include <list>
#include <vector>

#include "../include/CommonApi.h"
#include "../include/ProfileManagerLog.h"
#include "../include/ProfileManagerCfg.h"
#include "../include/SetUserIntf.h"

#include "CommonApiProfileManagerIntf.h"

/**
 * This class holds the main state-machines & logic for registering and notifying clients.
 * It contains the setUser function which is called by the identifaction plugins, as well
 * as the functions for the ProfileManager.fidl interface.
 * Functions are not designed thread safe. If functions need to be called from
 * multiple threads (timer, plugins), it would be expected, that events trigger the functions,
 * rather than using a mutex.
 * Timeout behavior currently not part of POC
 */
class ProfileManagerLogic : public SetUserIntf {
private:

   /// Describes the expected state of the client.
   enum EClientStatus {
      eNotRegistered = 0, eStop = 1, eStopped = 2, eDetected = 3, eConfirmed = 4, eSynced = 5
   };

   /// Describes the expected state of a seat, eNoUser => eStarting => eUser => eStopping => eNoUser
   enum ESeatStatus {
      eNoUser = 0, eStopping = 1, eStarting = 2, eUser = 3
   };

   /// Information needed for each client, that registered within current life-cycle
   struct ProfileManagerClient {
      ClientSelector mClientSelector;        ///< Address/ID needed to send messages to client
      unsigned int   mClientId;              ///< internally used ID of client
      std::string    mClientName;            ///< external and configuration identifcation of client
      EClientStatus  mClientCurrentStatus;   ///< currently expected state of client
      int            mClientDepLevel;        ///< dependency level, found in configuration of client
      int            mCurrentInternalSession;///< internal session, that client is expected to report on stopped/confirm calls
   };

   /// Information needed for each seat, according to defined numOfSeats on construction
   struct Seat {
      std::vector<ProfileManagerClient>   mClientList;      ///< List of clients registered during current life-cycle (will never shrink!)
      unsigned int                        mSeatId;          ///< internally used ID of seat
      int                                 mUserId;          ///< currently set user, -1 if no uses is set
      int                                 mNextUserId;      ///< next userId to be switched to equals mUserId, if no switch is scheduled
      int                                 mDepLevelIndex;   ///< current position of dependencylevel during switch
      ESeatStatus                         mStatus;          ///< the seats state
      int                                 mInternalSession; ///< current internal session of seat
   };

   static short         calcChecksum(uint64_t externalSession);
   static bool          checksumValid(uint64_t externalSession);
   static uint64_t      getExternalSession(int internalSession, int clientId, int seatId);
   static int           getClientId(uint64_t externalSession);
   static int           getInternalSession(uint64_t externalSession);
   static int           getSeatId(uint64_t externalSession);

   uint64_t             getExternalSession(Seat const &seat, ProfileManagerClient const  &client);
   bool                 checkStatus(EClientStatus clientStatus, Seat  const &s, int depLevel);
   bool                 checkNextUserPending(Seat &s);
   bool                 checkReady2Sync(Seat const &s);
   int                  sendSync(int seatId);
   int                  sendDetected(int seatId, int depLevel);
   int                  sendStop(int seatId, int depLevel);
   int                  sendNextLevelDetected(int seatId);
   int                  sendNextLevelStop(int seatId);

   ProfileManagerCfg*               mCfg;
   Seat*                            mSeats;
   int                              mNumOfSeats;
   int                              mInternalSession;
   ProfileManagerLog*               mLog;
   CommonApiProfileManagerIntf*     mClientSend;
   static uint64_t const            checksumKey;

public:

   ProfileManagerLogic(ProfileManagerLog& log, CommonApiProfileManagerIntf& clientSend, ProfileManagerCfg& cfg, int numOfSeats);
   virtual ~ProfileManagerLogic();

   /**
    * Overrides the setUser function of the SetUserIntf
    * @param seatId  Id of seat, where user has been detected
    * @param userId  Id of user, that was detected on the given seat
    */
   void setUser(int seatId, int userId);

   /**
    * Allows to reconfigure, if it might that changes have been done after ProfileManager instanciation
    * @param cfg New Configuration, dependency levels affects only clients, which have never registered during this life-cycle
    */
   void setCfg(ProfileManagerCfg& cfg);


   //functions, that are triggered by clients, via for example  ProfileManage CommanAPI Stub implementation
   void receiveRegister(ClientSelector clientId, std::string appID, int seatID);
   void receiveUnregister(ClientSelector clientId, std::string appID, int seatID);
   void receiveConfirm(uint64_t externalSession);
   void receiveStopped(uint64_t externalSession);
};

#endif /* PROFILEMANAGERLOGIC_H_ */
