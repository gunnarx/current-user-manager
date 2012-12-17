/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef TESTREGISTER_H_
#define TESTREGISTER_H_

#include "TestBase.h"

class TestRegister : public TestBase {
private:
   int mSeatId;
   int mClientId;

public:
   TestRegister(int testNo, int clientId, int seatId);
   virtual ~TestRegister();

   virtual void prepare(EventReceiver* er);
   virtual void execute(EventReceiver* er);
};

#endif /* TESTREGISTER_H_ */
