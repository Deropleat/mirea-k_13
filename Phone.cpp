#include "Phone.h"

std::vector<std::string> Phone::Unparsed(std::string info) {
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

Phone::Phone(std::string phone_info) {
	std::vector <std::string> new_phone = Unparsed(phone_info);
	this->number = new_phone[0];
	this->tower_affiliation = std::stoi(new_phone[1]);
}

Phone::Phone() {}