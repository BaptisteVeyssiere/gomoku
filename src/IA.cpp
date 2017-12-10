#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include "IA.h"

Gomoku::IA::IA() {
	std::srand(static_cast<unsigned int>(std::time(0)));
}

Gomoku::IA::~IA() {}

bool	Gomoku::IA::isGameFinished(std::pair<int, int> &lastPos, std::vector<std::vector<Tile>> &tmpBoard, int turn) {
	int	row = 1;
	std::pair<int, int> tmp = lastPos;
	Tile				check;

	std::cout << "1" << std::endl;
	check = Tile::OPPONENT;
	if (turn == 1)
		check = Tile::OWN;
	std::cout << "first = " << tmp.first << " second = " << tmp.second << std::endl;
	while (--tmp.first >= 0 && --tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	std::cout << "2" << std::endl;
	if (row == 5)
		return (true);
	std::cout << "3" << std::endl;
	std::cout << "first = " << tmp.first << " second = " << tmp.second << std::endl;
	tmp = lastPos;
	while (++tmp.first < static_cast<int>(tmpBoard.size()) && ++tmp.second < static_cast<int>(tmpBoard.size()) && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	std::cout << "4" << std::endl;
	if (row == 5)
		return (true);
	std::cout << "5" << std::endl;
	std::cout << "first = " << tmp.first << " second = " << tmp.second << std::endl;
	row = 1;
	tmp = lastPos;
	while (--tmp.first >= 0 && ++tmp.second < static_cast<int>(tmpBoard.size()) && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	std::cout << "6" << std::endl;
	if (row == 5)
		return (true);
	std::cout << "7" << std::endl;
	std::cout << "first = " << tmp.first << " second = " << tmp.second << std::endl;
	tmp = lastPos;
	while (++tmp.first < static_cast<int>(tmpBoard.size()) && --tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	std::cout << "8" << std::endl;
	if (row == 5)
		return (true);
	std::cout << "9" << std::endl;
	std::cout << "first = " << tmp.first << " second = " << tmp.second << std::endl;
	row = 1;
	tmp = lastPos;
	while (++tmp.first < static_cast<int>(tmpBoard.size()) && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	std::cout << "10" << std::endl;
	if (row == 5)
		return (true);
	std::cout << "11" << std::endl;
	std::cout << "first = " << tmp.first << " second = " << tmp.second << std::endl;
	tmp = lastPos;
	while (--tmp.first >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	std::cout << "12" << std::endl;
	if (row == 5)
		return (true);
	std::cout << "13" << std::endl;
	std::cout << "first = " << tmp.first << " second = " << tmp.second << std::endl;
	row = 1;
	tmp = lastPos;
	while (++tmp.second < static_cast<int>(tmpBoard.size()) && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	std::cout << "14" << std::endl;
	if (row == 5)
		return (true);
	std::cout << "15" << std::endl;
	std::cout << "first = " << tmp.first << " second = " << tmp.second << std::endl;
	tmp = lastPos;
	while (--tmp.second >= 0 && tmpBoard[tmp.first][tmp.second] == check && ++row < 5);
	std::cout << "16" << std::endl;
	if (row == 5)
		return (true);
	std::cout << "17" << std::endl;
	return (false);
}

int	Gomoku::IA::playGame(std::pair<int, int> pos, std::vector<std::vector<Tile>> tmpBoard) {
	std::pair<int, int>	lastPos = pos;
	std::vector<std::pair<int, int>>	possibleMoves;
	int					turn = 0;

	tmpBoard[pos.first][pos.second] = Tile::OWN;

	while (!isGameFinished(lastPos, tmpBoard, turn))
	{
		//std::cout << "first : " << lastPos.first << " second : " << lastPos.second << std::endl;
		possibleMoves = this->checkPossibleMoves(tmpBoard);
		if (possibleMoves.size() == 0)
			return (0);
		lastPos = possibleMoves[std::rand() % possibleMoves.size()];
		if (turn == 0) {
			turn = 1;
			tmpBoard[lastPos.first][lastPos.second] = Tile::OWN;
		}
		else {
			turn = 0;
			tmpBoard[lastPos.first][lastPos.second] = Tile::OPPONENT;
		}
	}
	return (turn);
}

std::string Gomoku::IA::makeDecision(std::vector<std::vector<Tile>>& board) {
	std::vector<std::pair<int, int>>	possibleMoves;
	std::pair<int, int>					bestMove;
	int									maxWin = 0;
	int									tmp = 0;

	possibleMoves = this->checkPossibleMoves(board);
	if (possibleMoves.size() == 0)
	{
		board[5][5] = Tile::OWN;
		return (std::string("5,5"));
	}
	for (int i = 0; i < static_cast<int>(possibleMoves.size()); ++i)
	{
		std::cout << i << " in " << possibleMoves.size() << std::endl;
		tmp = 0;
		for (int j = 0; j < 500; ++j)
		{
			tmp += playGame(possibleMoves[i], board);
		}
		if (tmp >= maxWin)
		{
			maxWin = tmp;
			bestMove = possibleMoves[i];
		}
	}
	return (std::string(std::to_string(bestMove.first) + "," + std::to_string(bestMove.second)));
}

void	Gomoku::IA::getPossibleMoves(std::vector<std::vector<Tile>> const & board,
									std::vector<std::pair<int, int>> &move, int y, int x)
{
	for (int i = y - 1; i < y + 2; i++)
	{
		if (i >= 0 && i < static_cast<int>(board.size()))
		{
			for (int j = x - 1; j < x + 2; j++)
			{
				if (j >= 0 && j < static_cast<int>(board[i].size()) && board[i][j] == Tile::EMPTY &&
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
	std::vector<std::pair<int, int>> move;
	for (int y = 0; y < static_cast<int>(board.size()); y++)
	{
		for (int x = 0; x < static_cast<int>(board[y].size()); x++)
		{
			if (board[y][x] != Tile::EMPTY)
			{
				getPossibleMoves(board, move, y, x);
			}
		}
	}
	return (move);
}