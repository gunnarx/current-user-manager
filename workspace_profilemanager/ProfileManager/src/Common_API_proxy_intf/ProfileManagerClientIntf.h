/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/
#ifndef PROFILEMANAGERCLIENTINTF_H_
#define PROFILEMANAGERCLIENTINTF_H_


#include <map>
#include <string>
#include <time.h>
#include <thread>
#include <future>

#include <CommonAPI/CommonAPI.h>
#include "org/genivi/profile_mgmt/ProfileManagerConsumerProxy.h"

#include "../_global_.h"

class CommonApiProfileManagerStub;

typedef std::string ClientSelector;

//typedefs are copy paste from generated code
typedef std::function<void(const CommonAPI::CallStatus&)> DetectedUserAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> SynchronizedUserAsyncCallback;
typedef std::function<void(const CommonAPI::CallStatus&)> StopAsyncCallback;

//Callback handlers for the Async communication
//THESE FUNCTIONS ARE INVOCED DIRECTLY AFTER CALL
void callbackHandler_detectedUser(const CommonAPI::CallStatus& s);
void callbackHandler_synchronizedUser(const CommonAPI::CallStatus& s);
void callbackHandler_stop(const CommonAPI::CallStatus& s);

/**
 * THIS INTERFACE IS USED BY PROFILEMANAGER TO COMMUNICATE WITH CLIENTS
 *
 * Provides calls for the logic to send signals (detected, synced, stop) to ProfileManager CLIENTS.
 * This interface enables the logic to stay the same, once the selective attribute is supported by
 * CommonAPI
 */
class ProfileManagerClientIntf {
private:
	//CommonApiProfileManagerStub* mStub;
	std::shared_ptr<CommonAPI::Factory> factory;

	void checkStatus(std::future<CommonAPI::CallStatus> &status);

public:
	ProfileManagerClientIntf(	std::shared_ptr<CommonAPI::Factory> &factory);
	virtual ~ProfileManagerClientIntf();

	void sendDetectedUser(ClientSelector clientId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId);
	void sendSynchronizedUser(ClientSelector clientId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId);
	void sendStop(ClientSelector clientId, u_int32_t seatId, uint64_t sessionId);
};


#endif /* COMMONAPIPROFILEMANAGERINTF_H */
