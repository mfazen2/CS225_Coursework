/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    vector<string> words;
    ifstream filewords(filename);
    string curword;
    if (filewords.is_open()){
        while(getline(filewords,curword)){
            string sort = curword;
            std::sort(sort.begin(),sort.end());
            dict[sort].push_back(curword);
        }
    }
    filewords.close();
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (string cur: words){
        string sort = cur;
        std::sort(sort.begin(),sort.end());
        dict[sort].push_back(cur);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sorted = word;
    std::sort(sorted.begin(),sorted.end());
    if(dict.find(sorted) == dict.end() || dict.at(sorted).size() == 1){return vector<string>();}
    return dict.at(sorted);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> output;
    for (auto gram : dict){
        if (gram.second.size() > 1){
            output.push_back(gram.second);
        }
    }
    return output;
}
