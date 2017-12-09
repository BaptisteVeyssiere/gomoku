#include <iostream>
#include <string>
#include "IA.h"

Gomoku::IA::IA() {
	std::srand(time(0));
}

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

bool	Gomoku::IA::isGameFinished(std::pair<int, int> &lastPos, std::vector<std::vector<Tile>> &tmpBoard, int turn) {
	int	row = 1;
	std::pair<int, int> tmp = lastPos;
	Tile				check;

	check = Tile::OPPONENT;
	if (turn == 1)
		check = Tile::OWN;
	while (--tmp.first >= 0 && --tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	tmp = lastPos;
	while (++tmp.first < tmpBoard.size() && ++tmp.second < tmpBoard.size() && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	row = 1;
	while (--tmp.first >= 0 && ++tmp.second < tmpBoard.size() && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	while (++tmp.first < tmpBoard.size() && --tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	row = 1;
	while (++tmp.first < tmpBoard.size() && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	while (--tmp.first >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	row = 1;
	while (++tmp.second < tmpBoard.size() && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	while (--tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	return (false);
}

int	Gomoku::IA::playGame(std::pair<int, int> pos, std::vector<std::vector<Tile>> tmpBoard) {
	std::pair<int, int>	lastPos = pos;
	std::vector<std::pair<int, int>>	possibleMoves;
	int					turn = 0;

	tmpBoard[pos.first][pos.second] = Tile::OWN;

	while (!isGameFinished(lastPos, tmpBoard, turn))
	{
		possibleMoves = this->checkPossibleMoves();
		lastPos = possibleMoves[std::rand() % possibleMoves.size()];
		if (turn == 0) {
			turn = 1;
			tmpBoard[pos.first][pos.second] = Tile::OWN;
		}
		else {
			turn = 0;
			tmpBoard[pos.first][pos.second] = Tile::OPPONENT;
		}
	}
	return (turn);
}

std::string Gomoku::IA::makeDecision(std::vector<std::vector<Tile>> const & board) {
	std::vector<std::pair<int, int>>	possibleMoves;
	std::pair<int, int>					bestMove;
	int									maxWin = 0;
	int									tmp = 0;

	possibleMoves = this->checkPossibleMoves();
	for (int i = 0; i < possibleMoves.size(); ++i)
	{
		tmp = 0;
		for (int j = 0; j < 1500; ++j)
		{
			tmp += playGame(possibleMoves[i], board);
		}
		if (tmp > maxWin)
		{
			maxWin = tmp;
			bestMove = possibleMoves[i];
		}
	}
	return (std::string(std::to_string(bestMove.first) + "," + std::to_string(bestMove.second)));
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