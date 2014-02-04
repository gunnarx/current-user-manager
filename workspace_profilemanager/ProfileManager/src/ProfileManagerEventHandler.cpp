/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#include "ProfileManagerEventHandler.h"

//event implementation
event::event(){};
event::~event(){};



//event_handler implementation
event_handler::event_handler(ProfileManagerLogic * ptr):ptrLogic(ptr){}
event_handler::~event_handler(){}

void event_handler::run(){
	while(!eventQueue.empty()){
		eventQueue.front()->execute(ptrLogic);
		eventQueue.pop();
		std::cout<<"event successfully executed!\t Number of events left in queue: "<<eventQueue.size()<<"\n\n";
	}
}


/*
 * THE REST OF THIS FILE HOLDS IMPLEMENTATIONS OF ALL EVENTS
 * Event implementations are gathered in one place to ensure transparency and clarity of the code
 * Specific implementation of all events :
 */


//event_logicClientReceive_Register
event_logicClientReceive_Register::event_logicClientReceive_Register(ClientSelector clientId, std::string appID, int seatID){
	this->clientId = clientId;
	this->appID = appID;
	this->seatID = seatID;
}
event_logicClientReceive_Register::~event_logicClientReceive_Register(){};

void event_logicClientReceive_Register::execute(ProfileManagerLogic * ptrLogic){
	ptrLogic->logicClientReceive_Register( clientId,appID, seatID);
}


//event_logicClientReceive_Unregister
event_logicClientReceive_Unregister::event_logicClientReceive_Unregister(ClientSelector clientId, std::string appID, int seatID){
	this->clientId = clientId;
	this->appID = appID;
	this->seatID = seatID;
}
event_logicClientReceive_Unregister::~event_logicClientReceive_Unregister(){};

void event_logicClientReceive_Unregister::execute(ProfileManagerLogic * ptrLogic){
	ptrLogic->logicClientReceive_Unregister( clientId,appID, seatID);
}


//event_logicClientReceive_Confirm
event_logicClientReceive_Confirm::event_logicClientReceive_Confirm(uint64_t externalSession){
	this->externalSession = externalSession;
}
event_logicClientReceive_Confirm::~event_logicClientReceive_Confirm(){};

void event_logicClientReceive_Confirm::execute(ProfileManagerLogic * ptrLogic){
	ptrLogic->logicClientReceive_Confirm(externalSession);
}


//event_logicClientReceive_Stopped
event_logicClientReceive_Stopped::event_logicClientReceive_Stopped(uint64_t externalSession){
	this->externalSession = externalSession;
}
event_logicClientReceive_Stopped::~event_logicClientReceive_Stopped(){};

void event_logicClientReceive_Stopped::execute(ProfileManagerLogic * ptrLogic){
	ptrLogic->logicClientReceive_Stopped(externalSession);
}


//event_logicControllerReceive_registerMe
event_logicControllerReceive_registerMe::event_logicControllerReceive_registerMe(std::string consumerAddress){
	this->consumerAddress = consumerAddress;
}
event_logicControllerReceive_registerMe::~event_logicControllerReceive_registerMe(){};

void event_logicControllerReceive_registerMe::execute(ProfileManagerLogic * ptrLogic){
	ptrLogic->logicControllerReceive_registerMe(consumerAddress);
}


//event_logicControllerReceive_setUser
event_logicControllerReceive_setUser::event_logicControllerReceive_setUser(u_int32_t userId, u_int32_t seatId){
	this->userId = userId;
	this->seatId = seatId;
}
event_logicControllerReceive_setUser::~event_logicControllerReceive_setUser(){};

void event_logicControllerReceive_setUser::execute(ProfileManagerLogic * ptrLogic){
	ptrLogic->logicControllerReceive_setUser(userId,seatId);
}


//event_logicControllerReceive_unsetUser
event_logicControllerReceive_unsetUser::event_logicControllerReceive_unsetUser(u_int32_t seatId){
	this->seatId = seatId;
}
event_logicControllerReceive_unsetUser::~event_logicControllerReceive_unsetUser(){};

void event_logicControllerReceive_unsetUser::execute(ProfileManagerLogic * ptrLogic){
	ptrLogic->logicControllerReceive_unsetUser(seatId);
}






/*
 //functions exposed via the Client interface
void logicClientReceive_Register(ClientSelector clientId, std::string appID, int seatID);
void logicClientReceive_Unregister(ClientSelector clientId, std::string appID, int seatID);
void logicClientReceive_Confirm(uint64_t externalSession);
void logicClientReceive_Stopped(uint64_t externalSession);

	//functions exposed via the Ctrl interface
void logicControllerReceive_registerMe(std::string consumerAddress, ProfileManagerCfg* cfg = 0);
void logicControllerReceive_setUser(u_int32_t userId, u_int32_t seatId);
void logicControllerReceive_unsetUser(u_int32_t seatId);
 */
