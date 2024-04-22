cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(AllHailPlankton VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    # Add your cpp files here
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

if (APPLE AND GEODE_TARGET_PLATFORM STREQUAL "iOS")
    # -DGEODE_TARGET_PLATFORM=iOS -DCMAKE_SYSTEM_NAME=iOS \
    # -DCURL_LIBRARY=/Users/fire/Downloads/curl.xcframework/ios-arm64/curl.framework/curl \
    # -DCURL_INCLUDE_DIR=/Users/fire/Downloads/curl.xcframework/ios-arm64/curl.framework/Headers
    set(CMAKE_OSX_ARCHITECTURES arm64)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0")
    set(CMAKE_SYSTEM_NAME "iOS")
    execute_process(COMMAND xcrun --show-sdk-path --sdk iphoneos
    OUTPUT_VARIABLE GEODE_IOS_SDK
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    target_link_libraries(${PROJECT_NAME}
        "-framework OpenGLES"
        "-framework GLKit"
        "-framework UIKit"
        "-framework WebKit"
        "-framework AVFoundation"
        "-framework CoreFoundation"
        "-framework Foundation"
        "-framework CoreGraphics"
        ${CURL_LIBRARIES}
    )
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
