/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#include "ProfileManagerCtrlStubImpl.h"
#include <iostream>

ProfileManagerCtrlStubImpl::ProfileManagerCtrlStubImpl( ProfileManagerLogic& logic,event_handler * eventHandler):mLogic(&logic), mEventHandler(eventHandler){}
ProfileManagerCtrlStubImpl::~ProfileManagerCtrlStubImpl(){}




void ProfileManagerCtrlStubImpl::registerMe(const std::shared_ptr<CommonAPI::ClientId> clientId, bool registerOnTimeOut, bool registerOnStateChangeStart, bool registerOnStateChangeStop, bool registerOnClientRegister, bool registerOnClientUnregister) {
	std::cout<<"Controller is invoking registerMe!\n";
	mEventHandler->eventQueue.push(new event_logicControllerReceive_registerMe(clientId));
	std::cout<<"registerMe event pushed to queue\n\n";}

void ProfileManagerCtrlStubImpl::setUser(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId) {
	std::cout<<"Controller is invoking setUser with params : userId: " <<userId << " seatId: " << seatId <<"\n";
	mEventHandler->eventQueue.push(new event_logicControllerReceive_setUser(userId,seatId));
	std::cout<<"setUser event pushed to queue\n\n";
}

void ProfileManagerCtrlStubImpl::unsetUser(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t seatId) {
	std::cout<<"Controller is invoking unsetUser with params : seatId: " << seatId <<"\n";
	mEventHandler->eventQueue.push(new event_logicControllerReceive_unsetUser(seatId));
	std::cout<<"unsetUser event pushed to queue\n\n";
}

void ProfileManagerCtrlStubImpl::timeOutAction(const std::shared_ptr<CommonAPI::ClientId> clientId, uint64_t timeOutSessionId, org::genivi::profile_mgmt_ctrl::ProfileManagerCtrl::ETimeOutAction timeOutActionItem) {
	//TODO: implementation of timeOutAction
}
