/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef PROFILEMANAGERTESTCLIENT_H_
#define PROFILEMANAGERTESTCLIENT_H_

#include <list>
#include "EventMessageQ.h"
#include "../include/CommonApi.h"

class EventReceiver;

class ProfileManagerTestClient {
public:
   enum EClientStatus {
      eNotRegistered, eStop, eStopped, eDetected, eConfirmed, eSynced
   };

private:

   bool checkEvent(std::list<PrflMgrTestTypes::TestEvent> e, PrflMgrTestTypes::ETestEventType t, unsigned int payload);

public:
   ProfileManagerTestClient(int id);
   virtual ~ProfileManagerTestClient();

   ClientSelector   mId;
   int              mSeatId;
   uint64_t         mSessionId;
   int              mUserId;
   EClientStatus    mState;

   void trigger(PrflMgrTestTypes::ClientMsg m, EventReceiver* er);
   void doRegister(int seatId, EventReceiver* er);
   EClientStatus getState();
   int getUserId();
};

#endif /* PROFILEMANAGERTESTCLIENT_H_ */
