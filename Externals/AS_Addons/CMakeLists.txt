SET(PWD ${CMAKE_CURRENT_SOURCE_DIR})
SET(Angelscript_SOURCES
	${PWD}/debugger/debugger.cpp
	${PWD}/scriptarray/scriptarray.cpp
	${PWD}/scriptbuilder/scriptbuilder.cpp
	${PWD}/scriptdictionary/scriptdictionary.cpp
	${PWD}/scripthelper/scripthelper.cpp
	${PWD}/scriptmath/scriptmath.cpp
	${PWD}/scriptmath/scriptmathcomplex.cpp
	${PWD}/scriptstdstring/scriptstdstring.cpp
	${PWD}/scriptstdstring/scriptstdstring_utils.cpp
	${PWD}/serializer/serializer.cpp
PARENT_SCOPE )
