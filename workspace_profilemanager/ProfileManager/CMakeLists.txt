cmake_minimum_required (VERSION 2.6)
project (ProfileManager)

#SET(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../ProfileManager") CMAKE moved to root folder

ADD_DEFINITIONS(
	-std=c++11 # Or -std=c++0x
)
#set (CMAKE_VERBOSE_MAKEFILE true)
#path to search for cmake package find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/") 

find_package(DBUS REQUIRED)
find_package(CommonAPI REQUIRED)
find_package(CommonAPI_DBus REQUIRED)

include_directories(${COMMON_API_INCLUDE_DIRS})
include_directories(${COMMON_API_DBUS_INCLUDE_DIRS})
include_directories(${DBUS_INCLUDE_DIRS})

#link_directories(${COMMON_API_INCLUDE_DIRS})

#source code

include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/src-gen")

#link_directories ("${PROJECT_SOURCE_DIR}/src")
#link_directories ("${PROJECT_SOURCE_DIR}/src-gen") 

add_executable(
ProfileManager
${PROJECT_SOURCE_DIR}/src/main.cpp
${PROJECT_SOURCE_DIR}/src/ProfileManagerLogic.cpp
${PROJECT_SOURCE_DIR}/src/ProfileManagerEventHandler.cpp
${PROJECT_SOURCE_DIR}/src/ProfileManagerMain.cpp
${PROJECT_SOURCE_DIR}/src/Common_API_proxy_intf/ProfileManagerControllerIntf.cpp
${PROJECT_SOURCE_DIR}/src/Common_API_proxy_intf/ProfileManagerClientIntf.cpp
${PROJECT_SOURCE_DIR}/src/Common_API_stubs_implementation/ProfileManagerStubImpl.cpp
${PROJECT_SOURCE_DIR}/src/Common_API_stubs_implementation/ProfileManagerCtrlStubImpl.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerDBusProxy.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerStubDefault.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerDBusStubAdapter.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlDBusProxy.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlStubDefault.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlDBusStubAdapter.cpp
)

TARGET_LINK_LIBRARIES(
ProfileManager
CommonAPI
CommonAPI-DBus
dbus-1
pthread
)

#to allow multithreading
find_package( Threads )
target_link_libraries( ProfileManager ${CMAKE_THREAD_LIBS_INIT} )

#neccessary to link install target against commonApi
#set_target_properties(ProfileManager PROPERTIES 
#                      INSTALL_RPATH_USE_LINK_PATH TRUE)

INSTALL(TARGETS ProfileManager
        DESTINATION "bin"
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

