/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
****************************************************************/

#ifndef TESTREGISTER_H_
#define TESTREGISTER_H_

#include "TestBase.h"
#include "../Client.h"
#include "../_global_.h"

class TestRegister : public TestBase {
private:
   int mSeatId;
   int mClientId;
   std::vector<Client*> c;
   Controller * Ctrl;

public:
   TestRegister(int testNo, int clientId, int seatId);
   virtual ~TestRegister();

   virtual void prepare(std::vector<Client*>& clientVect, Controller * ctrl);
   virtual void execute();
};

#endif /* TESTREGISTER_H_ */
