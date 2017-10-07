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

//const std::string serviceAddress_profileManager_controllerStub =	"local:profileManager.controllerStub:profileManager.controllerStub";
const std::string serviceAddress_profileManager_clientStub = 		"local:profileManager.clientStub:profileManager.clientStub";
const std::string serviceAddress_profileManager_controllerStub = 	"local:profileManager.controllerStub:profileManager.controllerStub";


const double 	_TIMEOUT_SECONDS_WAITFORPROXY_ = 5;
const double	_TIMEOUT_SECONDS_TESTWAITSFORRESPONSE_ = 5;
const int 		_TIMEOUT_SECONDS_WAITFORSTATUS_ = 1;

const int 		_MAX_NUM_OF_TEST_ERROR_RETRY_ = 3; // in case of test error, test is relunched max this number times

const int _NUM_OF_TEST_CLIENTS_ = 10;

#endif
