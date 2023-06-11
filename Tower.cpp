#include "Tower.h"

std::vector<std::string> Tower::Unparse(std::string info) {
	std::vector<std::string> unparsed;
	std::string tmp = "";
	for (int i = 0; i < info.size(); i++) {
		if (info[i] == ' ') {
			unparsed.push_back(tmp);
			tmp = "";
		}
		else {
			tmp += info[i];
		}
	}
	unparsed.push_back(tmp);
	return unparsed;
};

Tower::Tower(std::string tower_info) {
	std::vector <std::string> new_tower = Unparse(tower_info);
	number = std::stoi(new_tower[0]);
	channels = available_channels = std::stoi(new_tower[1]);
	for (int i = 2; i < new_tower.size(); i++) {
		available_towers.push_back(std::stoi(new_tower[i]));
	}
}

Tower::Tower() {}