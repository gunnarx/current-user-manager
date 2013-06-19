/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/


#ifndef COMMONAPIPROFILEMANAGERSTUB_H_
#define COMMONAPIPROFILEMANAGERSTUB_H_

#include <map>
#include <string>

#include "../include/CommonApi.h"
#include "../include/ProfileManagerStub.h"

#include "ProfileManagerLogic.h"


/**
 * Derives from the generated commonApi server stub for the given ProfileManager.fidl file.
 * Forwards the received calls to the Profile Manager logic
 */
class CommonApiProfileManagerStub : public ProfileManagerStub{
private:

   int                                                      mClientIdCtr;
   std::map<std::string, ProfileManagerConsumerProxyBase*>  mAddress2ClientId;
   CommonAPI::Factory*                                      mFactory;
   ProfileManagerLogic*                                     mLogic;

public:
   CommonApiProfileManagerStub(CommonAPI::Factory &factory, ProfileManagerLogic &logic);
   virtual ~CommonApiProfileManagerStub();

   ProfileManagerConsumerProxyBase* getConsumerProxy(ClientSelector s);

   void registerMe(std::string consumerAddress, std::string appID, u_int32_t seatID);

   void unregisterMe(std::string consumerAddress, std::string appID, u_int32_t seatID);

   void confirm(uint64_t sessionID);

   void stopped(uint64_t sessionID);
};

#endif /* COMMONAPIPROFILEMANAGERSTUB_H_ */
