/*
 * _global_.h
 *
 *  Created on: Dec 20, 2013
 *      Author: pbuli
 */

#ifndef _GLOBAL__H_
#define _GLOBAL__H_

#include <string>

typedef std::string ClientSelector;

const std::string serviceAddress_profileManager_controllerStub =	"local:profileManager.controllerStub:profileManager.controllerStub";
const std::string serviceAddress_profileManager_clientStub = 		"local:profileManager.clientStub:profileManager.clientStub";

const double _TIMEOUT_SECONDS_WAITFORPROXY_ = 3;
const int 	 _TIMEOUT_SECONDS_WAITFORSTATUS_= 1;

#endif /* _GLOBAL__H_ */
