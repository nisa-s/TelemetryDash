cmake_minimum_required(VERSION 3.16)

project(TelemetryDash VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets SerialPort)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    TelemetryDash.cpp
    SerialManager.cpp
)

set(HEADERS
    TelemetryDash.h
    SerialManager.h
)

set(UI_FILES
    TelemetryDash.ui
)

qt_add_executable(TelemetryDash
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
)

target_link_libraries(TelemetryDash PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::SerialPort
)

configure_file(style_Generic.css ${CMAKE_BINARY_DIR}/style_Generic.css COPYONLY)