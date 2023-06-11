#ifndef __TOWER__H
#define __TOWER__H
//#include "Systema.h"
#include <iostream>
#include <vector>
#include <string>

class Tower {
public:
	std::vector <int> available_towers;
	std::string readiness = "is ready";
	int number, channels, available_channels, busy_channels = 0;
	Tower(std::string tower_info);
	Tower();
	std::vector<std::string> Unparse(std::string info);
};

#endif