#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include "IA.h"

Gomoku::IA::IA() {
	std::srand(static_cast<unsigned int>(std::time(0)));
}

Gomoku::IA::~IA() {}

bool	Gomoku::IA::isGameFinished(std::pair<int, int> const & lastPos) {
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

void	Gomoku::IA::getPossibleMoves(std::vector<Gomoku::ScoredPosition> &move, int y, int x)
{
	int	size = static_cast<int>(this->tmpBoard.size());

	for (int i = y - 1; i < y + 2; ++i)
	{
		if (i >= 0 && i < size)
		{
			for (int j = x - 1; j < x + 2; ++j)
			{
				if (j >= 0 && j < size && this->tmpBoard[i][j] == Tile::EMPTY &&
					std::find(move.begin(), move.end(), std::make_pair(0, std::make_pair(i, j))) == move.end())
				{
					move.push_back(std::make_pair(0, std::make_pair(i, j)));
				}
			}
		}
	}
}

std::vector<Gomoku::ScoredPosition>	Gomoku::IA::checkPossibleMoves()
{
	std::vector<ScoredPosition>	move;
	int							size = static_cast<int>(this->tmpBoard.size());

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			if (tmpBoard[y][x] != Tile::EMPTY)
			{
				getPossibleMoves(move, y, x);
			}
		}
	}
	return (move);
}

double	Gomoku::IA::evaluate() {
	std::vector<int>	counts = this->countPossibilities(Tile::OWN);
	std::vector<int>	opponent = this->countPossibilities(Tile::OPPONENT);
	double				score;

	score = counts[0] * 100 + counts[1] * 5 + counts[2] * 1;
	score -= counts[0] * 50;
	return (score);
}

void				Gomoku::IA::getHorizontalPossibilities(Tile const & player, std::vector<int> & count, std::pair<int, int> const & pos)
{
	int					sizeX = static_cast<int>(this->tmpBoard[0].size());
	int y = pos.first;
	int x = pos.second;
	int lVoid = 0;
	int lFill = 0;
	int sVoid = 0;

	while (x >= 0 && x >= pos.second - 4)
	{
		if (this->tmpBoard[y][x] == player)
			++lFill;
		else if (this->tmpBoard[y][x] == Tile::EMPTY)
			++lVoid;
		else
			break;
		--x;
	}
	x = pos.second;
	while (x < sizeX && x <= pos.second + 4 && this->tmpBoard[y][x] == Tile::EMPTY)
	{
		++sVoid;
		++x;
	}
	if (lFill >= 2 && sVoid + lVoid + lFill >= 5)
	{
		sVoid = 5 - lFill;
		if (sVoid == 1)
			++count[0];
		else if (sVoid == 2)
			++count[1];
		else
			++count[2];
	}
}

void				Gomoku::IA::getVerticalPossibilities(Tile const & player, std::vector<int> & count, std::pair<int, int> const & pos)
{
	int					sizeY = static_cast<int>(this->tmpBoard.size());
	int y = pos.first;
	int x = pos.second;
	int uVoid = 0;
	int uFill = 0;
	int sVoid = 0;

	while (y >= 0 && y >= pos.first - 4)
	{
		if (this->tmpBoard[y][x] == player)
			++uFill;
		else if (this->tmpBoard[y][x] == Tile::EMPTY)
			++uVoid;
		else
			break;
		--y;
	}
	y = pos.first;
	while (y < sizeY && y <= pos.first + 4 && this->tmpBoard[y][x] == Tile::EMPTY)
	{
		++sVoid;
		++y;
	}
	if (uFill >= 2 && sVoid + uVoid + uFill >= 5)
	{
		sVoid = 5 - uFill;
		if (sVoid == 1)
			++count[0];
		else if (sVoid == 2)
			++count[1];
		else
			++count[2];
	}
}

void				Gomoku::IA::getDiagLPossibilities(Tile const & player, std::vector<int> & count, std::pair<int, int> const & pos)
{
	int	sizeY = static_cast<int>(this->tmpBoard.size());
	int	sizeX = static_cast<int>(this->tmpBoard[0].size());
	int y = pos.first;
	int x = pos.second;
	int dVoid = 0;
	int dFill = 0;
	int sVoid = 0;

	while (y >= 0 && y >= pos.first - 4 && x >= 0 && x >= pos.second - 4)
	{
		if (this->tmpBoard[y][x] == player)
			++dFill;
		else if (this->tmpBoard[y][x] == Tile::EMPTY)
			++dVoid;
		else
			break;
		--y;
		--x;
	}
	y = pos.first;
	x = pos.second;
	while (y < sizeY && y <= pos.first + 4 && x < sizeX && x <= pos.second + 4 && this->tmpBoard[y][x] == Tile::EMPTY)
	{
		++sVoid;
		++y;
		++x;
	}
	if (dFill >= 2 && sVoid + dVoid + dFill >= 5)
	{
		sVoid = 5 - dFill;
		if (sVoid == 1)
			++count[0];
		else if (sVoid == 2)
			++count[1];
		else
			++count[2];
	}
}

