#ifndef __CONTROLPANEL__H
#define __CONTROLPANEL__H
#include "Signal.h"
#include "Tower.h"
#include "Screen.h"
#include "Phone.h"
#include "AnalyticalDevice.h"

class ControlPanel : public AnalyticalDevice {
public:
	ControlPanel();
	std::string readiness = "is ready";
	std::vector <Phone> make_connections;
	std::string current_command;
	void signal_handler(Signal* ob, int* phase);
	void signal_transmitter(Signal* ob, std::string text);
	void New_Command_decoder(int* phase, Signal* ob);
};

#endif