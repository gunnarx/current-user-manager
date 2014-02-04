/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef CLIENTINTF_H_
#define CLIENTINTF_H_

#include <string>

#include "CommonAPI/CommonAPI.h"
#include "../_global_.h"

#include <org/genivi/profile_mgmt/ProfileManagerProxy.h>
#include <org/genivi/profile_mgmt/ProfileManagerProxyBase.h>

typedef std::function<void(const CommonAPI::CallStatus&)> RegisterMeAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> UnregisterMeAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> ConfirmAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> StoppedAsyncCallback;

typedef std::string ClientSelector;

void callbackHandler_registerMe(const CommonAPI::CallStatus& s);
void callbackHandler_sendUnegisterMe(const CommonAPI::CallStatus& s);
void callbackHandler_confirm(const CommonAPI::CallStatus& s);
void callbackHandler_stopped(const CommonAPI::CallStatus& s);

/**
 * THIS INTERFACE IS USED BY CLIENT TO COMMUNICATE WITH THE PROFILEMANAGER
 */
class ClientIntf {
private:

	std::shared_ptr<CommonAPI::Factory> factory;
	std::string ServiceAddress;
	void checkStatus(std::future<CommonAPI::CallStatus> &status);

public:
	ClientIntf(	std::shared_ptr<CommonAPI::Factory> &factory, std::string ServiceAddress);
	virtual ~ClientIntf();


	void sendRegisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID);
	void sendUnregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID);
	void sendConfirm(const uint64_t& sessionID);
	void sendStopped(const uint64_t& sessionID);


};


#endif /* COMMONAPIPROFILEMANAGERINTF_H */
