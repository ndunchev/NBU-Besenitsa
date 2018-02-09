#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void loadDictionary(const char* in_file, set<string>& words) {
	ifstream in;

	in.open(in_file);

	if (in.fail()) {
		throw - 1;
	}

	char buf[100];
	while (!in.eof()) {
		in.getline(buf, 99);
		words.insert(buf);
	}

	in.close();
}


char getLetterFromUser() {
	cout << "\nGuess a letter: ";
	char c;
	cin >> c;
	return c;
}

int main()
{
	set<string> words;
	loadDictionary("words.txt", words);
	set<string>::iterator it;
	for (it = words.begin(); it != words.end(); it++)
	{
		cout << *it << endl;
	}

	// TODO: ask user if the user is going to play or the computer should play by itself

	// TODO: Choose a random word from the set

	string chosen_word;

	int total_turns = chosen_word.length() - 1; // total_turns is the number of mistakes the user can make before being hanged

	int remaining_turns = total_turns;

	while (remaining_turns) {
		// TODO: print UI
		// get letter from user OR make the computer come up with a letter if the computer is playing
		// show if letter was correctly guessed
		// decrease turns if the letter was wrong
	}
}

