#ifndef IA_H_
# define IA_H_

# include <vector>
# include <limits>
# include "Board.h"

namespace Gomoku {
	using ScoredPosition = std::pair<int, std::pair<int, int>>;
	using Board = std::vector<std::vector<Tile>>;
	class IA {
	private:
		Board	tmpBoard;
		int		turn;
	public:
		IA();
		~IA();

		bool						isGameFinished(std::pair<int, int> const & lastPos);
		std::string					makeDecision(Board & board);
		std::vector<ScoredPosition>	checkPossibleMoves();
		void						getPossibleMoves(std::vector<ScoredPosition> &move, int y, int x);

		std::vector<int>	countPossibilities(Tile const & player);
		void	getHorizontalPossibilities(Tile const & player, std::vector<int> &count, std::pair<int, int> const &pos);
		void	getVerticalPossibilities(Tile const & player, std::vector<int> &count, std::pair<int, int> const &pos);
		void	getDiagLPossibilities(Tile const & player, std::vector<int> &count, std::pair<int, int> const &pos);
		void	getDiagRPossibilities(Tile const & player, std::vector<int> &count, std::pair<int, int> const &pos);

		double	minMove(int depth, double alpha, double beta, ScoredPosition &move);
		double	maxMove(int depth, double alpha, double beta, ScoredPosition &move);
		double	evaluate();
	};
};

#endif // !IA_H_
