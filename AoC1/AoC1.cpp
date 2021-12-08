// AoC1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	cout << "Which challenge? ";
	int challenge;
	cin >> challenge;
	switch( challenge )
	{
	case 11:
	{
		ifstream in( "input.txt" );
		string strVal;
		int lastVal = 999;
		int depInc = 0;
		while ( getline( in, strVal ) )
		{		
			int val = stoi( strVal );
			if ( val > lastVal )
				depInc++;
			lastVal = val;
		}
		cout << depInc;
		break;
	}
	case 12:
	{
		ifstream in( "input.txt" );
		string strVal;
		int window[4] = { -1, -1, -1, -1 };
		int line = 0;
		int depInc = 0;
		while ( getline( in, strVal ) )
		{
			int val = stoi( strVal );
			window[line%4] = val;
			line++;
			if ( line < 4 )
				continue;

			int d1 = window[ ((line - 4) % 4)] +
				window[((line - 3) % 4)] +
				window[((line - 2) % 4)];

			int d2 = window[((line - 3) % 4)] +
				window[((line - 2) % 4)] +
				window[((line - 1) % 4)];

			if ( d2 > d1 )
				depInc++;
		}
		cout << depInc;
		break;
	}
	case 21:
	{
		ifstream in( "input2.txt" );
		string strVal;
		int pos = 0, dep = 0;
		while ( getline( in, strVal ) )
		{
			size_t spos = strVal.find_last_of( ' ' );
			int val = stoi( strVal.substr( spos ) );
			switch ( strVal[0] )
			{
			case 'f':
				pos += val;
				break;
			case 'd':
				dep += val;
				break;
			case 'u':
				dep -= val;
				break;
			default:
				;
			}
		}
		cout << pos * dep;
		break;
	}
	case 22:
	{
		ifstream in( "input2.txt" );
		string strVal;
		int pos = 0, dep = 0;
		int aim = 0;
		while ( getline( in, strVal ) )
		{
			size_t spos = strVal.find_last_of( ' ' );
			int val = stoi( strVal.substr( spos ) );
			switch ( strVal[0] )
			{
			case 'f':
				pos += val;
				dep += aim * val;
				break;
			case 'd':
				aim += val;
				break;
			case 'u':
				aim -= val;
				break;
			default:
				;
			}
		}
		cout << pos * dep;
		break;
	}
	case 31:
	{
		break;
	}
	default:
		;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
