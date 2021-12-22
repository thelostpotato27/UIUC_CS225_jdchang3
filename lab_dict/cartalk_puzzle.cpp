/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    string word_orig;
        while (getline(wordsFile, word_orig)) {
            if(word_orig.size() > 1){
                string first_letter_gone = word_orig.substr(1, word_orig.size() - 1);
            	string sec_letter_gone = word_orig[0] + word_orig.substr(2, word_orig.size() - 1);
                if(d.homophones(word_orig, first_letter_gone) && d.homophones(word_orig, sec_letter_gone)){
                    std::tuple<string, string, string> return_val (word_orig, first_letter_gone, sec_letter_gone);
                    ret.push_back(return_val);
                }
            }
        }
        wordsFile.close();
    }
    return ret;
}
