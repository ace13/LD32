include(FindPackageHandleStandardArgs)

FIND_PATH(AngelscriptJIT_DIR as_jit.h)
SET(AngelscriptJIT_INCLUDE_DIR "" )
SET(AngelscriptJIT_SOURCES "" )

if (AngelscriptJIT_DIR)
  SET(AngelscriptJIT_SOURCES
    ${AngelscriptJIT_DIR}/as_jit.cpp
  )
  IF (WIN32)
    SET(AngelscriptJIT_SOURCES ${AngelscriptJIT_SOURCES} ${AngelscriptJIT_DIR}/virtual_asm_windows.cpp)
  ELSE()
    SET(AngelscriptJIT_SOURCES ${AngelscriptJIT_SOURCES} ${AngelscriptJIT_DIR}/virtual_asm_linux.cpp)
  ENDIF()
  IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(AngelscriptJIT_SOURCES ${AngelscriptJIT_SOURCES} ${AngelscriptJIT_DIR}/virtual_asm_x64.cpp)
  ELSE()
    SET(AngelscriptJIT_SOURCES ${AngelscriptJIT_SOURCES} ${AngelscriptJIT_DIR}/virtual_asm_x86.cpp)
  ENDIF()

  SET(AngelscriptJIT_INCLUDE_DIR ${AngelscriptJIT_DIR})
endif()


find_package_handle_standard_args(AngelscriptJIT DEFAULT_MSG
                                  AngelscriptJIT_DIR AngelscriptJIT_SOURCES)

MARK_AS_ADVANCED(
  AngelscriptJIT_DIR
  AngelscriptJIT_SOURCES
)
