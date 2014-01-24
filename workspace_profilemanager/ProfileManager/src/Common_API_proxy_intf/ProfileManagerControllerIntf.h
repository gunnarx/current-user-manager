/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/
#ifndef PROFILEMANAGERCONTROLLERINTF_H_
#define PROFILEMANAGERCONTROLLERINTF_H_

#include <time.h>
#include <thread>

#include <CommonAPI/CommonAPI.h>
#include "org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlConsumer.h"
#include "org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlConsumerProxy.h"

#include "../_global_.h"

typedef org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumer::ESignal ESignal;

typedef std::string ClientSelector;

//typedefs are copy paste from generated code
typedef std::function<void(const CommonAPI::CallStatus&)> OnTimeOutAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> OnStateChangeStartAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> OnStateChangeStopAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> OnClientRegisterAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> OnClientUnregisterAsyncCallback;

//Callback handlers for the Async communication
//THESE FUNCTIONS ARE INVOKED DIRECTLY AFTER CALL
void callbackHandler_onTimeOut			(const CommonAPI::CallStatus& s);
void callbackHandler_onStateChangeStart	(const CommonAPI::CallStatus& s);
void callbackHandler_onStateChangeStop	(const CommonAPI::CallStatus& s);
void callbackHandler_onClientRegister	(const CommonAPI::CallStatus& s);
void callbackHandler_onClientUnregister	(const CommonAPI::CallStatus& s);

/**
 * THIS INTERFACE IS USED BY PROFILEMANAGER TO COMMUNICATE WITH CONTROLLER
 *
 * Provides calls for the logic to send signals (sendOnTimeOut, sendOnStateChangeStart, sendOnStateChangeStop
 * sendOnClientRegister, sendOnClientUnregister) to ProfileManager CONTROLLER.
 * This interface enables the logic to stay the same, once the selective attribute is supported by
 * CommonAPI
 */
class ProfileManagerControllerIntf {
private:
	std::shared_ptr<CommonAPI::Factory> factory;

	void checkStatus(std::future<CommonAPI::CallStatus> &status);

public:
	std::string ServiceAddress;

	ProfileManagerControllerIntf(	std::shared_ptr<CommonAPI::Factory> &factory);//, std::string ServiceAddress);
	virtual ~ProfileManagerControllerIntf();

	void sendOnTimeOut			(const std::string& appName, const uint32_t& userId, const uint32_t& seatId, const ESignal& s, const uint64_t& sessionId, const int32_t& timeElapsedMs, const uint64_t& timeOutSessionId);
	void sendOnStateChangeStart	(const uint32_t& userId, const uint32_t& seatId, const int32_t& depLevel, const ESignal& s, const uint64_t& sessionId);
	void sendOnStateChangeStop	(const uint32_t& userId, const uint32_t& seatId, const int32_t& depLevel, const ESignal& s, const uint64_t& sessionId);
	void sendOnClientRegister	(const std::string& appName, const uint32_t& seatId);
	void sendOnClientUnregister	(const std::string& appName, const uint32_t& seatId);

};


#endif /* COMMONAPIPROFILEMANAGERINTF_H */
