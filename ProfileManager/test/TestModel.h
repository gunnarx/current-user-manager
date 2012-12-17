/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef TESTMODEL_H_
#define TESTMODEL_H_

#define NUM_OF_TEST_CLIENTS 10

class TestModel {
public:
   int mSeats[NUM_OF_TEST_CLIENTS];

   TestModel();
   virtual ~TestModel();


   void setUser(int seatId, int userId);
   int getUserId(int seatId);
};

#endif /* TESTMODEL_H_ */
