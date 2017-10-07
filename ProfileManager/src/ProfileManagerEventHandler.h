/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef PROFILEMANAGEREVENTHANDLER_H_
#define PROFILEMANAGEREVENTHANDLER_H_

#include <queue>

#include "_global_.h"
#include "ProfileManagerLogic.h"

class event;

/*
 * PM stubs while receiving create specific events which are put into event_handler queue
 * Event handler executes those events and than removes them from queue
 */
class event_handler{
private:
	ProfileManagerLogic * ptrLogic;
public:
	std::queue<event *> eventQueue;

	event_handler(ProfileManagerLogic * ptr);
	~event_handler();

	void run();
};

//basic event class:
class event{
public:
	virtual void execute(ProfileManagerLogic *) = 0;

	event();
	virtual ~event();
};



/*
 * THE REST OF THIS FILE HOLDS DEFINITOIONS OF ALL EVENTS
 * Event definitions are gathered in one place to ensure transparency and clarity of the code
 * Specific definitions of all events :
 */

class event_logicClientReceive_Register : public event{
private:
	std::shared_ptr<CommonAPI::ClientId> clientId;
	std::string appID;
	int seatID;
public:
	event_logicClientReceive_Register(std::shared_ptr<CommonAPI::ClientId> clientId, std::string appID, int seatID);
	~event_logicClientReceive_Register();

	void execute(ProfileManagerLogic * ptrLogic);
};


class event_logicClientReceive_Unregister : public event{
private:
	ClientSelector clientId;
	std::string appID;
	int seatID;
public:
	event_logicClientReceive_Unregister(ClientSelector clientId, std::string appID, int seatID);
	~event_logicClientReceive_Unregister();

	void execute(ProfileManagerLogic * ptrLogic);
};

class event_logicClientReceive_Confirm : public event{
private:
	uint64_t externalSession;
public:
	event_logicClientReceive_Confirm(uint64_t externalSession);
	~event_logicClientReceive_Confirm();

	void execute(ProfileManagerLogic * ptrLogic);
};

class event_logicClientReceive_Stopped : public event{
private:
	uint64_t externalSession;
public:
	event_logicClientReceive_Stopped(uint64_t externalSession);
	~event_logicClientReceive_Stopped();

	void execute(ProfileManagerLogic * ptrLogic);
};

class event_logicControllerReceive_registerMe :public event{
private:
	std::shared_ptr<CommonAPI::ClientId> clientId;
public:
	event_logicControllerReceive_registerMe(std::shared_ptr<CommonAPI::ClientId> clientId);
	~event_logicControllerReceive_registerMe();

	void execute(ProfileManagerLogic * ptrLogic);
};

class event_logicControllerReceive_setUser :public event{
private:
	u_int32_t userId;
	u_int32_t seatId;
public:
	event_logicControllerReceive_setUser(u_int32_t userId, u_int32_t seatId);
	~event_logicControllerReceive_setUser();

	void execute(ProfileManagerLogic * ptrLogic);
};

class event_logicControllerReceive_unsetUser :public event{
private:
	u_int32_t seatId;
public:
	event_logicControllerReceive_unsetUser(u_int32_t seatId);
	~event_logicControllerReceive_unsetUser();

	void execute(ProfileManagerLogic * ptrLogic);
};


//functions exposed via the Client interface:
//void logicClientReceive_Register(ClientSelector clientId, std::string appID, int seatID);
//void logicClientReceive_Unregister(ClientSelector clientId, std::string appID, int seatID);
//void logicClientReceive_Confirm(uint64_t externalSession);
//void logicClientReceive_Stopped(uint64_t externalSession);

//functions exposed via the Ctrl interface:
//void logicControllerReceive_registerMe(std::string consumerAddress, ProfileManagerCfg* cfg = 0);
//void logicControllerReceive_setUser(u_int32_t userId, u_int32_t seatId);
//void logicControllerReceive_unsetUser(u_int32_t seatId);


#endif /* _PROFILEMANAGEREVENTHANDLER_H_ */
