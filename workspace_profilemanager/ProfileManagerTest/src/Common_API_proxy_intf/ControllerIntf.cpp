/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#include "ControllerIntf.h"


using namespace std;

void callbackHandler_registerMe_(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_registerMe\n";
}
void callbackHandler_unsetUser(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_unsetUser\n";
}
void callbackHandler_setUser(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_setUser\n";
}
void callbackHandler_timeOutAction(const CommonAPI::CallStatus& s){
	//std::cout<<"end call callbackHandler_timeOutAction\n";
}

ControllerIntf::ControllerIntf
(std::shared_ptr<CommonAPI::Factory> &factory, 	std::string ServiceAddress) :
factory(factory),
ServiceAddress(ServiceAddress)
{

}


ControllerIntf::~ControllerIntf() {
}

void ControllerIntf::sendRegisterMe(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister)
{
	std::cout<<"#Controller is Invoking sendRegisterMe\n";

	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(ServiceAddress);
	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		RegisterMeAsyncCallback Callback = callbackHandler_registerMe_;

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = p->registerMeAsync(consumerAddress, registerOnTimeOut, registerOnStateChangeStart, registerOnStateChangeStop,  registerOnClientRegister, registerOnClientUnregister, Callback);
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}
	else std::cout << "proxy failed!\n";
}

void ControllerIntf::sendSetUser(const uint32_t& userId, const uint32_t& seatId)
{
	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(ServiceAddress);
	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		SetUserAsyncCallback Callback = callbackHandler_setUser;

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = p->setUserAsync(userId, seatId, Callback);
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}
	else std::cout << "proxy failed!\n";
}

void ControllerIntf::sendUnsetUser(const uint32_t& seatId)
{
	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(ServiceAddress);
	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		UnsetUserAsyncCallback Callback = callbackHandler_unsetUser;

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = p->unsetUserAsync(seatId, Callback);
			checkStatus(status);
		}
		catch (char e) {
			if(e=='t') std::cout << "timeout during proxy send!\n";
			else std::cout<< "Unexpected error during proxy send!\n";
		}
	}
	else std::cout << "proxy failed!\n";
}

void ControllerIntf::sendTimeOutAction(const uint64_t& timeOutSessionId, const ETimeOutAction& timeOutActionItem)
{
	auto p = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(ServiceAddress);
	if (p != 0) {
		std::future<CommonAPI::CallStatus> status;
		TimeOutActionAsyncCallback Callback = callbackHandler_timeOutAction;

		try {
			time_t begin;
			time(&begin);
			while(!p->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = p->timeOutActionAsync(timeOutSessionId, timeOutActionItem, Callback);
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
void ControllerIntf::checkStatus(std::future<CommonAPI::CallStatus> &status){
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
			std::cout << "Unknown status\n";
			break;
		}
	}
	else{
		std::cout<<"#CallStatus: STATUS HAS NOT APPEARED!\n";
	}
}

