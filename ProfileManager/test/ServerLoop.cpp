/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "ServerLoop.h"
#include <cstdio>

#include "../src/ProfileManagerLogic.h"
#include "../src/CommonApiProfileManagerIntf.h"
#include "../src/CommonApiProfileManagerStub.h"

#include "TestFactory.h"


ServerLoop::ServerLoop(EventMessageQ<PrflMgrTestTypes::SrvMsg>& SrvQ, TestFactory* factory)
: IdentificationPlugin()
, mSrvQ(&SrvQ)
, mProfileManager(0)
, mCfg(0)
, mFactory(factory)
, mSetUserIntf(0){
   mCfg = new ProfileManagerCfg();

   mCfg->mDepLevels.push_back(10);
   mCfg->mDepLevels.push_back(100);
   mCfg->mDepLevels.push_back(1000);

   ProfileManagerCfg::ClientCfg clientCfg;

   clientCfg.mAppId = "Client_4";
   clientCfg.mDepLevel = 10;
   clientCfg.mSeatId = -1;
   mCfg->mClientCfgs.push_back(clientCfg);

   clientCfg.mAppId = "Client_5";
   clientCfg.mDepLevel = 10;
   clientCfg.mSeatId = -1;
   mCfg->mClientCfgs.push_back(clientCfg);

   clientCfg.mAppId = "Client_6";
   clientCfg.mDepLevel = 100;
   clientCfg.mSeatId = -1;
   mCfg->mClientCfgs.push_back(clientCfg);

   clientCfg.mAppId = "Client_7";
   clientCfg.mDepLevel = 100;
   clientCfg.mSeatId = -1;
   mCfg->mClientCfgs.push_back(clientCfg);

   clientCfg.mAppId = "Client_8";
   clientCfg.mDepLevel = 1000;
   clientCfg.mSeatId = -1;
   mCfg->mClientCfgs.push_back(clientCfg);

   clientCfg.mAppId = "Client_9";
   clientCfg.mDepLevel = 1000;
   clientCfg.mSeatId = -1;
   mCfg->mClientCfgs.push_back(clientCfg);

   mProfileManager = new ProfileManagerMain(factory, mCfg, new Logger, 5);
   mProfileManager->registerPlugin(this);
}

void ServerLoop::initPlugin(SetUserIntf* intf){
   mSetUserIntf = intf;
}


void ServerLoop::run(){
   bool stop = false;
   while (!stop) {
      PrflMgrTestTypes::SrvMsg m = mSrvQ->poll();
      switch (m.mReceiveSelector ) {
      case PrflMgrTestTypes::eSrvInvalid:
         stop = true;
         break;
      case PrflMgrTestTypes::eSrvRegister:
         mFactory->getStub()->registerMe(m.mClientSelector, m.mAppId, m.mSeatId);
         break;
      case PrflMgrTestTypes::eSrvUnregister:
         mFactory->getStub()->unregisterMe(m.mClientSelector, m.mAppId, m.mSeatId);
         break;
      case PrflMgrTestTypes::eSrvConfirm:
         mFactory->getStub()->confirm(m.mSessionId);
         break;
      case PrflMgrTestTypes::eSrvStopped:
         mFactory->getStub()->stopped(m.mSessionId);
         break;
      case PrflMgrTestTypes::eSrvSetUser:
         mSetUserIntf->setUser(m.mSeatId, m.mUserId);
         break;
      default: stop = true;
         break;
      }
   }
}


ServerLoop::~ServerLoop() {
}
