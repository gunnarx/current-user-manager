/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#include "Controller.h"


Controller::Controller(){
	/* Each client has his own commonAPI proxy to make calls and recive broadcasts */
	factory = CommonAPI::Runtime::load()->createFactory();
	openProxy(serviceAddress_profileManager_controllerStub);

	//the controller registers immediately after its creation
	sendRegisterMe(1,1,1,1,1); //TODO
}

Controller::~Controller(){
}


void Controller::sendRegisterMe(const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister){
	registerMe(registerOnTimeOut,registerOnStateChangeStart,registerOnStateChangeStop,registerOnClientRegister,registerOnClientUnregister);
}
void Controller::sendSetUser(const uint32_t& userId, const uint32_t& seatId){
	std::printf("p:s.setUser(seat=%i, user=%i)\n", userId, seatId);
	setUser(userId,seatId);
}
void Controller::sendUnsetUser(const uint32_t& seatId){
	std::printf("p:s.unsetUser(seat=%i)\n", seatId);
	unsetUser(seatId);
}
void Controller::sendTimeOutAction(const uint64_t& timeOutSessionId, const ETimeOutAction& timeOutActionItem){
	timeOutAction(timeOutSessionId,timeOutActionItem);
}


void Controller::receiveOnTimeOut(std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId){
	std::printf("s:p.onTimeOut(app=%s, user=%i, seat=%i, signal=%s)\n", appName.data(), userId, seatId, s==ESignal::eConfirm ? "confirmed" : "stopped");
}
void Controller::receiveOnStateChangeStart(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId){
	std::printf("s:p.onStateChangeStart(level=%i, user=%i, seat=%i, signal=%s)\n", depLevel, userId, seatId, s==ESignal::eConfirm ? "confirmed": "stopped");
}
void Controller::receiveOnStateChangeStop(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId){
	std::printf("s:p.onStateChangeStop(level=%i, user=%i, seat=%i, signal=%s)\n", depLevel, userId, seatId, s==ESignal::eConfirm ? "confirmed": "stopped");
}
void Controller::receiveOnClientRegister(std::string appName, uint32_t seatId){
	std::printf("s:p.onClientRegister(seat=%i, app=%s)\n", seatId, appName.data());
}
void Controller::receiveOnClientUnregister(std::string appName, uint32_t seatId){
	std::printf("s:p.onClientUnregister(seat=%i, app=%s)\n", seatId, appName.data());

}






/*
 * Opens proxy and subscribes for broadcasts
 */
void Controller::openProxy(const std::string migrationAddress){

	proxy = factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(serviceAddress_profileManager_controllerStub);
	std::cout << "#controller proxy is ready!\n";

	this->proxy->getOnTimeOutSelectiveEvent().subscribe([&](
			const std::string& appName,
			const uint32_t& userId,
			const uint32_t& seatId,
			const ESignal& s,
			const uint64_t& sessionId,
			const int32_t& timeElapsedMs,
			const uint64_t& timeOutSessionId)
			{
		receiveOnTimeOut(appName, userId, seatId, s, sessionId, timeElapsedMs, timeOutSessionId);
			});

	this->proxy->getOnStateChangeStartSelectiveEvent().subscribe([&](
			const uint32_t& userId,
			const uint32_t& seatId,
			const int32_t& depLevel,
			const ESignal& s,
			const uint64_t& sessionId)
			{
		receiveOnStateChangeStart( userId,  seatId,  depLevel,  s,  sessionId);
			});


	this->proxy->getOnStateChangeStopSelectiveEvent().subscribe([&](
			const uint32_t& userId,
			const uint32_t& seatId,
			const int32_t& depLevel,
			const ESignal& s,
			const uint64_t& sessionId)
			{
		receiveOnStateChangeStop( userId,  seatId,  depLevel,  s,  sessionId);
			});

	this->proxy->getOnClientRegisterSelectiveEvent().subscribe([&](
			const std::string& appName,
			const uint32_t& seatId)
			{
		receiveOnClientRegister(appName, seatId);
			});

	this->proxy->getOnClientUnregisterSelectiveEvent().subscribe([&](
			const std::string& appName,
			const uint32_t& seatId)
			{
		receiveOnClientUnregister(appName, seatId);
			});

}


void Controller::registerMe(const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister)
{
	std::cout<<"#Controller is Invoking sendRegisterMe\n";

	//auto proxy= factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(ServiceAddress);
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

			status = proxy->registerMeAsync(registerOnTimeOut, registerOnStateChangeStart, registerOnStateChangeStop,  registerOnClientRegister, registerOnClientUnregister,
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

void Controller::setUser(const uint32_t& userId, const uint32_t& seatId)
{
	//auto proxy= factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(ServiceAddress);
	if (proxy!= 0) {
		std::future<CommonAPI::CallStatus> status;

		try {
			time_t begin;
			time(&begin);
			while(!proxy->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = proxy->setUserAsync(userId, seatId,
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

void Controller::unsetUser(const uint32_t& seatId)
{
	//auto proxy= factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(ServiceAddress);
	if (proxy!= 0) {
		std::future<CommonAPI::CallStatus> status;

		try {
			time_t begin;
			time(&begin);
			while(!proxy->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = proxy->unsetUserAsync(seatId,
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

void Controller::timeOutAction(const uint64_t& timeOutSessionId, const ETimeOutAction& timeOutActionItem)
{
	//auto proxy= factory->buildProxy<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy>(ServiceAddress);
	if (proxy!= 0) {
		std::future<CommonAPI::CallStatus> status;

		try {
			time_t begin;
			time(&begin);
			while(!proxy->isAvailable()){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_WAITFORPROXY_){
					throw 't';
				}
			}

			status = proxy->timeOutActionAsync(timeOutSessionId, timeOutActionItem,
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
void Controller::checkStatus(std::future<CommonAPI::CallStatus> &status){
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


