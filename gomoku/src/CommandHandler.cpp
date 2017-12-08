#include <iostream>
#include "CommandHandler.h"

CommandHandler::CommandHandler() {}

CommandHandler::~CommandHandler() {}

std::string	CommandHandler::getCommand() {
	std::string	command = nullptr;

	try {
		std::getline(std::cin, command);
	}
	catch (ios_base::failure const & e) {
		throw std::runtime_error("Stream error in std::getline()");
	}
	return (command);
}

void	CommandHandler::sendCommand(std::string const & msg) {
	if (msg != nullptr) {
		std::cout << msg << std::endl;
	}
}