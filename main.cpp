#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

vector<char> letters_used;

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

string get_word_from_dictionary(int random_word_index, set<string> &words)
{
	set<string>::iterator it;
	int index = 0;

	for (it = words.begin(); it != words.end(); it++)
	{
		if (index == random_word_index)
		{
			return *it;
		}
		index++;
	}
}

string get_mask(int mask_length)
{
	string mask = "";

	for (int i = 0; i < mask_length; i++)
	{
		mask.append("*");
	}

	return mask;
}
/*
	Searches the word for chars like the one the user entered.
*/
string update_word(string word)
{
	cout << "Chosen word is: " << word << endl;
 
	string full_word = word;

	// Always start by replacing all chars except the first and last one
	string word_with_mask = word.replace(1, word.size() - 2, get_mask(word.size() - 2));

	// Show the chars the users already guessed
	for (int i = 0; i < letters_used.size(); i++)
	{
		for (int j = 0; j < full_word.length(); j++)
		{
			if (letters_used[i] == full_word[j])
			{
				word_with_mask[j] = letters_used[i];
			}
		}
	}

	return word_with_mask;
}
/* Reads current game state (how many moves are left, which letters are used) and updates the interface accordingly*/
vector< vector<string> > update_interface(int total_turns, int remaining_turns, string word)
{
	/*
	game_ui[0][1] = moves left
	game_ui[1][1] = letters used
	game_ui[2][0] = word
	*/
	vector< vector<string> > game_ui =
	{
		{ "Moves left: ", "" },
		{ "Letters used: ", "" },
		{ "Word: ", "" },
		{ "      ", " _" },
		{ "      ", " |"},
		{ "      ", " |"},
		{ "      ", " |"},
		{ "      ", " O ", "" },
		{ "      ", "-|-", "" },
		{ "      ", "( )", "" },
		{ "\n" }
	};

	// TODO: update game_ui
	// Show the number of moves left
	game_ui[0][1] = to_string(remaining_turns);
	game_ui[1][1] = string(letters_used.begin(), letters_used.end());
	game_ui[2][1] = update_word(word);
	/*game_ui = update_hangman(game_ui);*/

	return game_ui;
}

void draw_interface(int total_turns, int remaining_turns, string word)
{
	system("CLS");
	vector< vector<string> > game_ui = update_interface(total_turns, remaining_turns, word);

	for (int i = 0; i < game_ui.size(); i++)
	{
		for (int j = 0; j < game_ui[i].size(); j++)
		{
			cout << game_ui[i][j];
		}
		cout << endl;
	}
}

int calculate_remaining_turns(string word, char input, int remaining_turns)
{
	bool char_found = false;

	// Iterate through word and compare each char with input 
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] == input)
		{
			char_found = true;
			break;
		}
	}

	if (char_found)
	{
		return remaining_turns;
	}

	return --remaining_turns;
}

int main()
{
	set<string> words;

	loadDictionary("words.txt", words);

	srand(time(NULL));

	int word_count = words.size();
	int random_word_index = rand() % word_count;

	string random_word = get_word_from_dictionary(random_word_index, words);

	cout << random_word << endl;

	// TODO: ask user if the user is going to play or the computer should play by itself

	int total_turns = random_word.length() - 1; // total_turns is the number of mistakes the user can make before being hanged

	int remaining_turns = total_turns;

	while (remaining_turns) {
		draw_interface(total_turns, remaining_turns, random_word);

		// TODO: print UI
		// get letter from user OR make the computer come up with a letter if the computer is playing
		// show if letter was correctly guessed
		// decrease turns if the letter was wrong

		char input;

		cout << "Guess a letter: ";
		cin >> input;

		if (input)
		{
			letters_used.push_back(input); // TODO: only take first letter of input
			remaining_turns = calculate_remaining_turns(random_word, input, remaining_turns);
			continue;
		}
	}
}

