cmake_minimum_required(VERSION 3.16)
project(config-json LANGUAGES CXX)

include(CheckIncludeFileCXX)
check_include_file_cxx(stdint.h HAVE_STDINT_H)
if(HAVE_STDINT_H)
    add_definitions(-DHAVE_STDINT_H)
endif()


find_package(nlohmann_json QUIET)
set(JSON_LIBS)
if(nlohmann_json_FOUND)
    list(APPEND JSON_LIBS nlohmann_json::nlohmann_json)
    message(STATUS "Found nlohmann_json package")
else()
    message(STATUS "nlohmann_json not found, try third_party header")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/nlohmann/json.hpp")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party")
        message(STATUS "Using bundled nlohmann_json header")
    else()
        message(FATAL_ERROR "nlohmann_json not found. Install nlohmann-json3-dev or place single header in contrib/json-config/third_party/nlohmann/json.hpp")
    endif()
endif()

set(CONFIG_JSON_SRC
    # === Helper Headers ===
    helper/application-json-helper.cc
    helper/config-json-helper.cc
    helper/internet-stack-json-helper.cc
    helper/ipv4-network-json-helper.cc
    helper/ipv4-routing-protocol-json-helper.cc
    helper/ipv6-network-json-helper.cc
    helper/ipv6-routing-protocol-json-helper.cc
    helper/link-json-helper.cc
    helper/mobility-json-helper.cc
    helper/node-json-helper.cc
    #helper/wifi-channel-json-helper.cc
    helper/dump-json-helper.cc    

    # === Model Headers ===
    model/application-json.cc
    model/config-json.cc
    model/internet-stack-json.cc
    model/ipv4-network-json.cc
    model/ipv4-routing-protocol-json.cc
    model/ipv6-network-json.cc
    model/ipv6-routing-protocol-json.cc
    model/link-json.cc
    model/mobility-json.cc
    model/node-json.cc
    helper/simulator-json-helper.cc
)

set(CONFIG_JSON_HDR
    # === Helper Headers ===
    helper/simulator-json-helper.h
    helper/application-json-helper.h
    helper/config-json-helper.h
    helper/internet-stack-json-helper.h
    helper/ipv4-network-json-helper.h
    helper/ipv4-routing-protocol-json-helper.h
    helper/ipv6-network-json-helper.h
    helper/ipv6-routing-protocol-json-helper.h
    helper/link-json-helper.h
    helper/mobility-json-helper.h
    helper/node-json-helper.h
    helper/dump-json-helper.h    

    # === Model Headers ===
    model/application-json.h
    model/config-json.h
    model/internet-stack-json.h
    model/ipv4-network-json.h
    model/ipv4-routing-protocol-json.h
    model/ipv6-network-json.h
    model/ipv6-routing-protocol-json.h
    model/link-json.h
    model/mobility-json.h
    model/node-json.h
)


build_lib(
    LIBNAME           config-json
    SOURCE_FILES      ${CONFIG_JSON_SRC}
    HEADER_FILES      ${CONFIG_JSON_HDR}
    LIBRARIES_TO_LINK ${libcore} ${JSON_LIBS} protobuf
)
find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(${libconfig-json} PUBLIC Boost::filesystem)