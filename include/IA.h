#ifndef IA_H_
# define IA_H_

# include <vector>
# include "Board.h"

namespace Gomoku {
	class IA {
	public:
		IA();
		~IA();

		std::string	turn(std::vector<std::vector<Tile>> & board);
		bool		isMovePossible(std::vector<std::vector<Tile>> const & board, unsigned int x, unsigned int y);
		bool		isGameFinished(std::pair<int, int> &lastPos, std::vector<std::vector<Tile>> &tmpBoard, int turn);
		int			playGame(std::pair<int, int> pos, std::vector<std::vector<Tile>> tmpBoard);
		std::string	makeDecision(std::vector<std::vector<Tile>> const & board);
	};
};

#endif // !IA_H_
