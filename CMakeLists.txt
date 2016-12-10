cmake_minimum_required(VERSION 3.4)

if (WIN32)
	message("Detected Windows")
	include(cmake/WinMakeLists.txt)
elseif(UNIX)
	message("Detected Linux")
	include(cmake/LinMakeLists.txt)
endif()
