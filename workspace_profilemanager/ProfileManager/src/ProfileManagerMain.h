/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#ifndef PROFILEMANAGERMAIN_H_
#define PROFILEMANAGERMAIN_H_

#include "ProfileManagerCfg.hpp"
#include "ProfileManagerEventHandler.h"
#include "ProfileManagerLogic.h"

#include "Common_API_stubs_implementation/ProfileManagerCtrlStubImpl.h"
#include "Common_API_stubs_implementation/ProfileManagerStubImpl.h"


/*
 * This is main PM class, it creates an instance of logger, Client and Controller interfaces,
 * event handler, Client and Controller stubs.
 * Class constructor runs forever, event handler awaits for new events and executes them,
 * therefore provides whole PM functionality
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
   ProfileManagerMain();
   virtual ~ProfileManagerMain();

};

#endif /* PROFILEMANAGERMAIN_H_ */
