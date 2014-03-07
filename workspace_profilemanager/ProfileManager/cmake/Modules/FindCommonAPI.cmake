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

pkg_check_modules(COMMON_API CommonAPI)

IF(COMMON_API_FOUND)
    
	#VARIABLES READ FROM PKG-CONFIG	
	#${COMMON_API_VERSION}
	#${COMMON_API_LIBRARIES}
	#${COMMON_API_INCLUDE_DIRS}
                 
ELSE(COMMON_API_FOUND)
    
	MESSAGE(STATUS "  pkg-config have not found CommonAPI package, searching directly ...")

	FIND_PATH(COMMON_API_INCLUDE_DIR
		NAMES CommonAPI/CommonAPI.h
		PATHS
		#APPEND WITH MORE VERSIONS	      	
		/usr/local/include/CommonAPI-2.1   	
		/usr/include/CommonAPI-2.1)

	FIND_LIBRARY(COMMON_API_LIBRARY 
		NAMES CommonAPI
		PATHS
		#APPEND WITH MORE VERSIONS
		/usr/local/lib
		/usr/lib)
              
ENDIF(COMMON_API_FOUND)

## To sucesfully start a Profile Manager it is required to link it against dir with CommonAPI lib
FIND_PATH(COMMON_API_LINK_INCLUDE_DIR
	NAMES libCommonAPI.so.3.0.0 libCommonAPI.so libCommonAPI libCommonAPI.so.3
	PATHS	
	${COMMON_API_LIBRARIES}
	${COMMON_API_INCLUDE_DIRS}	
	/usr/local/lib 
	/usr/local/        	
	/usr/)

SET(COMMON_API_INCLUDE_DIRS ${COMMON_API_INCLUDE_DIRS} ${COMMON_API_INCLUDE_DIR} ${COMMON_API_LINK_INCLUDE_DIR})
SET(COMMON_API_LIBRARIES ${COMMON_API_LIBRARIES} ${COMMON_API_LIBRARY})

IF(COMMON_API_INCLUDE_DIRS AND COMMON_API_LIBRARIES)   
	message(STATUS "  Found CommonAPI")
ELSE(COMMON_API_INCLUDE_DIRS AND COMMON_API_LIBRARIES)   
	message(STATUS "  CommonAPI NOT found.")
ENDIF(COMMON_API_INCLUDE_DIRS AND COMMON_API_LIBRARIES)

IF(COMMON_API_LINK_INCLUDE_DIR)   
	message(STATUS "  CommonAPI lib linked properly")
ELSE(COMMON_API_LINK_INCLUDE_DIR)   
	message(STATUS "  CommonAPI lib NOT linked properly.")
ENDIF(COMMON_API_LINK_INCLUDE_DIR)	
	
MARK_AS_ADVANCED(
    COMMON_API_LIBRARIES 
    COMMON_API_INCLUDE_DIRS
)
