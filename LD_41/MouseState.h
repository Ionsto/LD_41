#pragma once
#include "KeyState.h"
#include <Box2D\Common\b2Math.h>
class MouseState
{
public:
	ButtonState Left;
	ButtonState Right;
	b2Vec2 Location;
	MouseState();
	~MouseState();
	void Update();
};