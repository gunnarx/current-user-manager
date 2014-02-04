/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef PROFILEMANAGERCTRLSTUBIMPL_H_
#define PROFILEMANAGERCTRLSTUBIMPL_H_

#include <org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlStubDefault.h>
#include "../ProfileManagerLogic.h"
#include "../ProfileManagerEventHandler.h"

/**
 * IMPLEMENTATION OF : ProfileManagerCtrlStubDefault : STUB METHODS
 * THESE METHODS ARE INVOKED BY CONTROLLER via CommonAPI DBus
 *
 * When a PM stub receives a call, it creates object of proper event which is pushed to PM EventHandler queue.
 */
class ProfileManagerCtrlStubImpl : public org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlStubDefault {

	ProfileManagerLogic* mLogic;		//to directly invoke the Logic methods  !!SHALL NOT BE USED -> WHOLE DBUS IS BLOCKED!!
	event_handler* mEventHandler; 		//to push events to the queue

public:
	ProfileManagerCtrlStubImpl( ProfileManagerLogic& logic, event_handler * eventHandler);

	virtual ~ProfileManagerCtrlStubImpl();

	void registerMe(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string consumerAddress, bool registerOnTimeOut, bool registerOnStateChangeStart, bool registerOnStateChangeStop, bool registerOnClientRegister, bool registerOnClientUnregister);
	void registerMe(std::string consumerAddress, bool registerOnTimeOut, bool registerOnStateChangeStart, bool registerOnStateChangeStop, bool registerOnClientRegister, bool registerOnClientUnregister);

	void setUser(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId);
	void setUser(uint32_t userId, uint32_t seatId);

	void unsetUser(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t seatId);
	void unsetUser(uint32_t seatId);

	void timeOutAction(const std::shared_ptr<CommonAPI::ClientId> clientId, uint64_t timeOutSessionId, org::genivi::profile_mgmt_ctrl::ProfileManagerCtrl::ETimeOutAction timeOutActionItem);
	void timeOutAction(uint64_t timeOutSessionId, org::genivi::profile_mgmt_ctrl::ProfileManagerCtrl::ETimeOutAction timeOutActionItem);
};

#endif
