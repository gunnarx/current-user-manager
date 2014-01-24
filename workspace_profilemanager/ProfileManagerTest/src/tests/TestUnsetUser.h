/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef TESTUNSETUSER_H_
#define TESTUNSETUSER_H_
#include "TestBase.h"
#include "../_global_.h"

class TestUnsetUser : public TestBase {
private:
   int mSeatId;
   std::vector<Client*> c;
   Controller * Ctrl;

public:
   TestUnsetUser(int testNo, int seatId);
   virtual ~TestUnsetUser();

   virtual void prepare(std::vector<Client*>& clientVect, Controller * ctrl);
   virtual void execute();
};

#endif /* TESTUNSETUSER_H_ */
