function(Format target directory)
    find_program(CLANG-FORMAT_PATH clang-format-17
        PATHS "${CLANG-FORMAT_INSTALL_DIR}")
    if(NOT "${CLANG-FORMAT_INSTALL_DIR}")
        find_program(CLANG-FORMAT_PATH clang-format REQUIRED
            PATHS "${CLANG-FORMAT_INSTALL_DIR}")
    endif()

    set(EXPRESSION h hpp hh c cc cxx cpp cppm)
    list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
    file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
        LIST_DIRECTORIES false ${EXPRESSION}
    )
    add_custom_command(TARGET ${target} PRE_BUILD 
        COMMAND ${CLANG-FORMAT_PATH} -i --style=file ${SOURCE_FILES}
    )
endfunction()
