set(HEADERS
	GameClass.hpp

	Game/Camera.hpp
	Game/ScriptMan.hpp
	Game/ScriptObj.hpp

	Math/Common.hpp
	Math/Common.inl
	Math/Eases.hpp
	Math/Eases.inl
	Math/Rect.hpp
	Math/Spinor.hpp
	Math/Vec2.hpp

	Util/DateTime.hpp
	Util/DefaultFont.hpp
	Util/Time.hpp
)

set(SOURCES
	GameClass.cpp

	Game/Camera.cpp
	Game/ScriptMan.cpp
	Game/ScriptObj.cpp

	Math/Common.cpp
	Math/Rect.cpp
	Math/Spinor.cpp
	Math/Vec2.cpp

	Util/DateTime.cpp
	Util/DefaultFont.cpp
	Util/Time.cpp

	${Angelscript_SOURCES}
	${AngelscriptJIT_SOURCES}
)

source_group("Header Files\\Game" REGULAR_EXPRESSION "Game/[^./]+\\.(hpp|inl)")
source_group("Source Files\\Game" REGULAR_EXPRESSION "Game/[^./]+\\.cpp")
source_group("Header Files\\Math" REGULAR_EXPRESSION "Math/[^./]+\\.(hpp|inl)")
source_group("Source Files\\Math" REGULAR_EXPRESSION "Math/[^./]+\\.cpp")
source_group("Header Files\\Util" REGULAR_EXPRESSION "Util/[^./]+\\.(hpp|inl)")
source_group("Source Files\\Util" REGULAR_EXPRESSION "Util/[^./]+\\.cpp")
source_group("Source Files\\Script" FILES ${Angelscript_SOURCES})
source_group("Source Files\\Script\\JIT" FILES ${AngelscriptJIT_SOURCES})

add_library(LD32_Core STATIC ${HEADERS} ${SOURCES})

add_subdirectory(AS_SFML)
add_subdirectory(Warmup)
