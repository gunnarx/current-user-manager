/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#include "ProfileManagerClientIntf.h"
#include "../Common_API_stubs_implementation/ProfileManagerStubImpl.h"

void callbackHandler_detectedUser(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_detectedUser\n";
}
void callbackHandler_synchronizedUser(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_synchronizedUser\n";
}
void callbackHandler_stop(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_stop\n";
}

ProfileManagerClientIntf::ProfileManagerClientIntf(){
}


ProfileManagerClientIntf::~ProfileManagerClientIntf() {
}




void ProfileManagerClientIntf::sendDetectedUser(std::shared_ptr<CommonAPI::ClientId> clientDbusId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId){
	std::cout<<"Invoking sendDetectedUser  : calling: "<<sessionId<<"\n";

	std::shared_ptr<CommonAPI::ClientIdList> receivers = std::make_shared<CommonAPI::ClientIdList>();
	receivers->insert(clientDbusId);
	stubPtr->fireDetectedUserSelective(seatId, userId, sessionId, receivers);
}


void ProfileManagerClientIntf::sendSynchronizedUser(std::shared_ptr<CommonAPI::ClientId> clientDbusId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId){
	std::cout<<"Invoking sendSynchronizedUser : calling: "<<sessionId<<"\n";

	std::shared_ptr<CommonAPI::ClientIdList> receivers = std::make_shared<CommonAPI::ClientIdList>();
	receivers->insert(clientDbusId);
	stubPtr->fireSynchronizedUserSelective(seatId, userId, sessionId, receivers);
}


void ProfileManagerClientIntf::sendStop(std::shared_ptr<CommonAPI::ClientId> clientDbusId, u_int32_t seatId, uint64_t sessionId){
	std::cout<<"Invoking sendStop : calling: "<<sessionId<<"\n";

	std::shared_ptr<CommonAPI::ClientIdList> receivers = std::make_shared<CommonAPI::ClientIdList>();
	receivers->insert(clientDbusId);
	stubPtr->fireStopSelective(seatId, sessionId, receivers);
}
