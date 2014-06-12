cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH ../../cmake)

# This is your project name
project (quoter)

include (MacroOpenSplice)
include (osmacros)
find_package (OpenSplice REQUIRED)
# If you need to add external libraries dependencies, add them here
# find_package (YourPackage REQUIRED)

#
# You may add your include directories below
#
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${OpenSplice_INCLUDE_DIRS}
  ../../src/
)


# Define the idl file that you want to be compiled
set (idls quoter.idl)


foreach(idl ${idls})
	OpenSplice_IDLGEN (${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1.cpp" VARS_1 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1.h" VARS_2 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps.cpp" VARS_3 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps.h" VARS_4 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps_impl.cpp" VARS_5 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps_impl.h" VARS_6 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1SplDcps.cpp" VARS_7 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1SplDcps.h" VARS_8 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/ccpp_\\1.h" VARS_9 ${idl})
	set(OpenSplice_DATAMODEL ${OpenSplice_DATAMODEL} ${VARS_1} ${VARS_2} ${VARS_3} ${VARS_4} ${VARS_5} ${VARS_6} ${VARS_7} ${VARS_8} ${VARS_9})
endforeach(idl)

set (DW_SOURCES
  quoter.cpp
)

set (DR_SOURCES
  logger.cpp
)

set (RDR_SOURCES
  rlogger.cpp
)


set (EXE_DW quoter)
set (EXE_DR logger)
set (EXE_RDR rlogger)

set (DATAMODEL datamodel)

add_executable (${EXE_DW} ${DW_SOURCES})
add_executable (${EXE_DR} ${DR_SOURCES})
add_executable (${EXE_RDR} ${RDR_SOURCES})
add_library (${DATAMODEL} STATIC ${OpenSplice_DATAMODEL})

add_definitions (
 ${OpenSplice_DEFINITIONS}
 ${DEFINITIONS}
)

target_link_libraries (
  ${DATAMODEL} 
  ${OpenSplice_LIBRARIES}
)

target_link_libraries (${EXE_DW}
 ${OpenSplice_LIBRARIES}
 ${DATAMODEL} 
)

target_link_libraries (${EXE_DR}
 ${OpenSplice_LIBRARIES}
 ${DATAMODEL} 
)

target_link_libraries (${EXE_RDR}
 ${OpenSplice_LIBRARIES}
 ${DATAMODEL} 
)
