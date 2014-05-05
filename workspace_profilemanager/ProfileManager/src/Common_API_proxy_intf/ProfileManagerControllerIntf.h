/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#ifndef PROFILEMANAGERCONTROLLERINTF_H_
#define PROFILEMANAGERCONTROLLERINTF_H_

#include <time.h>
#include <future>
#include <string>
#include <iostream>

#include <CommonAPI/CommonAPI.h>

#include "../_global_.h"
#include "org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlStubDefault.h"

typedef org::genivi::profile_mgmt_ctrl::ProfileManagerCtrl::ESignal ESignal;

typedef std::string ClientSelector;

class ProfileManagerCtrlStubImpl;

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

public:
	//Calls to the controller will be made to this address!
	std::shared_ptr<CommonAPI::ClientId> controllerId;
	ProfileManagerCtrlStubImpl * stubPtr;

	ProfileManagerControllerIntf();
	virtual ~ProfileManagerControllerIntf();

	void sendOnTimeOut			(const std::string& appName, const uint32_t& userId, const uint32_t& seatId, const ESignal& s, const uint64_t& sessionId, const int32_t& timeElapsedMs, const uint64_t& timeOutSessionId);
	void sendOnStateChangeStart	(const uint32_t& userId, const uint32_t& seatId, const int32_t& depLevel, const ESignal& s, const uint64_t& sessionId);
	void sendOnStateChangeStop	(const uint32_t& userId, const uint32_t& seatId, const int32_t& depLevel, const ESignal& s, const uint64_t& sessionId);
	void sendOnClientRegister	(const std::string& appName, const uint32_t& seatId);
	void sendOnClientUnregister	(const std::string& appName, const uint32_t& seatId);

};


#endif /* COMMONAPIPROFILEMANAGERINTF_H */
