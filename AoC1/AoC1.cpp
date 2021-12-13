// AoC1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
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
		ifstream in( "input3.txt" );
		string strVal;
		int oneCnt[12] = { 0 };
		int rowCnt = 0;
		while ( getline( in, strVal ) )
		{
			rowCnt++;
			for ( int i = 0; i < 12; i++ )
			{
				if ( strVal[i] == '1' )
					oneCnt[i]++;
			}
		}
		int g = 0, e = 0;
		for ( int i = 0; i < 12; i++ )
		{
			g <<= 1;
			e <<= 1;
			if ( oneCnt[i] > rowCnt / 2 )
				g |= 1;
			else
				e |= 1;
		}
		cout << g * e;
		break;
	}
	case 32:
	{
		ifstream in( "input3.txt" );
		string strVal;
		deque<string> allVals;

		// Build deque of input
		while ( getline( in, strVal ) )
			allVals.push_back( strVal );
		const auto arrSz = allVals[0].size();

		// Go through list and count most in each position,
		// then eliminate values that don't have the most
		// in given position
		int results[2] = { 0 };
		for ( int state = 0; state < 2; state++ )
		{
			auto myVals = allVals;
			for ( int col = 0; col < arrSz && myVals.size() > 1; col++ )
			{
				int cntOfOnes = 0;
				for ( auto row = myVals.begin(); row != myVals.end(); row++ )
				{
					if ( (*row)[col] == '1' )
						cntOfOnes++;
				}
				char most = '0';
				if ( ((double)cntOfOnes / myVals.size()) >= 0.5 )
					most = '1';

				for ( auto row = myVals.begin(); row != myVals.end() && myVals.size() > 1; )
				{
					if ( (*row)[col] == most)
					{
						if ( state == 0 )
							row++;
						else
							row = myVals.erase( row );
					}
					else
					{
						if ( state == 0 )
							row = myVals.erase( row );
						else
							row++;
					}
				}
			}

			for ( int col = 0; col < arrSz; col++ )
			{
				results[state] <<= 1;
				if ( myVals[0][col] == '1' )
					results[state] |= 1;
			}
		}
		cout << results[0] * results[1];
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
