// AoC1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
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
	case 41:
	{
		ifstream in( "input4.txt" );
		string strIn;
		vector< int > drawnVals;

		getline( in, strIn );
		
		// Get drawn values
		stringstream ssIn( strIn );
		string strTemp;
		while ( getline( ssIn, strTemp, ',' ) )
			drawnVals.push_back( stoi( strTemp ) );

		// Get all our Bingo squares
		typedef pair< int, bool > Number; // Value and whether it's been drawn
		typedef vector< Number > Row;
		typedef vector< Row > Square;
		Square square;
		vector< Square > squares;
		getline( in, strIn ); // First line is blank
		while ( getline( in, strIn ) )
		{
			if ( strIn.length() == 0 )
			{
				squares.push_back( square );
				square.clear();
				continue;
			}

			stringstream ssIn( strIn );
			string strTemp;
			Row row;
			while ( getline( ssIn, strTemp, ' ' ) )
				if ( strTemp.length() != 0 )
					row.push_back( Number( stoi( strTemp ), false ) );

			square.push_back( row );
		}

		// Start marking numbers
		for ( auto val = drawnVals.begin(); val != drawnVals.end(); val++ )
		{
			for ( auto square = squares.begin(); square != squares.end(); square++ )
				for ( auto row = (*square).begin(); row != (*square).end(); row++ )
					for ( auto number = (*row).begin(); number != (*row).end(); number++ )
						if ( (*number).first == *val )
							(*number).second = true;

			// Check if a square has a full row/col
			auto square = squares.begin();
			for ( ; square != squares.end(); square++ )
			{
				bool fullRow = false;
				// Check for a row first
				for ( int row = 0; row < (*square).size(); row++ )
				{
					fullRow = true;
					for ( int col = 0; col < (*square)[row].size() && fullRow; col++ )
					{
						fullRow &= (*square)[row][col].second;
					}
					if ( fullRow )
						break;
				}

				// Now check for a column
				bool fullCol = false;
				for ( int col = 0; col < (*square)[0].size(); col++ )
				{
					fullCol = true;
					for ( int row = 0; row < (*square).size() && fullCol; row++ )
					{
						fullCol &= (*square)[row][col].second;
					}
					if ( fullCol )
						break;
				}
				if ( fullCol )
					break;
			}

			// Did we find one?
			if ( square != squares.end() )
			{
				// Yes! Bingo!
				cout << "Bingo!";
				int unmarkedSum = 0;
				for ( auto row = (*square).begin(); row != (*square).end(); row++ )
				{
					for ( auto number = (*row).begin(); number != (*row).end(); number++ )
					{
						if ( !(*number).second )
							unmarkedSum += (*number).first;
					}
				}
				cout << unmarkedSum * *val;
				break;
			}
		}

		break;
	}
	case 42:
	{
		ifstream in( "input4.txt" );
		string strIn;
		vector< int > drawnVals;

		getline( in, strIn );

		// Get drawn values
		stringstream ssIn( strIn );
		string strTemp;
		while ( getline( ssIn, strTemp, ',' ) )
			drawnVals.push_back( stoi( strTemp ) );

		// Get all our Bingo squares
		typedef pair< int, bool > Number; // Value and whether it's been drawn
		typedef vector< Number > Row;
		typedef vector< Row > Square;
		Square square;
		vector< Square > squares;
		getline( in, strIn ); // First line is blank
		while ( getline( in, strIn ) )
		{
			if ( strIn.length() == 0 )
			{
				squares.push_back( square );
				square.clear();
				continue;
			}

			stringstream ssIn( strIn );
			string strTemp;
			Row row;
			while ( getline( ssIn, strTemp, ' ' ) )
				if ( strTemp.length() != 0 )
					row.push_back( Number( stoi( strTemp ), false ) );

			square.push_back( row );
		}

		// Start marking numbers
		Square lastWinner;
		int winnerVal;
		for ( auto val = drawnVals.begin(); val != drawnVals.end(); val++ )
		{
			for ( auto square = squares.begin(); square != squares.end(); square++ )
				for ( auto row = (*square).begin(); row != (*square).end(); row++ )
					for ( auto number = (*row).begin(); number != (*row).end(); number++ )
						if ( (*number).first == *val )
							(*number).second = true;

			// Check if a square has a full row/col
			auto square = squares.begin();
			for ( ; square != squares.end(); )
			{
				bool fullRow = false;
				// Check for a row first
				for ( int row = 0; row < (*square).size(); row++ )
				{
					fullRow = true;
					for ( int col = 0; col < (*square)[row].size() && fullRow; col++ )
					{
						fullRow &= (*square)[row][col].second;
					}
					if ( fullRow )
					{
						// Yes, pull it out of the list
						lastWinner = *square;
						winnerVal = *val;
						square = squares.erase( square );
						break;
					}
				}
				if ( fullRow )
					continue;

				// Now check for a column
				bool fullCol = false;
				for ( int col = 0; col < (*square)[0].size(); col++ )
				{
					fullCol = true;
					for ( int row = 0; row < (*square).size() && fullCol; row++ )
					{
						fullCol &= (*square)[row][col].second;
					}
					if ( fullCol )
					{
						// Yes, pull it out of the list
						lastWinner = *square;
						winnerVal = *val;
						square = squares.erase( square );
						break;
					}
				}
				if ( fullCol )
					continue;

				square++;
			}
		}

		int unmarkedSum = 0;
		for ( auto row = lastWinner.begin(); row != lastWinner.end(); row++ )
		{
			for ( auto number = (*row).begin(); number != (*row).end(); number++ )
			{
				if ( !(*number).second )
					unmarkedSum += (*number).first;
			}
		}
		cout << unmarkedSum * winnerVal;
		break;
	}
	default:
		;
	}
}