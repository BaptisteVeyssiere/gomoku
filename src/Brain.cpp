#include <sstream>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <functional>
#include "Brain.h"

Gomoku::Brain::Brain() {}

Gomoku::Brain::~Brain() {}

void	Gomoku::Brain::start(std::vector<std::string> const & parameters) {
	std::size_t	size;

	if (parameters.size() != 1)
		throw std::runtime_error("Invalid number of parameters in START command");
	try {
		size = std::stoi(parameters[0]);
	}
	catch (std::invalid_argument const & e) {
		throw std::runtime_error("Invalid parameter in START command");
	}
	if (size < 15 || size > 20)
	{
		throw std::runtime_error("Invalid size of board");
	}
	this->board = std::vector<std::vector<Tile>>(size, std::vector<Tile>(size, Tile::EMPTY));
	this->stream.sendCommand("OK");
}

void	Gomoku::Brain::turn(std::vector<std::string> const & parameters) {
	int		x;
	int		y;
	bool	begin;

	if (parameters.size() != 3)
		throw std::runtime_error("Invalid number of parameters in BEGIN / TURN command");
	try {
		x = std::stoi(parameters[0]);
		y = std::stoi(parameters[1]);
	}
	catch (std::invalid_argument const & e) {
		throw std::runtime_error("Invalid parameter in BEGIN / TURN command");
	}
	if (parameters[2] != "true" && parameters[2] != "false")
		throw std::runtime_error("Invalid parameter in turn function");
	begin = parameters[2] == "true" ? true : false;
	if (!begin) {
		if (x < 0 || y < 0 || x >= static_cast<int>(this->board.size()) || y >= static_cast<int>(this->board.size())) {
			throw std::runtime_error("Invalid opponent's move coordinates");
		}
		this->board[y][x] = Tile::OPPONENT;
	}
	std::string coordinates = this->ia.turn(this->board);
	this->stream.sendCommand(coordinates);
}

void	Gomoku::Brain::makeBoard(std::vector<std::string> const & parameters) {
	std::string	command = "";
	std::stringstream	sstream;
	int					x = 0;
	int					y = 0;
	int					field = 0;
	Tile				tile = Tile::EMPTY;

	if (parameters.size() != 0) {
		throw std::runtime_error("Invalid parameter in BOARD command");
	}
	while (command != "DONE") {
		if (!command.empty()) {
			sstream.str(command);
			sstream >> x;
			sstream >> y;
			sstream >> field;
			if (sstream.fail()) {
				throw std::runtime_error("Stringstream error");
			}
			else if (field < 1 || field > 3 || x < 0 || y < 0 ||
				x >= static_cast<int>(this->board.size()) || y >= static_cast<int>(this->board.size())) {
				throw std::runtime_error("Invalid BOARD command data");
			}
			tile = (field == 1 ? Tile::OWN : (field == 2 ? Tile::OPPONENT : Tile::EMPTY));
			this->board[y][x] = tile;
		}
		command = this->stream.getCommand();
	}
	std::string coordinates = this->ia.turn(this->board);
	this->stream.sendCommand(coordinates);
}

void	Gomoku::Brain::end(std::vector<std::string> const & parameters) {
	if (parameters.size() != 0) {
		throw std::runtime_error("Invalid parameter in BOARD command");
	}
	this->running = false;
}

void	Gomoku::Brain::about(std::vector<std::string> const & parameters) const {
	std::string const name = "GodzIA";
	std::string const version = "1.0";
	std::string const author = "GodzIA";
	std::string const country = "France";
	std::string	const info = "name=\"" + name + "\", version=\"" + version + "\", author=\"" + author + "\", country=\"" + country + "\"";

	if (parameters.size() != 0) {
		throw std::runtime_error("Invalid parameter in BOARD command");
	}
	this->stream.sendCommand(info);
}

void	Gomoku::Brain::splitLineToWords(std::string const & command, std::vector<std::string> & words) const {
	std::istringstream	isstream(command);
	std::string			word;

	while (isstream) {
		word = "";
		isstream >> word;
		if (!word.empty())
			words.push_back(word);
	}
}

std::string		Gomoku::Brain::interpretCommand(std::string const & command) {
	std::unordered_map<std::string, std::function<void(Gomoku::Brain &, std::vector<std::string> const &)>>	functions = {
		{"START", &Gomoku::Brain::start},
		{"TURN", &Gomoku::Brain::turn},
		{"BEGIN", &Gomoku::Brain::turn},
		{"BOARD", &Gomoku::Brain::makeBoard},
		{"END", &Gomoku::Brain::end},
		{"ABOUT", &Gomoku::Brain::about}
	};
	std::vector<std::string>																						parameters;
	std::string																										tmp;

	this->splitLineToWords(command, parameters);
	if (parameters[0] == "INFO")
		return ("INFO"); 
	else if (functions.count(parameters[0]) < 1) {
		this->stream.sendCommand("UNKNOWN");
		return ("UNKNOWN");
	}
	else {
		tmp = parameters[0];
		parameters.erase(parameters.begin());
		if (tmp == "BEGIN") {
			parameters.push_back("0");
			parameters.push_back("0");
			parameters.push_back("true");
		}
		else if (tmp == "TURN")
			parameters.push_back("false");
		functions[tmp](*this, parameters);
	}
	return ("");
}

bool	Gomoku::Brain::run() {
	std::string	command = "";

	this->running = true;
	while (running) {
		try {
			command = this->stream.getCommand();
			if (!command.empty()) {
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