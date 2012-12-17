/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "TestSetUser.h"
#include "EventReceiver.h"
#include "ProfileManagerTestClient.h"


TestSetUser::TestSetUser(int testNo, int seatId, int userId)
: TestBase(testNo)
, mSeatId(seatId)
, mUserId(userId){
}


TestSetUser::~TestSetUser() {
}


void TestSetUser::prepare(EventReceiver* er){
   er->addExpectedMsg(PrflMgrTestTypes::eTSetUser, mSeatId << 8 | mUserId);
   if (er->mModel.getUserId(mSeatId) >= 0) {
      for (int i = 0; i < NUM_OF_TEST_CLIENTS; ++i) {
         if (er->mClients[i]->getState()!= ProfileManagerTestClient::eNotRegistered) {
            er->addExpectedMsg(PrflMgrTestTypes::eTStop, i << 16 | mSeatId << 8);
            er->addExpectedMsg(PrflMgrTestTypes::eTStopped, i << 16 );
         }
      }
   }

   if (mUserId >= 0 && mUserId != er->mModel.getUserId(mSeatId)) {
      for (int i = 0; i < NUM_OF_TEST_CLIENTS; ++i) {
         if (er->mClients[i]->getState()!= ProfileManagerTestClient::eNotRegistered)  {
            er->addExpectedMsg(PrflMgrTestTypes::eTDetected, i << 16 | mSeatId << 8 | mUserId);
            er->addExpectedMsg(PrflMgrTestTypes::eTConfirm, i << 16);
            er->addExpectedMsg(PrflMgrTestTypes::eTSynced, i << 16 | mSeatId << 8 | mUserId);
         }
      }
   }
   er->mModel.setUser(mSeatId, mUserId);
}


void TestSetUser::execute(EventReceiver* er){
   er->sendSetUser(mSeatId, mUserId);
}
