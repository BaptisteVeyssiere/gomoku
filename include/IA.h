#ifndef IA_H_
# define IA_H_

# include <vector>
# include "Board.h"

namespace Gomoku {
	class IA {
	public:
		IA();
		~IA();

		bool		isGameFinished(std::pair<int, int> const & lastPos, std::vector<std::vector<Tile>> const & tmpBoard, int turn);
		int			playGame(std::pair<int, int> const & pos, std::vector<std::vector<Tile>> tmpBoard);
		std::string	makeDecision(std::vector<std::vector<Tile>>& board);
		void	getPossibleMoves(std::vector<std::vector<Tile>> const & board, std::vector<std::pair<int, int>> &move, int y, int x);
		std::vector<std::pair<int, int>>	checkPossibleMoves(std::vector<std::vector<Tile>> const & board);
		bool	cutDangerousMove(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove);
		bool	checkDangerousMove(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x);
		bool	checkHorizontal(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x);
		bool	checkVertical(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x);
		bool	checkDiagRight(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x);
		bool	checkDiagLeft(std::vector<std::vector<Tile>> const & board, std::pair<int, int> &bestMove, int y, int x);

	};
};

#endif // !IA_H_
