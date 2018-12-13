/*
                       Programed by :          Mouatassim Boulahsen
					   Date :                  7/12/2018
					   Goal :                  guess the word game...
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

// globale variables and consts....

// fonctions...

vector<char> returnWordLines(string &word, vector<char> &word2); // a function that takes a string and a vector as paramametres and return a vector
void verifyTheAnswer(string &word, vector<char> &word2, int &count, char answer, int &lives, int &score); // verifiy the answers and calculate the score
string getWordFlux(); // opens the file and gets the word
void reset(vector<char> &word, vector<char> &history, int &result, int &lives, int &count, char &choice, string &word1); // reset all values
// --- Main ---

int main(void) {

	// Declare variables...
	string word1 = "", player1Name = "", player2Name = "";
	char answer = NULL, choice = NULL;
	int count = 0, lives = 10, score = 0;
	int result = 0;
	vector<char> word2 , history;

		// main menu
		cout << setw(70) << right << "=== BONHOMME PENDU === \n\n" << endl; // title

		// rules..
		cout << "Rules :" << endl
			<< "\t1 - You have to guess the word !"<< endl
			<< "\t2 - You got only 10 tries to guess the word" << endl
			<< "\t4 - have fun..." << endl << endl;
		cout << setfill('=') << right << setw(50) << "=" << endl << endl;
		cout << "Enter player1's name : "; // ask the user to enter the name
		cin >> player1Name; // input of user
		cout << setfill('=') << right << setw(50) << "=" << endl << endl;

		do {
			// Reset
			reset(word2, history, result, lives, count, choice, word1);
			// start of turn
			word1 = getWordFlux(); // gets the word from the function and assign it to the variable

			system("cls"); // clear screen
			cout << word1 << endl; // show the word to the developper
			word2 = returnWordLines(word1, word2); // return the word as lines

			do {
				cout << "\n" << player1Name << " -> " << score << "/ Answer : "; // ask the player to answer
				cin >> answer; // input user's answer
				answer = tolower(answer); // turn the answer into lower case
				history.push_back(answer); // adds the used character to the array
				verifyTheAnswer(word1, word2, count, answer, lives, score); // verify the answer

				cout << "Used lettres -> "; // output history letters
				for (int i = 0; i < history.size(); i++) // loop throught the history array
					cout << history[i] << ", "; // output the array
				cout << endl; // new line

				// gameOver...
				if (!lives) { // verify if letters equal to 0
					result = 0; // then result equal 0
					cout << "\n\n\n[GAME OVER] You lost this round!!!!" << endl // ouput game over
						<< "Score : " << score << endl; // output the score
					break; // break for loop
				}

				if (count >= word2.size()) { // verify if the correct letters is equal to the length of the word

					for (int i = 0; i < word2.size(); i++) { // loops through the array num 2
						if (word1[i] == word2[i]) // if the word is equal to array
							result += 100; // set result to 100
						else // if not
							result = 0; // set result to 0
					}

					if (result >= 100) { // if result is 100
						cout << "\n\nYou've won this round!!!! \n" << endl // output game won
							<< "Score : " << score << endl; // ouput score
						break;
					}
				}

			} while (!result); // repeat while result is null

			// Repeat ??
			cin.clear(); // clear error flags
			cin.ignore(); // ignore next new line
			cout << "Would you like to play another turn (Y -> Yes /N -> No) ? :"; // ask the user if he wants to repeat
			cin >> choice; // input of user
			choice = toupper(choice); // turn the input into upper case

			while (choice != 'Y' && choice != 'N') { // validate the user input 
				cin.clear(); // clear error flags
				cin.ignore(); // ignore next new line
				cerr << "[ERROR]: Your choice doesn't exist" << endl; // output error
				cout << "(Y/N) : "; // ask the user to enter new value
				cin >> choice; // input of user
				choice = toupper(choice); // turn the input into upper case
			}

		} while (choice == 'Y'); // repeat if the input is equal to Ym

	// end of program
	cout << "\n\nThank you for playing our game! See you next time.... "; // output goodbye text
	cin.clear(); // clear error flags
	cin.ignore(); // ignore next new line
	cin.get(); // get enter from user
	return(0);
}

vector<char> returnWordLines(string &word, vector<char> &word2)
{

	for (int i = 0; i < word.length(); i++) { // loops as much as the word length
		word2.push_back('_'); // adds a _ to the array
		cout << word2[i] << " "; // output the array
	}
	
	cout << endl; // new line
	return word2; // return the array
}

void verifyTheAnswer(string &word, vector<char> &word2, int &count, char answer, int &lives, int &score)
{
	system("cls"); // clear the screen
	int num = 0; // declare a variable

	for (int j = 0; j < word2.size(); j++) { // loops throught the array
		if (answer == word[j]) { // verify if the answer is equal to the character of the world
			word2[j] = answer; // change the _ into the given letter
			count++; // adds 1 to the count
			score += 5; // add one to the score
			num++; // adds one to num
		}
		else
			num += 0; // add 0 to num
	}
	for (int i = 0; i < word2.size(); i++)
		cout << word2[i] << " "; // outputs the new version of the array

	cout << endl; // new line

	if (!num) { // if num is false
		cout << "\nWrong guess!!!!!" << endl  // outputs error 
			 << "Remaining chances -> " << --lives << endl; // and shows remaining lives
	}
}

string getWordFlux()
{
	ifstream dictionnaire("ressources/dictionnaire.txt"); // a file stream directory
	string word = ""; // initialize the variable
	srand(static_cast<unsigned int> (time(NULL))); 
	rand(); // get random number

	if (dictionnaire) // verify if the file stream exists
		for(int w = 0; w < (rand() % 837); w++) // loop as long as it's less than the random number
		getline(dictionnaire, word); // get the line in the file

	else { // if not
		cerr << "[ERROR]: The file doesn't exist, or curropted..." << endl; // output an error text
		return "\0"; // return a string equal to 0
	}
	dictionnaire.close(); // close file...
	return word; // return the word
}

void reset(vector<char> &word, vector<char> &history, int &result, int &lives, int &count, char &choice, string &word1)
{
	result = 0; lives = 10; count = 0; choice = 'N'; word1 = ""; word.clear(); history.clear(); // reset all values...
}

