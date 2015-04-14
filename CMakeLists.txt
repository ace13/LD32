cmake_minimum_required(VERSION 2.8)

project(LD32)

IF (MSVC)
	IF (${MSVC_VERSION} VERSION_LESS 11.0)
		MESSAGE(FATAL_ERROR "This project uses C++11, so you need at least Visual Studio 2012")
	ENDIF ()

	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /MP")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
	SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
ELSE () # Linux / Cygwin
	IF (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
		EXECUTE_PROCESS(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
		IF (${GCC_VERSION} VERSION_LESS 4.7)
			MESSAGE(FATAL_ERROR "This project uses C++11, so you need at least GCC 4.7 to compile this project.")
		ENDIF ()
	ELSEIF (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
		EXECUTE_PROCESS( COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE clang_full_version_string )
		STRING (REGEX REPLACE ".*clang version ([0-9]+\\.[0-9]+).*" "\\1" CLANG_VERSION_STRING ${clang_full_version_string})

		IF (${CLANG_VERSION_STRING} VERSION_LESS 3.3)
			MESSAGE(FATAL_ERROR "This project uses C++11, so you need at least Clang 3.3 to compile this project.")
		ENDIF ()

#		ADD_DEFINITIONS(-DAS_CAN_USE_CPP11 -D__GNUC_MINOR__=8) # Clang hack, makes asGetTypeTraits work
	ENDIF ()

	SET(CMAKE_CXX_FLAGS                "-Wall -Wextra -std=c++11 -pedantic")
	SET(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
	SET(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
	SET(CMAKE_CXX_FLAGS_RELEASE        "-Ofast -DNDEBUG")
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
ENDIF ()

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

SET(CMAKE_DEBUG_POSTFIX "d")
SET(CMAKE_MINSIZEREL_POSTFIX "s")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
SET(OUTPUT_BINDIR ${PROJECT_BINARY_DIR}/bin)
FILE(MAKE_DIRECTORY ${OUTPUT_BINDIR})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
FOREACH(CONF ${CMAKE_CONFIGURATION_TYPES})
	STRING(TOUPPER "${CONF}" CONF)
	SET("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}")
ENDFOREACH()

if (MSVC)
	find_package(SFML 2.2 REQUIRED COMPONENTS main system window graphics audio)
else()
	find_package(SFML 2.2 REQUIRED COMPONENTS system window graphics audio)
endif()

find_package(Angelscript REQUIRED)
# find_package(AngelscriptJIT)
add_subdirectory(Externals/AS_Addons)
add_subdirectory(Externals/Kunlaboro)

include_directories(
	Sources/
	Externals/AS_Addons/
	Externals/Kunlaboro/include
	${Angelscript_INCLUDE_DIR}
	${AngelscriptJIT_INCLUDE_DIR}
	${SFML_INCLUDE_DIR}
)

add_subdirectory(Sources)

set(DATA
	Scripts
)

FILE(COPY ${DATA} DESTINATION ${OUTPUT_BINDIR})
