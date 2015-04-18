set(HEADERS
	Gameplay/Character.hpp
	Gameplay/Enemy.hpp
	Gameplay/FallacyTime.hpp
	Gameplay/GameState.hpp
	Gameplay/NameGen.hpp

	Menu.hpp
	Resources.hpp
)
set(SOURCES
	Gameplay/Character.cpp
	Gameplay/Enemy.cpp
	Gameplay/FallacyTime.cpp
	Gameplay/GameState.cpp
	Gameplay/NameGen.cpp

	Menu.cpp
	Resources.cpp

	main.cpp
)

source_group("Header Files\\Gameplay" REGULAR_EXPRESSION "Gameplay/[^./]+\\.(hpp|inl)")
source_group("Source Files\\Gameplay" REGULAR_EXPRESSION "Gameplay/[^./]+\\.cpp")

add_executable(LD32_Game ${HEADERS} ${SOURCES})
target_link_libraries(LD32_Game
	LD32_Core
	AS_SFML
	Kunlaboro

	${Angelscript_LIBRARIES}
	${Fontconfig_LIBRARIES}
	${SFML_LIBRARIES}
)

IF(WIN32)
	SET_TARGET_PROPERTIES(LD32_Game PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE /ignore:4099")
	SET_TARGET_PROPERTIES(LD32_Game PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
	SET_TARGET_PROPERTIES(LD32_Game PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE /ignore:4099")
	SET_TARGET_PROPERTIES(LD32_Game PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
	SET_TARGET_PROPERTIES(LD32_Game PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	SET_TARGET_PROPERTIES(LD32_Game PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
ENDIF(WIN32)
