set(curr_lib_name jpp)

set(currsources
	libs/jpp/Jpp.h
)

set(source_files ${source_files} ${currsources})

source_group(libs\\${curr_lib_name} FILES ${currsources})