/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "ProfileManagerTestClient.h"
#include <string>
#include "EventReceiver.h"
#include <cstdio>
#include <sstream>


ProfileManagerTestClient::ProfileManagerTestClient(int id)
: mId()
, mSeatId(-1)
, mSessionId(0)
, mUserId(-1)
, mState(eNotRegistered) {
   std::stringstream ss;
   ss << "Client_" << id;
   mId = ss.str();
}


ProfileManagerTestClient::~ProfileManagerTestClient() {
}


void ProfileManagerTestClient::trigger(PrflMgrTestTypes::ClientMsg m, EventReceiver* er){
   PrflMgrTestTypes::SrvMsg srvM;
   switch (m.mReceiveSelector) {
   case PrflMgrTestTypes::eClientDetected:
      mSessionId = m.mSessionId;
      mUserId = m.mUserId;
      er->sendConfirm(mId, mSessionId);
      mState = eConfirmed;
      break;
   case PrflMgrTestTypes::eClientSynchronized:
      mSessionId = m.mSessionId;
      if (mUserId == m.mUserId) {
         mState = eSynced;
      } else {
         printf("UNEXPECTED SYNC!!\n");
      }
      break;
   case PrflMgrTestTypes::eClientStop:
      mSessionId = m.mSessionId;
      er->sendStopped(mId, mSessionId);
      mState = eStopped;
      break;
   }
}


void ProfileManagerTestClient::doRegister(int seatId, EventReceiver* er){
   mState = eStopped;
   er->sendRegister(mId, mId, seatId);
}


ProfileManagerTestClient::EClientStatus ProfileManagerTestClient::getState(){
   return mState;
}


int ProfileManagerTestClient::getUserId(){
   return mUserId;
}


