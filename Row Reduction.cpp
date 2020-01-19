#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctype.h>   //isdigit()

#include "Fraction.h"

using namespace std;

struct Operation
{
	int row1 = 0;
	int row2 = 0;
	float scaler = 1;
	int replaceRow;
};

int whatDigit(char character)
{
	switch (character)
	{
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;

	default:
		return -1;
	}
}

void printMatrix(float** matrix, int rowCount, int columnCount)
{
	cout << endl << "Your Matrix: " << endl;

	for (int i = 0; i < rowCount; i++)
	{
		cout << "| ";

		for (int j = 0; j < columnCount; j++)
		{
			cout << matrix[i][j];

			if ((j + 1) == columnCount)
			{
				cout << " |" << endl;
				continue;
			}
			
			cout << ", ";
		}
	}
}

int main()
{
	int rowCount = 0;
	int columnCount = 0;

	Fraction fraction(.25);

	fraction.toFraction();

	cout << fraction.numerator << '/' << fraction.denominator << endl;
	
	cout << "How many rows? ";
	cin >> rowCount;

	cout << "How many columns? ";
	cin >> columnCount;
	
	float** matrix = new float* [rowCount];
	for (int i = 0; i < rowCount; ++i)
	{
		matrix[i] = new float[columnCount];
	}

	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			float value = 0;
			cout << "What value is in row " << (i + 1)
			     << " column " << (j + 1) << "? ";
			cin >> value;

			matrix[i][j] = value;
		}
	}
	
	string rowOperation;
	cin.ignore();
	while ((!rowOperation.find("done") != string::npos || rowOperation.find("Done") != string::npos))
	{
		printMatrix(matrix, rowCount, columnCount);

		cout << endl; 
		cout << "Row Operation: ";
		getline(cin, rowOperation);

		Operation operation;
		int passedRChar = 0;
		int isNegative = 1;
		bool passedGreaterThan = false;
		bool isFraction = false;

		//Parse the operation to get necessary information
		for (size_t i = 0; i < rowOperation.size(); i++)
		{
			stringstream ss;
			char rowOperationChar;

			ss << rowOperation[i];
			ss >> rowOperationChar;

			if (isdigit(rowOperationChar))
			{
				if (passedRChar == 0)
				{
					if (isFraction)
					{
						operation.scaler /= whatDigit(rowOperationChar);
						isFraction = false;
					}
					else
					{
						operation.scaler = (whatDigit(rowOperationChar) * isNegative);
					}
				}
				else if (passedRChar == 3 || passedGreaterThan)
				{
					operation.replaceRow = whatDigit(rowOperationChar);
				}
				else if (passedRChar == 1)
				{
					operation.row1 = whatDigit(rowOperationChar);
				}
				else if (passedRChar == 2)
				{
					operation.row2 = whatDigit(rowOperationChar);
				}


			}
			else if (rowOperationChar == '-')
			{
				if (passedRChar == 0)
				{
					isNegative = -1;
				}
			}
			else if (rowOperationChar == 'R')
			{
				passedRChar++;
			}
			else if (rowOperationChar == '>')
			{
				passedGreaterThan = true;
			}
			else if (rowOperationChar == '/')
			{
				isFraction = true;
			}
		}

		//Begin executing operation
		for (int i = 0; i < columnCount; i++)
		{
			if (operation.row2 == 0)
			{
				matrix[operation.replaceRow - 1][i] = (matrix[operation.row1 - 1][i] * operation.scaler);
			}
			else
			{
				matrix[operation.replaceRow - 1][i] = (matrix[operation.row1 - 1][i] * operation.scaler) + matrix[operation.row2 - 1][i];
			}
		}

		rowOperation.clear();
	}



	return 0;
}

