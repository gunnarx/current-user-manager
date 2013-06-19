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

ProfileManagerMain::ProfileManagerMain(CommonAPI::Factory* factory, ProfileManagerLog* log)
: mLogic(0) {
   if (factory == 0) {
      //factory = Create Standard CommonAPI factory here
   }
   if (log == 0){
      //logger = Create standard DLT logger here
   }

   CommonApiProfileManagerIntf* intf = new CommonApiProfileManagerIntf();
   mLogic = new ProfileManagerLogic(*log, *intf);
   CommonApiProfileManagerStub* stub = new CommonApiProfileManagerStub(*factory, *mLogic);
   intf->init(stub);
   std::string serviceAddress = "local:org.genivi.profilemanager:HUInstance";
   factory->registerService(stub, serviceAddress);
}


ProfileManagerMain::~ProfileManagerMain() {
   //Assume ProfileManageMain, is always used until process end, or power off, no destruction needed!
}



CProfileManagerCtrl* ProfileManagerMain::getProfileManagerCtrl() {
   return mLogic;
}
