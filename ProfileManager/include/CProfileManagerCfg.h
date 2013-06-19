/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef PROFILEMANAGERCFG_H_
#define PROFILEMANAGERCFG_H_

#include <string>
#include <vector>
#include "CommonApi.h"

/**
 * Holds the configuration of the ProfileManager. For each application, that needs specific treatment via
 * ProfileManager, a configuration file must be provided upon application installation. The configuration files
 * of all applications need to be collected and merged into a central configuration file. The result of passing
 * this configuration file must be saved to this structure and given to the ProfileManagerLogic upon construction.
 */
class CProfileManagerCfg {
public:

   struct ClientCfg {
      std::string    mAppName;//application name as it used by Lifecycle
      u_int32_t      mSeatId;//0xff ff ff ff indicates non seat specific
      int32_t        mDepLevel;
      int32_t        mTimeOutMs;
   };

   int32_t                 mDefaultDepLevel;
   int32_t                 mDefaultTimeOutMs;
   int32_t                 mNumOfSeats;
   std::vector<ClientCfg>  mClientCfgs;
};


#endif /* PROFILEMANAGERCFG_H_ */
