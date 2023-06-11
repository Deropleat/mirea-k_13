#ifndef __SCREEN__H
#define __SCREEN__H
#include "Signal.h"
#include "Tower.h"
#include <iostream>

class Screen : public Tower, public Signal {
public:
	Screen();
	std::string readiness = "is ready";
	std::string output_command;
	void signal_handler(Signal* ob);
	void consol_output();
};

#endif