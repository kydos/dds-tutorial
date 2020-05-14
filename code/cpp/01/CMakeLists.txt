#
# Copyright(c) 2006 to 2018 ADLINK Technology Limited and others
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License v. 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0, or the Eclipse Distribution License
# v. 1.0 which is available at
# http://www.eclipse.org/org/documents/edl-v10.php.
#
# SPDX-License-Identifier: EPL-2.0 OR BSD-3-Clause
#
cmake_minimum_required(VERSION 3.5)
set(Boost_INCLUDE_DIR /Users/kydos/tool/boost_1_73_0)
set(Boost_LIBRARY_DIR /Users/kydos/tool/boost_1_73_0/stage/lib)

project("TempControl")
find_package(Idlpp-cxx REQUIRED)
find_package(CycloneDDS REQUIRED)
find_package(Boost REQUIRED)

if (NOT TARGET CycloneDDS_CXX_API::ddscxx)
    # Find the CycloneDDS_CXX_API package. If it is not in a default location, try
    # finding it relative to the example where it most likely resides.
    find_package(CycloneDDS_CXX_API REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/../../../..")
endif()

include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIR} )
link_libraries(boost_program_options)

# This is a convenience function, provided by the CycloneDDS_CXX_API package,
# that will supply a library target related the the given idl file.
# In short, it takes the idl file, generates the source files with
# the proper data types and compiles them into a library.
idl_ddscxx_generate(temp_ctrl "TempControl.idl")

# Both executables have only one related source file.
add_executable(tspub tspub.cpp util.cpp)
add_executable(tssub tssub.cpp util.cpp)

# Both executables need to be linked to the idl data type library and
# the ddsc API library.
target_link_libraries(tspub temp_ctrl CycloneDDS_CXX_API::ddscxx )


target_link_libraries(tssub temp_ctrl CycloneDDS_CXX_API::ddscxx)

set_property(TARGET tspub PROPERTY CXX_STANDARD 11)
set_property(TARGET tssub PROPERTY CXX_STANDARD 11)
