/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#ifndef PROFILEMANAGERCLIENTINTF_H_
#define PROFILEMANAGERCLIENTINTF_H_


#include <time.h>
#include <future>
#include <string>
#include <iostream>

#include <CommonAPI/CommonAPI.h>
#include "org/genivi/profile_mgmt/ProfileManagerProxy.h"

#include "../_global_.h"

class ProfileManagerStubImpl;

typedef std::string ClientSelector;


/**
 * THIS INTERFACE IS USED BY PROFILEMANAGER TO COMMUNICATE WITH CLIENTS
 *
 * Provides calls for the logic to send signals (detected, synced, stop) to ProfileManager CLIENTS.
 * This interface enables the logic to stay the same, once the selective attribute is supported by
 * CommonAPI
 */
class ProfileManagerClientIntf {

public:
	//std::shared_ptr<CommonAPI::ClientId> clientDbusId;
	ProfileManagerStubImpl * stubPtr;

	ProfileManagerClientIntf();
	virtual ~ProfileManagerClientIntf();

	void sendDetectedUser		(std::shared_ptr<CommonAPI::ClientId> clientDbusId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId);
	void sendSynchronizedUser	(std::shared_ptr<CommonAPI::ClientId> clientDbusId, u_int32_t seatId, u_int32_t userId, uint64_t sessionId);
	void sendStop				(std::shared_ptr<CommonAPI::ClientId> clientDbusId, u_int32_t seatId, uint64_t sessionId);
};


#endif /* COMMONAPIPROFILEMANAGERINTF_H */
