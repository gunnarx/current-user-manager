cmake_minimum_required (VERSION 2.6)
project (ProfileManagerTest)

SET(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../ProfileManagerTest")

ADD_DEFINITIONS(
	-std=c++11 # Or -std=c++0x
    # Other flags
)

#Please, change this paths to yours if you have commonAPI and/or DBus installed in not default paths!
#
include_directories ("/usr/local/include/CommonAPI-2.1")
include_directories ("/usr/local/include/dbus-1.0")
include_directories ("/usr/local/lib/dbus-1.0/include")

link_directories ("/usr/local/include/CommonAPI-2.1")
link_directories ("/usr/local/include/dbus-1.0")
link_directories ("/usr/local/lib/dbus-1.0/include")

include_directories ("/usr/local/lib/")
link_directories ("/usr/local/lib/")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)
#
################

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

