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

class IdentificationPlugin;

/**
 * Holds the configuration of the ProfileManager. For each application, that needs specific treatment via
 * ProfileManager, a configuration file must be provided upon application installation. The configuration files
 * of all applications need to be collected and merged into a central configuration file. The result of passing
 * this configuration file must be saved to this structure and given to the ProfileManagerLogic upon construction.
 */
struct ProfileManagerCfg {
   enum EErrorAction {eReset = 0, eBlock = 1, eIgnore = 2 };

   struct ClientCfg {
      std::string    mAppId;
      int            mSeatId;
      int            mDepLevel;
      int            mTimeOutMs;
      EErrorAction   mTimeOutAction;
   };

   std::vector<ClientCfg>              mClientCfgs;
   std::vector<IdentificationPlugin*>  mIdPlugins;
   std::vector<int>                    mDepLevels;
};


#endif /* PROFILEMANAGERCFG_H_ */
