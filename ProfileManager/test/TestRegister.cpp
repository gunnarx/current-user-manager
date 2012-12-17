/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "TestRegister.h"
#include "EventReceiver.h"


TestRegister::TestRegister(int testNo, int clientId, int seatId)
: TestBase(testNo)
, mSeatId(seatId)
, mClientId(clientId){
}


TestRegister::~TestRegister() {
}


void TestRegister::prepare(EventReceiver* er){
   er->addExpectedMsg(PrflMgrTestTypes::eTRegister, mClientId << 16 | mSeatId << 8);
   if (er->mModel.mSeats[mSeatId] >= 0) {
      er->addExpectedMsg(PrflMgrTestTypes::eTDetected, mClientId << 16 | mSeatId << 8 | er->mModel.mSeats[mSeatId]);
      er->addExpectedMsg(PrflMgrTestTypes::eTConfirm, mClientId << 16);
      er->addExpectedMsg(PrflMgrTestTypes::eTSynced, mClientId << 16 | mSeatId << 8 | er->mModel.mSeats[mSeatId]);
   }
}


void TestRegister::execute(EventReceiver* er){
   er->mClients[mClientId]->doRegister(mSeatId, er);
}
