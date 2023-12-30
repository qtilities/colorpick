find_package(Git REQUIRED)
function(git_download_translations repo destdir)
    if(NOT EXISTS "${destdir}/translations")
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/i18n")
        execute_process(COMMAND ${GIT_EXECUTABLE} clone ${repo}
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/i18n"
            COMMAND_ERROR_IS_FATAL ANY
        )
        file(COPY "${CMAKE_CURRENT_BINARY_DIR}/i18n/${PROJECT_ID}/translations" DESTINATION ${destdir})
        file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/i18n")
    endif()
endfunction()
