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
#include "../include/IdentificationPlugin.h"

class ProfileManagerCfg;
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
    * @param cfg        Contains the configuration like timeouts and dependency level for specific clients
    * @param logger     Contains the class instance enabling to log, should default to DLT
    * @param numOfSeats Number of Seats to be supported by Profile Manager.
    */
   ProfileManagerMain(CommonAPI::Factory* factory, ProfileManagerCfg* cfg, ProfileManagerLog* logger, int numOfSeats);
   virtual ~ProfileManagerMain();


   /**
    * Identification plugins, once loaded from shared libraries, or instanciated by other means need to register
    * with ProfileManager, so that the setUser interface is exposed to them.
    * @param plugin  Pointer to the plugin that needs to be registered.
    */
   void registerPlugin(IdentificationPlugin* plugin);
};

#endif /* PROFILEMANAGERMAIN_H_ */
