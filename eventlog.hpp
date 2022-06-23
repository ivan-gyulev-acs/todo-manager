#ifndef EVENTLOG_HPP
#define EVENTLOG_HPP

#include <exception>
#include <string>
#include <iostream>
using std::string;

struct Event {
	Event(): info("empty") {}
	Event(string info): info(info) {}
	Event(const Event & copy): info(copy.info) {}
	Event & operator=(const Event & copy) {
		if (this == &copy) return *this;
		info = copy.info;
		return *this;
	}
	~Event() {}
	void Print(size_t max_length) {
		for (size_t i = 0; i < info.length(); i++) {
			if (i % max_length == 0 && i != 0) std::cout << '\n';
			std::cout << info[i];
		}
	}
	string info;
};

class EventLog {
public:
	EventLog():	first(nullptr),
				last(nullptr),
				current(nullptr),
				length(0) {}
	~EventLog() {}
	void Delete() {
		Node * iterator;
		while (first) {
			iterator = first;
			first = first->next;
			delete iterator;
		}
		last = nullptr;
		current = nullptr;
		length = 0;
	}
	void AddLeft(Event new_event) {
		length++;
		if (current == nullptr) {
			current = new Node(new_event);
			last = current;
			first = current;
			return;
		}
		if (current->previous == nullptr) {
			current = new Node(new_event, current, nullptr);
			current->next->previous = current;
			first = current;
			return;
		}
		current = new Node(new_event, current, current->previous);
		current->previous->next = current;
		current->next->previous = current;
	}
	void AddRight(Event new_event) {
		length++;
		if (current == nullptr) {
			current = new Node(new_event);
			last = current;
			first = current;
			return;
		}
		if (current->next == nullptr) {
			current = new Node(new_event, nullptr, current);
			current->previous->next = current;
			last = current;
			return;
		}
		current = new Node(new_event, current->next, current);
		current->previous->next = current;
		current->next->previous = current;
	}
	void Remove() {
		if (current == nullptr) return;
		Node* holder = nullptr;
		if (current->next == nullptr) last = current->previous;
		else {
			current->next->previous = current->previous;
			holder = current->next;
		}
		if (current->previous == nullptr) first = current->next;
		else {
			current->previous->next = current->next;
			holder = current->previous;
		}
		delete current;
		current = holder;
		length--;
	}
	void MoveLeft() {
		if (current == nullptr) return;
		if (current->previous == nullptr) current = last;
		else current = current->previous;
	}
	void MoveRight() {
		if (current == nullptr) return;
		if (current->next == nullptr) current = first;
		else current = current->next;
	}
	size_t Length() {
		return length;
	}
	void ChangeEvent(Event new_event) {
		if (current == nullptr) return;
		current->event = new_event;
	}
	Event GetEvent() {
		if (current != nullptr) return current->event;
		return Event("");
	}
	void Print() {
		if (length == 0) return;
		Node * iterator = first;
		for (size_t i = 0; i < length; i++) {
			std::cout << "event " << i << ":\n";
			iterator->event.Print(20);
			std::cout << "\n\n";
			iterator = iterator->next;
		}
	}
private:
	struct Node {
		Event event;
		Node * next;
		Node * previous;
		Node(): event(), next(nullptr), previous() {}
		Node(Event event):	event(event), next(nullptr), previous(nullptr) {}
		Node(Node * next, Node * previous): event(), next(next), previous(previous) {}
		Node(Event event, Node * next, Node * previous):	event(event),
															next(next),
															previous(previous) {}
	};
	Node * first;
	Node * last;
	Node * current;
	size_t length;
};

#endif // EVENTLOG_HPP