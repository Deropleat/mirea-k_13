#include "Screen.h"

Screen::Screen() {};

void Screen::signal_handler(Signal* ob) {
	output_command = ob->signal;
}
void Screen::consol_output() {
	std::cout << output_command;
}
