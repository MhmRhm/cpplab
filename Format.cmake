function(Format directory)
	find_program(
		CLANG-FORMAT_PATH clang-format REQUIRED
		PATHS "${CLANG-FORMAT_INSTALL_DIR}"
	)

	set(EXPRESSION h hpp hh c cc cxx cpp cppm)
	list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
	file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
		LIST_DIRECTORIES false ${EXPRESSION}
	)

	add_custom_target(format
		COMMAND ${CLANG-FORMAT_PATH} -i --style=file ${SOURCE_FILES}
	)
endfunction()
