#pragma once
#include "Board.h"
#include "Location.h"
#include <vector>

class Cell
{
public:
	Cell(const Location loc);
	void MoveToNextState();
	void Update(const std::vector<std::vector<Cell>>& cells);
	void Draw(Board & brd) const;
	bool IsAlive() const;
	void FlipState();
	void SetToDead();
private:
	const Location l;
	bool alive = false;
	bool nextState = false;
	std::vector<Location> neighbors;
};