#Sourced files should use add_sub for a separate project
add_subdirectory(libs/googletest/ googletest)
include(libs/jpp/CMakeLists.txt)

set(additional_libs
	${additional_libs}
	googletest
)

set(additional_includes
	${additional_includes}
	libs/
)

set(linker_includes
	${linker_includes}
	googletest
)