/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "TestProfileManagerConsumerProxy.h"


TestProfileManagerConsumerProxy::TestProfileManagerConsumerProxy(EventReceiver* er, ClientSelector s)
: ProfileManagerConsumerProxyBase()
, mEventReceiver(er)
, mClientId(s){
}


TestProfileManagerConsumerProxy::~TestProfileManagerConsumerProxy() {
}


void TestProfileManagerConsumerProxy::TestProfileManagerConsumerProxy::detectedUser(u_int32_t seatID, u_int32_t userID, uint64_t sessionID){
   mEventReceiver->sendDetectedUser(mClientId, seatID, userID, sessionID);
   mEventReceiver->notify();
}


void TestProfileManagerConsumerProxy::synchronizedUser(u_int32_t seatID, u_int32_t userID, uint64_t sessionID){
   mEventReceiver->sendSynchronizedUser(mClientId, seatID, userID, sessionID);
   mEventReceiver->notify();
}


void TestProfileManagerConsumerProxy::stop(u_int32_t seatID, uint64_t sessionID){
   mEventReceiver->sendStop(mClientId, seatID, sessionID);
   mEventReceiver->notify();
}



