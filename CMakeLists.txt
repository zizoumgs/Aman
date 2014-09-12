# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

if (UNIX)
   message(STATUS "This is UNIX (including OS X and CygWin)")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif (UNIX)
if (MSVC)
	message(STATUS "This is Windows Boss)")
	check_include_file_concat("ws2tcpip.h"     HAVE_WS2TCPIP_H)
	check_include_file_concat("winsock2.h"     HAVE_WINSOCK2_H)
  	# Force to always compile with W4
  	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  	else()
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  	endif()
#   set(MY_SRCS ${MY_SRCS} winextra.cpp)
endif (MSVC)
# Set the name and the supported language of the project
project(main C)
# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
IF		(PKG_CONFIG_FOUND)
	message(STATUS "Pkg config di temukan")
endif 	(PKG_CONFIG_FOUND )
pkg_check_modules(GTK2 REQUIRED gtk+-2.0 )
#mencari gstremaer
pkg_check_modules(GSTREAMER REQUIRED gstreamer-0.10 )	
SET(GSTREAMER_VERSION ${GSTREAMER_VERSION})
#mencari sqlite
pkg_check_modules(SQLITE3 REQUIRED sqlite3 )	
SET(SQLITE3_VERSION ${SQLITE3_VERSION})
#mencari unique
pkg_check_modules(UNIQUE REQUIRED unique-1.0)	#unique-1.0 menyesuaikan dengan file unique-1.0
SET(UNIQUE_VERSION 		${UNIQUE_VERSION})
# mencari libnotify
pkg_check_modules(LIBNOTIFY REQUIRED libnotify)
SET(LIBNOTIFY_VERSION 		${LIBNOTIFY_VERSION})

# Add other flags to the compiler
add_definitions(
	${GTK2_CFLAGS_OTHER}
	${GSTREAMER_DEFINITIONS}
	${SQLITE3_DEFINITIONS}
	${UNIQUE_DEFINITIONS}
	${LIBNOTIFY_DEFINITIONS}
)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(
	${GTK2_INCLUDE_DIRS} 
	${GSTREAMER_INCLUDE_DIRS}
	${SQLITE3_INCLUDE_DIRS}
	${LIBNOTIFY_INCLUDE_DIRS}
)
include_directories(${UNIQUE_INCLUDE_DIRS})
link_directories(
	${GTK2_LIBRARY_DIRS} 
	${GSTREAMER_LIBRARY_DIRS}
	${SQLITE3_LIBRARY_DIRS}
	${UNIQUE_LIBRARIES}
	${LIBNOTIFY_LIBRARY_DIRS}
)
# Add an executable compiled from hello.c
file(GLOB helloworld_SRC
    "*.h"
    "*.c"
)
add_executable(main ${helloworld_SRC})

# Link the target to the GTK+ libraries
target_link_libraries(
	main
	${GTK2_LIBRARIES} 
	${GSTREAMER_LIBRARIES} 
	${SQLITE3_LIBRARIES} 
	${LIBNOTIFY_LIBRARIES}
	${UNIQUE_LIBRARIES} 
)


