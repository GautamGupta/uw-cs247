#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <random>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

using namespace std;

namespace {

    const int MIN_WORD_LENGTH = 6;
    const string FILE_OUT = "gamewords";
    const int MAX_GUESSES = 5;
    const char PLAY_AGAIN_ANSWER = 'Y';
    const string TXT_WIN = "WIN";
    const string TXT_LOSE = "LOSE";

    /**
     * Check if character is an alphabet or not
     */
    class isNonAlpha {
    public:
        bool operator() (char c) {
            return !isalpha(c);
        }
    };

    /**
     * Print WIN/LOSE (+ word)
     */
    void printGameResult(string result, string word = "") {
        cout << "You " << result << "!";
        if (word.length() > 0) {
            cout << "  The word was \"" << word << "\".";
        }
        cout << endl;
    }

    bool isLetterInGuesses(vector<char> guessed, char c) {
        return find(guessed.begin(), guessed.end(), c) != guessed.end();
    }

    /**
     * Count matching characters
     */
    int countMatches(vector<char> guessed, string word) {
        return count_if(word.begin(), word.end(), [guessed](char c) -> bool {
            return isLetterInGuesses(guessed, c);
        });
    }
}

int main(int argc, char* argv[]) {

    // Read parameters
    string inName;
    int seed = 0;
    if (argc > 1) {
        inName = string(argv[1]);
    } else {
        cout << "Error: No input file specified." << endl;
        return -1;
    }
    if (argc > 2) {
        seed = atoi(argv[2]);
    }

    // RNG
    mt19937 random(seed);

    // Read words from file into vector
    ifstream inFile(inName);
    if (!inFile) {
        cout << "Error: Could not open file \"" << inName << "\"." << endl;
        return -1;
    }
    istream_iterator<string> inIter(inFile);
    istream_iterator<string> eof;
    vector<string> unfilteredWords(inIter, eof), words;
    inFile.close();

    // Filter words
    remove_copy_if(unfilteredWords.begin(), unfilteredWords.end(), back_inserter(words),
        [](const string &word) -> bool {
            bool containsNonAlpha = find_if(word.begin(), word.end(), isNonAlpha()) != word.end();
            return (word.length() < MIN_WORD_LENGTH || containsNonAlpha);
    });
    if (words.size() == 0) {
        cout << "Error: Pool of game words is empty." << endl;
        return -1;
    }

    // Output words to a file
    ofstream outFile(FILE_OUT);
    ostream_iterator<string> outIter(outFile, "\n");
    copy(words.begin(), words.end(), outIter);
    outFile.close();

    // Game loop
    do {
        // Reset
        int remainingGuesses = MAX_GUESSES;
        vector<char> guessed;
        string word = words.at(random() % words.size());

        // Game loop
        while (remainingGuesses > 0) {
            cout << "Word: ";

            // Print guessed part of the word
            string partWord = accumulate(word.begin(), word.end(), string(), [&guessed](string &partWord, char c) -> string {
                partWord.push_back(isLetterInGuesses(guessed, c) ? c : '-');
                return partWord;
            });
            cout << partWord << endl;

            // Letters used
            cout << "Letters used: ";
            ostream_iterator<char> outIter(cout, " ");
            copy(guessed.begin(), guessed.end(), outIter);
            cout << endl;

            // Num lives left
            if (remainingGuesses == 1) {
                cout << "You have 1 life left." << endl;
            } else {
                cout << "You have " << remainingGuesses << " lives left." << endl;
            }

            // Ask for next guess
            cout << "Next guess: ";
            string guess;
            cin >> guess;

            // Guess whole word
            if (guess.length() > 1) {
                if (guess != word) {
                    printGameResult(TXT_LOSE, word);
                } else {
                    printGameResult(TXT_WIN);
                }
                break;

            // Guess letter
            } else {
                char guessChar = tolower(guess[0]);

                // Check if the player has already guessed the letter
                if (isLetterInGuesses(guessed, guessChar)) {
                    cout << "You already guessed letter \"" << guessChar << "\"." << endl;
                } else {
                    // Compare matching # letters before and after
                    int matchesBefore = countMatches(guessed, word);
                    guessed.push_back(guessChar);
                    int matchesAfter = countMatches(guessed, word);

                    // Correct guess
                    if (matchesAfter > matchesBefore) {
                        if (matchesAfter == word.size()) {
                            // Guessed full word
                            printGameResult(TXT_WIN, word);
                            break;
                        }

                    // Wrong guess
                    } else {
                        remainingGuesses--;
                    }
                }
            }

            if (remainingGuesses == 0) {
                printGameResult(TXT_LOSE, word);
            }
        }

        char answer;
        cout << "Do you want to play again? [Y/N] ";
        cin >> answer;
        if (toupper(answer) != PLAY_AGAIN_ANSWER) {
            break;
        }
    } while (true);

    return 0;
}
