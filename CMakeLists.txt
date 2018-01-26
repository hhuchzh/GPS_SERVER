# stop if cmake version below 2.8
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# project name
project(BusServer)

set(BINARY_NAME BusServer)

# enable c language
enable_language(C)

set(CMAKE_C_COMPILER "g++")

# project version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

#set(CMAKE_BUILD_TYPE "release")
## debug
#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE "Debug")
#endif()
#
#if(${CMAKE_BUILD_TYPE} MATCH "Debug")
#	ADD_DEFINITIONS(-DDEV_MODE)
#endif()
#message( "------CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE}------" )


if(CMAKE_C_COMPILER_ID MATCHES GNU)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wwrite-strings -Wno-unused")
	#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -O0 -g3")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")
endif()

set(BUSSERVER_SRC
	src/main.c
	src/logger.c
	src/dispatcher.c
	src/engine.c
	src/gps_user.c
	src/crc_itu.c
	src/msg.c
   	src/listener.c)

include_directories(include
	include/log4c
	include/client64)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib )
link_libraries(liblog4c.a
	libevent_core.a
	libevent_extra.a
	libevent_pthreads.a
        libocci.so
        libclntsh.so
	libociei.so
	libocijdbc11.so
	libsqlplusic.so
	libsqlplus.so)


message( "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message( "SRC: ${BUSSERVER_SRC}")

# compile main executable
add_executable(${BINARY_NAME}  ${BUSSERVER_SRC})

# link library
target_link_libraries(${BINARY_NAME} pthread rt -L/usr/lib64/ ${PKGS_LDFLAGS})
