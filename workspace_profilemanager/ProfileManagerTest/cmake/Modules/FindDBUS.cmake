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

pkg_check_modules(DBUS dbus-1)

IF(DBUS_FOUND)

	#VARIABLES READ FROM PKG-CONFIG
	#${DBUS_VERSION}
	#${DBUS_INCLUDE_DIRS}
	#${dbus-1_PKG_LIBRARY_DIRS} 

ELSE(DBUS_FOUND)

	MESSAGE(STATUS "  pkg-config have not found DBUS package, searching directly ...")

	FIND_PATH(DBUS_INCLUDE_DIR
		NAMES
		dbus/dbus.h
		PATHS
		/usr/include/dbus-1.0
		/usr/local/include/dbus-1.0
	)

	FIND_PATH(DBUS_ARCH_INCLUDE_DIR
		NAMES
		dbus/dbus-arch-deps.h
		PATHS	
		/usr/lib/dbus-1.0/include
		/usr/local/lib/dbus-1.0/include
	)

	FIND_LIBRARY(DBUS_LIBRARY
		NAMES
		dbus-1
		PATHS 
		/lib
		/usr/lib
		/usr/local/lib
	)

ENDIF(DBUS_FOUND)

SET(DBUS_INCLUDE_DIRS ${DBUS_INCLUDE_DIR} ${DBUS_ARCH_INCLUDE_DIR})
SET(DBUS_LIBRARIES ${DBUS_LIBRARY})

IF(DBUS_INCLUDE_DIRS AND DBUS_LIBRARIES)
	message(STATUS "  Found DBUS")
ELSE(DBUS_INCLUDE_DIRS AND DBUS_LIBRARIES)
	message(STATUS "  DBUS not found.")
ENDIF(DBUS_INCLUDE_DIRS AND DBUS_LIBRARIES)

MARK_AS_ADVANCED(
  DBUS_INCLUDE_DIRS
  DBUS_LIBRARIES
)
