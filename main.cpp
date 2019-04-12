//20181224 Jeong GangSan

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int* strSplit(string, int*);
int getAvg(int*, int);

int main()
{
	ifstream inFile;
	inFile.open("input.txt");

	string _totalNumber;
	getline(inFile, _totalNumber);
	int totalNumber = stoi(_totalNumber);
	_totalNumber.clear();

	if (totalNumber == 0)
		return 0;

	//Exception 1
	if (totalNumber > 1000 || totalNumber < 0)
	{
		cout << "error_code_1";
		return -1;
	}

	int *scores;
	int studentNumber;
	int average = 0;
	int belowAvgCount;
	int classNumber = 0;
	int scoreCount = 0;
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
		average = 0;
		belowAvgCount = 0;
		scoreCount = 0;

		getline(inFile, classInfo);
		scores = strSplit(classInfo, &scoreCount);	//split string to int array[102]
		studentNumber = scores[0];

		//Exception 3
		if (studentNumber > 100 || studentNumber <= 0)
		{
			cout << "error_code_3";
			return -1;
		}

		//Exception 4
		if (scoreCount != studentNumber)
		{
			cout << "error_code_4";
			return -1;
		}

		// sum components and get average
		average = getAvg(scores, studentNumber);
		//Exception 5
		if (average == -1)
		{
			cout << "error_code_5";
			return -1;
		}


		// get percentage below average
		for (int i = 0; i < studentNumber; ++i)
		{
			if (scores[i + 1] < average)
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
int* strSplit(string str, int *ScoreCount)
{
	static int Scores[101]; // ***Need to optimzie. Use list?***

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
			ScoreCount[0]++;
			continue;
		}
		else
		{
			num += ch;
			strIndex++;
		}
	}
	ScoreCount[0] -= 1;	//except student number

	return Scores;
}


//get score average and return -1 if exception5
int getAvg(int Scores[], int StudentNumber)
{
	int sum = 0;
	for (int i = 0; i < StudentNumber; ++i)
	{
		//Exception 5
		if (Scores[i + 1] < 0 || Scores[i + 1] > 100)
		{
			return -1;
		}

		sum += Scores[i + 1];
	}

	return (double)sum / StudentNumber;
}
