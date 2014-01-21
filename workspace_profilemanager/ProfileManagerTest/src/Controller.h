/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <list>

#include "Common_API_stubs_implementation/ControllerStubImpl.h"
#include "Common_API_proxy_intf/ControllerIntf.h"
#include "_global_.h" // for serviceAddress_profileManager_controllerStub

typedef org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumer::ESignal ESignal;



class ControllerIntf;
class ControllerStubImpl;
class Controller {
public:
	std::shared_ptr<ControllerStubImpl> CtrlStub;
   enum EClientStatus {
      eNotRegistered, eStop, eStopped, eDetected, eConfirmed, eSynced
   };

private:
   std::shared_ptr<ControllerStubImpl> stubController;
   ControllerIntf * intfController;

public:
   Controller();
   virtual ~Controller();

	void sendRegisterMe(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister);
	void sendSetUser(const uint32_t& userId, const uint32_t& seatId);
	void sendUnsetUser(const uint32_t& seatId);
	void sendTimeOutAction(const uint64_t& timeOutSessionId, const ETimeOutAction& timeOutActionItem);

	void receiveOnTimeOut(std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId);
	void receiveOnStateChangeStart(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);
	void receiveOnStateChangeStop(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);
	void receiveOnClientRegister(std::string appName, uint32_t seatId);
	void receiveOnClientUnregister(std::string appName, uint32_t seatId);

};

#endif /*CONTROLLER_H_ */
