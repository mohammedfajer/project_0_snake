#pragma once

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 700;

#define GRID_WIDTH SCR_WIDTH/50 
#define GRID_HEIGHT SCR_HEIGHT/50

enum class SNAKE_DIRECTION : unsigned int {
	LEFT	= 0,
	RIGHT	= 1,
	UP		= 2,
	DOWN	= 3,
	STILL   = 4
};
