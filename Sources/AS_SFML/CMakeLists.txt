set(HEADERS
	Common.hpp
	Internal.hpp
)

set(SOURCES
	Color.cpp
	Common.cpp
	Joystick.cpp
	Keyboard.cpp
	Mouse.cpp
	Music.cpp
	RenderTarget.cpp
	Shader.cpp
	Shape.cpp
	Sound.cpp
	Sprite.cpp
	Text.cpp
	Texture.cpp
	View.cpp
)

source_group("Header Files\\" FILES ${HEADERS})
source_group("Source Files\\" FILES ${HEADERS})

add_library(AS_SFML STATIC ${HEADERS} ${SOURCES})
