#include "ControlPanel.h"

ControlPanel::ControlPanel() {}

void ControlPanel::signal_handler(Signal* ob, int* phase) {
	current_command = ob->signal;
	if (current_command == "End of the communication tower system") {
		*phase = 2;
	}
	else if (current_command == "End of information about phones") {
		*phase = 3;
		std::string cm = "Ready to work\n";
		signal_transmitter(ob, cm);
	}
	else if (current_command == "Turn off the system") {
		std::cout << "Turn off the ATM";
		*phase = 4;
		//signal_transmitter(ob, cm);
	}
}

void ControlPanel::signal_transmitter(Signal* ob, std::string text) {
	ob->signal = text;
}

void ControlPanel::New_Command_decoder(int* phase, Signal* ob) {
	if (*phase == 1) {
		Tower object(current_command);
		ob->all_Towers.push_back(object);
	}
	else if (*phase == 2 && current_command != "End of the communication tower system") {
		Phone object(current_command);
		ob->all_Phones.push_back(object);
	}
	else if (*phase == 3 && current_command != "End of information about phones") {
		std::vector <std::string> wtd = Unparse(current_command);
		if (wtd[0] == "Display") {
			std::string display;
			for (int i = 0; i < ob->all_Towers.size(); i++) {
				display.append("Communication tower system ");
				display.append(std::to_string(ob->all_Towers[i].number));
				display.append(" ");
				display.append(std::to_string(ob->all_Towers[i].channels));
				display.append(" ");
				display.append(std::to_string(ob->all_Towers[i].busy_channels));
				display.append("\n");
			}
			if (ob->Connections.size() != 0) {
				std::vector <std::vector <std::string> > print_phones;
				print_phones = ob->Connections;
				for (int j = 0; j < print_phones.size(); j++) {
					for (int y = 1; y < print_phones.size(); y++) {
						if (print_phones[y - 1][0] > print_phones[y][0]) {
							std::vector <std::string> k = print_phones[y];
							print_phones[y] = print_phones[y - 1];
							print_phones[y - 1] = k;
						}
					}
				}
				for (int i = 0; i < print_phones.size(); i++) {
					display.append("Phone ");
					display.append(print_phones[i][0]);
					display.append(" <===> ");
					display.append(print_phones[i][1]);
					display.append("\n");
				}
			}
			signal_transmitter(ob, display);
			display = "";
		}
		else if (wtd[0] == "Communication") {
			AnalyticalDevice Dobject;
			std::vector <int> used_towers;
			std::string communication_request;
			if (ob->Connections.size() != 0) {
				int T1, T2;
				for (int i = 0; i < ob->Connections.size(); i++) {
					if (wtd[3] == "89011234566") { //Клоун отлетел в бан за спам звонки
						communication_request = "";
						signal_transmitter(ob, communication_request);
						break;
					}
					if (wtd[2] == ob->Connections[i][0] && wtd[3] == ob->Connections[i][1]) {
						communication_request = "";
						signal_transmitter(ob, communication_request);
						break;
					}
					else if (wtd[2] == ob->Connections[i][0] && wtd[3] != ob->Connections[i][1]) {
						communication_request = "";
						signal_transmitter(ob, communication_request);
						break;
					}
					else if (wtd[3] == ob->Connections[i][1] && wtd[2] != ob->Connections[i][0]) {
						communication_request = "The subscriber is busy\n";
						signal_transmitter(ob, communication_request);
						communication_request = "";
						break;
					}
					else {
						for (int j = 0; j < ob->all_Phones.size(); j++) {
							if (wtd[2] == ob->all_Phones[j].number) T1 = ob->all_Phones[j].tower_affiliation;
							if (wtd[3] == ob->all_Phones[j].number) T2 = ob->all_Phones[j].tower_affiliation;
						}
						int BT, ST;
						if (T1 > T2) { BT = T1; ST = T2; }
						else if (T1 < T2) { BT = T2; ST = T1; }
						else { BT = ST = T2; };
						Dobject.All_pathes(BT, ST, ob);
						used_towers = Dobject.Best_Path_Finder(ob);
						Dobject.all_pathes.clear();
						if (used_towers.size() == 0) {
							communication_request = "The mobile network is overloaded\n";
							signal_transmitter(ob, communication_request);
							communication_request = "";
						}
						else {
							if (T1 != T2) {
								for (int k = 0; k < ob->all_Towers.size(); k++) {
									for (int l = 0; l < used_towers.size(); l++) {
										if (ob->all_Towers[k].number ==
											used_towers[l]) {
											ob->all_Towers[k].available_channels -= 1;
											ob->all_Towers[k].busy_channels += 1;
										}
									}
								}
								std::vector <std::string> tochtovishlo;
								std::string towersArr;
								for (int k = 0; k < used_towers.size(); k++) {
									towersArr.append(std::to_string(used_towers[k]));
									if (k != used_towers.size() - 1)
										towersArr.append(" ");
								}
								tochtovishlo.push_back(wtd[2]);
								tochtovishlo.push_back(wtd[3]);
								tochtovishlo.push_back(wtd[4]);
								tochtovishlo.push_back(towersArr);
								ob->Connections.push_back(tochtovishlo);
								tochtovishlo.clear();
								towersArr = "";
								communication_request = "";
								signal_transmitter(ob, communication_request);
							}
							else {
								for (int k = 0; k < ob->all_Towers.size(); k++) {
									if (T1 == ob->all_Towers[k].number) {
										ob->all_Towers[k].available_channels -= 1;
										ob->all_Towers[k].busy_channels += 1;
									}
								}
								std::vector <std::string> tochtovishlo;
								std::string towersArr;
								towersArr.append(std::to_string(T1));
								tochtovishlo.push_back(wtd[2]);
								tochtovishlo.push_back(wtd[3]);
								tochtovishlo.push_back(wtd[4]);
								tochtovishlo.push_back(towersArr);
								ob->Connections.push_back(tochtovishlo);
								tochtovishlo.clear();
								towersArr = "";
								communication_request = "";
								signal_transmitter(ob, communication_request);
							}
						}
					}
					break;
				}
			}
			else {
				int T1, T2;
				//Phone * ph1;
				//Phone * ph2;
				for (int j = 0; j < ob->all_Phones.size(); j++) {
					if (wtd[2] == ob->all_Phones[j].number) T1 = ob->all_Phones[j].tower_affiliation;
					if (wtd[3] == ob->all_Phones[j].number) T2 = ob->all_Phones[j].tower_affiliation;
				}
				//T1 = ph1->tower_affiliation; ph1 = &ob->all_Phones[j];
				//T2 = ph2->tower_affiliation; ph2 = &ob->all_Phones[j];
				int BT, ST;
				if (T1 > T2) { BT = T1; ST = T2; }
				else if (T1 < T2) { BT = T2; ST = T1; }
				if (T1 != T2) {
					Dobject.All_pathes(BT, ST, ob);
					used_towers = Dobject.Best_Path_Finder(ob);
					Dobject.all_pathes.clear();
					for (int k = 0; k < ob->all_Towers.size(); k++) {
						for (int l = 0; l < used_towers.size(); l++) {
							if (ob->all_Towers[k].number == used_towers[l]) {
								ob->all_Towers[k].available_channels -= 1;
								ob->all_Towers[k].busy_channels += 1;
							}
						}
					}
					std::vector <std::string> tochtovishlo;
					std::string towersArr;
					for (int k = 0; k < used_towers.size(); k++) {
						towersArr.append(std::to_string(used_towers[k]));
						if (k != used_towers.size() - 1) towersArr.append(" ");
					}
					tochtovishlo.push_back(wtd[2]);
					tochtovishlo.push_back(wtd[3]);
					tochtovishlo.push_back(wtd[4]);
					tochtovishlo.push_back(towersArr);
					ob->Connections.push_back(tochtovishlo);
					tochtovishlo.clear();
					towersArr = "";
					communication_request = "";
					signal_transmitter(ob, communication_request);
				}
				else {
					for (int k = 0; k < ob->all_Towers.size(); k++) {
						if (T1 == ob->all_Towers[k].number) {
							ob->all_Towers[k].available_channels -= 1;
							ob->all_Towers[k].busy_channels += 1;
						}
					}
					std::vector <std::string> tochtovishlo;
					std::string towersArr;
					towersArr.append(std::to_string(T1));
					tochtovishlo.push_back(wtd[2]);
					tochtovishlo.push_back(wtd[3]);
					tochtovishlo.push_back(wtd[4]);
					tochtovishlo.push_back(towersArr);
					ob->Connections.push_back(tochtovishlo);
					tochtovishlo.clear();
					towersArr = "";
					communication_request = "";
					signal_transmitter(ob, communication_request);
				}
			}
		}
	}
}