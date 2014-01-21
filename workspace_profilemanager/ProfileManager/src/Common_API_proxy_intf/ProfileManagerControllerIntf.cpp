/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/

#include "ProfileManagerControllerIntf.h"

void callbackHandler_onTimeOut(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_onTimeOut\n";
}
void callbackHandler_onStateChangeStart(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_onStateChangeStart\n";
}
void callbackHandler_onStateChangeStop(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_onStateChangeStop\n";
}
void callbackHandler_onClientRegister(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_onClientRegister\n";
}
void callbackHandler_onClientUnregister(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_onClientUnregister\n";
}

ProfileManagerControllerIntf::ProfileManagerControllerIntf
(std::shared_ptr<CommonAPI::Factory> &factory) : factory(factory){
	//std::cout << "ProfileManagerControllerIntf created\n";
}


ProfileManagerControllerIntf::~ProfileManagerControllerIntf() {
}


void ProfileManagerControllerIntf::sendOnTimeOut(const std::string& appName, const uint32_t& userId, const uint32_t& seatId, const ESignal& s, const uint64_t& sessionId, const int32_t& timeElapsedMs, const uint64_t& timeOutSessionId)
{
	std::cout<<"invoking: sendOnTimeOut : calling: "<<ServiceAddress<<"\n";
	OnTimeOutAsyncCallback Callback = callbackHandler_onTimeOut;
	std::future<CommonAPI::CallStatus> status;

	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumerProxy>(ServiceAddress);
	if (p != 0) {

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->onTimeOutAsync(appName, userId, seatId, s,  sessionId, timeElapsedMs, timeOutSessionId, Callback);

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
void ProfileManagerControllerIntf::sendOnStateChangeStart(const uint32_t& userId, const uint32_t& seatId, const int32_t& depLevel, const ESignal& s, const uint64_t& sessionId)
{
	std::string tmp = "";
	if (s == ESignal::eStopped) tmp = "eStopped";
	if (s == ESignal::eConfirm) tmp = "eConfirmed";

	std::cout<<"Invoking: sendOnStateChangeStart : signal: "<<tmp<<" : depLevel: " << depLevel << " : calling: "<<ServiceAddress<<"\n";
	OnStateChangeStartAsyncCallback Callback = callbackHandler_onStateChangeStart;
	std::future<CommonAPI::CallStatus> status;

	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumerProxy>(ServiceAddress);
	if (p != 0) {
		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			status = p->onStateChangeStartAsync(userId, seatId, depLevel, s,  sessionId, Callback);


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
void ProfileManagerControllerIntf::sendOnStateChangeStop(const uint32_t& userId, const uint32_t& seatId, const int32_t& depLevel, const ESignal& s, const uint64_t& sessionId)
{
	std::string tmp = "";
	if (s == ESignal::eStopped) tmp = "eStopped";
	if (s == ESignal::eConfirm) tmp = "eConfirmed";
	std::cout<<"Invoking: sendOnStateChangeStop : signal: "<<tmp<<" : depLevel: " << depLevel << " : calling: "<<ServiceAddress<<"\n";
	OnStateChangeStopAsyncCallback Callback = callbackHandler_onStateChangeStop;
	std::future<CommonAPI::CallStatus> status;

	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumerProxy>(ServiceAddress);

	if (p != 0) {
		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->onStateChangeStopAsync(userId, seatId, depLevel, s,  sessionId, Callback);

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

void ProfileManagerControllerIntf::sendOnClientRegister(const std::string& appName, const uint32_t& seatId)
{
	std::cout<<"invoking: sendOnClientRegister : calling: "<<ServiceAddress<<"\n";
	OnClientRegisterAsyncCallback Callback = callbackHandler_onClientRegister;
	std::future<CommonAPI::CallStatus> status;
	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumerProxy>(ServiceAddress);
	if (p != 0) {
		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->onClientRegisterAsync(appName, seatId, Callback);

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
void ProfileManagerControllerIntf::sendOnClientUnregister(const std::string& appName, const uint32_t& seatId)
{
	std::cout<<"invoking: sendOnClientUnregister : calling: "<<ServiceAddress<<"\n";
	OnClientUnregisterAsyncCallback Callback = callbackHandler_onClientUnregister;
	std::future<CommonAPI::CallStatus> status;

	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumerProxy>(ServiceAddress);
	if (p != 0) {
		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
				// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			status = p->onClientUnregisterAsync(appName, seatId, Callback);

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


void ProfileManagerControllerIntf::checkStatus(std::future<CommonAPI::CallStatus> &status){
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

