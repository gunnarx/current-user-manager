/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef _GLOBAL__H_
#define _GLOBAL__H_

/*
 * This file holds and defines all global parameters
 */

#include <string>

typedef std::string ClientSelector;

const std::string serviceAddress_profileManager_controllerStub =	"local:profileManager.controllerStub:profileManager.controllerStub";
const std::string serviceAddress_profileManager_clientStub = 		"local:profileManager.clientStub:profileManager.clientStub";

const double _TIMEOUT_SECONDS_WAITFORPROXY_ 	= 3;
const int 	 _TIMEOUT_SECONDS_WAITFORSTATUS_	= 1;
const int 	 _EVENT_HANDLER_LOOP_WAIT_TIME_MS_	= 150;

#endif /* _GLOBAL__H_ */
