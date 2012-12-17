/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include "EventMessageQ.h"

int selector2Int(ClientSelector s){
   s = s.substr(7,1);
   return atoi(s.c_str());
}

const char* selector2Char(ClientSelector s){
   return s.c_str();
}
