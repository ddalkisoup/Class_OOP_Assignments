//20181224 Jeong GangSan

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int* strSplit(string);

int main()
{
	ifstream inFile;
	inFile.open("input.txt");
	//Get first line of classes
	//and convert to int
	string _totalNumber;
	getline(inFile, _totalNumber);
	int totalNumber = stoi(_totalNumber);

	if (totalNumber == 0)
		return 0;

	//Exception 1
	if (totalNumber > 1000 || totalNumber < 0)
	{
		cout << "error_code_1";
		return -1;
	}

	//for totalnumber, get lines
	int *scores;
	int studentNumber;
	int sum = 0;
	int belowAvgCount;
	int classNumber = 0;
	string classInfo;

	//Exception 2
	int getLineCount = 0;
	string testString;
	while (true)
	{
		getline(inFile, testString);
		if (!inFile.fail())
			getLineCount++;
		else
			break;
	}
	if (getLineCount != totalNumber)
	{
		cout << "error_coed_2";
		return -1;
	}

	inFile.clear();
	inFile.seekg(0L, ios::beg);	//move cursor to begining	
	getline(inFile, testString);    //move cursor to 2nd line
	testString.clear();

	ofstream outFile;
	outFile.open("output.txt");

	for (int i = 0; i < totalNumber; ++i)
	{
		getline(inFile, classInfo);
		scores = strSplit(classInfo);	//split string to int array[102]
		studentNumber = scores[0];

		//Exception 3
		if (studentNumber > 100 || studentNumber <= 0)
		{
			cout << "error_code_3";
			return -1;
		}

		//Exception 4
		if (scores[102] != studentNumber)
		{
			cout << "error_code_4";
			return -1;
		}

		sum = 0;
		belowAvgCount = 0;

		// sum components and get average
		for (int i = 0; i < studentNumber; ++i)
		{
			//Exception 5
			if (scores[i + 1] < 0 || scores[i + 1] > 100)
			{
				cout << "error_code_5";
				return -1;
			}
			
			sum += scores[i + 1];
		}

		// get percentage below average
		for (int i = 0; i < studentNumber; ++i)
		{
			if (scores[i + 1] < (double)sum / studentNumber)	//average
				belowAvgCount++;
		}
		classNumber++;

		// #CN xx.xxx%
		outFile << "#" << classNumber << " "
			<< fixed << setprecision(3)
			<< (double)belowAvgCount / studentNumber * 100    //below average percent
			<< "%" << endl;
	}

	inFile.close();
	outFile.close();


	return 0;
}


//Split strings with scores
//text.substr(start, end): string slice 
int* strSplit(string str)
{
	static int Scores[102]; // ***Need to optimzie. Use list?***
	                        // Scores[102]: number of scores

	char ch;
	int strIndex = 0;
	int scoreIndex = 0;
	int scoreCount = 0;    //for exception 4
	string num = "";

	for (int i = 0; i < str.length() + 1; i++)
	{
		ch = str[strIndex];
		if (ch == ' ' || ch == '\0')	//When meet seperator, store and reset
		{
			Scores[scoreIndex++] = stoi(num);
			num = "";
			strIndex++;
			scoreCount++;
			continue;
		}
		else
		{
			num += ch;
			strIndex++;
		}
	}
	Scores[102] = scoreCount - 1;    //except student number

	return Scores;
}
