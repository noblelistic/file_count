/*****************************************************************************************************************
* main.cpp of the FileCount program
* Program takes string of file name ending in .txt and adds all numbers in file. If there is a 
* string it will be assumed to be another file name. Number and strings must be one per line.
* If file has no numbers then the file total is 0. Program treats all files has separate even
* if they are the same. Be careful not to do repeat nest(ex. If a.txt has b.txt in it then a.txt
* can not be in b.txt). This will cause an infinte loop, stack overflow. In order the open file 
* that the user inputs file must be in local directory.
* Brian Phipps - April 1, 2015
******************************************************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<regex>
#include<vector>

using namespace std;

int openFileAdd(vector<int>&, vector<string>&, string, int&);
void fileCount(string);
void fileCountDisplay(vector<int>, vector<string>);

int main(){
	
	string file;                                           // Where string of file name will stored
	
	cout << "Pease enter file name to start File Count: "; // Get file name from user
	cin >> file;
	
	fileCount(file);                                       // Counting all the number in file(s)
	
	system("PAUSE");
	return 0;

}

void fileCount(string file)
// POSTCONDITION: Print to screen file information
{

	int count = 0;
	vector<int> vInt;
	vector<string> vString;

	openFileAdd(vInt, vString, file, count);

	fileCountDisplay(vInt, vString);
}

int openFileAdd(vector<int>& vInt, vector<string>& vString, string file, int& count)
// PRECONDITION: Do not repeat nest(ex. If a.txt has b.txt in it then a.txt can not be in b.txt)
// POSTCONDITION: Loads both vectors with file information and returns sum of all files it has opened
{
	
	int position = count;
	string stringLine;
	
	ifstream myfile;
	myfile.open(file);

	vInt.push_back(0); 
	vString.push_back(file); // In order the open file that the user inputs file must be in local directory.

	if (myfile.is_open()){  // if: for testing to ensure file is open

		while ( getline (myfile,stringLine) ){   // while: for getting line till eof
			// setup regex for string evaluation
			regex is_int("\\d+");
			regex is_string("(.*)\\.txt");
			bool matchInt = regex_match(stringLine, is_int);
			bool matchString = regex_match(stringLine, is_string);

			if (matchInt){                                            
				int intLine = stoi(stringLine);
				vInt.at(position) += intLine;
			}else if(matchString) {
				count++;
				int a = vInt.at(position);
				a += openFileAdd(vInt, vString, stringLine, count);  // Recursivly call openFileAdd 
				vInt.at(position) = a;                               // and add its return to current file

			}
		}
	}else{
		cout << "Can't open file" << endl;
	}

	return (vInt.at(position));

}

void fileCountDisplay(vector<int> vInt, vector<string> vString)
// POSTCONDITION: Iterates through both vectors, vInt all file sums and vString file names, and prints.
{
	
	for (unsigned int i = 0; (i < vInt.size()) && (i < vString.size()); i++){
			cout << "File name: " << vString.at(i) << " File count : " << vInt.at(i) << endl;
		}
}
