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
#include "../include/IdentificationPlugin.h"
#include "../src/ProfileManagerMain.h"



#include "EventMessageQ.h"

class TestFactory;
class EventReceiver;

class ServerLoop : public IdentificationPlugin {
public:
   ServerLoop(EventMessageQ<PrflMgrTestTypes::SrvMsg>& SrvQ, TestFactory* factory);
   void run();
   virtual ~ServerLoop();

   void initPlugin(SetUserIntf* usrIf);

private:
   class Logger : public ProfileManagerLog {
    public:
      void log(int level, std::string msg){ /*std::cout << msg << std::endl;*/ };
   };


   EventMessageQ<PrflMgrTestTypes::SrvMsg>*   mSrvQ;
   ProfileManagerMain*                       mProfileManager;
   ProfileManagerCfg*                        mCfg;
   TestFactory*                              mFactory;
   SetUserIntf*                              mSetUserIntf;
};

#endif /* SERVERLOOP_H_ */
