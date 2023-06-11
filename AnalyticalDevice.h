#ifndef __ANALYTICALDEVICE__H
#define __ANALYTICALDEVICE__H
#include "Signal.h"
#include "Tower.h"

class AnalyticalDevice :public Tower {
public:
	AnalyticalDevice();
	std::string readiness = "is ready";
	std::vector <int> path;
	std::vector < std::vector <int> > all_pathes;
	void Path_Finder(int start, int end, Signal* obj);
	void All_pathes(int start, int end, Signal* obj);
	std::vector <int> Best_Path_Finder(Signal* obj);
};

#endif