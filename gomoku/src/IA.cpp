#include <iostream>
#include <string>
#include "IA.h"

Gomoku::IA::IA() {}

Gomoku::IA::~IA() {}

bool	Gomoku::IA::isMovePossible(std::vector<std::vector<Tile>> const & board, unsigned int const x, unsigned int const y) {
	if (x > 0) {
		if (board[y][x - 1] != Tile::EMPTY)
			return (true);
		if (y > 0 && board[y - 1][x - 1] != Tile::EMPTY)
			return (true);
		if (y < (board.size() - 1) && board[y + 1][x - 1] != Tile::EMPTY)
			return (true);
	}
	if (x < (board.size() - 1)) {
		if (board[y][x + 1] != Tile::EMPTY)
			return (true);
		if (y > 0 && board[y - 1][x + 1] != Tile::EMPTY)
			return (true);
		if (y < (board.size() - 1) && board[y + 1][x + 1] != Tile::EMPTY)
			return (true);
	}
	if (y > 0 && board[y - 1][x] != Tile::EMPTY)
		return (true);
	if (y < (board.size() - 1) && board[y + 1][x] != Tile::EMPTY)
		return (true);
	return (false);
}

std::string	Gomoku::IA::turn(std::vector<std::vector<Tile>> & board) {
	bool		begin = true;

	for (unsigned int y = 0; y < board.size(); ++y) {
		for (unsigned int x = 0; x < board.size(); ++x) {
			if (board[y][x] == Tile::EMPTY && this->isMovePossible(board, x, y)) {
				board[y][x] = Tile::OWN;
				return (std::to_string(x) + "," + std::to_string(y));
			}
			else if (board[y][x] != Tile::EMPTY) {
				begin = false;
			}
		}
	}
	if (begin == true) {
		board[board.size() / 2][board.size() / 2] = Tile::OWN;
		return (std::to_string(board.size() / 2) + "," + std::to_string(board.size() / 2));
	}
	throw std::runtime_error("Impossible to play");
}