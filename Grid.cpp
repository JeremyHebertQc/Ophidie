#include "Grid.h"

Grid::Grid() {
	board.reserve(10);
	for (std::vector<int> &temp : board) {
		temp.reserve(10);
	}
}

Grid::~Grid() {
}

void Grid::handleCollision(TileType type) {
}
