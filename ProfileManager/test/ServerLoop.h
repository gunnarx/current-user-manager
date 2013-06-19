/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef SERVERLOOP_H_
#define SERVERLOOP_H_

#include <iostream>

#include "../include/CommonApi.h"
#include "../include/ProfileManagerLog.h"
#include "../include/CProfileManagerCtrlConsumer.h"
#include "../src/ProfileManagerMain.h"



#include "EventMessageQ.h"

class TestFactory;
class EventReceiver;

class ServerLoop : public CProfileManagerCtrlConsumer {
public:
   ServerLoop(EventMessageQ<PrflMgrTestTypes::SrvMsg>& SrvQ, TestFactory* factory);
   void run();
   virtual ~ServerLoop();

private:
   class Logger : public ProfileManagerLog {
    public:
      void log(int level, std::string msg){ /*std::cout << msg << std::endl;*/ };
   };


   EventMessageQ<PrflMgrTestTypes::SrvMsg>*   mSrvQ;
   ProfileManagerMain*                       mProfileManager;
   TestFactory*                              mFactory;

   void onTimeOut(std::string& appName, u_int32_t userId, u_int32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs);
   void onStateChangeStart(u_int32_t userId, u_int32_t seatId, u_int32_t depLevel, ESignal s, uint64_t sessionId);
   void onStateChangeStop( u_int32_t userId, u_int32_t seatId, u_int32_t depLevel, ESignal s, uint64_t sessionId);
   void onClientRegister( u_int32_t seatId, std::string& appName);
   void onClientUnregister( u_int32_t seatId, std::string& appName);
};

#endif /* SERVERLOOP_H_ */
