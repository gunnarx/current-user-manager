/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
****************************************************************/

#ifndef TESTSETUSER_H_
#define TESTSETUSER_H_
#include "TestBase.h"
#include "../_global_.h"

class TestSetUser : public TestBase {
private:
   int mSeatId;
   int mUserId;
   std::vector<Client*> c;
   Controller * Ctrl;

public:
   TestSetUser(int testNo, int seatId, int userId);
   virtual ~TestSetUser();

   virtual void prepare(std::vector<Client*>& clientVect, Controller * ctrl);
   virtual void execute();
};

#endif /* TESTSETUSER_H_ */
