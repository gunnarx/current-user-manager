/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <CommonAPI/CommonAPI.h>

#include "_global_.h" // for serviceAddress_profileManager_controllerStub
#include "org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlProxy.h"

typedef org::genivi::profile_mgmt_ctrl::ProfileManagerCtrl::ESignal ESignal;
typedef org::genivi::profile_mgmt_ctrl::ProfileManagerCtrl::ETimeOutAction ETimeOutAction;

typedef std::string ClientSelector;



/*
 * This class represents  the PM controller
 * Controller registers to the PM in it's constructor during creation.
 */
class Controller {
private:

	std::shared_ptr<CommonAPI::Factory> factory;
	std::shared_ptr<org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlProxy<>> proxy;
	std::string ServiceAddress;

	void checkStatus(std::future<CommonAPI::CallStatus> &);

	void registerMe(const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister);
	void setUser(const uint32_t& userId, const uint32_t& seatId);
	void unsetUser(const uint32_t& seatId);
	void timeOutAction(const uint64_t& timeOutSessionId, const ETimeOutAction& timeOutActionItem);

	void receiveOnTimeOut(std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId);
	void receiveOnStateChangeStart(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);
	void receiveOnStateChangeStop(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);
	void receiveOnClientRegister(std::string appName, uint32_t seatId);
	void receiveOnClientUnregister(std::string appName, uint32_t seatId);

public:

	Controller();
	virtual ~Controller();

	void sendRegisterMe(const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister);
	void sendSetUser(const uint32_t& userId, const uint32_t& seatId);
	void sendUnsetUser(const uint32_t& seatId);
	void sendTimeOutAction(const uint64_t& timeOutSessionId, const ETimeOutAction& timeOutActionItem);

	void openProxy(const std::string migrationAddress);
};

#endif /*CONTROLLER_H_ */
