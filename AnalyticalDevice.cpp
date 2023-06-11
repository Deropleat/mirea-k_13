#include "AnalyticalDevice.h"

AnalyticalDevice::AnalyticalDevice() {};

void AnalyticalDevice::Path_Finder(int start, int end, Signal* obj) {
	for (int i = 0; i < obj->all_Towers.size(); i++) {
		if (obj->all_Towers[i].number == start) {
			path.push_back(obj->all_Towers[i].number);
			if (obj->all_Towers[i].number == end) return;
			bool flag1 = false;
			for (int j = 0; j < obj->all_Towers[i].available_towers.size(); j++) {
				if (obj->all_Towers[i].available_towers[j] == end) {
					flag1 = true;
					path.push_back(obj->all_Towers[i].available_towers[j]);
					break;
				}
			}
			if (flag1) return;
			else {
				for (int h = 0; h < obj->all_Towers[i].available_towers.size(); h++) {
					bool flag2 = true;
					for (int g = 0; g < path.size(); g++) {
						if (obj->all_Towers[i].available_towers[h] == path[g]) flag2 = false; break;
					}
					if (flag2) Path_Finder(obj->all_Towers[i].available_towers[h], end, obj);
				}
			}
		}
	}
}

void AnalyticalDevice::All_pathes(int start, int end, Signal* obj) {
	for (int i = 0; i < obj->all_Towers.size(); i++) {
		if (obj->all_Towers[i].number == start) {
			for (int j = 0; j < obj->all_Towers[i].available_towers.size(); j++) {
				Path_Finder(obj->all_Towers[i].available_towers[j], end, obj);
				std::vector <int> accurate_path;
				int k = 0;
				while (true) {
					accurate_path.push_back(path[k]);
					if (path[k] == end) break;
					k++;
				}
				bool failure = true;
				for (int f = 0; f < accurate_path.size(); f++) {
					if (accurate_path[f] == start) {
						failure = false;
						break;
					}
				}
				if (failure) accurate_path.push_back(start);
				all_pathes.push_back(accurate_path);
				accurate_path.clear();
				path.clear();
			}
		}
	}
}

std::vector <int> AnalyticalDevice::Best_Path_Finder(Signal* obj) {
	int size = 100;
	std::vector <int> result;
	std::vector <int> busy_channels;
	for (int i = 0; i < obj->all_Towers.size(); i++) {
		if (obj->all_Towers[i].available_channels == 0) {
			busy_channels.push_back(obj->all_Towers[i].number);
		}
	}
	for (int i = 0; i < all_pathes.size(); i++) {
		bool vacant = true;
		for (int j = 0; j < all_pathes[i].size(); j++) {
			for (int k = 0; k < busy_channels.size(); k++) {
				if (all_pathes[i][j] == busy_channels[k]) {
					vacant = false;
					break;
				}
			}
		}
		if (vacant) {
			if (all_pathes[i].size() < size) {
				size = all_pathes[i].size();
				result = all_pathes[i];
			}
		}
		else {
			continue;
		}
	}
	busy_channels.clear();
	return result;
}