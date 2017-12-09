#ifndef IA_H_
# define IA_H_

# include <vector>
# include <ctime>
# include "Board.h"

namespace Gomoku {
	class IA {
	public:
		IA();
		~IA();

		std::string	turn(std::vector<std::vector<Tile>> & board);
		bool		isMovePossible(std::vector<std::vector<Tile>> const & board, unsigned int x, unsigned int y);
		std::string	makeDecision(std::vector<std::vector<Tile>> const & board);
		int			playGame(std::pair<int, int> pos, std::vector<std::vector<Tile>> tmpBoard);
		bool		isGameFinished(std::pair<int, int> &lastPos, std::vector<std::vector<Tile>> &board, int turn);

	};
};

#endif // !IA_H_
