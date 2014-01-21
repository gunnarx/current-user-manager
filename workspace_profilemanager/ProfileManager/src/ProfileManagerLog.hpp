/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/
#ifndef PROFILEMANAGERLOG_H_
#define PROFILEMANAGERLOG_H_


#define PROFILEMAMAGERLOG_LEVEL_WARNING 1
#define PROFILEMAMAGERLOG_LEVEL_DBG 2
#define PROFILEMAMAGERLOG_LEVEL_ERROR 3

/**
 * This is the IF for the ProfileManagerLogic to report Debug, tracing or log output.
 * On a running IVI an instance of this class, which reports to DLT should be given
 * to the ProfileManagerLogic constructor
 *
 * Logger is not yet implemented
 */
class ProfileManagerLog {
public:
	ProfileManagerLog(){};
	virtual ~ProfileManagerLog(){};

	/**
	 * Sends a message to the log
	 * @param level Sets the severity level of the message, which can be used for filtering
	 * @param msg A message string
	 */
	virtual void log(int level, std::string msg) = 0;
};

class Logger : public ProfileManagerLog {
public:
	void log(int level, std::string msg){ /*std::cout << msg << std::endl;*/ };
};




#endif /* PROFILEMANAGERLOG_H_ */
