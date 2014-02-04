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

	bool success;

	//serviceAddress_profileManager_controllerStub 	!!! to this address we will call	  !!!
	//serviceAddress_controllerStub					!!! on this address we will be called !!!

	std::shared_ptr<CommonAPI::Factory> factory = CommonAPI::Runtime::load()->createFactory();

	intfController = new ControllerIntf(factory,serviceAddress_profileManager_controllerStub);
	stubController = std::make_shared<ControllerStubImpl>(this);

	success = factory->getRuntime()->getServicePublisher()->registerService(stubController, serviceAddress_controllerStub, factory);
	if(success) std::cout << "#Controller stub successfully registered on address: "<< serviceAddress_controllerStub << std::endl;
	else		std::cout << "#Controller stub registration failed!!!" << std::endl;

	//the controller registers immediately after its creation
	sendRegisterMe(serviceAddress_controllerStub,1,1,1,1,1);
}

Controller::~Controller(){
}


void Controller::sendRegisterMe(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister){
	intfController->sendRegisterMe(consumerAddress,registerOnTimeOut,registerOnStateChangeStart,registerOnStateChangeStop,registerOnClientRegister,registerOnClientUnregister);

}
void Controller::sendSetUser(const uint32_t& userId, const uint32_t& seatId){
	std::printf("p:s.setUser(seat=%i, user=%i)\n", userId, seatId);
	intfController->sendSetUser(userId,seatId);
}
void Controller::sendUnsetUser(const uint32_t& seatId){
	std::printf("p:s.unsetUser(seat=%i)\n", seatId);
	intfController->sendUnsetUser(seatId);
}
void Controller::sendTimeOutAction(const uint64_t& timeOutSessionId, const ETimeOutAction& timeOutActionItem){
	intfController->sendTimeOutAction(timeOutSessionId,timeOutActionItem);
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
