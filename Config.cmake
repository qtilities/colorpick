# Editable project configuration

# Essential, non translatable application information (except DESCRIPTION).
# Translatable strings are passed via code.
string(TOLOWER ${PROJECT_NAME}  PROJECT_ID)
list(APPEND PROJECT_CATEGORIES  "Qt;KDE;Graphics;Utility") # Freedesktop menu categories
list(APPEND PROJECT_KEYWORDS    "colorpicker;color-picker;contrast-ratio")
set(PROJECT_AUTHOR_NAME         "Aurélien Gâteau, Andrea Zanellato")
set(PROJECT_AUTHOR_EMAIL        "redtid3@gmail.com") # Used also for organization email
set(PROJECT_COPYRIGHT_YEAR      "2023") # TODO: from git
set(PROJECT_DESCRIPTION         "A color picker with a builtin loop and a contrast checker.")
set(PROJECT_ORGANIZATION_NAME   "qtilities") # Might be equal to PROJECT_AUTHOR_NAME
set(PROJECT_ORGANIZATION_URL    "${PROJECT_ORGANIZATION_NAME}.github.io")
set(PROJECT_HOMEPAGE_URL        "https://${PROJECT_ORGANIZATION_URL}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_URL      "https://github.com/${PROJECT_ORGANIZATION_NAME}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_I18N_URL "https://github.com/${PROJECT_ORGANIZATION_NAME}-i18n/${PROJECT_ID}")
set(PROJECT_REPOSITORY_BRANCH   "master")
set(PROJECT_SPDX_ID             "BSD-3-Clause-Clear")
set(PROJECT_TRANSLATIONS_DIR    "resources/translations")
set(PROJECT_ICON_FORMAT         "svg")

# Appstream
if(PROJECT_USE_APPSTREAM)
    include(AppStream)
    to_appstream_id("io.github.${PROJECT_ORGANIZATION_NAME}.${PROJECT_NAME}" PROJECT_APPSTREAM_ID)
else()
    set(PROJECT_APPSTREAM_ID "${PROJECT_ID}")
endif()
set(PROJECT_APPSTREAM_SPDX_ID "FSFAP")

# Icon filename
if(UNIX AND NOT APPLE)
    set(PROJECT_ICON_FILE_NAME "${PROJECT_APPSTREAM_ID}.${PROJECT_ICON_FORMAT}")
elseif(APPLE)
    # TODO: macOS and Windows
else()
endif()

# Adapt to CMake variables
set(${PROJECT_NAME}_DESCRIPTION  "${PROJECT_DESCRIPTION}")
set(${PROJECT_NAME}_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
