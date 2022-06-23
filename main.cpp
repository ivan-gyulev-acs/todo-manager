#include <iostream>
#include <string>
#include "eventlog.hpp"
using std::string;

void PrintEvent(EventLog & event_log, Event & event_holder) {
	event_holder = event_log.GetEvent();
	if (event_log.Length() == 0) {
		std::cout << "EventLog is empty.\n\n";
	} else {
		std::cout << "Current Event:\n";
		event_holder.Print(20);
		std::cout << "\n\n";
	}
}

int main() {
	EventLog event_log;
	string input;
	Event event_holder;
	while (true) {
		system("cls");
		PrintEvent(event_log, event_holder);
		std::cout << "Event Log Length: " << event_log.Length() << '\n';
		std::cout << "1) Edit Event\n";
		std::cout << "2) Add Event\n";
		std::cout << "3) Delete Current Event\n";
		std::cout << "4) Go To Next Event\n";
		std::cout << "5) Go To Previous Event\n";
		std::cout << "6) Print All Events\n";
		std::cout << "7) Exit\n";
		std::cout << "\nCommand: ";
		std::getline(std::cin, input);
		if (input == "1") {
			if (event_log.Length() == 0) {
				std::cout << "You can't edit an event if the log is empty, add an event first.\n";
				std::cout << "Press ENTER to go back\n";
				std::getline(std::cin, input);
				continue;
			}
			system("cls");
			PrintEvent(event_log, event_holder);
			std::cout << "\nNew Event Description: \n";
			std::getline(std::cin, input);
			event_log.ChangeEvent(Event(input));
		} else if (input == "2") {
			if (event_log.Length() == 100) {
				std::cout << "You can't add more than a hundred events.\n";
				std::cout << "Press ENTER to go back\n";
				std::getline(std::cin, input);
				continue;
			}
			system("cls");
			PrintEvent(event_log, event_holder);
			std::cout << "1) Add To The Left Of Current Event\n";
			std::cout << "2) Add To The Right Of Current Event\n";
			std::cout << "3) Go Back\n";
			std::cout << "4) Exit\n";
			std::cout << "\nCommand: ";
			std::getline(std::cin, input);
			if (input == "4") break;
			if (input == "3" || input != "1" && input != "2") continue;
			if (input == "1") {
				do {
					std::cout << "Event Description:\n";
					std::getline(std::cin, input);
				} while (input == "");
				event_log.AddLeft(Event(input));
			}
			else if (input == "2") {
				do {
					std::cout << "Event Description:\n";
					std::getline(std::cin, input);
				} while (input == "");
				event_log.AddRight(Event(input));
			}
		} else if (input == "3") {
			event_log.Remove();
		} else if (input == "4") {
			event_log.MoveRight();
		} else if (input == "5") {
			event_log.MoveLeft();
		} else if (input == "6") {
			system("cls");
			std::cout << "Events:\n\n";
			event_log.Print();
			std::cout << "\n\nPress ENTER to go back\n";
			std::getline(std::cin, input);
		} else if (input == "7") break;
	}
}