/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
****************************************************************/

#ifndef TESTUNREGISTER_H_
#define TESTUNREGISTER_H_

#include "TestBase.h"
#include "../Client.h"
#include "../_global_.h"

class TestUnregister : public TestBase {
private:
   int mSeatId;
   int mClientId;
   std::vector<Client*> c;
   Controller * Ctrl;

public:

   TestUnregister(int testNo, int clientId);
   virtual ~TestUnregister();

   virtual void prepare(std::vector<Client*>& clientVect, Controller * ctrl);
   virtual void execute();
};

#endif /* TESTUNREGISTER_H_ */
