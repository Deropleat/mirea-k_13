#ifndef __SIGNAL__H
#define __SIGNAL__H
#include <iostream>
#include <vector>
#include <string>
#include "Phone.h"
#include "Tower.h"

class Signal {
public:
	Signal();
	std::string readiness = "is ready";
	std::string signal;
	Signal(std::string text);
	std::vector<Phone> all_Phones;
	std::vector<Tower> all_Towers;
	//std::vector<std::vector <Phone> > connections;
	std::vector<std::vector <std::string> > Connections;
};

#endif
