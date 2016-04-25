
/*
 ---Vinyas Harish---

 The following program is designed to serve as a source for Shakesperian insults. 2 adjectives and a noun are read from a text
 file called "InsultsSource.txt", and a number of unique insults are generated and written to a new text file. To ensure that the
 insults are unique, the C++ Standard Library container-type set is used. Thereby, we ensure that they are always in sorted order
 and are unique. Internally, this is done using a red-black tree.

 */

#ifndef INSULTGENERATOR
#define INSULTGENERATOR

using namespace std;
#include <string>
#include <vector>

//Since the source of the insults is just one file, it is hard-coded.
//We can also specify the number of insults as a constant.
const string INSULTS_SOURCE("InsultsSource.txt");
const int MAX_NUM_INSULTS(10000);

//The exception thrown if the file cannot be read or if the output file cannot be read.
class FileException {
public:
	FileException(const string&);
	string what() const;
private:
	string message;
};//end FileException class

//The exception thrown if the supplied number of insults is not inclusive between 1 and 10,000
class NumInsultsOutOfBounds {
public:
	NumInsultsOutOfBounds(const string&);
	string what() const;
private:
	string message;
}; //end NumInsultsOutOfBounds exception class

// The class used to generate insults.
class InsultGenerator {
public:
	InsultGenerator();										//The default empty constructor.
	void initialize();										//Reads in the source file.
	string talkToMe();										//Creates one random insult.
	vector<string> generate(int);							//Creates a specified number of unique insults
	void generateAndSave(string filename, int numInsults);	//Generates a specified number of insults, sorted in a text file.
private:
	int sourceLength;						//The length of the source text file.
	vector<string> adjective1;				//The words in the first column of the source file.
	vector<string> adjective2;				//The phrases in the second column of the source file.
	vector<string> noun;				    //The phrases in the third column of the source file.
	int randomInt(int);                     //Returns a random integer that falls below an upper bound.
};//end InsultGenerator class

#endif /* INSULTGENERATOR */
