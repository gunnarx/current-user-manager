/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2013 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef CPROFILEMANAGERCTRL_H_
#define CPROFILEMANAGERCTRL_H_

#include "CProfileManagerCtrlConsumer.h"
#include "CProfileManagerCfg.h"

class CProfileManagerCtrl {
public:

   enum ETimeOutAction {
      eDropApplication,
      eIgnore,
      eReTime,
      eStopWaitForNewUser,
      eReturnToOldUser
   };

   // Profile Manager Controller needs to register once. Callback/Consumer interface must
   // be provided, factory and configuration can be optionally provided, otherwise the configuration will be read
   // automatically and the standard factory is used.
   virtual void registerMe(CProfileManagerCtrlConsumer& consumer, CProfileManagerCfg* cfg = 0) = 0;

   // Sets the detected user (userId 0 is defined as the default user)
   virtual void setUser(u_int32_t userId, u_int32_t seatId) = 0;

   // Unsets the detected user
   virtual void unsetUser(u_int32_t seatId) = 0;

   // If the Profile Manager Controller receives a onTimeOut call via it's
   // CProfileManagerCtrlConsumer interface, the ProfileManager will stop it's activities.
   // Only after the Profile Manager Controller has given instructions on how to
   // continue with the encountered timeout, the Profile Manager will continue.
   virtual void timeOutAction(uint64_t timeOutSessionId, ETimeOutAction timeOutAction) = 0;
};

#endif
