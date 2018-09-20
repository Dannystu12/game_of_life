#pragma once
#include "Graphics.h"
#include "Colors.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx_in);
	void DrawCell(Location l);
	void DrawBoard();
	static bool IsValidLocation(Location l);
	static Location ConvertCoordToLocation(int x, int y);
	static constexpr int width = 38;
	static constexpr int height = 38;
private:
	Graphics& gfx;
	static constexpr int dimension = 15;
	static constexpr Color c = Colors::White;
	static constexpr Color bc = Color(60, 60, 60);
	static const int xPadding = Graphics::ScreenWidth / 2 - width/2 * dimension;
	static const int yPadding = Graphics::ScreenHeight / 2 - height / 2 * dimension;
};