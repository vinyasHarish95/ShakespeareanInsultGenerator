
/*
 ---Vinyas Harish---

 The following program is designed to serve as a source for Shakesperian insults. 2 adjectives and a noun are read from a text
 file called "InsultsSource.txt", and a number of unique insults are generated and written to a new text file. To ensure that the
 insults are unique, the C++ Standard Library container-type set is used. Thereby, we ensure that they are always in sorted order
 and are unique. Internally, this is done using a red-black tree.

 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include "InsultGenerator.h"

using namespace std;

FileException::FileException(const string& m) : message(m) {} //end exception constructor

string FileException::what() const {
	return message;
} //end file exception method

InsultGenerator::InsultGenerator() : sourceLength(0) {} //end insult constructor

void InsultGenerator::initialize() {
	string line;
	ifstream fileIn(INSULTS_SOURCE.c_str());
	sourceLength = 0;
	if (fileIn.is_open()){
	 while (!fileIn.eof()) {
		 fileIn >> line;
		 adjective1.push_back(line);
		 fileIn >> line;
		 adjective2.push_back(line);
		 fileIn >> line;
		 noun.push_back(line);
		 sourceLength++;
	 }
	fileIn.close();
	}
	else if (fileIn.fail()) {
		throw FileException("Insults source file: " + INSULTS_SOURCE + " cannot be read.");
		return;
	} //end exception check
} //end initialize method

int InsultGenerator::randomInt(int upperBound){
	int randInt = rand() %upperBound; //Use built-in random number generator.
	return randInt;
} //end randomInt method

string InsultGenerator::talkToMe(){
	string insult("Thou ");
		insult += adjective1.at(randomInt(sourceLength));
		insult += ", " + adjective2.at(randomInt(sourceLength)) + " ";
		insult += noun.at(randomInt(sourceLength)) + "!";
		return insult;
	} // end talkToMe method

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& m) : message(m) {} //end exception constructor

string NumInsultsOutOfBounds::what() const {
	return message;
} //end exception method

vector<string> InsultGenerator::generate(int numInsults){
	if (numInsults < 1 || numInsults > MAX_NUM_INSULTS){
		throw NumInsultsOutOfBounds("This is not valid for the number of insults! Must be between 1-10,000");
	} //end exception check

	set<string> setOfInsults;
	string insult;
	while (numInsults > setOfInsults.size()) {
		insult = std::string(talkToMe());
		setOfInsults.insert(insult);
	} //Create a set of insults, sets do not have repeats and are sorted.

	vector<string> insults;
	copy(setOfInsults.begin(), setOfInsults.end(), back_inserter(insults));
	return insults;
} //end generate method

void InsultGenerator::generateAndSave(string filename,int numInsults){
	int lineNumber = 0;
	vector <string> insultVector = generate(numInsults);
	ofstream fileOut(filename.c_str());
	if (fileOut.fail()){
		throw FileException("Your file:" + filename + "cannot be written");
	} //end file exception check

	while (lineNumber <numInsults) {
		fileOut << insultVector[lineNumber] <<endl;
		lineNumber++;
	}
	fileOut.close();
} //end generateAndSave method
