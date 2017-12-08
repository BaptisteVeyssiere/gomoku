#ifndef BRAIN_H_
# define BRAIN_H_

# include <vector>
# include <cstddef>
# include "Board.h"
# include "IA.h"
# include "CommandHandler.h"

# define ERRORMSG "ERROR an unexpected error occured"
# define NAME "GodzIA"
# define VERSION "1.0"
# define AUTHOR "GodzIA"
# define COUNTRY "France"

namespace Gomoku {
	class Brain {
	private:
		std::vector<std::vector<Tile>>	board;
		IA                              ia;
		CommandHandler					stream;
		bool							running = false;

	public:
		Brain();
		~Brain();

		void		start(std::size_t size);
		void		turn(int x, int y);
		void		board();
		void		about();
		void		end();
		bool		run();
		std::string	interpretCommand(std::string const & command);

	private:
		Brain(Brain const &other);
		Brain &operator=(Brain const &other);
	};
};

#endif // !BRAIN_H_
