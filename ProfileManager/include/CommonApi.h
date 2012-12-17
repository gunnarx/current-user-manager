/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef COMMONAPI_H_
#define COMMONAPI_H_
#include <string>
#include <sys/types.h>

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//This file is used temporarily to reflect the CommonAPI files to be generated.
//This file should vanish, once CommonAPI generation is available.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define uint64_t unsigned long long
typedef std::string ClientSelector;
class ProfileManagerConsumerProxyBase;

namespace CommonAPI{
   class Stub {
   public:
      Stub(){};
      virtual ~Stub(){};
   };

   class Factory {
   public:
      Factory(){};
      virtual ~Factory(){};
      virtual ProfileManagerConsumerProxyBase*  buildProxy(std::string address) = 0;
      virtual bool                              registerService(Stub* s, const std::string& address) = 0;
   };
}

namespace CommonAPI{
   class Proxy {

   };
}


#endif /* COMMONAPI_H_ */
