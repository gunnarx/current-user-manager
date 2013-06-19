/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef TESTPROFILEMANAGERCONSUMERPROXY_H_
#define TESTPROFILEMANAGERCONSUMERPROXY_H_

#include "../include/CommonApi.h"
#include "../include/ProfileManageConsumerProxyBase.h"

#include "EventReceiver.h"

class TestProfileManagerConsumerProxy : public ProfileManagerConsumerProxyBase {
private:
   EventReceiver* mEventReceiver;
   ClientSelector mClientId;

public:
   TestProfileManagerConsumerProxy(EventReceiver* er, ClientSelector s);
   virtual ~TestProfileManagerConsumerProxy();

   void detectedUser(u_int32_t seatID, u_int32_t userID, uint64_t sessionID);
   void synchronizedUser(u_int32_t seatID, u_int32_t userID, uint64_t sessionID);
   void stop(u_int32_t seatID, uint64_t sessionID);

};

#endif /* TESTPROFILEMANAGERCONSUMERPROXY_H_ */
