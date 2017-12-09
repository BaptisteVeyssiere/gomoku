#ifndef COMMANDHANDLER_H_
# define COMMANDHANDLER_H_

# include <string>

namespace Gomoku {
	class CommandHandler {
	public:
		CommandHandler();
		~CommandHandler();

		std::string getCommand() const;
		void		sendCommand(std::string const &msg) const;

	private:
		CommandHandler(CommandHandler const &other);
		CommandHandler &operator=(CommandHandler const &other);
	};
};

#endif // !COMMANDHANDLER_H_
