/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
***************************************************************/
#include "ProfileManagerMain.h"
#include "ProfileManagerLogic.h"
#include "CommonApiProfileManagerIntf.h"
#include "CommonApiProfileManagerStub.h"

ProfileManagerMain::ProfileManagerMain(CommonAPI::Factory* factory, ProfileManagerCfg* cfg, ProfileManagerLog* log, int numOfSeats)
: mLogic(0) {
   if (factory == 0) {
      //factory = Create Standard CommonAPI factory here
   }

   if (cfg == 0) {
      //cfg = Read configuration from file here.
   }

   if (log == 0){
      //logger = Create standard DLT logger here
   }

   if (numOfSeats == 0) {
      numOfSeats = 5;
   }

   CommonApiProfileManagerIntf* intf = new CommonApiProfileManagerIntf();
   mLogic = new ProfileManagerLogic(*log, *intf, *cfg, numOfSeats);
   CommonApiProfileManagerStub* stub = new CommonApiProfileManagerStub(*factory, *mLogic);
   intf->init(stub);
   std::string serviceAddress = "local:org.genivi.profilemanager:HUInstance";
   factory->registerService(stub, serviceAddress);
}


ProfileManagerMain::~ProfileManagerMain() {
   //Assume ProfileManageMain, is always used until process end, or power off, no destruction needed!
}


void ProfileManagerMain::registerPlugin(IdentificationPlugin* plugin){
   if (mLogic != 0 && plugin != 0) {
      plugin->initPlugin(mLogic);
   }
}
