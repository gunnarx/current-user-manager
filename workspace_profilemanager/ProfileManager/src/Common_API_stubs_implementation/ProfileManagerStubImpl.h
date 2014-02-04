/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef PROFILEMANAGERSTUBIMPL_H_
#define PROFILEMANAGERSTUBIMPL_H_

#include <org/genivi/profile_mgmt/ProfileManagerStubDefault.h>
#include "../ProfileManagerLogic.h"
#include "../ProfileManagerEventHandler.h"

typedef std::string ClientSelector;

/**
 * IMPLEMENTATION OF : ProfileManagerStubDefault : STUB METHODS
 * THESE METHODS ARE INVOKED BY CLIENTS via CommonAPI DBus
 *
 * When a PM stub receives a call, it creates object of proper event which is pushed to PM EventHandler queue.
 */
class ProfileManagerStubImpl : public org::genivi::profile_mgmt::ProfileManagerStubDefault{

	ProfileManagerLogic* mLogic;		//to directly invoke the Logic methods  !!SHALL NOT BE USED -> WHOLE DBUS IS BLOCKED!!
	event_handler* mEventHandler; 		//to push events to the queue

public:

	ProfileManagerStubImpl( ProfileManagerLogic& logic, event_handler * eventHandler);
	virtual ~ProfileManagerStubImpl();


	void registerMe(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string consumerAddress, std::string appID, int32_t seatID);
	void registerMe(std::string consumerAddress, std::string appID, int32_t seatID);

	void unregisterMe(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string consumerAddress, std::string appID, int32_t seatID);
	void unregisterMe(std::string consumerAddress, std::string appID, int32_t seatID);

	void confirm(const std::shared_ptr<CommonAPI::ClientId> clientId, uint64_t sessionID);
	void confirm(uint64_t sessionID);

	void stopped(const std::shared_ptr<CommonAPI::ClientId> clientId, uint64_t sessionID);
	void stopped(uint64_t sessionID);

};

#endif
