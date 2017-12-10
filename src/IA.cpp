#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include "IA.h"

Gomoku::IA::IA() {
	std::srand(static_cast<unsigned int>(std::time(0)));
}

Gomoku::IA::~IA() {}

bool	Gomoku::IA::isGameFinished(std::pair<int, int> const & lastPos, std::vector<std::vector<Tile>> const & tmpBoard, int turn) {
	int					row = 1;
	std::pair<int, int> tmp = lastPos;
	Tile				check = turn == 1 ? Tile::OWN : Tile::OPPONENT;
	int					size = static_cast<int>(tmpBoard.size());

	while (--tmp.first >= 0 && --tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	tmp = lastPos;
	while (++tmp.first < size && ++tmp.second < size && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	row = 1;
	tmp = lastPos;
	while (--tmp.first >= 0 && ++tmp.second < size && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	tmp = lastPos;
	while (++tmp.first < size && --tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	row = 1;
	tmp = lastPos;
	while (++tmp.first < size && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	tmp = lastPos;
	while (--tmp.first >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	row = 1;
	tmp = lastPos;
	while (++tmp.second < size && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	tmp = lastPos;
	while (--tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	if (row == 5)
		return (true);
	return (false);
}

int	Gomoku::IA::playGame(std::pair<int, int> const & pos, std::vector<std::vector<Tile>> tmpBoard) {
	std::pair<int, int>					lastPos = pos;
	std::vector<std::pair<int, int>>	possibleMoves;
	int									turn = 0;

	tmpBoard[pos.first][pos.second] = Tile::OWN;
	if (isGameFinished(lastPos, tmpBoard, 1))
		return (1);
	else if (isGameFinished(lastPos, tmpBoard, 0))
		return (1);

	while (!isGameFinished(lastPos, tmpBoard, turn))
	{
		possibleMoves = this->checkPossibleMoves(tmpBoard);
		if (possibleMoves.size() == 0)
			return (0);
		lastPos = possibleMoves[std::rand() % possibleMoves.size()];
		tmpBoard[lastPos.first][lastPos.second] = turn == 1 ? Tile::OPPONENT : Tile::OWN;
		turn = (turn + 1) % 2;
	}
	return (turn);
}

std::string Gomoku::IA::makeDecision(std::vector<std::vector<Tile>>& board) {
	std::vector<std::pair<int, int>>	possibleMoves;
	std::pair<int, int>					bestMove;
	int									maxWin = 0;
	int									tmp = 0;
	int									size;

	possibleMoves = this->checkPossibleMoves(board);
	if (possibleMoves.size() == 0)
	{
		board[board.size() / 2][board.size() / 2] = Tile::OWN;
		return (std::string(std::to_string(board.size() / 2) + ',' + std::to_string(board.size() / 2)));
	}
	size = static_cast<int>(possibleMoves.size());
	for (int i = 0; i < size; ++i)
	{
		tmp = 0;
		for (int j = 0; j < 4500 / size; ++j)
		{
			tmp += playGame(possibleMoves[i], board);
		}
		if (tmp >= maxWin)
		{
			maxWin = tmp;
			bestMove = possibleMoves[i];
		}
	}
	board[bestMove.first][bestMove.second] = Tile::OWN;
	return (std::string(std::to_string(bestMove.second) + "," + std::to_string(bestMove.first)));
}

void	Gomoku::IA::getPossibleMoves(std::vector<std::vector<Tile>> const & board,
									std::vector<std::pair<int, int>> &move, int y, int x)
{
	int									size = static_cast<int>(board.size());

	for (int i = y - 1; i < y + 2; ++i)
	{
		if (i >= 0 && i < size)
		{
			for (int j = x - 1; j < x + 2; ++j)
			{
				if (j >= 0 && j < size && board[i][j] == Tile::EMPTY &&
					std::find(move.begin(), move.end(), std::make_pair(i, j)) == move.end())
				{
					move.push_back(std::make_pair(i, j));
				}
			}
		}
	}
}

std::vector<std::pair<int, int>>	Gomoku::IA::checkPossibleMoves(std::vector<std::vector<Tile>> const & board)
{
	std::vector<std::pair<int, int>>	move;
	int									size = static_cast<int>(board.size());

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			if (board[y][x] != Tile::EMPTY)
			{
				getPossibleMoves(board, move, y, x);
			}
		}
	}
	return (move);
}