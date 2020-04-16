#include <iostream> //std::cout, std::cin
#include <fstream> //std::fstream, loads files into buffer for allocation to table
#include <string> //std::string
#include <vector>
#include <cassert>
#include <list>
#include <windows.h>
#define MAXCHAR 256

//REF1 https://www.tutorialspoint.com/Rabin-karp-Algorithm
//REF2 https://www.tutorialspoint.com/Boyer-Moore-Algorithm

void RobinKarpSearch(std::string mainString, std::string Pattern, int Prime, int Array[], int* index);
void BoyerMooreSearch(std::string mainString, std::string Pattern, int Array[], int* index);
void Totalmatch(int Shift[], int Array2[], std::string Pattern);
void Totalmatch(int Shift[], int Array2[], std::string Pattern);
void NotTotalMatch(int Shift[], int Array2[], std::string Pattern);

int main()
{
	//Declaring search list
	int Prime = 7;
	int index = -1;
	int X = 0;

	std::cin.clear(); //Clear buffer
	std::ifstream file("Macbeth.txt"); //Load file as string into Mac string
	std::string Mac; //Loads file into buffer
	std::getline(file, Mac); //Load text continuing from line 1
	std::string Term = "Scotland"; //Search term to use

	int Size = Mac.size();
	bool input;
	std::string S = "Scotland found";
	std::vector<int> VectorA(Size);

	std::cout << "0 Boyer Moore \n" << "1 Rabin Karp \n";
	std::cin >> input;
	switch (input)
	{
	case 0: std::cin.clear(); Search(Mac, Term, &(VectorA)[0], &index);
		for (int i = 0; i <= index; i++) 
		{
			X = X + 1;
			std::cout << S << " found at \n" << VectorA[i] << "\n";
		}
		std::cout << S << X << " times \n";
		break;

	case 1: std::cin.clear(); FishmanSearch(Mac, Term, Prime, &(VectorA)[0], &index);
		for (int i = 0; i <= index; i++) 
		{
			X = X + 1;
			std::cout << S << " found at \n" << VectorA[i] << "\n";
		}
		std::cout << S << X << " times \n";
		break;
	}
	Sleep(10000);
	std::cout << "Byebye";
	exit(0);
}

void RobinKarpSearch(std::string mainString, std::string Pattern, int Prime, int Array[], int* index)
{ 
	int patLen = Pattern.size();
	int strLen = mainString.size();
	int charIndex, pattHash = 0, strHash = 0, h = 1;

	for (int i = 0; i < patLen - 1; i++) 
	{
		h = (h * MAXCHAR) % Prime;
	}

	for (int i = 0; i < patLen; i++) 
	{
		pattHash = (MAXCHAR * pattHash + Pattern[i]) % Prime;
		strHash = (MAXCHAR * strHash + mainString[i]) % Prime;
	}

	for (int i = 0; i <= (strLen - patLen); i++) 
	{
		if (pattHash == strHash) {
			for (charIndex = 0; charIndex < patLen; charIndex++) 
			{
				if (mainString[i + charIndex] != Pattern[charIndex])
					break;
			}

			if (charIndex == patLen) 
			{
				(*index)++;
				Array[(*index)] = i;
			}
		}
		if (i < (strLen - patLen)) 
		{
			strHash = (MAXCHAR * (strHash - mainString[i] * h) + mainString[i + patLen]) % Prime;
			if (strHash < 0) 
			{
				strHash += Prime;
			}
		}
	}
}

void BoyerMooreSearch(std::string mainString, std::string Pattern, int Array[], int* index)
{
	int patLen = Pattern.size();
	int strLen = mainString.size();
	int* Array2ay = new int[patLen + 1];
	int* ShiftArray = new int[patLen + 1];

	for (int i = 0; i <= patLen; i++) 
	{
		ShiftArray[i] = 0;
	}

	Totalmatch(ShiftArray, Array2ay, Pattern);
	NotTotalMatch(ShiftArray, Array2ay, Pattern);
	int Shift = 0;

	while (Shift <= (strLen - patLen)) 
	{
		int j = patLen - 1;
		while (j >= 0 && Pattern[j] == mainString[Shift + j]) 
		{
			j--;
		}

		if (j < 0) 
		{
			(*index)++;
			Array[(*index)] = Shift;
			Shift += ShiftArray[0];
		}else 
		{
			Shift += ShiftArray[j + 1];
		}
	}
}

void Totalmatch(int Shift[], int Array2[], std::string Pattern)
{                            
	int n = Pattern.size();
	int i = n;
	int j = n + 1;
	Array2[i] = j;

	while (i > 0) {
		while (j <= n && Pattern[i - 1] != Pattern[j - 1]) 
		{
			if (Shift[j] == 0)
				Shift[j] = j - i;
			j = Array2[j];
		}
		i--;
		j--;
		Array2[i] = j;
	}
}

void NotTotalMatch(int Shift[], int Array2[], std::string Pattern)
{                         
	int n = Pattern.size();
	int j;
	j = Array2[0];

	for (int i = 0; i < n; i++) 
	{
		if (Shift[i] == 0)
		Shift[i] = j;
		if (i == j)
		j = Array2[j];
	}
}

