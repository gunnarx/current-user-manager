#ifndef _GLOBAL__H_
#define _GLOBAL__H_

const std::string serviceAddress_profileManager_controllerStub =	"local:profileManager.controllerStub:profileManager.controllerStub";
const std::string serviceAddress_profileManager_clientStub = 		"local:profileManager.clientStub:profileManager.clientStub";

const std::string serviceAddress_controllerStub = 		"local:org.genivi.controller:org.genivi.controller";
// *no client addresses* ! each client has his own address inside class Client


const double 	_TIMEOUT_SECONDS_WAITFORPROXY_ = 10;
const double	_TIMEOUT_SECONDS_TESTWAITSFORRESPONSE_ = 10;
const int 		_TIMEOUT_SECONDS_WAITFORSTATUS_ = 1;

const int _NUM_OF_TEST_CLIENTS_ = 10;

#endif
