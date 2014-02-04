/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef CONTROLLERSTUBIMPL_H_
#define CONTROLLERSTUBIMPL_H_

#include <org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlConsumerStubDefault.h>
#include "Controller.h"

typedef org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumer::ESignal ESignal;

class Controller;
class ControllerIntf;

/**
 * IMPLEMENTATION OF ProfileManagerCtrlConsumerStubDefault STUB METHODS
 * provides an interface for PM to communicate with the controller
 */
class ControllerStubImpl : public org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumerStubDefault {

public:
	Controller * ptrController;

	ControllerStubImpl();
	ControllerStubImpl( Controller * ptr);

	virtual ~ControllerStubImpl();

	void onTimeOut(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId);
	void onTimeOut(std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId);

	void onStateChangeStart(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);
	void onStateChangeStart(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);

	void onStateChangeStop(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);
	void onStateChangeStop(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);

	void onClientRegister(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t seatId);
	void onClientRegister(std::string appName, uint32_t seatId);

	void onClientUnregister(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t seatId);
	void onClientUnregister(std::string appName, uint32_t seatId);

};

#endif
