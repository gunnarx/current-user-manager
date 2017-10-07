/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#include "Client.h"

#include <string>
#include <cstdio>
#include <sstream>


Client::Client(ClientSelector UID, int clientIdNum){
	mUID = UID;
	mClientIdNum = clientIdNum;
	mAddressClientStub = "local:org.genivi." + UID +":org.genivi."+UID; //DBUS ADDRESS NAMING CONVENTION IS NOT YET SPECIFIED

	mState = EClientStatus::eNotRegistered;
	mSeatId = -1;	//not yet assigned
	mSessionId = 0;	//not yet assigned


	/* Each client has his own commonAPI proxy to make calls and recive broadcasts */
	factory = CommonAPI::Runtime::load()->createFactory();
	openProxy(serviceAddress_profileManager_clientStub);
}


Client::~Client() {
	this->factory.reset();
	this->proxy.reset();
}



/*
 * Opens proxy and subscribes for broadcasts
 */
void Client::openProxy(const std::string profileManagerAddress){

	this->proxy = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(profileManagerAddress);
	std::cout << "#Client "<<mClientIdNum<<" proxy is ready!\n";

	this->proxy->getDetectedUserSelectiveEvent().subscribe([&](
			const int32_t& seatID,
			const int32_t& userID,
			const uint64_t& sessionID)
			{
		receiveDetectedUser(seatID, userID, sessionID);
			});

	this->proxy->getSynchronizedUserSelectiveEvent().subscribe([&](
			const int32_t& seatID,
			const int32_t& userID,
			const uint64_t& sessionID)
			{
		receiveSynchronizedUser(seatID, userID, sessionID);
			});


	this->proxy->getStopSelectiveEvent().subscribe([&](
			const int32_t& seatID,
			const uint64_t& sessionID)
			{
		receiveStop(seatID,sessionID);
			});

}

void Client::sendRegisterMe(const std::string& appID, const int32_t& seatID){
	std::printf("c%i:s.register(seat=%i)\n", mClientIdNum, seatID);
	registerMe(appID,seatID);
}
void Client::sendUnregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID){
	std::printf("c%i:s.unregister\n", mClientIdNum);

	mState = EClientStatus::eNotRegistered;
	unregisterMe(consumerAddress,appID,seatID);
}
void Client::sendConfirm(const uint64_t& sessionID){
	std::printf("c%i:s.confirm\n",  mClientIdNum);

	mState = EClientStatus::eConfirmed;
	confirm(sessionID);
}
void Client::sendStopped(const uint64_t& sessionID){
	std::printf("c%i:s.stopped\n", mClientIdNum);

	mState = EClientStatus::eStopped;
	stopped(sessionID);
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



void Client::registerMe(const std::string& appID, const int32_t& seatID)
{
	//auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(ServiceAddress);
	if (proxy != 0) {
		std::future<CommonAPI::CallStatus> status;
		try {
			time_t begin;
			time(&begin);
			while(!proxy->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = proxy->registerMeAsync(appID, seatID,
					[&](const CommonAPI::CallStatus& s){/*put callback code here*/});
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}

	else std::cout << "proxy failed!\n";
}
void Client::unregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID)
{
	//auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(ServiceAddress);
	if (proxy != 0) {
		std::future<CommonAPI::CallStatus> status;
		try {
			time_t begin;
			time(&begin);
			while(!proxy->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = proxy->unregisterMeAsync(consumerAddress, appID, seatID,
					[&](const CommonAPI::CallStatus& s){/*put callback code here*/});
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}

	else std::cout << "proxy failed!\n";

}
void Client::confirm(const uint64_t& sessionID)
{
	//auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(ServiceAddress);
	if (proxy != 0) {
		std::future<CommonAPI::CallStatus> status;
		try {
			time_t begin;
			time(&begin);
			while(!proxy->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = proxy->confirmAsync(sessionID,
					[&](const CommonAPI::CallStatus& s){/*put callback code here*/});
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}

	else std::cout << "proxy failed!\n";

}
void Client::stopped(const uint64_t& sessionID)
{
	//auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(ServiceAddress);
	if (proxy != 0) {

		std::future<CommonAPI::CallStatus> status;
		try {
			time_t begin;
			time(&begin);
			while(!proxy->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = proxy->stoppedAsync(sessionID,
					[&](const CommonAPI::CallStatus& s){/*put callback code here*/});
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}

	else std::cout << "proxy failed!\n";

}

/*
 * Displays call status
 *
 * If your version of gcc does not support std::future or std::promise
 * this function and it's every invocation can be safely commented out
 */
void Client::checkStatus(std::future<CommonAPI::CallStatus> &status){
	//std::cout<<"waiting for status...\n";
	std::future_status s;
	s = status.wait_for(std::chrono::seconds(_TIMEOUT_SECONDS_WAITFORSTATUS_));
	if(s == std::future_status::ready){
		switch (status.get())
		{
		case CommonAPI::CallStatus::SUCCESS:
			//std::cout << "#CallStatus::SUCCESS\n";
			std::cout.flush();
			break;
		case CommonAPI::CallStatus::OUT_OF_MEMORY:
			std::cout << "#CallStatus::OUT_OF_MEMORY\n";
			break;
		case CommonAPI::CallStatus::NOT_AVAILABLE:
			std::cout << "#CallStatus::NOT_AVAILABLE\n";
			break;
		case CommonAPI::CallStatus::CONNECTION_FAILED:
			std::cout << "#CallStatus::CONNECTION_FAILED\n";
			break;
		case CommonAPI::CallStatus::REMOTE_ERROR:
			std::cout << "#CallStatus::REMOTE_ERROR\n";
			break;
		default:
			std::cout << "#Unknown status\n";
			break;
		}
	}
	else{
		std::cout<<"#CallStatus: STATUS HAS NOT APPEARED!\n";
	}
}
