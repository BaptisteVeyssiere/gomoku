#include <iostream>
#include <algorithm>
#include "CommandHandler.h"

Gomoku::CommandHandler::CommandHandler() {}

Gomoku::CommandHandler::~CommandHandler() {}

std::string	Gomoku::CommandHandler::getCommand() const {
	std::string	command = "";

	try {
		std::getline(std::cin, command);
		std::replace(command.begin(), command.end(), ',', ' ');
	}
	catch (std::ios_base::failure const & e) {
		throw std::runtime_error(std::string("Stream error in std::getline() : ") + e.what());
	}
	return (command);
}

void	Gomoku::CommandHandler::sendCommand(std::string const & msg) const {
	if (!msg.empty()) {
		std::cout << msg << std::endl << std::flush;
	}
}