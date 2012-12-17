/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef SETUSERINTF_H_
#define SETUSERINTF_H_


/**
 * Interface to be exposed to identification plugins, which allows to set a user on a certain seat
 * Will be returned to plugins upon registration with ProfileManager (ProfileManagerMain::registerPlugin)
 */
class SetUserIntf {
public:
	SetUserIntf(){};
	virtual ~SetUserIntf(){};


	/**
	 * Sets the user ID to the seat where it was detected
	 * @param seatId seat Id of seat the user was detected on
	 * @param userId of the detected user
	 */
   virtual void setUser(int seatId, int userId) = 0;
};

#endif /* SETUSERINTF_H_ */
