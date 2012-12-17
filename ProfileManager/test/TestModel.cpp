/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "TestModel.h"

TestModel::TestModel() {
   for (int i = 0; i < NUM_OF_TEST_CLIENTS; ++i) {
      mSeats[i] = -1;
   }
}

TestModel::~TestModel() {
}


void TestModel::setUser(int seatId, int userId){
   mSeats[seatId] = userId;
}


int TestModel::getUserId(int seatId){
   return mSeats[seatId];
}

