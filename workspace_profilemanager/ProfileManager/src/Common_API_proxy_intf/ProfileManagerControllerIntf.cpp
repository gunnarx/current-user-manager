/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#include "ProfileManagerControllerIntf.h"
#include "../Common_API_stubs_implementation/ProfileManagerCtrlStubImpl.h"


ProfileManagerControllerIntf::ProfileManagerControllerIntf(){}


ProfileManagerControllerIntf::~ProfileManagerControllerIntf() {
}


void ProfileManagerControllerIntf::sendOnTimeOut(const std::string& appName, const uint32_t& userId, const uint32_t& seatId, const ESignal& s, const uint64_t& sessionId, const int32_t& timeElapsedMs, const uint64_t& timeOutSessionId)
{
	std::cout<<"invoking: sendOnTimeOut\n";

	std::shared_ptr<CommonAPI::ClientIdList> receivers = std::make_shared<CommonAPI::ClientIdList>();
	receivers->insert(controllerId);
	stubPtr->fireOnTimeOutSelective(appName, userId, seatId, s,  sessionId, timeElapsedMs, timeOutSessionId, receivers);

}
void ProfileManagerControllerIntf::sendOnStateChangeStart(const uint32_t& userId, const uint32_t& seatId, const int32_t& depLevel, const ESignal& s, const uint64_t& sessionId)
{
	std::string tmp = "";
	if (s == ESignal::eStopped) tmp = "eStopped";
	if (s == ESignal::eConfirm) tmp = "eConfirmed";

	std::cout<<"Invoking: sendOnStateChangeStart : signal: "<<tmp<<" : depLevel: " << depLevel << "\n";

	std::shared_ptr<CommonAPI::ClientIdList> receivers = std::make_shared<CommonAPI::ClientIdList>();
	receivers->insert(controllerId);
	stubPtr->fireOnStateChangeStartSelective(userId, seatId, depLevel, s,  sessionId, receivers);

}
void ProfileManagerControllerIntf::sendOnStateChangeStop(const uint32_t& userId, const uint32_t& seatId, const int32_t& depLevel, const ESignal& s, const uint64_t& sessionId)
{
	std::string tmp = "";
	if (s == ESignal::eStopped) tmp = "eStopped";
	if (s == ESignal::eConfirm) tmp = "eConfirmed";
	std::cout<<"Invoking: sendOnStateChangeStop : signal: "<<tmp<<" : depLevel: " << depLevel << "\n";

	std::shared_ptr<CommonAPI::ClientIdList> receivers = std::make_shared<CommonAPI::ClientIdList>();
	receivers->insert(controllerId);
	stubPtr->fireOnStateChangeStopSelective(userId, seatId, depLevel, s,  sessionId, receivers);
}

void ProfileManagerControllerIntf::sendOnClientRegister(const std::string& appName, const uint32_t& seatId)
{
	std::cout<<"invoking: sendOnClientRegister\n";

	std::shared_ptr<CommonAPI::ClientIdList> receivers = std::make_shared<CommonAPI::ClientIdList>();
	receivers->insert(controllerId);
	stubPtr->fireOnClientRegisterSelective(appName, seatId, receivers);

}
void ProfileManagerControllerIntf::sendOnClientUnregister(const std::string& appName, const uint32_t& seatId)
{
	std::cout<<"invoking: sendOnClientUnregister\n";

	std::shared_ptr<CommonAPI::ClientIdList> receivers = std::make_shared<CommonAPI::ClientIdList>();
	receivers->insert(controllerId);
	stubPtr->fireOnClientUnregisterSelective(appName, seatId, receivers);
}
