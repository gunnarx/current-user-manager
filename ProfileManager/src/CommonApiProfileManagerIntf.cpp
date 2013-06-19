/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/

#include "CommonApiProfileManagerIntf.h"
#include "../include/ProfileManageConsumerProxyBase.h"
#include "CommonApiProfileManagerStub.h"


CommonApiProfileManagerIntf::CommonApiProfileManagerIntf()
: mStub(0) {
}


CommonApiProfileManagerIntf::~CommonApiProfileManagerIntf() {
}


void CommonApiProfileManagerIntf::init(CommonApiProfileManagerStub* stub){
   mStub = stub;
}


void CommonApiProfileManagerIntf::sendDetectedUser(ClientSelector clientId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId){
   ProfileManagerConsumerProxyBase* p = mStub->getConsumerProxy(clientId);
   if (p != 0) {
      p->detectedUser(seatId, userId, sessionId);
   }
}


void CommonApiProfileManagerIntf::sendSynchronizedUser(ClientSelector clientId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId){
   ProfileManagerConsumerProxyBase* p = mStub->getConsumerProxy(clientId);
   if (p != 0) {
      p->synchronizedUser(seatId, userId, sessionId);
   }
}


void CommonApiProfileManagerIntf::sendStop(ClientSelector clientId, u_int32_t seatId, uint64_t sessionId){
   ProfileManagerConsumerProxyBase* p = mStub->getConsumerProxy(clientId);
   if (p != 0) {
      p->stop(seatId, sessionId);
   }
}


