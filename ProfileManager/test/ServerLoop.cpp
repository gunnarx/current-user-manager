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
#include "../include/CProfileManagerCtrlConsumer.h"

#include "TestFactory.h"


ServerLoop::ServerLoop(EventMessageQ<PrflMgrTestTypes::SrvMsg>& SrvQ, TestFactory* factory)
: mSrvQ(&SrvQ)
, mProfileManager(0)
, mFactory(factory) {
   mProfileManager = new ProfileManagerMain(factory, new Logger());
}

void ServerLoop::run(){
   bool stop = false;

   mProfileManager->getProfileManagerCtrl()->registerMe(*this);
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
         mProfileManager->getProfileManagerCtrl()->setUser(m.mSeatId, m.mUserId);
         break;
      default: stop = true;
         break;
      }
   }
}

ServerLoop::~ServerLoop() {
}

void ServerLoop::onTimeOut(std::string& appName, u_int32_t userId, u_int32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs){
   char buf[200];
   std::sprintf(buf, "s:p.onTimeOut(app=%s, user=%i, seat=%i, signal=%s)\n", appName.data(), userId, seatId, s==CProfileManagerCtrlConsumer::eConfirm ? "confirmed" : "stopped");
   mFactory->getEventReceiver()->sendMessage2Client(buf);

}

void ServerLoop::onStateChangeStart(u_int32_t userId, u_int32_t seatId, u_int32_t depLevel, ESignal s, uint64_t sessionId){
   char buf[200];
   std::sprintf(buf, "s:p.onStateChangeStart(level=%i, user=%i, seat=%i, signal=%s)\n", depLevel, userId, seatId, s==CProfileManagerCtrlConsumer::eConfirm ? "confirmed": "stopped");
   mFactory->getEventReceiver()->sendMessage2Client(buf);
}

void ServerLoop::onStateChangeStop( u_int32_t userId, u_int32_t seatId, u_int32_t depLevel, ESignal s, uint64_t sessionId){
   char buf[200];
   std::sprintf(buf, "s:p.onStateChangeStop(level=%i, user=%i, seat=%i, signal=%s)\n", depLevel, userId, seatId, s==CProfileManagerCtrlConsumer::eConfirm ? "confirmed": "stopped");
   mFactory->getEventReceiver()->sendMessage2Client(buf);
}

void ServerLoop::onClientRegister( u_int32_t seatId, std::string& appName){
   char buf[200];
   std::sprintf(buf, "s:p.onClientRegister(seat=%i, app=%s)\n", seatId, appName.data());
   mFactory->getEventReceiver()->sendMessage2Client(buf);
}

void ServerLoop::onClientUnregister( u_int32_t seatId, std::string& appName){
   char buf[200];
   std::sprintf(buf, "s:p.onClientUnregister(seat=%i, app=%s)\n", seatId, appName.data());
   mFactory->getEventReceiver()->sendMessage2Client(buf);
}
