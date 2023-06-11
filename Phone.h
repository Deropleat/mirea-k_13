#ifndef __PHONE__H
#define __PHONE__H
#include <iostream>
#include <vector>
#include <string>

class Phone {
public:
	Phone();
	std::string readiness = "is ready";
	std::string number;
	int call_duration = 0, tower_affiliation;
	Phone(std::string phone_info);
	std::vector<std::string> Unparsed(std::string info);
};

#endif