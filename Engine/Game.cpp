/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Location.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx)
{
	for (int i = 0; i < Board::height; i++)
	{
		std::vector<Cell> row;
		for (int j = 0; j < Board::width; j++)
		{
			Cell cell(Location{ j, i });
			row.push_back(cell);
		}
		cells.push_back(row);
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (hasStarted)
	{
		float dt = ft.Mark();
		if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		{
			Reset();
			return;
		}
		stateCounter += dt;
		if (stateCounter >= nextStatePeriod)
		{
			stateCounter -= nextStatePeriod;
			for (int i = 0; i < cells.size(); i++)
			{
				for (int j = 0; j < cells[0].size(); j++)
				{
					cells[i][j].Update(cells);
				}
			}
			for (int i = 0; i < cells.size(); i++)
			{
				for (int j = 0; j < cells[0].size(); j++)
				{
					cells[i][j].MoveToNextState();
				}
			}
			stateCounter = 0;
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			hasStarted = true;
			ft = FrameTimer();
		} 
		

		if (wnd.mouse.LeftIsPressed() && !lmPressed)
		{
			Location mouseLoc = brd.ConvertCoordToLocation(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
			if (Board::IsValidLocation(mouseLoc))
			{
				cells[mouseLoc.y][mouseLoc.x].FlipState();
			}
			lmPressed = true;
		}
		else if(!wnd.mouse.LeftIsPressed())
		{
			lmPressed = false;
		}

	}
}

void Game::Reset()
{
	hasStarted = false;
	for (int i = 0; i < cells.size(); i++)
	{
		for (int j = 0; j < cells[0].size(); j++)
		{
			cells[i][j].SetToDead();
			stateCounter = 0;
		}
	}
}

void Game::ComposeFrame()
{
	brd.DrawBoard();
	for (int i = 0; i < cells.size(); i++)
	{
		for (int j = 0; j < cells[0].size(); j++)
		{
			cells[i][j].Draw(brd);
		}
	}

}
