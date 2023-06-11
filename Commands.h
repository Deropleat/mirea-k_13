#ifndef __COMMANDS__H
#define __COMMANDS__H
#include <iostream>
#include <vector>
#include <string>
#include "Signal.h"

class Commands {
public:
	Commands();
	std::string readiness = "is ready";
	std::string get_command();
	void signal_transmitter(Signal* ob, std::string text);
};

#endif