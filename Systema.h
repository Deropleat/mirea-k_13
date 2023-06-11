#ifndef __SYSTEMA__H
#define __SYSTEMA__H
#include <vector>
#include <string>
#include "Tower.h"
#include "Phone.h"
#include "AnalyticalDevice.h"
#include "Screen.h"
#include "Commands.h"
#include "Signal.h"
#include "ControlPanel.h"

class Systema {
public:
	Systema();
	std::string readiness = "is ready";
	std::vector<std::string> Unparse(std::string info);
	int SHOWTREE();
	void build_tree();
	int exec_app();
};

#endif