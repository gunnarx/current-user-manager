
#ifndef CONTROLLERSTUBIMPL_H_
#define CONTROLLERSTUBIMPL_H_

#include <org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlConsumerStubDefault.h>
#include "Controller.h"

typedef org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumer::ESignal ESignal;

class Controller;
class ControllerIntf;

/**
 * Provides a default implementation for ProfileManagerCtrlStubRemoteEvent and
 * ProfileManagerCtrlStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class ControllerStubImpl : public org::genivi::profile_mgmt_ctrl::ProfileManagerCtrlConsumerStubDefault {

public:
	Controller * ptrController;

	ControllerStubImpl();
	ControllerStubImpl( Controller * ptr);

	virtual ~ControllerStubImpl();

	void onTimeOut(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId);
	void onTimeOut(std::string appName, uint32_t userId, uint32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs, uint64_t timeOutSessionId);

	void onStateChangeStart(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);
	void onStateChangeStart(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);

	void onStateChangeStop(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);
	void onStateChangeStop(uint32_t userId, uint32_t seatId, int32_t depLevel, ESignal s, uint64_t sessionId);

	void onClientRegister(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t seatId);
	void onClientRegister(std::string appName, uint32_t seatId);

	void onClientUnregister(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string appName, uint32_t seatId);
	void onClientUnregister(std::string appName, uint32_t seatId);

};

#endif
