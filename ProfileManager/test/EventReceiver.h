/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "EventMessageQ.h"
#include "ServerLoop.h"
#include "TestBase.h"
#include "TestModel.h"
#include "ProfileManagerTestClient.h"
#include <list>

#include "../include/CommonApi.h"

#ifndef EVENTRECEIVER_H_
#define EVENTRECEIVER_H_

class EventReceiver {
public:


private:
   bool checkDone();
   void onEvent(PrflMgrTestTypes::ETestEventType t, unsigned int payload);

   EventMessageQ<PrflMgrTestTypes::ClientMsg>*   mClientQ;
   EventMessageQ<PrflMgrTestTypes::SrvMsg>*      mSrvQ;
   std::list<PrflMgrTestTypes::TestEvent>        mEvents;
   bool                                          mSuccess;
   int                                           mTestNo;

public:
   ProfileManagerTestClient*                     mClients[NUM_OF_TEST_CLIENTS];
   TestModel                                     mModel;

   EventReceiver(EventMessageQ<PrflMgrTestTypes::ClientMsg>& clientQ, EventMessageQ<PrflMgrTestTypes::SrvMsg>& srvQ);
   EventReceiver();
   virtual ~EventReceiver();

   void notify();

   virtual void sendDetectedUser(ClientSelector clientSelector, int seatId, int userId, uint64_t sessionId);
   virtual void sendSynchronizedUser(ClientSelector clientSelector, int seatId, int userId, uint64_t sessionId);
   virtual void sendStop(ClientSelector clientSelector, int seatId, uint64_t sessionId);

   bool execute(TestBase& test);
   void addExpectedMsg(PrflMgrTestTypes::ETestEventType t, unsigned int payload);

   void sendRegister(ClientSelector clientSelector, std::string appID, int seatID);
   void sendUnregister(ClientSelector clientSelector, int seatId);
   void sendConfirm(ClientSelector clientSelector, uint64_t sessionId);
   void sendStopped(ClientSelector clientSelector, uint64_t sessionId);
   void sendSetUser(int seatId, int userId);

};

#endif /* EVENTRECEIVER_H_ */
