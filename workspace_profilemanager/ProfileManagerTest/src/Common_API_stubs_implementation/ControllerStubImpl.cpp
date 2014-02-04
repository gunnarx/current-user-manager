/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#include "ControllerStubImpl.h"
#include <iostream>

ControllerStubImpl::ControllerStubImpl(){
	ptrController=0;
}
ControllerStubImpl::ControllerStubImpl( Controller * ptr){
	ptrController = ptr;
}
ControllerStubImpl::~ControllerStubImpl(){

}



void ControllerStubImpl::onTimeOut(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId) {
	onTimeOut(appName, userId, seatId, s, sessionId, timeElapsedMs, timeOutSessionId);
}
void ControllerStubImpl::onTimeOut(std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId) {
	ptrController->receiveOnTimeOut(appName, userId, seatId, s, sessionId, timeElapsedMs, timeOutSessionId);
}

void ControllerStubImpl::onStateChangeStart(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId) {
	onStateChangeStart(userId, seatId, depLevel, s, sessionId);
}
void ControllerStubImpl::onStateChangeStart(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId) {
	ptrController->receiveOnStateChangeStart( userId,  seatId,  depLevel,  s,  sessionId);
}

void ControllerStubImpl::onStateChangeStop(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId) {
	onStateChangeStop(userId, seatId, depLevel, s, sessionId);
}
void ControllerStubImpl::onStateChangeStop(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId) {
	ptrController->receiveOnStateChangeStop( userId,  seatId,  depLevel,  s,  sessionId);
}

void ControllerStubImpl::onClientRegister(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t seatId) {
	onClientRegister(appName, seatId);
}
void ControllerStubImpl::onClientRegister(std::string appName, uint32_t seatId) {
	ptrController->receiveOnClientRegister(appName, seatId);
}

void ControllerStubImpl::onClientUnregister(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t seatId) {
	onClientUnregister(appName, seatId);
}
void ControllerStubImpl::onClientUnregister(std::string appName, uint32_t seatId) {
	ptrController->receiveOnClientUnregister(appName, seatId);
}


