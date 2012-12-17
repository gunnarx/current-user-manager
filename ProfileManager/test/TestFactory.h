/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef TESTFACTORY_H_
#define TESTFACTORY_H_

#include "../include/CommonApi.h"
#include "EventReceiver.h"

class CommonApiProfileManagerStub;

class TestFactory : public CommonAPI::Factory {
private:
   EventReceiver*               mEventReceiver;
   CommonApiProfileManagerStub* mStub;

public:
   TestFactory(EventReceiver* er);
   virtual ~TestFactory();

   ProfileManagerConsumerProxyBase* buildProxy(std::string address);
   bool                             registerService(CommonAPI::Stub* s, const std::string& address);
   CommonApiProfileManagerStub*     getStub();
};

#endif /* TESTFACTORY_H_ */
