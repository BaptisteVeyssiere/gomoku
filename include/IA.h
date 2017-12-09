#ifndef IA_H_
# define IA_H_

# include <vector>
# include "Board.h"

namespace Gomoku {
	class IA {
	public:
		IA();
		~IA();

		bool		isGameFinished(std::pair<int, int> &lastPos, std::vector<std::vector<Tile>> &tmpBoard, int turn);
		int			playGame(std::pair<int, int> pos, std::vector<std::vector<Tile>> tmpBoard);
		std::string	makeDecision(std::vector<std::vector<Tile>>& board);
		void	getPossibleMoves(std::vector<std::vector<Tile>> const & board, std::vector<std::pair<int, int>> &move, int y, int x);
		std::vector<std::pair<int, int>>	checkPossibleMoves(std::vector<std::vector<Tile>> const & board);

	};
};

#endif // !IA_H_
