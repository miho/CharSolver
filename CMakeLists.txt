project(char-solver) # project name

cmake_minimum_required(VERSION 2.4.0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

# dependencies

find_package(Qt4 REQUIRED) # find and setup Qt
include (${QT_USE_FILE})

find_package(FlexPars REQUIRED) #find and setup flexpars
find_package(Gensolver REQUIRED) # find and setup gensolver

add_subdirectory(src) # tells cmake to process this directory

#set_target_properties(gensolver-test PROPERTIES VERSION)

IF (UNIX)
	MESSAGE(STATUS "This is UNIX")
ENDIF (UNIX)


# adding uninstall target
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_modules/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_modules/cmake_uninstall.cmake")
