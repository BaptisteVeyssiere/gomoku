#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>
#include <ctime>
#include "IA.h"

Gomoku::IA::IA()
	: depth(3) {
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
	double				score = 0;

	score -= this->countPossibilities(Tile::OPPONENT);
	score += (this->countPossibilities(Tile::OWN) / 2);
	return (score);
}

int			Gomoku::IA::getHorizontalPossibilities(Tile const &player, std::vector<int> &count, std::pair<int, int> const &pos) {
	int y = pos.first;
	int x = pos.second;
	int	consecutive = 1;
	int	open = 0;
	int size = this->tmpBoard[0].size();

	if (x - 1 >= 0 && this->tmpBoard[y][x - 1] == Tile::EMPTY)
		open = 1;
	else if (x - 1 >= 0 && this->tmpBoard[y][x - 1] == player)
		return (0);

	while (++x < size && tmpBoard[y][x] == player) {
		++consecutive;
	}
	if (x < size && tmpBoard[y][x] == Tile::EMPTY)
		++open;
	
	if (consecutive == 5 || (consecutive == 4 && open == 2))
		return (10000);
	else if (consecutive < 3 || open == 0)
		return (0);
	if (consecutive == 3 && open == 2) {
		return (1000);
	}
	if (consecutive == 4 && open == 1) {
		return (200);
	}
	if (consecutive == 3 && open == 1) {
		return (100);
	}
	else if (consecutive == 4 && open == 1) {
		return (1050);
	}
	return (0);
}

int				Gomoku::IA::getVerticalPossibilities(Tile const & player, std::vector<int> & count, std::pair<int, int> const & pos)
{
	int y = pos.first;
	int x = pos.second;
	int	consecutive = 1;
	int	open = 0;
	int size = this->tmpBoard[0].size();

	if (y - 1 >= 0 && this->tmpBoard[y - 1][x] == Tile::EMPTY)
		open = 1;
	else if (y - 1 >= 0 && this->tmpBoard[y - 1][x] == player)
		return (0);

	while (++y < size && tmpBoard[y][x] == player) {
		++consecutive;
	}
	if (y < size && tmpBoard[y][x] == Tile::EMPTY)
		++open;

	if (consecutive == 5 || (consecutive == 4 && open == 2))
		return (10000);
	else if (consecutive < 3 || open == 0)
		return (0);
	else if (consecutive == 3 && open == 2) {
		return (1000);
	}
	else if (consecutive == 3 && open == 1) {
		return (100);
	}
	else if (consecutive == 4 && open == 1) {
		return (1050);
	}
	return (0);
}

int				Gomoku::IA::getDiagLPossibilities(Tile const & player, std::vector<int> & count, std::pair<int, int> const & pos)
{
	int y = pos.first;
	int x = pos.second;
	int	consecutive = 1;
	int	open = 0;
	int size = this->tmpBoard[0].size();

	if (y - 1 >= 0 && x + 1 < size && this->tmpBoard[y - 1][x + 1] == Tile::EMPTY)
		open = 1;
	else if (y - 1 >= 0 && x + 1 < size && this->tmpBoard[y - 1][x + 1] == player)
		return (0);

	while (++y < size && --x >= 0 && tmpBoard[y][x] == player) {
		++consecutive;
	}
	if (y < size && x >= 0 && tmpBoard[y][x] == Tile::EMPTY)
		++open;

	if (consecutive == 5 || (consecutive == 4 && open == 2))
		return (10000);
	else if (consecutive < 3 || open == 0)
		return (0);
	if (consecutive == 3 && open == 2) {
		return (1000);
	}
	if (consecutive == 3 && open == 1) {
		return (100);
	}
	else if (consecutive == 4 && open == 1) {
		return (1050);
	}
	return (0);
}

int				Gomoku::IA::getDiagRPossibilities(Tile const & player, std::vector<int> & count, std::pair<int, int> const & pos)
{
	int y = pos.first;
	int x = pos.second;
	int	consecutive = 1;
	int	open = 0;
	int size = this->tmpBoard[0].size();

	if (y - 1 >= 0 && x - 1 >= 0 && this->tmpBoard[y - 1][x - 1] == Tile::EMPTY)
		open = 1;
	else if (y - 1 >= 0 && x - 1 >= 0  && this->tmpBoard[y - 1][x - 1] == player)
		return (0);

	while (++y < size && ++x < size && tmpBoard[y][x] == player) {
		++consecutive;
	}
	if (y < size && x < size && tmpBoard[y][x] == Tile::EMPTY)
		++open;

	if (consecutive == 5 || (consecutive == 4 && open == 2))
		return (10000);
	else if (consecutive < 3 || open == 0)
		return (0);
	if (consecutive == 3 && open == 2) {
		return (1000);
	}
	if (consecutive == 3 && open == 1) {
		return (100);
	}
	else if (consecutive == 4 && open == 1) {
		return (1050);
	}
	return (0);
}

int		Gomoku::IA::countPossibilities(Tile const & player)
{
	std::vector<int>	count(3, 0);
	int					score = 0;
	int					sizeY = static_cast<int>(this->tmpBoard.size());
	int					sizeX = static_cast<int>(this->tmpBoard[0].size());


	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			if (this->tmpBoard[y][x] == player)
			{
				score += getHorizontalPossibilities(player, count, std::make_pair(y, x));
				score += getVerticalPossibilities(player, count, std::make_pair(y, x));
				score += getDiagLPossibilities(player, count, std::make_pair(y, x));
				score += getDiagRPossibilities(player, count, std::make_pair(y, x));
			}
		}
	}
	return (score);
}

double		Gomoku::IA::maxMove(int depth, double alpha, double beta, ScoredPosition &move) {
	double	best;
	double	score;

	this->turn = (this->turn + 1) % 2;
	if (depth == 0 || isGameFinished(move.second)) {
		best = this->evaluate();
		best -= depth == 0 ? 0 : 10000;
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
	bool						warning = false;
	double						score;
	int							depth = this->depth;
	ScoredPosition				bestMove = { 0, {-1, -1} };
	auto						start = std::chrono::system_clock::now();
	std::chrono::duration<double>	diff;

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
			auto end = std::chrono::system_clock::now();
			diff = end - start;
			if (warning == false && diff.count() >= 2.0) {
				if (this->depth == 3)
				{
					this->depth -= 2;
					warning = true;
				}
				else if (this->depth == 2)
					this->depth = 1;
			}
			this->turn = 0;
			this->tmpBoard[move.second.first][move.second.second] = (this->turn == 1 ? Tile::OPPONENT : Tile::OWN);
			score = this->minMove(depth, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), move);
			this->tmpBoard[move.second.first][move.second.second] = Tile::EMPTY;
			if (bestMove.second.first == -1 || score > bestMove.first) {
				bestMove = { score, move.second };
			}
		}
	}
	if (warning)
		this->depth += 1;
	board[bestMove.second.first][bestMove.second.second] = Tile::OWN;
	return (std::string(std::to_string(bestMove.second.second) + "," + std::to_string(bestMove.second.first)));
}