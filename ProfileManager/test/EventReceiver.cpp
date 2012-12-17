/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "EventReceiver.h"
#include "EventMessageQ.h"
#include <list>
#include <cstdio>

using namespace std;

void EventReceiver::sendRegister(ClientSelector clientSelector, std::string appID, int seatId){
   PrflMgrTestTypes::SrvMsg m;
   m.mTestNo = mTestNo;
   m.mReceiveSelector = PrflMgrTestTypes::eSrvRegister;
   m.mClientSelector = clientSelector;
   m.mAppId = appID;
   m.mSeatId = seatId;
   mSrvQ->push(m);
   onEvent(PrflMgrTestTypes::eTRegister, selector2Int(m.mClientSelector) << 16 | m.mSeatId << 8 );
   std::printf("c%i:s.register(seat=%i)\n", selector2Int(m.mClientSelector), m.mSeatId);
}


void EventReceiver::sendUnregister(ClientSelector clientSelector, int seatId){
   PrflMgrTestTypes::SrvMsg m;
   m.mTestNo = mTestNo;
   m.mReceiveSelector = PrflMgrTestTypes::eSrvUnregister;
   m.mClientSelector = clientSelector;
   m.mSeatId = seatId;
   mSrvQ->push(m);
}


void EventReceiver::sendConfirm(ClientSelector clientSelector, uint64_t sessionId){
   PrflMgrTestTypes::SrvMsg m;
   m.mTestNo = mTestNo;
   m.mReceiveSelector = PrflMgrTestTypes::eSrvConfirm;
   m.mClientSelector = clientSelector;
   m.mSessionId = sessionId;
   mSrvQ->push(m);
   onEvent(PrflMgrTestTypes::eTConfirm, selector2Int(m.mClientSelector) << 16);
   std::printf("c%i:s.confirm\n", selector2Int(m.mClientSelector));
}


void EventReceiver::sendStopped(ClientSelector clientSelector, uint64_t sessionId){
   PrflMgrTestTypes::SrvMsg m;
   m.mTestNo = mTestNo;
   m.mReceiveSelector = PrflMgrTestTypes::eSrvStopped;
   m.mClientSelector = clientSelector;
   m.mSessionId = sessionId;
   mSrvQ->push(m);
   onEvent(PrflMgrTestTypes::eTStopped, selector2Int(m.mClientSelector) << 16);
   std::printf("c%i:s.stopped\n", selector2Int(m.mClientSelector));
}


void EventReceiver::sendSetUser(int seatId, int userId){
   PrflMgrTestTypes::SrvMsg m;
   m.mReceiveSelector = PrflMgrTestTypes::eSrvSetUser;
   m.mSeatId = seatId;
   m.mUserId = userId;
   mSrvQ->push(m);
   onEvent(PrflMgrTestTypes::eTSetUser, m.mSeatId << 8 | m.mUserId);
   std::printf("p:s.setUser(seat=%i, user=%i)\n", m.mSeatId, m.mUserId);
}


EventReceiver::EventReceiver(EventMessageQ<PrflMgrTestTypes::ClientMsg>& clientQ, EventMessageQ<PrflMgrTestTypes::SrvMsg>& srvQ)
: mClientQ(&clientQ)
, mSrvQ(&srvQ)
, mSuccess(false)
, mTestNo(-1){
   for (int i = 0; i < NUM_OF_TEST_CLIENTS; i++){
      mClients[i] = new ProfileManagerTestClient(i);
   }
}


EventReceiver::~EventReceiver() {
}


void EventReceiver::sendDetectedUser(ClientSelector clientSelector, int seatId, int userId, uint64_t sessionId){
   PrflMgrTestTypes::ClientMsg m;
   m.mReceiveSelector = PrflMgrTestTypes::eClientDetected;
   m.mClientSelector = clientSelector;
   m.mSeatId = seatId;
   m.mUserId = userId;
   m.mSessionId = sessionId;
   mClientQ->push(m);
}


void EventReceiver::sendSynchronizedUser(ClientSelector clientSelector, int seatId, int userId, uint64_t sessionId){
   PrflMgrTestTypes::ClientMsg m;
   m.mReceiveSelector = PrflMgrTestTypes::eClientSynchronized;
   m.mClientSelector = clientSelector;
   m.mSeatId = seatId;
   m.mUserId = userId;
   m.mSessionId = sessionId;
   mClientQ->push(m);
}


void EventReceiver::sendStop(ClientSelector clientSelector, int seatId, uint64_t sessionId){
   PrflMgrTestTypes::ClientMsg m;
   m.mReceiveSelector = PrflMgrTestTypes::eClientStop;
   m.mClientSelector = clientSelector;
   m.mSeatId = seatId;
   m.mSessionId = sessionId;
   mClientQ->push(m);
}


void EventReceiver::addExpectedMsg(PrflMgrTestTypes::ETestEventType t, unsigned int payload){
   PrflMgrTestTypes::TestEvent e;
   e.mT = t;
   e.mPayload = payload;
   e.mOccured = false;
   mEvents.push_back(e);
}


bool EventReceiver::checkDone(){
   for (list<PrflMgrTestTypes::TestEvent>::const_iterator eventIt = mEvents.begin(); eventIt != mEvents.end(); eventIt++) {
      if (!(*eventIt).mOccured) {
         return false;
      }
   }
   return mSuccess;
}


void EventReceiver::onEvent(PrflMgrTestTypes::ETestEventType t, unsigned int payload){
   for (std::list<PrflMgrTestTypes::TestEvent>::iterator eventIt = mEvents.begin(); eventIt != mEvents.end(); ++eventIt) {
      if (!(*eventIt).mOccured && (*eventIt).mT == t && (*eventIt).mPayload == payload) {
         (*eventIt).mOccured = true;
         return;
      }
   }
   mSuccess = false;
}


void EventReceiver::notify(){
   mClientQ->notify();
}


bool EventReceiver::execute(TestBase& test){
   mSuccess = true;
   mTestNo = test.getTestNo();
   test.execute(this);
   mSrvQ->notify();

   while (!checkDone()) {
      PrflMgrTestTypes::ClientMsg m = mClientQ->poll();
      int clientId = selector2Int(m.mClientSelector);
      if (clientId >= 0 && clientId < NUM_OF_TEST_CLIENTS) {
         switch (m.mReceiveSelector) {
         case PrflMgrTestTypes::eClientDetected:
            onEvent(PrflMgrTestTypes::eTDetected, clientId << 16 | m.mSeatId << 8 | m.mUserId);
            std::printf("s:c%i.detected(seat=%i, user=%i)\n", clientId, m.mSeatId, m.mUserId);
            break;
         case PrflMgrTestTypes::eClientSynchronized:
            onEvent(PrflMgrTestTypes::eTSynced, clientId << 16 | m.mSeatId << 8 | m.mUserId);
            std::printf("s:c%i.synced(seat=%i, user=%i)\n", clientId, m.mSeatId, m.mUserId);
            break;
         case PrflMgrTestTypes::eClientStop:
            onEvent(PrflMgrTestTypes::eTStop, clientId << 16 | m.mSeatId << 8);
            std::printf("s:c%i.stop(seat=%i)\n", clientId, m.mSeatId);
            break;
         }

         mClients[clientId]->trigger(m, this);
         mSrvQ->notify();
      } else {
         //add unknwon client event....
      }
   }
   return true;
}
