/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
****************************************************************/

#include "TestBase.h"

TestBase::TestBase(int testNo) : mTestNo(testNo)
{
}

TestBase::~TestBase() {
}


int TestBase::getTestNo(){
   return mTestNo;
}
