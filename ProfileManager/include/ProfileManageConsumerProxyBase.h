/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef PROFILEMANAGECONSUMERPROXYBASE_H_
#define PROFILEMANAGECONSUMERPROXYBASE_H_

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//This file is used temporarily to reflect the CommonAPI files to be generated.
//This file should vanish, once CommonAPI generation is available.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include "CommonApi.h"

/**
 * Pseudo CommonAPI generated proxy class for the ProfileManagerConsumer.fidl interface
 */
class ProfileManagerConsumerProxyBase : public CommonAPI::Proxy {
public:
   ProfileManagerConsumerProxyBase(){};
   virtual ~ProfileManagerConsumerProxyBase(){};

   virtual void detectedUser(u_int32_t seatID, u_int32_t userID, uint64_t sessionID) = 0;
   virtual void synchronizedUser(u_int32_t seatID, u_int32_t userID, uint64_t sessionID) = 0;
   virtual void stop(u_int32_t seatID, uint64_t sessionID) = 0;
};


#endif /* PROFILEMANAGECONSUMERPROXYBASE_H_ */
