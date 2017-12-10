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


bool	Gomoku::IA::checkHorizontal(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x) {
	int					nbr = 1;
	int					horizontal[4][2] = {
		{ 0, 1 },
		{ 0, 2 },
		{ 0, 3 },
		{ 0, 4 }
	};

	for (int i = 0; i < 4 && x + horizontal[0][i] < board.size(); ++i) {
		if (board[y][x + horizontal[i][1]] == Tile::OPPONENT)
			++nbr;
		else if (board[y][x + horizontal[i][1]] == Tile::OWN)
			return (false);
	}
	if (nbr == 3) {
		for (int i = 0; i < 4 && x + horizontal[0][i] < board.size(); ++i)
			if (board[y][x + horizontal[i][1]] == Tile::EMPTY) {
				bestMove.first = y;
				bestMove.second = x + horizontal[i][1];
				return (true);
			}
	}
	return (false);
}

bool	Gomoku::IA::checkVertical(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x) {
	int					nbr = 1;
	int					vertical[4][2] = {
		{ 1, 0 },
		{ 2, 0 },
		{ 3, 0 },
		{ 4, 0 }
	};

	for (int i = 0; i < 4 && y + vertical[i][0] < board.size(); ++i) {
		if (board[y + vertical[i][0]][x] == Tile::OPPONENT)
			++nbr;
		else if (board[y + vertical[i][0]][x] == Tile::OWN)
			return (false);
	}
	if (nbr == 3) {
		for (int i = 0; i < 4 && y + vertical[i][0] < board.size(); ++i)
			if (board[y + vertical[i][0]][x] == Tile::EMPTY) {
				bestMove.first = y + vertical[i][0];
				bestMove.second = x;
				return (true);
			}
	}
	return (false);
}

bool	Gomoku::IA::checkDiagRight(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x) {
	int					nbr = 1;
	int					diagRight[4][2] = {
		{ 1, 1 },
		{ 2, 2 },
		{ 3, 3 },
		{ 4, 4 }
	};

	for (int i = 0; i < 4 && y + diagRight[i][0] < board.size() && x + diagRight[i][1] < board.size(); ++i) {
		if (board[y + diagRight[i][0]][x + diagRight[i][1]] == Tile::OPPONENT)
			++nbr;
		else if (board[y + diagRight[i][0]][x + diagRight[i][1]] == Tile::OWN)
			return (false);
	}
	if (nbr == 3) {
		for (int i = 0; i < 4 && y + diagRight[i][0] && x + diagRight[i][1] < board.size(); ++i)
			if (board[y + diagRight[i][0]][x + diagRight[i][1]] == Tile::EMPTY) {
				bestMove.first = y + diagRight[i][0];
				bestMove.second = x + diagRight[i][1];
				return (true);
			}
	}
	return (false);
}

bool	Gomoku::IA::checkDiagLeft(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x) {
	int					nbr = 1;
	int					diagLeft[4][2] = {
		{ 1, -1 },
		{ 2, -2 },
		{ 3, -3 },
		{ 4, -4 }
	};

	for (int i = 0; i < 4 && y + diagLeft[i][0] < board.size() && x + diagLeft[i][1] >= 0; ++i) {
		if (board[y + diagLeft[i][0]][x + diagLeft[i][1]] == Tile::OPPONENT)
			++nbr;
		else if (board[y + diagLeft[i][0]][x + diagLeft[i][1]] == Tile::OWN)
			return (false);
	}
	if (nbr == 3) {
		for (int i = 0; i < 4 && y + diagLeft[i][0] && x + diagLeft[i][1] >= 0; ++i)
			if (board[y + diagLeft[i][0]][x + diagLeft[i][1]] == Tile::EMPTY) {
				bestMove.first = y + diagLeft[i][0];
				bestMove.second = x + diagLeft[i][1];
				return (true);
			}
	}
	return (false);
}

bool	Gomoku::IA::checkDangerousMove(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x) {
	if (checkHorizontal(board, bestMove, y, x) ||
		checkVertical(board, bestMove, y, x) ||
		checkDiagRight(board, bestMove, y, x) ||
		checkDiagLeft(board, bestMove, y, x))
		return (true);
	return (false);
}

bool	Gomoku::IA::cutDangerousMove(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove) {
	for (int y = 0; y < board.size(); ++y) {
		for (int x = 0; x < board.size(); ++x) {
			if (board[y][x] == Tile::OPPONENT && checkDangerousMove(board, bestMove, y, x))
				return (true);
		}
	}
	return (false);
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
	if (cutDangerousMove(board, bestMove))
	{
		board[bestMove.first][bestMove.second] = Tile::OWN;
		return (std::string(std::to_string(bestMove.second) + "," + std::to_string(bestMove.first)));
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