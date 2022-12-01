// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
#include <vector>
using namespace std;


// Add prototypes of helper functions here
void helper(
    std::string float_in,
    const std::set<std::string>& dict,
    std::set<std::string>& result,
		int blanks);

void floating_helper(
	string in,
	vector<char> floating,
	set<string> &floating_possibilities
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

		vector<char> floating_vec = vector<char>(floating.begin(),floating.end());
		set<string> floating_possibilities;
		floating_helper(in, floating_vec, floating_possibilities);

    std::set<std::string> result;
		int count = -floating.size();
		for(unsigned int i = 0; i < in.size(); i++){
			if(in[i] == '-'){
				count++;
			}
		}

		for (string float_in: floating_possibilities) {
			helper(float_in, dict, result, count);
		}

    return result;
}

// Define any helper functions here

void floating_helper(
	std::string in,
	std::vector<char> floating,
	std::set<std::string> &floating_possibilities) 
{
	if (!floating.size()) {

		floating_possibilities.insert(in);
		return;

	}

	char curr = floating[floating.size() -1];

	floating.pop_back();

	for (unsigned int i = 0; i < in.size(); i++) {
		if (in[i] != '-') {
			continue;
		}

		string copy_in = in;
		copy_in[i] = curr;
		floating_helper(copy_in, floating, floating_possibilities);
	}

}

void helper(
    std::string in,
    const std::set<std::string>& dict,
    std::set<std::string>& result,
		int blanks)
{

  string temp = in;

	if (!blanks) {
		// Check if word in dict

		if(dict.find(temp) != dict.end()){
			result.insert(temp);
		}

		return;
	}

	// Get index of next '-' 
	int idx = 0;
	for (unsigned int i = 0; i < in.size(); i++) {
		if (in[i] == '-') {
			idx = i;
			break;
		}
	}

	// Fill blank spot
	for (int i = 97; i < 123; i++) {
		in[idx] = i;
		helper(in,dict,result,blanks-1);
	}

}
