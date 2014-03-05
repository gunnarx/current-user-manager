cmake_minimum_required (VERSION 2.6)
project (ProfileManagerTest)

#SET(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../ProfileManagerTest")

ADD_DEFINITIONS(
	-std=c++11 # Or -std=c++0x
    # Other flags
)

#path to search for cmake package find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/") 

find_package(DBUS REQUIRED)
find_package(CommonAPI REQUIRED)
find_package(CommonAPI_DBus REQUIRED)

include_directories(${COMMON_API_INCLUDE_DIRS})
include_directories(${COMMON_API_DBUS_INCLUDE_DIRS})
include_directories(${DBUS_INCLUDE_DIRS})

link_directories(${COMMON_API_INCLUDE_DIRS})

#source code

include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/src-gen")

link_directories ("${PROJECT_SOURCE_DIR}/src")
link_directories ("${PROJECT_SOURCE_DIR}/src-gen") 

add_executable(
ProfileManagerTest
${PROJECT_SOURCE_DIR}/src/TestMainLoop.cpp
${PROJECT_SOURCE_DIR}/src/Controller.cpp
${PROJECT_SOURCE_DIR}/src/Client.cpp
${PROJECT_SOURCE_DIR}/src/Common_API_proxy_intf/ClientIntf.cpp
${PROJECT_SOURCE_DIR}/src/Common_API_proxy_intf/ControllerIntf.cpp
${PROJECT_SOURCE_DIR}/src/tests/TestUnregister.cpp
${PROJECT_SOURCE_DIR}/src/tests/TestUnsetUser.cpp
${PROJECT_SOURCE_DIR}/src/tests/TestRegister.cpp
${PROJECT_SOURCE_DIR}/src/tests/TestSetUser.cpp
${PROJECT_SOURCE_DIR}/src/tests/TestBase.cpp
${PROJECT_SOURCE_DIR}/src/Common_API_stubs_implementation/ControllerStubImpl.cpp
${PROJECT_SOURCE_DIR}/src/Common_API_stubs_implementation/ClientStubImpl.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlDBusProxy.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlConsumerDBusStubAdapter.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlStubDefault.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlDBusStubAdapter.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlConsumerDBusProxy.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlConsumerStubDefault.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerStubDefault.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerDBusProxy.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerDBusStubAdapter.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerConsumerDBusProxy.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerConsumerStubDefault.cpp
${PROJECT_SOURCE_DIR}/src-gen/org/genivi/profile_mgmt/ProfileManagerConsumerDBusStubAdapter.cpp
)

TARGET_LINK_LIBRARIES(
ProfileManagerTest
CommonAPI
CommonAPI-DBus
dbus-1
pthread
)

find_package( Threads )
target_link_libraries( ProfileManagerTest ${CMAKE_THREAD_LIBS_INIT} )

