#include "Cell.h"
#include "Board.h"

Cell::Cell(const Location loc)
	:
	l(loc)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			Location neighbor = Location{l.x + i, l.y + j};
			if (Board::IsValidLocation(neighbor) && !(neighbor.x == l.x && neighbor.y == l.y))
			{
				neighbors.push_back(neighbor);
			}
		}
	}
}

void Cell::MoveToNextState()
{
	alive = nextState;
	nextState = false;
}

void Cell::Update(const std::vector<std::vector<Cell>>& cells)
{
	int neighborsAlive = 0;
	for (int i = 0; i < int(neighbors.size()); i++)
	{
		Location& neighbor = neighbors[i];
		if (cells[neighbor.y][neighbor.x].IsAlive())
		{
			neighborsAlive++;
		}
	}

	if (!alive)
	{
		if (neighborsAlive == 3)
		{
			nextState = true;
		}
		else
		{
			nextState = false;
		}

	}
	else if (alive)
	{
		if (neighborsAlive < 2)
		{
			nextState = false;
		}
		else if (neighborsAlive > 3)
		{
			nextState = false;
		}
		else
		{
			nextState = true;
		}
	}
}

void Cell::Draw(Board & brd) const
{
	if(alive) brd.DrawCell(l);
}

bool Cell::IsAlive() const
{
	return alive;
}

void Cell::FlipState()
{
	alive = !alive;
}

void Cell::SetToDead()
{
	alive = false;
}
