cmake_minimum_required(VERSION 3.10)
project(SmartGrid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets Charts REQUIRED)

# Liste des fichiers sources
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")
file(GLOB UI_FILES "ui/*.ui")
file(GLOB RESOURCES "resources/*.qrc")

add_executable(SmartGrid 
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
)

target_include_directories(SmartGrid PRIVATE include)
target_link_libraries(SmartGrid PRIVATE Qt5::Core Qt5::Widgets Qt5::Charts)

# Configuration spécifique Windows
if(WIN32)
    add_definitions(-DQT_QMAKE_EXPORT_WORKSPACE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")
endif()