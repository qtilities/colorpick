cmake_minimum_required(VERSION 3.15)
project(Colorpick
    VERSION 0.1.0
    LANGUAGES CXX
)
include(Config.cmake)

set(CMAKE_CXX_STANDARD 17) #Qt6 needs C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
# Qt
#
option(PROJECT_TRANSLATIONS_UPDATE "Update source translations [default: OFF]" OFF)
set(PROJECT_QT_VERSION 5 CACHE STRING "Qt version to use: 5 (default) or 6")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(QT NAMES Qt${PROJECT_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED Core LinguistTools Widgets)
#
# Project files
#
set(PROJECT_SOURCES
    src/colorbutton.h
    src/colorbutton.cpp
    src/coloreditor.h
    src/coloreditor.cpp
    src/colorpicker.h
    src/colorpicker.cpp
    src/colorspace.h
    src/colorspace.cpp
    src/componenteditor.h
    src/componenteditor.cpp
    src/contrastpreview.h
    src/contrastpreview.cpp
    src/hcycolorspace.h
    src/hsvcolorspace.h
    src/hsvcolorspace.cpp
    src/imagegradientselector.h
    src/imagegradientselector.cpp
    src/rgbcolorspace.h
    src/rgbcolorspace.cpp
    src/window.h
    src/window.cpp
    src/main.cpp
)
source_group("Sources" FILES ${PROJECT_SOURCES})
#
# Resources
#
set(PROJECT_RESOURCES
    resources/application.qrc
    resources/freedesktop/${PROJECT_ID}.desktop
)
set(PROJECT_TRANSLATION_TEMPLATE resources/translations/${PROJECT_ID}.ts)
file(GLOB PROJECT_TRANSLATION_SOURCES "resources/translations/${PROJECT_ID}_*.ts")

source_group("Resource Files" FILES
    ${PROJECT_RESOURCES}
    ${PROJECT_TRANSLATION_TEMPLATE}
    ${PROJECT_TRANSLATION_SOURCES}
)
# Copy the application icon into the build dir to be used when running from IDE
configure_file("resources/icons/application.svg"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_ID}.svg" COPYONLY
)
#
# Translations
#
if(${QT_VERSION_MAJOR} VERSION_LESS 6.2)
    if(PROJECT_TRANSLATIONS_UPDATE)
        # the first call creates/updates the <appname>.ts template file, it should not be compiled,
        # the other the actual <appname>_<country-code>.ts translation files to be installed later.
        qt_create_translation(QM_DUMMY
            ${PROJECT_SOURCES}
            ${PROJECT_TRANSLATION_TEMPLATE}
        )
        qt_create_translation(PROJECT_QM_FILES
            ${PROJECT_SOURCES}
            ${PROJECT_TRANSLATION_SOURCES}
        )
        add_custom_target(TemplateUpdate ALL DEPENDS ${QM_DUMMY})
    endif()
    qt_add_translation(PROJECT_QM_FILES ${PROJECT_TRANSLATION_SOURCES})
else()
    # FIXME: updating the .ts files seems not to work in Qt6, even by using the deprecated
    #        qt_create_translation() used with Qt5. It's not clear where qt_add_lupdate() call
    #        should be placed, qt_add_lrelease() wants to be called after add_executable() for sure.
    if(PROJECT_TRANSLATIONS_UPDATE)
        qt_add_lupdate(${PROJECT_NAME}
            TS_FILES ${PROJECT_TRANSLATION_TEMPLATE} ${PROJECT_TRANSLATION_SOURCES}
            SOURCES ${PROJECT_SOURCES}
        )
    endif()
endif()
#
# Build
#
add_executable(${PROJECT_NAME}
    ${PROJECT_QM_FILES}
    ${PROJECT_RESOURCES}
    ${PROJECT_SOURCES}
    ${PROJECT_TRANSLATION_SOURCES}
    ${PROJECT_TRANSLATION_TEMPLATE}
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Widgets
)
if (UNIX AND NOT APPLE)
    include(GNUInstallDirs)
    set(PROJECT_DATA_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_ID}")
    set(PROJECT_ICON_SYSTEM_PATH "${CMAKE_INSTALL_FULL_DATADIR}/icons/hicolor/scalable/apps")
else()
    #TODO: macOS and Windows
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_ID}")
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Woverloaded-virtual)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    APPLICATION_NAME="${PROJECT_ID}"
    APPLICATION_DISPLAY_NAME="${PROJECT_NAME}"
    ORGANIZATION_NAME="${PROJECT_ORGANIZATION_NAME}"
    ORGANIZATION_DOMAIN="${PROJECT_ORGANIZATION_URL}"
    PROJECT_DATA_DIR="${PROJECT_DATA_DIR}"
    PROJECT_ICON_SYSTEM_PATH="${PROJECT_ICON_SYSTEM_PATH}"
)
if(${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL 6.2)
    qt_add_lrelease(${PROJECT_NAME}
        TS_FILES ${PROJECT_TRANSLATION_SOURCES}
        QM_FILES_OUTPUT_VARIABLE PROJECT_QM_FILES
    )
endif()
#
# Install
#
if (UNIX AND NOT APPLE)
    install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(FILES "resources/freedesktop/${PROJECT_ID}.desktop"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
    )
    install(FILES "resources/freedesktop/${PROJECT_ID}.appdata.xml"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/metainfo"
    )
    install(FILES "${PROJECT_QM_FILES}"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_ID}/translations"
    )
    install(FILES "resources/icons/application.svg"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps"
        RENAME "${PROJECT_ID}.svg"
    )
endif()
#
# Project information
#
message(STATUS "
Qt version:                       ${QT_VERSION}
Build type:                       ${CMAKE_BUILD_TYPE}
Install prefix:                   ${CMAKE_INSTALL_PREFIX}
Update translations before build: ${PROJECT_TRANSLATIONS_UPDATE}
")
