/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/

#ifndef PROFILEMANAGERMAIN_H_
#define PROFILEMANAGERMAIN_H_

#include "../include/CommonApi.h"
#include "../include/CProfileManagerCtrl.h"

class CProfileManagerCfg;
class ProfileManagerLog;
class ProfileManagerLogic;

/**
 * Main class for the profile manager
 */
class ProfileManagerMain {
private:
   ProfileManagerLogic* mLogic;

public:
   /**
    * Constructs the ProfileManager. Use it to initialize the ProfileManager Component.
    * In the future all parameters can be set with a null pointer, if default behavior is OK.
    * However within the limits of the POC, currently all parameters must be provided.
    * @param factory    Needed to create CommmonAPI proxy and register stubs
    * @param logger     Contains the class instance enabling to log, should default to DLT
    */
   ProfileManagerMain(CommonAPI::Factory* factory, ProfileManagerLog* logger);
   virtual ~ProfileManagerMain();

   CProfileManagerCtrl* getProfileManagerCtrl();


};

#endif /* PROFILEMANAGERMAIN_H_ */
