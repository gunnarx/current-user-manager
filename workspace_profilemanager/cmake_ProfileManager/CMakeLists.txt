#COMMANDS:
#cmake .
#make

#ELCIPSE PROJECT
#cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug . 

cmake_minimum_required (VERSION 2.6)
project (ProfileManager)

SET(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../ProfileManager")

ADD_DEFINITIONS(
	-std=c++11 # Or -std=c++0x
    # Other flags
)

include_directories ("/usr/local/include/CommonAPI-2.1")
include_directories ("/usr/local/include/dbus-1.0")
include_directories ("/usr/local/lib/dbus-1.0/include")

include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/src-gen")

link_directories ("${PROJECT_SOURCE_DIR}/src")
link_directories ("${PROJECT_SOURCE_DIR}/src-gen") 

link_directories ("/usr/local/include/CommonAPI-2.1")
link_directories ("/usr/local/include/dbus-1.0")
link_directories ("/usr/local/lib/dbus-1.0/include")

include_directories ("/usr/local/lib/")
link_directories ("/usr/local/lib/")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)

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
ProfileManager
CommonAPI
CommonAPI-DBus
dbus-1
pthread
)

find_package( Threads )
target_link_libraries( ProfileManager ${CMAKE_THREAD_LIBS_INIT} )

