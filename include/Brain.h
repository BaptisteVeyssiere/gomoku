#ifndef BRAIN_H_
# define BRAIN_H_

# include <vector>
# include <cstddef>
# include "Board.h"
# include "IA.h"
# include "CommandHandler.h"

# define ERRORMSG "ERROR an unexpected error occured"

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

		void		start(std::vector<std::string> const & parameters);
		void		turn(std::vector<std::string> const & parameters);
		void		makeBoard(std::vector<std::string> const & parameters);
		void		about(std::vector<std::string> const & parameters) const;
		void		end(std::vector<std::string> const & parameters);
		bool		run();
		void		splitLineToWords(std::string const & command, std::vector<std::string> & words) const;
		std::string	interpretCommand(std::string const & command);

	private:
		Brain(Brain const &other);
		Brain &operator=(Brain const &other);
	};
};

#endif // !BRAIN_H_
