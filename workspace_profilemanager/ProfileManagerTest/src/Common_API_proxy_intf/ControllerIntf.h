/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef CONTROLLERINTF_H_
#define CONTROLLERINTF_H_

#include <CommonAPI/CommonAPI.h>

#include "../_global_.h"

#include <org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlProxy.h>
#include <org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlProxyBase.h>

typedef org::genivi::profile_mgmt_ctrl::ProfileManagerCtrl::ETimeOutAction ETimeOutAction;

typedef std::string ClientSelector;

typedef std::function<void(const CommonAPI::CallStatus&)> RegisterMeAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> SetUserAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> UnsetUserAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> TimeOutActionAsyncCallback;

void callbackHandler_registerMe_(const CommonAPI::CallStatus& s);
void callbackHandler_unsetUser(const CommonAPI::CallStatus& s);
void callbackHandler_setUser(const CommonAPI::CallStatus& s);
void callbackHandler_timeOutAction(const CommonAPI::CallStatus& s);

/**
 * THIS INTERFACE IS USED BY THE CONTROLLER TO COMMUNICATE WITH THE PROFILEMANAGER
 */
class ControllerIntf {

private:
	std::shared_ptr<CommonAPI::Factory> factory;
	std::string ServiceAddress;
	void checkStatus(std::future<CommonAPI::CallStatus> &);

public:
	ControllerIntf(	std::shared_ptr<CommonAPI::Factory> &factory, std::string ServiceAddress);
	virtual ~ControllerIntf();

	void sendRegisterMe(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister);
	void sendSetUser(const uint32_t& userId, const uint32_t& seatId);
	void sendUnsetUser(const uint32_t& seatId);
	void sendTimeOutAction(const uint64_t& timeOutSessionId, const ETimeOutAction& timeOutActionItem);
};

#endif /* COMMONAPIPROFILEMANAGERINTF_H */
