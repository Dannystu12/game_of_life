#include "Board.h"

Board::Board(Graphics & gfx_in)
	: gfx(gfx_in)
{
}

void Board::DrawCell(Location l)
{
	if(IsValidLocation(l))
		gfx.DrawRect(xPadding + l.x * dimension, yPadding + l.y * dimension, dimension, dimension, c);
}

void Board::DrawBoard()
{
	for (int i = 0; i <= width; i++)
	{
		for (int j = 0; j < height * dimension; j++)
		{
			gfx.PutPixel(xPadding + i * dimension, yPadding + j, bc);
		}
	}

	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j < width * dimension; j++)
		{
			gfx.PutPixel(xPadding + j , yPadding + i * dimension, bc);
		}
	}
}

bool Board::IsValidLocation(Location l) 
{
	return l.x >= 0
		&& l.x < width
		&& l.y >= 0
		&& l.y < height;
}

Location Board::ConvertCoordToLocation(int x, int y)
{
	int x_loc = (x - xPadding) / dimension;
	int y_loc = (y - yPadding) / dimension;
	return Location{x_loc, y_loc};
}