void				Gomoku::IA::getDiagRPossibilities(Tile const & player, std::vector<int> & count, std::pair<int, int> const & pos)
{
	int					sizeY = static_cast<int>(this->tmpBoard.size());
	int					sizeX = static_cast<int>(this->tmpBoard[0].size());
	int y = pos.first;
	int x = pos.second;
	int dVoid = 0;
	int dFill = 0;
	int sVoid = 0;

	while (y >= 0 && y >= pos.first - 4 && x < sizeX && x <= pos.second + 4)
	{
		if (this->tmpBoard[y][x] == player)
			++dFill;
		else if (this->tmpBoard[y][x] == Tile::EMPTY)
			++dVoid;
		else
			break;
		--y;
		++x;
	}
	y = pos.first;
	x = pos.second;
	while (y < sizeY && y <= pos.first + 4 && x >= 0 && x >= pos.second - 4 && this->tmpBoard[y][x] == Tile::EMPTY)
	{
		++sVoid;
		++y;
		--x;
	}
	if (dFill >= 2 && sVoid + dVoid + dFill >= 5)
	{
		sVoid = 5 - dFill;
		if (sVoid == 1)
			++count[0];
		else if (sVoid == 2)
			++count[1];
		else
			++count[2];
	}
}

std::vector<int>	Gomoku::IA::countPossibilities(Tile const & player)
{
	std::vector<int>	count(3, 0);
	int					sizeY = static_cast<int>(this->tmpBoard.size());
	int					sizeX = static_cast<int>(this->tmpBoard[0].size());


	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			if (this->tmpBoard[y][x] == player)
			{
				getHorizontalPossibilities(player, count, std::make_pair(y, x));
				getVerticalPossibilities(player, count, std::make_pair(y, x));
				getDiagLPossibilities(player, count, std::make_pair(y, x));
				getDiagRPossibilities(player, count, std::make_pair(y, x));
			}
		}
	}
	return (count);
}

double		Gomoku::IA::maxMove(int depth, double alpha, double beta, ScoredPosition &move) {
	double	best;
	double	score;

	this->turn = (this->turn + 1) % 2;
	if (depth == 0 || isGameFinished(move.second)) {
		best = this->evaluate();
		best += depth == 0 ? 0 : 10000;
	}
	else {
		best = -std::numeric_limits<double>::infinity();
		std::numeric_limits<double>::infinity();
		std::vector<ScoredPosition>	moves = this->checkPossibleMoves();
		for (ScoredPosition move : moves) {
			this->tmpBoard[move.second.first][move.second.second] = (this->turn == 1 ? Tile::OPPONENT : Tile::OWN);
			score = this->minMove(depth - 1, alpha, beta, move);
			this->tmpBoard[move.second.first][move.second.second] = Tile::EMPTY;
			best = std::max(score, best);
			alpha = std::max(score, alpha);
			if (beta <= alpha) {
				break;
			}
		}
	}
	this->turn = (this->turn + 1) % 2;
	return (best);
}

double		Gomoku::IA::minMove(int depth, double alpha, double beta, ScoredPosition &move) {
	double	best;
	double	score;

	this->turn = (this->turn + 1) % 2;
	if (depth == 0 || isGameFinished(move.second)) {
		best = this->evaluate();
		best += depth == 0 ? 0 : 10000;
	}
	else {
		best = std::numeric_limits<double>::infinity();
		std::vector<ScoredPosition>	moves = this->checkPossibleMoves();
		for (ScoredPosition move : moves) {
			this->tmpBoard[move.second.first][move.second.second] = (this->turn == 1 ? Tile::OPPONENT : Tile::OWN);
			score = this->maxMove(depth - 1, alpha, beta, move);
			this->tmpBoard[move.second.first][move.second.second] = Tile::EMPTY;
			best = std::min(score, best);
			beta = std::min(score, beta);
			if (beta <= alpha) {
				break;
			}
		}
	}
	this->turn = (this->turn + 1) % 2;
	return (best);
}

std::string Gomoku::IA::makeDecision(Board& board) {
	std::vector<ScoredPosition>	moves;
	int							size;
	double						score;
	int							depth = 4;
	ScoredPosition				bestMove = { 0, {-1, -1} };

	this->tmpBoard = board;
	moves = this->checkPossibleMoves();
	size = moves.size();
	if (size == 0)
	{
		board[board.size() / 2][board.size() / 2] = Tile::OWN;
		return (std::string(std::to_string(board.size() / 2) + ',' + std::to_string(board.size() / 2)));
	}
	else {
		for (ScoredPosition move : moves) {
			this->turn = 0;
			this->tmpBoard[move.second.first][move.second.second] = (this->turn == 1 ? Tile::OPPONENT : Tile::OWN);
			score = this->minMove(depth, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), move);
			this->tmpBoard[move.second.first][move.second.second] = Tile::EMPTY;
			if (bestMove.second.first == -1 || score > bestMove.first) {
				bestMove = { score, move.second };
			}
		}
	}
	board[bestMove.second.first][bestMove.second.second] = Tile::OWN;
	return (std::string(std::to_string(bestMove.second.second) + "," + std::to_string(bestMove.second.first)));
}