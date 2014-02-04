/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#include "ClientStubImpl.h"
#include <iostream>


	ClientStubImpl::ClientStubImpl( ){
		ptrClient=0;
	}
	ClientStubImpl::ClientStubImpl( Client * ptr){
		ptrClient=ptr;
	}
	ClientStubImpl::~ClientStubImpl(){

	}


	void ClientStubImpl::detectedUser(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, int32_t userID, uint64_t sessionID) {
	    detectedUser(seatID, userID, sessionID);
	}
	void ClientStubImpl::detectedUser(int32_t seatID, int32_t userID, uint64_t sessionID) {
		ptrClient->receiveDetectedUser(seatID, userID, sessionID);
	}

	void ClientStubImpl::synchronizedUser(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, int32_t userID, uint64_t sessionID) {
	    synchronizedUser(seatID, userID, sessionID);
	}
	void ClientStubImpl::synchronizedUser(int32_t seatID, int32_t userID, uint64_t sessionID) {
		ptrClient->receiveSynchronizedUser(seatID, userID, sessionID);
	}

	void ClientStubImpl::stop(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, uint64_t sessionID) {
	    stop(seatID, sessionID);
	}
	void ClientStubImpl::stop(int32_t seatID, uint64_t sessionID) {
		ptrClient->receiveStop(seatID,sessionID);
	}


