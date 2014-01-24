/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/

#include "ClientIntf.h"

void callbackHandler_registerMe(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_registerMe\n";
}
void callbackHandler_sendUnegisterMe(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_sendUnegisterMe\n";
}
void callbackHandler_confirm(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_confirm\n";
}
void callbackHandler_stopped(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_stopped\n";
}

ClientIntf::ClientIntf
(std::shared_ptr<CommonAPI::Factory> &factory, 	std::string ServiceAddress) : factory(factory), ServiceAddress(ServiceAddress){
}


ClientIntf::~ClientIntf() {
}

void ClientIntf::sendRegisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID)
{
	auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(ServiceAddress);
	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		RegisterMeAsyncCallback Callback = callbackHandler_registerMe;
		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->registerMeAsync(consumerAddress, appID, seatID, Callback);
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}

	else std::cout << "proxy failed!\n";
}


void ClientIntf::sendUnregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID)
{
	auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(ServiceAddress);
	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		UnregisterMeAsyncCallback Callback = callbackHandler_sendUnegisterMe;
		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->unregisterMeAsync(consumerAddress, appID, seatID, Callback);
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}

	else std::cout << "proxy failed!\n";

}


void ClientIntf::sendConfirm(const uint64_t& sessionID)
{
	auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(ServiceAddress);
	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		ConfirmAsyncCallback Callback = callbackHandler_confirm;
		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->confirmAsync(sessionID, Callback);
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}

	else std::cout << "proxy failed!\n";

}
void ClientIntf::sendStopped(const uint64_t& sessionID)
{
	auto p = factory->buildProxy<org::genivi::profile_mgmt::ProfileManagerProxy>(ServiceAddress);
	if (p != 0) {
		std::future<int> a;

		std::future<CommonAPI::CallStatus> status;
		StoppedAsyncCallback Callback = callbackHandler_stopped;

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->stoppedAsync(sessionID, Callback);
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}

	else std::cout << "proxy failed!\n";

}


void ClientIntf::checkStatus(std::future<CommonAPI::CallStatus> &status){
	//std::cout<<"waiting for status...\n";
	std::future_status s;
	s = status.wait_for(std::chrono::seconds(_TIMEOUT_SECONDS_WAITFORSTATUS_));
	if(s == std::future_status::ready){
		switch (status.get())
		{
		case CommonAPI::CallStatus::SUCCESS:
			std::cout << "#CallStatus::SUCCESS\n";
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
