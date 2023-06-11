#include "Commands.h"

Commands::Commands() {};

std::string Commands::get_command() {
	std::string command;
	std::getline(std::cin, command);
	return command;
}

void Commands::signal_transmitter(Signal* ob, std::string text) {
	ob->signal = text;
}
