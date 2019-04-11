//20181224 Jeong GangSan

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int* strSplit(string);

int main()
{
	ifstream inFile;
	inFile.open("input.txt");
	//Get first line of classes
	//and convert to int
	char _totalNumber;
	inFile.get(_totalNumber);
	int totalNumber = (int)_totalNumber - 48;
	

	//for totalnumber, get lines
	//
	int *scores;
	int studentNumber;
	int sum = 0;

	string classInfo;
	for (int i = 0; i < totalNumber; ++i)
	{
		getline(inFile, classInfo);
		scores = strSplit(classInfo);	//split string to int array? list?
		studentNumber = scores[0];
		sum = 0;

		// sum components and get average
		for (int i = 0; i < studentNumber; ++i)
		{
			sum += scores[i + 1];
		}


		// get percentage below average

	}

	//test
	/*string testString = "500 50 50 70 80 100";
	int *scores = strSplit(testString);
	for (int i = 0; i < 6; ++i)
	{
		cout << scores[i] << " ";
	}*/


	return 0;
}


//Split strings with scores
//text.substr(start, end): string slice 
int* strSplit(string str)
{
	static int Scores[100]; // ***Need to optimzie. Use list?***

	char ch;
	int strIndex = 0;
	int scoreIndex = 0;
	string num = "";

	for (int i = 0; i < str.length() + 1; i++)
	{
		ch = str[strIndex];
		if (ch == ' ' || ch == '\0')	//When meet seperator, store and reset
		{
			Scores[scoreIndex++] = stoi(num);
			num = "";
			strIndex++;
			continue;
		}
		else
		{
			num += ch;
			strIndex++;
		}
	}

	return Scores;
}
