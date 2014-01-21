/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/

#include "ProfileManagerClientIntf.h"

void callbackHandler_detectedUser(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_detectedUser\n";
}
void callbackHandler_synchronizedUser(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_synchronizedUser\n";
}
void callbackHandler_stop(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_stop\n";
}

ProfileManagerClientIntf::ProfileManagerClientIntf
(std::shared_ptr<CommonAPI::Factory> &factory) : factory(factory){
}


ProfileManagerClientIntf::~ProfileManagerClientIntf() {
}




void ProfileManagerClientIntf::sendDetectedUser(ClientSelector clientId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId){
	std::cout<<"Invoking sendDetectedUser  : calling: "<<clientId<<"\n";

	//std::shared_ptr<org::genivi::profile_mgmt::ProfileManagerConsumerProxy<> >
	auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerConsumerProxy>(clientId);

	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		DetectedUserAsyncCallback Callback = callbackHandler_detectedUser;

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->detectedUserAsync(seatId, userId, sessionId, Callback);
			checkStatus(status);
			std::cout<<"\n";



		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}
	else std::cout<<"Proxy Error\n";
}


void ProfileManagerClientIntf::sendSynchronizedUser(ClientSelector clientId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId){
	std::cout<<"Invoking sendSynchronizedUser : calling: "<<clientId<<"\n";

	auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerConsumerProxy>(clientId);  //std::shared_ptr<org::genivi::profile_mgmt::ProfileManagerConsumerProxy<> >

	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		SynchronizedUserAsyncCallback Callback = callbackHandler_synchronizedUser;

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->synchronizedUserAsync(seatId, userId, sessionId, Callback);

			checkStatus(status);
			std::cout<<"\n";
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}
	else std::cout<<"Proxy Error\n";
}


void ProfileManagerClientIntf::sendStop(ClientSelector clientId, u_int32_t seatId, uint64_t sessionId){
	std::cout<<"Invoking sendStop : calling: "<<clientId<<"\n";


	auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerConsumerProxy>(clientId);

	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		StopAsyncCallback Callback = callbackHandler_stop;

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->stopAsync(seatId, sessionId, Callback);
			checkStatus(status);
			std::cout<<"\n";
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}
	else std::cout<<"Proxy Error\n";
}

void ProfileManagerClientIntf::checkStatus(std::future<CommonAPI::CallStatus> &status){
	//std::cout<<"waiting for status...\n";
	std::future_status s;
	s = status.wait_for(std::chrono::seconds(_TIMEOUT_SECONDS_WAITFORSTATUS_));
	if(s == std::future_status::ready){
		switch (status.get())
		{
		case CommonAPI::CallStatus::SUCCESS:
			std::cout << "CallStatus::SUCCESS\n";
			std::cout.flush();
			break;
		case CommonAPI::CallStatus::OUT_OF_MEMORY:
			std::cout << "CallStatus::OUT_OF_MEMORY\n";
			break;
		case CommonAPI::CallStatus::NOT_AVAILABLE:
			std::cout << "CallStatus::NOT_AVAILABLE\n";
			break;
		case CommonAPI::CallStatus::CONNECTION_FAILED:
			std::cout << "CallStatus::CONNECTION_FAILED\n";
			break;
		case CommonAPI::CallStatus::REMOTE_ERROR:
			std::cout << "CallStatus::REMOTE_ERROR\n";
			break;
		default:
			std::cout << "Unknown status\n";
			break;
		}
	}
	else{
		std::cout<<"CallStatus: STATUS HAS NOT APPEARED!\n";
	}
}
