/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (C) 2014, GENIVI Alliance, Inc.
 * All rights reserved
 * Author: Przemyslaw Bularz
 ****************************************************************/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <list>
#include <string>

#include <CommonAPI/CommonAPI.h>

#include "_global_.h"
#include "org/genivi/profile_mgmt/ProfileManagerProxy.h"

typedef std::string ClientSelector;

/*
 * This class represents the PM client
 * Clients do not register to the PM automatically.
 * The registration of each client is part of test sequence.
 */
class Client {
public:
	enum EClientStatus {
		eNotRegistered, eStop, eStopped, eDetected, eConfirmed, eSynced
	};

private:

	std::future<CommonAPI::CallStatus> status;
	std::shared_ptr<CommonAPI::Factory> factory;
	std::shared_ptr<org::genivi::profile_mgmt::ProfileManagerProxy<>> proxy;

	std::string ServiceAddress;

	//bool prepareProxy();
	void checkStatus(std::future<CommonAPI::CallStatus>&);

	void receiveDetectedUser(int32_t seatID, int32_t userID, uint64_t sessionID);
	void receiveSynchronizedUser(int32_t seatID, int32_t userID, uint64_t sessionID);
	void receiveStop(int32_t seatID, uint64_t sessionID);

	void registerMe(const std::string& appID, const int32_t& seatID);
	void unregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID);
	void confirm(const uint64_t& sessionID);
	void stopped(const uint64_t& sessionID);


public:

	Client(ClientSelector UID, int userIdNum);
	virtual ~Client();

	//during creation
	ClientSelector   mUID;
	int              mClientIdNum;
	std::string 	mAddressClientStub;

	//during connection
	EClientStatus    mState;
	int              mSeatId;
	uint64_t         mSessionId;

	void sendRegisterMe(const std::string& appID, const int32_t& seatID);
	void sendUnregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID);
	void sendConfirm(const uint64_t& sessionID);
	void sendStopped(const uint64_t& sessionID);

	void openProxy(const std::string profileManagerAddress);
};

#endif /*CLIENT_H_ */
