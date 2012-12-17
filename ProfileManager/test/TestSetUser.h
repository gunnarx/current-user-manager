/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef TESTSETUSER_H_
#define TESTSETUSER_H_
#include "TestBase.h"

class EventReceiver;

class TestSetUser : public TestBase {
private:
   int mSeatId;
   int mUserId;

public:
   TestSetUser(int testNo, int seatId, int userId);
   virtual ~TestSetUser();

   virtual void prepare(EventReceiver* er);
   virtual void execute(EventReceiver* er);
};

#endif /* TESTSETUSER_H_ */
