#include <map>
#include <iostream>
#include <stdio.h>
#include <string> 
#include <sstream>
#include <utility>
#define OCTAVE 7
#define MIDI_START -1
#define MIDI_VALUES 128
#define QUIT_COMMAND ":quit"

const char letters[OCTAVE] = {
	'C',
	'D',
	'E',
	'F',
	'G',
	'A',
	'B'
};
const bool sharps[OCTAVE] = {
	true,
	true,
	false,
	true,
	true,
	true, 
	false
};

std::map<std::string, int> buildMap();
int toMIDI(std::string, std::map<std::string, int>);
std::string concat(char note, char modifier, int octave);
void printMap(std::map<std::string, int> hashmap);
int getMin(int* arr, int len);
int getMax(int* arr, int len);

int main() {
	const std::map<std::string, int> notes = buildMap();
	//printMap(notes);
	std::cout << "Welcome to MIDI Encoder!" << std::endl
		<< "Please note that C++ only supports ASCII characters. Use '#' for sharps and 'b' for flats." << std::endl
		<< "Type ':quit' to exit the program at any time." << std::endl
		<< "Enter space-separated notes for conversion to MIDI values:" << std::endl;

	std::string input;
	std::getline(std::cin, input);
	do {
		std::istringstream values(input);
		int int_arr[10];
		int i = 0;
		while (values.good()) {
			std::string v;
			values >> v;
			int_arr[i] = toMIDI(v, notes);
			std::cout << int_arr[i] << " ";
			i++;
		}
		std::cout << std::endl;
		int min = getMin(int_arr, 10), max = getMax(int_arr, 10);
		int min_diff = min - 65, max_diff = 122 - max;
		for (int j = 0; j <= min_diff + max_diff; j++) {
			for (i = 0; i < 10; i++) {
				char x = (int_arr[i] - min_diff) + j;
				int y = (int_arr[i] - min_diff) + j;
				std::cout << x << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "Enter space-separated notes for conversion to MIDI values:" << std::endl;
		std::getline(std::cin, input);
	} while (input != QUIT_COMMAND);
	return 0;
}

std::map<std::string, int> buildMap() {
	int i = 0, j = MIDI_START;
	std::map<std::string, int> notes;
	while (i < MIDI_VALUES) {
		for (int k = 0; k < OCTAVE; k++) {
			notes.insert(std::make_pair(concat(letters[k], '\0', j), i));
			i++;
			if (sharps[k]) {
				notes.insert(std::make_pair(concat(letters[k], '#', j), i));
				notes.insert(std::make_pair(concat(letters[k], '#', j), i));
				notes.insert(std::make_pair(concat(letters[k + 1], 'b', j), i));
				notes.insert(std::make_pair(concat(letters[k + 1], 'b', j), i));
				i++;
			}
		}
		j++;
	}
	return notes;
}

int toMIDI(std::string key, std::map<std::string, int> notes) {
	auto it = notes.find(key);
	if (it == notes.end()) {
		std::cout << "Couldn't find key " << key << std::endl;
		return -1;
	};
	return it->second;
}

std::string concat(char note, char modifier, int octave) {
	std::ostringstream pitch;
	if (modifier) pitch << note << modifier << octave;
	else pitch << note << octave;
	return pitch.str();
}

void printMap(std::map<std::string, int> hashmap) {
	for (auto i = hashmap.begin(); i != hashmap.end(); i++) {
		std::cout << i->first << " :: " << i->second << std::endl;
	}
}

int getMin(int* arr, int len) {
	int curr = INT_MAX;
	for (int i = 0; i < len; i++) {
		if (arr[i] < curr) curr = arr[i];
	}
	return curr;
}

int getMax(int* arr, int len) {
	int curr = INT_MIN;
	for (int i = 0; i < len; i++) {
		if (arr[i] > curr) curr = arr[i];
	}
	return curr;
}