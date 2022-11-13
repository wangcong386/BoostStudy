cmake_minimum_required(VERSION 3.5)

project(BoostStudy VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find boost
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    set(BOOST_ROOT "/user/local/include/boost")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    set(BOOST_ROOT C:/Boost)
    set(Boost_LIBRARY_DIRS C:/Boost/lib)
endif()

find_package(Boost REQUIRED COMPONENTS)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION = ${Boost_VERSION}")
    message(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}")
endif()

# find qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS)

if(QT_FOUND)
    message("QT_VERSION_MAJOR = ${QT_VERSION_MAJOR}")
    message("QT_VERSION_MAJOR = ${QT_VERSION_MINOR}")
    message("QT_VERSION_PATCH = ${QT_VERSION_PATCH}")
    message("Qt${QT_VERSION_MAJOR}_DIR = ${Qt${QT_VERSION_MAJOR}_DIR}")
endif(QT_FOUND)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

message("PROJECT_SOURCE_DIR" ${PROJECT_SOURCE_DIR})

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)
set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/boosttestwin.cpp
    ${PROJECT_SOURCE_DIR}/src/timedate.cpp
    ${PROJECT_SOURCE_DIR}/include/boosttestwin.h
    ${PROJECT_SOURCE_DIR}/include/timedate.h
    ${PROJECT_SOURCE_DIR}/src/boosttestwin.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BoostStudy
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET BoostStudy APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BoostStudy SHARED
            ${PROJECT_SOURCES}
        )

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BoostStudy
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BoostStudy PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Boost_LIBRARIES})

set_target_properties(BoostStudy PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BoostStudy)
endif()
