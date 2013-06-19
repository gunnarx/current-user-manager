/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2013 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef CPROFILEMANAGERCTRLCONSUMER_H_
#define CPROFILEMANAGERCTRLCONSUMER_H_

#include "CommonApi.h"

class CProfileManagerCtrlConsumer {

public:

   enum ESignal {eConfirm = 0, eStopped = 1};
   // A registered client hasen't responded in time
   virtual void onTimeOut(std::string& appName, u_int32_t userId, u_int32_t seatId, ESignal s, uint64_t sessionId, int32_t timeElapsedMs) = 0;
   // Signals to clients are about to be send out, that should trigger
   // the response set in Esignal according to dependency level
   virtual void onStateChangeStart(u_int32_t userId, u_int32_t seatId, u_int32_t depLevel, ESignal s, uint64_t sessionId) = 0;
   // All clients have answered with the given ESignal,
   // according to the given dependency level
   virtual void onStateChangeStop( u_int32_t userId, u_int32_t seatId, u_int32_t depLevel, ESignal s, uint64_t sessionId) = 0;
   // A client has registered
   virtual void onClientRegister( u_int32_t seatId, std::string& appName) = 0;
   //A client has unregistered
   virtual void onClientUnregister( u_int32_t seatId, std::string& appName) = 0;
};

#endif
