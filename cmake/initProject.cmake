set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
elseif(UNIX)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif()

function(setup_project_vars)
	if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		set(TARGET_PLATFORM "win32" PARENT_SCOPE)
		if(CMAKE_GENERATOR_PLATFORM STREQUAL "x64")
		    set(TARGET_ARCH "x64" PARENT_SCOPE)
		    set(TARGET_XARCH "x64" PARENT_SCOPE)
		elseif(CMAKE_GENERATOR_PLATFORM STREQUAL "win32")
			set(TARGET_ARCH "ia32" PARENT_SCOPE)
			set(TARGET_XARCH "x86" PARENT_SCOPE)
		endif()
	elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set(TARGET_PLATFORM "linux" PARENT_SCOPE)
		if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
			set(TARGET_ARCH "x64" PARENT_SCOPE)
		elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
			set(TARGET_ARCH "arm64" PARENT_SCOPE)
		endif()
	endif()

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(TARGET_BUILD_TYPE "Debug" PARENT_SCOPE)
	else()
		set(TARGET_BUILD_TYPE "Release" PARENT_SCOPE)
	endif()
endfunction()

if(WIN32)
	add_compile_options(/utf-8)
	add_compile_definitions(UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS)

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
	else()
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
	endif()
elseif(UNIX)
	add_compile_options(-Wall -Wextra)
	add_link_options(-static-libgcc -static-libstdc++)
endif()
