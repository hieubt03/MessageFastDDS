cmake_minimum_required(VERSION 3.16)
project(SubscriberApp LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(fastrtps_LIBRARY_DIRS "E:/FastDDS/lib/x64Win64VS2019")
set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL-Win64/include")
set(OPENSSL_CRYPTO_LIBRARY "E:/FastDDS/lib/x64Win64VS2019/libcrypto.lib")


if(NOT fastcdr_FOUND)
    find_package(fastcdr REQUIRED)
endif()

if(NOT foonathan_memory_FOUND)
    find_package(foonathan_memory REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()

find_package(OpenSSL REQUIRED)

include_directories(
    ${fastcdr_INCLUDE_DIR}
    ${fastrtps_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/Subscriber
)

link_directories(${fastrtps_LIBRARY_DIRS})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    smain.cpp
    SubscriberApp.ui
    SubscriberApp.h
    SubscriberApp.cpp 
    SubscribeMessage.h 
    SubscribeMessage.cpp 
    Message.h 
    Message.cpp 
)

qt_add_executable(SubscriberApp ${PROJECT_SOURCES})

set_target_properties(SubscriberApp
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(SubscriberApp
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        fastrtps 
        fastcdr 
        foonathan_memory
)
