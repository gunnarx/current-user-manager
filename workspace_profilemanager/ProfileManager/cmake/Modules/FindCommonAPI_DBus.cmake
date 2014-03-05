# Copyright (C) 2014, Ericpol
#
# This file is part of GENIVI Project ProfileManager.
# 
# Contributions are licensed to the GENIVI Alliance under one or more
# Contribution License Agreements.
# 
# copyright
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a  copy of the MPL was not distributed with
# this file, You can obtain one at http://mozilla.org/MPL/2.0/.
# 
# author Przemyslaw Bularz, przemyslaw.bularz@ericpol.com
#
# For further information see http://www.genivi.org/.
#


include(FindPkgConfig)

pkg_check_modules(COMMON_API_DBUS CommonAPI-DBus)

IF(COMMON_API_DBUS_FOUND)

	#VARIABLES READ FROM PKG-CONFIG	
	#${COMMON_API_VERSION}
	#${COMMON_API_DBUS_INCLUDE_DIRS}
	#${CommonAPI_PKG_LIBRARY_DIRS}                 
                                                                
ELSE(COMMON_API_DBUS_FOUND)
    
	MESSAGE(STATUS "  pkg-config have not found CommonAPI_DBUS package, searching directly ...")

	FIND_PATH(COMMON_API_DBUS_INCLUDE_DIR
		NAMES CommonAPI/DBus/DBusRuntime.h CommonAPI/DBus/DBusProxy.h 	 
		PATHS
		#APPEND WITH MORE VERSIONS	
		/usr/local/include/CommonAPI-2.1        	
		/usr/include/CommonAPI-2.1)

	FIND_LIBRARY(COMMON_API_DBUS_LIBRARY 
		NAMES CommonAPI-DBus 
		PATHS
		/usr/local/lib
		/usr/lib
		/lib)             
         
ENDIF(COMMON_API_DBUS_FOUND)
    
SET(COMMON_API_DBUS_INCLUDE_DIRS ${COMMON_API_DBUS_INCLUDE_DIR})
SET(COMMON_API_DBUS_LIBRARIES ${COMMON_API_DBUS_LIBRARY} ${CommonAPI_PKG_LIBRARY_DIRS})

IF(COMMON_API_DBUS_INCLUDE_DIRS AND COMMON_API_DBUS_LIBRARIES)
	message(STATUS "  Found CommonAPI_DBUS")
ELSE(COMMON_API_DBUS_INCLUDE_DIRS AND COMMON_API_DBUS_LIBRARIES)
	message(STATUS "  CommonAPI_DBUS not found.")
ENDIF(COMMON_API_DBUS_INCLUDE_DIRS AND COMMON_API_DBUS_LIBRARIES)
		
MARK_AS_ADVANCED(
    COMMON_API_DBUS_LIBRARIES 
    COMMON_API_DBUS_INCLUDE_DIRS
)
