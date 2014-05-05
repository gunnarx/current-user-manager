/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#include "ProfileManagerStubImpl.h"
#include <iostream>


ProfileManagerStubImpl::ProfileManagerStubImpl( ProfileManagerLogic& logic,event_handler * eventHandler):mLogic(&logic), mEventHandler(eventHandler){}
ProfileManagerStubImpl::~ProfileManagerStubImpl(){

}




void ProfileManagerStubImpl::registerMe(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appID, int32_t seatID) {
	std::cout<<"Client: " << appID <<" is invoking registerMe!\n";
	mEventHandler->eventQueue.push(new event_logicClientReceive_Register(clientId,appID,seatID));
	std::cout<<"registerMe event from Client pushed to queue\n\n";
}

void ProfileManagerStubImpl::unregisterMe(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string consumerAddress, std::string appID, int32_t seatID) {
	std::cout<<"Client: " << appID <<" on address: " << consumerAddress <<" is invoking unregisterMe!\n";
	mEventHandler->eventQueue.push(new event_logicClientReceive_Unregister(consumerAddress,appID,seatID));
	std::cout<<"unregisterMe event from Client pushed to queue\n\n";
}

void ProfileManagerStubImpl::confirm(const std::shared_ptr<CommonAPI::ClientId> clientId, uint64_t sessionID) {
	std::cout<<"Client using sesseionID: " << sessionID <<" is invoking confirm!\n";
	mEventHandler->eventQueue.push(new event_logicClientReceive_Confirm(sessionID));
	std::cout<<"Confirm event from Client pushed to queue\n\n";
}

void ProfileManagerStubImpl::stopped(const std::shared_ptr<CommonAPI::ClientId> clientId, uint64_t sessionID) {
	std::cout<<"Client using sesseionID: " << sessionID <<" is invoking stopped!\n";
	mEventHandler->eventQueue.push(new event_logicClientReceive_Stopped(sessionID));
	std::cout<<"Stopped event from Client pushed to queue\n\n";
}



