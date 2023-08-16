#
# Editable project configuration
#
# Essential, non translatable application information (except DESCRIPTION).
# Translatable strings are passed via code.
#
string(TOLOWER ${PROJECT_NAME} PROJECT_ID)
list(APPEND PROJECT_CATEGORIES "Qt;KDE;Graphics;Utility") # Freedesktop menu categories
list(APPEND PROJECT_KEYWORDS   "colorpicker;color-picker;contrast-ratio")
set(PROJECT_AUTHOR_NAME        "Andrea Zanellato")
set(PROJECT_AUTHOR_EMAIL       "redtid3@gmail.com") # Used also for organization email
set(PROJECT_COPYRIGHT_YEAR     "2023") # TODO: from git
set(PROJECT_DESCRIPTION        "Color picker and contrast checker")
set(PROJECT_ORGANIZATION_NAME  "qtilities") # Might be equal to PROJECT_AUTHOR_NAME
set(PROJECT_ORGANIZATION_URL   "${PROJECT_ORGANIZATION_NAME}.github.io")
set(PROJECT_HOMEPAGE_URL       "https://${PROJECT_ORGANIZATION_URL}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_URL     "https://github.com/${PROJECT_ORGANIZATION_NAME}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_BRANCH  "master")
set(PROJECT_SPDX_ID            "BSD-3-Clause-Clear")
set(PROJECT_TRANSLATIONS_DIR   "resources/translations")
#
# Adapt to CMake variables
#
set(${PROJECT_NAME}_DESCRIPTION  "${PROJECT_DESCRIPTION}")
set(${PROJECT_NAME}_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
