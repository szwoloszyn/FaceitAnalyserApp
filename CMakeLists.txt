cmake_minimum_required(VERSION 3.5)

project(FaceitAnalyserApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)



set(PROJECT_SOURCES
        src/main.cpp
        src/player.cpp
        src/faceitapiclient.cpp
        src/playerstatsmanager.cpp
        src/mainwindow.cpp
        src/playerinputpanel.cpp
        src/playerdatapanel.cpp
        src/playerstatswidget.cpp
        src/matchinputpanel.cpp
        src/matchdatapanel.cpp
        src/matchstatswidget.cpp
)
set(HEADERS
    include/player.h
    include/faceitapiclient.h
    include/playerstatsmanager.h
    include/mainwindow.h
    include/playerinputpanel.h
    include/playerdatapanel.h
    include/playerstatswidget.h
    include/matchinputpanel.h
    include/matchdatapanel.h
    include/matchstatswidget.h
)

set(UIS
    ui/mainwindow.ui
    ui/playerinputpanel.ui
    ui/playerdatapanel.ui
    ui/playerstatswidget.ui
    ui/matchinputpanel.ui
    ui/matchdatapanel.ui
    ui/matchstatswidget.ui
)

set(RESOURCES
    resources.qrc
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FaceitAnalyserApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${HEADERS}
        ${UIS}
        ${RESOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FaceitAnalyserApp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FaceitAnalyserApp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FaceitAnalyserApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(FaceitAnalyserApp PRIVATE src)
target_include_directories(FaceitAnalyserApp PRIVATE include)
target_include_directories(FaceitAnalyserApp PRIVATE ui)

set(RESOURCE_FILES resources.qrc)
qt6_add_resources(RESOURCES_RCC ${RESOURCE_FILES})


target_sources(FaceitAnalyserApp PRIVATE ${RESOURCES_RCC})

target_include_directories(FaceitAnalyserApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(FaceitAnalyserApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(FaceitAnalyserApp PRIVATE Qt${QT_VERSION_MAJOR}::Network)
set_target_properties(FaceitAnalyserApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS FaceitAnalyserApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FaceitAnalyserApp)
endif()
