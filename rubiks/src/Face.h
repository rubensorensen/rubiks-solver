#pragma once

class Face {
	
public:
	enum class Color{yellow, blue, red, green, orange, white};
	Face(Color center);
	

private:
	Color center;
};
