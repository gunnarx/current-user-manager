/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef CLIENTSTUBIMPL_H_
#define CLIENTSTUBIMPL_H_

#include <org/genivi/profile_mgmt/ProfileManagerConsumerStubDefault.h>
#include "../Client.h"

typedef std::string ClientSelector;

class Client;
class ClientIntf;

/**
 * IMPLEMENTATION OF ProfileManagerConsumerStubDefault STUB METHODS
 * provides an interface for PM to communicate with a specific client
 */
class ClientStubImpl : public org::genivi::profile_mgmt::ProfileManagerConsumerStubDefault{

public:
	Client* ptrClient;

	ClientStubImpl( );
	ClientStubImpl( Client * ptr);
	virtual ~ClientStubImpl();



     void detectedUser(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, int32_t userID, uint64_t sessionID);
     void detectedUser(int32_t seatID, int32_t userID, uint64_t sessionID);

     void synchronizedUser(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, int32_t userID, uint64_t sessionID);
     void synchronizedUser(int32_t seatID, int32_t userID, uint64_t sessionID);

     void stop(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, uint64_t sessionID);
     void stop(int32_t seatID, uint64_t sessionID);



};

#endif
