/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "TestFactory.h"

#include "../src/CommonApiProfileManagerStub.h"

#include "TestProfileManagerConsumerProxy.h"


TestFactory::TestFactory(EventReceiver* er)
: mEventReceiver(er )
, mStub(0){
}

TestFactory::~TestFactory() {
}

ProfileManagerConsumerProxyBase* TestFactory::buildProxy(std::string address){
   return new TestProfileManagerConsumerProxy(mEventReceiver, address);
}

bool TestFactory::registerService(CommonAPI::Stub* s, const std::string&){
   mStub = dynamic_cast<CommonApiProfileManagerStub*>(s);
   return (mStub != 0);
}


CommonApiProfileManagerStub* TestFactory::getStub(){
   return mStub;
}
