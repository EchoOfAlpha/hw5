#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <queue>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool isValid(const std::string test, const std::set<std::string>& dict);

void wordGen(std::string in_, std::queue<char> floating_, const std::set<std::string>& dict_, std::set<string>& solutions_, int currIndex_, int max, const std::string& orig);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    // Possible solutions
    std::set<std::string> solutions;

    // assign modFloat
    std::queue<char> modFloat;
    int fSize = 0;
    int modFCount = 0;
    if(floating.size() > 0)
    {
        fSize = floating.size();
    }
    for(unsigned int i = 0; i < in.size(); i++)
    {
        if(in[i] == '-')
        {
            if(fSize != 0)
            {
                modFloat.push(floating[modFCount]);
                modFCount++;
                fSize--;
            }
            else
            {
                modFloat.push('*');
            }  
        }
    }

    // modifiable input
    std::string input = in;

    if(input != "")
    {
        wordGen(input, modFloat, dict, solutions, 0, in.size(), in);
    }
    

    return solutions;

}

// Define any helper functions here
bool isValid(const std::string test, const std::set<std::string>& dict)
{
    if(dict.find(test) == dict.end())
    {
        return false;
    }

    return true;
}

void wordGen(std::string in_, std::queue<char> floating_, const std::set<std::string>& dict_, std::set<string>& solutions_, int currIndex_, int max, const std::string& orig) 
{
    // base case - hitting past the last letter
    if(currIndex_ == max)
    {
        //std::cout << in_.size() << ": " << in_ << endl;
        if(dict_.find(in_) == dict_.end())
        {
            return;
        }

        else
        {
            solutions_.insert(in_);
        }
    }
    // skip case
    if(orig[currIndex_] != '-')
    {
        wordGen(in_, floating_, dict_, solutions_, currIndex_ + 1, max, orig );
    }

    else
    {
        int fSize = floating_.size();
        for(int i = 0; i < fSize; i++)
        {
            if(floating_.front() == '*')
            {
                floating_.pop();
                
                for(char c = 'a'; c <= 'z'; c++)
                {
                    in_[currIndex_] = c;
                    wordGen(in_, floating_, dict_, solutions_, currIndex_ + 1, max, orig);
                }

                floating_.push('*');
            }

            else 
            {
                in_[currIndex_] = floating_.front();
                floating_.pop();
                wordGen(in_, floating_, dict_, solutions_, currIndex_ + 1, max, orig);
                floating_.push(in_[currIndex_]); 
            }
            
        }
    }
}