/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef COMMONAPIPROFILEMANAGERINTF_H_
#define COMMONAPIPROFILEMANAGERINTF_H_

#include <map>
#include <string>

#include "../include/CommonApi.h"

class CommonApiProfileManagerStub;

/**
 * Provides calls for the logic to send signals (detected, synced, stop) to ProfileManager clients.
 * This interface enables the logic to stay the same, once the selective attribute is supported by
 * CommonAPI
 * Due to initialization logic, stub is not available during creation and must be set late via init.
 * Do not use the send functions before init was called!
 */
class CommonApiProfileManagerIntf {
private:
   CommonApiProfileManagerStub* mStub;

public:
   CommonApiProfileManagerIntf();
   virtual ~CommonApiProfileManagerIntf();

   void init(CommonApiProfileManagerStub* stub);

   void sendDetectedUser(ClientSelector clientId, int seatId, int userId, uint64_t sessionId);
   void sendSynchronizedUser(ClientSelector clientId, int seatId, int userId, uint64_t sessionId);
   void sendStop(ClientSelector clientId, int seatId, uint64_t sessionId);
};


#endif /* COMMONAPIPROFILEMANAGERINTF_H */
