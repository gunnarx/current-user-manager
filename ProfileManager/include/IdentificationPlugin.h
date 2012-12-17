/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef IDENTIFICATIONPLUGIN_H_
#define IDENTIFICATIONPLUGIN_H_

class SetUserIntf;

/**
 * First idea of how identification plugins could be initialized by ProfileManager
 */
class IdentificationPlugin {
public:
   IdentificationPlugin(){};
   virtual ~IdentificationPlugin(){};

   /**
    * identification plugins must provide this function. It will be called by ProfileManager,
    * once it is ready to use the plugin. The exposed SetUserIntf maybe used by the plugins to set
    * detected users.
    * @param usrIf Exposed SetUserIntf, which allows plugins to associate users with seats.
    */
   virtual void initPlugin(SetUserIntf* usrIf) = 0;
};


#endif /* IDENTIFICATIONPLUGIN_H_ */
