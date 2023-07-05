cmake_minimum_required(VERSION 3.5)

project(MonitorController VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

set(PROJECT_SOURCES
        main.cpp
        trayicon.cpp
        trayicon.h
        monitorcontroller.cpp
        monitorcontroller.h
)

qt_add_executable(MonitorController
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(MonitorController PRIVATE
    Qt6::Widgets
    Qt6::Core
    dxva2.lib
)

# <a href="https://www.flaticon.com/free-icons/sun" title="sun icons">Sun icons created by Freepik - Flaticon</a>
qt_add_resources(MonitorController "images"
    FILES "icon.png"
)

set_target_properties(MonitorController PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS MonitorController
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(MonitorController)
