cmake_minimum_required(VERSION 3.16)

project(Joy_Animation_App VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appJoy_Animation_App
    main.cpp
    cpp/Project.cpp
    resources.qrc
)

qt_add_qml_module(appJoy_Animation_App
    URI Joy_Animation_App
    VERSION 1.0
    QML_FILES
        Main.qml
        CustomSlider.qml
    SOURCES
        filters_class.h
        filters_class.cpp
)

qt_add_resources(appJoy_Animation_App "resources"
    PREFIX "/"
    FILES
        assets/JA_Logo.svg
)


set_target_properties(appJoy_Animation_App PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appJoy_Animation_App
    PRIVATE Qt6::Quick Qt6::Core
)

include(GNUInstallDirs)
install(TARGETS appJoy_Animation_App
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
