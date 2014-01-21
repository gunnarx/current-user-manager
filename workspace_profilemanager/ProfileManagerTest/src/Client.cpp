/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/
#include "Client.h"

#include <string>
#include <cstdio>
#include <sstream>


Client::Client(ClientSelector UID, int clientIdNum){
	mUID = UID;
	mClientIdNum = clientIdNum;
	mAddressClientStub = "local:org.genivi." + UID +":org.genivi."+UID; //name convention not specified

	mState = EClientStatus::eNotRegistered;
	mSeatId = -1;	//not yet assigned
	mSessionId = 0;	//not yet assigned

	std::shared_ptr<CommonAPI::Factory> factory = CommonAPI::Runtime::load()->createFactory();

	/* Each client has his own commonAPI stub and Interface to make calls via proxy */
	intfClient = new ClientIntf(factory,serviceAddress_profileManager_clientStub);
	stubClient = std::make_shared<ClientStubImpl>(this);

	bool success; //debug
	success = factory->getRuntime()->getServicePublisher()->registerService(stubClient, mAddressClientStub, factory);
	if(success) std::cout << "#Client id: " << clientIdNum << " stub successfully registered on address: " << mAddressClientStub << std::endl;
	else		std::cout << "#Client id: " << clientIdNum << " " << mAddressClientStub << " stub registration failed!!!" << std::endl;

}


Client::~Client() {
}


void Client::sendRegisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID){
	std::printf("c%i:s.register(seat=%i)\n", mClientIdNum, seatID);
	intfClient->sendRegisterMe(consumerAddress,appID,seatID);
}
void Client::sendUnregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID){
	std::printf("c%i:s.unregister\n", mClientIdNum);

	mState = EClientStatus::eNotRegistered;
	intfClient->sendUnregisterMe(consumerAddress,appID,seatID);
}
void Client::sendConfirm(const uint64_t& sessionID){
	std::printf("c%i:s.confirm\n",  mClientIdNum);

	mState = EClientStatus::eConfirmed;
	intfClient->sendConfirm(sessionID);
}
void Client::sendStopped(const uint64_t& sessionID){
	std::printf("c%i:s.stopped\n", mClientIdNum);

	mState = EClientStatus::eStopped;
	intfClient->sendStopped(sessionID);
}

void Client::receiveDetectedUser(int32_t seatID, int32_t userID, uint64_t sessionID){
	std::printf("s:c%i.detected(seat=%i, user=%i)\n", mClientIdNum, seatID, userID);

	this->mSessionId=sessionID;

	this->mState=EClientStatus::eDetected;
}

void Client::receiveSynchronizedUser(int32_t seatID, int32_t userID, uint64_t sessionID){
	std::printf("s:c%i.synced(seat=%i, user=%i)\n", mClientIdNum, seatID, userID);

	this->mSeatId=seatID;
	this->mSessionId=sessionID;

	this->mState=EClientStatus::eSynced;
}

void Client::receiveStop(int32_t seatID, uint64_t sessionID){
	std::printf("s:c%i.stop(seat=%i)\n", mClientIdNum, seatID);

	this->mSessionId=sessionID;
	this->mState=EClientStatus::eStopped;
}
