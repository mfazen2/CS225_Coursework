/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iterator>

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
                                                                         const string &word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    string curline;
    ifstream file(word_list_fname);
    if (file.is_open()){
        while(getline(file,curline)){
            if (curline.size() == 5){
                string w1 = curline.substr(1,curline.size()-1);
                string w2 = curline[0] + curline.substr(2, curline.size() -1);
                if (d.homophones(curline,w1) && d.homophones(curline,w2)){
                    ret.push_back(std::tuple<std::string,std::string,std::string>(curline,w1,w2));
                }
            }
        }
    }
    return ret;
}
