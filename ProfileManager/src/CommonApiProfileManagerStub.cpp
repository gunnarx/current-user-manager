/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "CommonApiProfileManagerStub.h"
#include "../include/ProfileManageConsumerProxyBase.h"


CommonApiProfileManagerStub::CommonApiProfileManagerStub(CommonAPI::Factory &factory, ProfileManagerLogic &logic)
: mClientIdCtr(0)
, mFactory(&factory)
, mLogic(&logic){
}


CommonApiProfileManagerStub::~CommonApiProfileManagerStub() {
}


ProfileManagerConsumerProxyBase* CommonApiProfileManagerStub::getConsumerProxy(ClientSelector s){
   std::map<std::string, ProfileManagerConsumerProxyBase*>::const_iterator i = mAddress2ClientId.find(s);
   if (i == mAddress2ClientId.end ()) {
      return 0;
   }
   return (*i).second;
}


void CommonApiProfileManagerStub::registerMe (std::string consumerAddress, std::string appID, u_int32_t seatID){
   std::map<std::string, ProfileManagerConsumerProxyBase*>::const_iterator i = mAddress2ClientId.find(consumerAddress);
   if (i == mAddress2ClientId.end ()) {
      mAddress2ClientId[consumerAddress] = mFactory->buildProxy(consumerAddress);
   }
   mLogic->receiveRegister(consumerAddress, appID, seatID);
}


void CommonApiProfileManagerStub::unregisterMe(std::string consumerAddress, std::string appID, u_int32_t seatID){
   mLogic->receiveUnregister(consumerAddress, appID, seatID);
   ProfileManagerConsumerProxyBase* p = mAddress2ClientId[consumerAddress];
   if (p != 0) {
      delete p;
   }
   mAddress2ClientId.erase(consumerAddress);
}


void CommonApiProfileManagerStub::confirm(uint64_t sessionID){
   mLogic->receiveConfirm(sessionID);
}


void CommonApiProfileManagerStub::stopped(uint64_t sessionID){
   mLogic->receiveStopped(sessionID);
}
