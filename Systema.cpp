#include "Systema.h"
Systema::Systema() {}
std::vector<std::string> Systema::Unparse(std::string info) {
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
void Systema::build_tree() {
	Signal main_signal;
	AnalyticalDevice device;
	Commands commands;
	Signal* commands_sig = &main_signal;
	ControlPanel control_panel;
	Screen screen;
	int phase = 1;
	int* phase_pointer = &phase;
	while (phase < 4) {
			if (main_signal.Connections.size() != 0) {
				for (int i = 0; i < main_signal.Connections.size(); i++) {
					int p = std::stoi(main_signal.Connections[i][2]);
					p -= 10;
					if (p == 0) {
						std::vector <int> To;
						std::vector <std::string> T =
							Unparse(main_signal.Connections[i][3]);
						for (int y = 0; y < T.size(); y++) {
							To.push_back(std::stoi(T[y]));
						}
						for (int t = 0; t < main_signal.all_Towers.size(); t++) {
							for (int g = 0; g < To.size(); g++) {
								if (main_signal.all_Towers[t].number == To[g]) {
									main_signal.all_Towers[t].available_channels += 1;
									main_signal.all_Towers[t].busy_channels -= 1;
								}
							}
						}
						main_signal.Connections.erase(main_signal.Connections.begin()
							+ i);
					}
					else {
						main_signal.Connections[i][2] = std::to_string(p);
					}
				}
			}
		std::string cm = commands.get_command();
		commands.signal_transmitter(commands_sig, cm);
		control_panel.signal_handler(commands_sig, phase_pointer);
		if (commands_sig->signal != "End of the communication tower system" ||
			commands_sig->signal
			!= "End of information about phones" || commands_sig->signal !=
			"Turn off the system") {
			control_panel.New_Command_decoder(phase_pointer, commands_sig);
			if (phase == 3) {
				if (commands_sig->signal == "") { continue; }
				else {
					screen.signal_handler(commands_sig);
					screen.consol_output();
				}
			}
		}
		else if (commands_sig->signal == "End of information about phones") {
			screen.signal_handler(commands_sig);
			screen.consol_output();
		}
		else if (commands_sig->signal == "Turn off the system") {
			screen.signal_handler(commands_sig);
			screen.consol_output();
			phase = 4;
			break;
		}
	}
}

int Systema::exec_app() {
	void build_tree();
	return 0;
}

int SHOWTREE() {
	Phone ph;
	Tower tr;
	Commands cd;
	Signal sg;
	AnalyticalDevice dv;
	ControlPanel pn;
	Screen sc;
	std::cout << "Systema is ready";
	std::cout << "Commands " << cd.readiness;
	std::cout << "Signal " << sg.readiness;
	std::cout << " Screen " << sc.readiness;
	std::cout << "Phone " << ph.readiness;
	std::cout << "Tower " << tr.readiness;
	std::cout << " AnalyticalDevice " << dv.readiness;
	std::cout << " ControlPanel " << pn.readiness;
	return 0;
};