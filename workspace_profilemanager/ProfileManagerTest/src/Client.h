/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef CLIENT_H_
#define CLIENT_H_

#include <list>
#include "Common_API_stubs_implementation/ClientStubImpl.h"
#include "Common_API_proxy_intf/ClientIntf.h"
#include "_global_.h" // for serviceAddress_profileManager_clientStub



class ClientStubImpl;
class ClientIntf;
class Client {
public:
   enum EClientStatus {
      eNotRegistered, eStop, eStopped, eDetected, eConfirmed, eSynced
   };

private:
   std::shared_ptr<ClientStubImpl> stubClient;
   ClientIntf* intfClient;

public:

   Client(ClientSelector UID, int userIdNum);
   virtual ~Client();

   //during creation
   ClientSelector   mUID;
   int              mClientIdNum;
   std::string 		mAddressClientStub;

   //during connection
   EClientStatus    mState;
   int              mSeatId;
   uint64_t         mSessionId;

   void sendRegisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID);
   void sendUnregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID);
   void sendConfirm(const uint64_t& sessionID);
   void sendStopped(const uint64_t& sessionID);

   void receiveDetectedUser(int32_t seatID, int32_t userID, uint64_t sessionID);
   void receiveSynchronizedUser(int32_t seatID, int32_t userID, uint64_t sessionID);
   void receiveStop(int32_t seatID, uint64_t sessionID);

};

#endif /*CLIENT_H_ */
