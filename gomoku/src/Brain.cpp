#include <sstream>
#include "Brain.h"

Gomoku::Brain::Brain() {}

Gomoku::Brain::~Brain() {}

void	Gomoku::Brain::start(std::size_t size) {
	if (size < 15 || size > 20)
	{
		throw std::runtime_error("Invalid size of board");
	}
	this->board = std::vector<std::vector<Tile>>(size, std::vector<Tile>(size, EMPTY));
}

void	Gomoku::Brain::turn(int x, int y, bool begin) {
	if (!begin) {
		if (x < 0 || y < 0 || x >= this->board.size() || y >= this->board.size()) {
			throw std::runtime_error("Invalid opponent's move coordinates");
		}
		this->board[y][x] = OPPONENT;
	}
	std::string coordinates = this->ia.turn(this->board);
	this->stream.sendCommand(coordinates);
}

void	Gomoku::Brain::board() {
	std::string	command != nullptr;
	std::stringstream	sstream;
	int					x = 0;
	int					y = 0;
	int					field = 0;
	Tile				tile = EMPTY;

	while (command != "DONE") {
		if (command != nullptr) {
			std::replace(command.begin(), command.end(), ',', ' ');
			sstream.str(command);
			x << sstream;
			y << sstream;
			field << sstream;
			if (sstream.fail()) {
				throw std::runtime_error("Stringstream error");
			}
			else if (field < 1 || field > 3 || x < 0 || y < 0 || x >= this->board.size() || y >= this->board.size()) {
				throw std::runtime_error("Invalid BOARD command data");
			}
			tile = (field == 1 ? OWN : (field == 2 ? OPPONENT : EMPTY));
			this->board[y][x] = tile;
		}
		command = this->stream.getCommand();
	}
	std::string coordinates = this->ia.turn(this->board);
	this->stream.sendCommand(coordinates);
}

void	Gomoku::Brain::end() {
	this->running = false;
}

void	Gomoku::Brain::about() {
	std::string	info = "name=\"" + NAME + "\", version=\"" + VERSION + "\", author=\"" + AUTHOR + "\", country=\"" + COUNTRY + "\"";

	this->stream.sendCommand(info);
}

std::string		Gomoku::Brain::interpretCommand(std::string const & command) {

}

bool	Gomoku::Brain::run() {
	std::string	command = nullptr;

	this->running = true;
	while (running) {
		try {
			command = this->stream.getCommand();
			if (command != nullptr) {
				this->interpretCommand(command);
			}
		}
		catch (std::runtime_error const & e) {
			this->stream.sendCommand(ERRORMSG);
			std::cerr << e.what() << std::endl;
			return (false);
		}
	}
	return (true);
}