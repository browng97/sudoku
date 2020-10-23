/*
 * Name: Geno Brown, Sudoku Solver
 * Description: Given initial positions in a soduko board,
 * finds the solution to the board.
 * Input: Takes input for the coordinates of initial numbers in the board
 * Output: Outputs the filled board or the board being filled.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <unistd.h>

const int N = 9;       //constant for 9

using namespace std;

//prints the board
void printBoard(int arr[][N]);      

//checks if current board values are valid
bool isValidBoard(int arr[][N]);

//finds an unset location
bool findUnsetLocation(int arr[][N], int& row, int& col);

//recursive function to solve the board
bool solveBoard(int arr[][N]);

int main()
{   
    //2d int array for storing board values
    int board[N][N];

    //initializing 2d array board values
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    //setting the board
    /*
    board[0][1] = 6;
    board[0][3] = 3;
    board[0][6] = 8;
    board[0][8] = 4;

    board[1][0] = 5;
    board[1][1] = 3;
    board[1][2] = 7;
    board[1][4] = 9;

    board[2][1] = 4;
    board[2][5] = 6;
    board[2][6] = 3;
    board[2][8] = 7;

    board[3][1] = 9;
    board[3][4] = 5;
    board[3][5] = 1;
    board[3][6] = 2;
    board[3][7] = 3;
    board[3][8] = 8;

    board[5][0] = 7;
    board[5][1] = 1;
    board[5][2] = 3;
    board[5][3] = 6;
    board[5][4] = 2;
    board[5][7] = 4;

    board[6][0] = 3;
    board[6][2] = 6;
    board[6][3] = 4;
    board[6][7] = 1;

    board[7][4] = 6;
    board[7][6] = 5;
    board[7][7] = 2;
    board[7][8] = 3;

    board[8][0] = 1;
    board[8][2] = 2;
    board[8][5] = 9;
    board[8][7] = 8;
    */

    string input;
    int row, col, val, oldVal;

    cout << "Enter your own values? (y/n): ";
    cin >> input;

    while (input == "y")
    {
        printBoard(board);

        cout << endl << "Enter the coordinates separated by a space. ('row col'): ";
        cin >> row >> col;

        while (row > N || col > N || row < 1 || col < 1)
        {
            cout << "Coordinates entered are out of range. Resubmit: ";
            cin >> row >> col;
        }

        cout << "Enter the value of that spot: ";
        cin >> val;

        while (val > N || val < 1)
        {
            cout << "Value entered is out of range. Resubmit: ";
            cin >> val;
        }

        oldVal = board[row - 1][col - 1];
        board[row - 1][col - 1] = val;

        if (!isValidBoard(board))
        {
            cout << "This board is not valid. The entered value has been ignored." << endl;

            board[row - 1][col - 1] = oldVal;
        }

        cout << "Enter another value? (y/n): ";
        cin >> input;
    }

    printBoard(board);

    if (isValidBoard(board))
        cout << endl << "     This board is valid." << endl;
    else
    {
        cout << "     This board is not valid." << endl;
    
        return 0;
    }

    solveBoard(board);

    printBoard(board);

    if (isValidBoard(board))
        cout << endl << "     This board is complete and valid." << endl;
    else
    {
        cout << "     This board is not valid." << endl;
    
        return 0;
    }

    cout << endl;

    return 0;
}

/*
 * function_identifier: printBoard
 * prints the sudoku board
 * parameters: int arr[][N]
 * return value: no return values
 */
void printBoard(int arr[][N])
{
    cout << endl;

    //printing column numbers and divider
    cout << "      1  2  3     4  5  6     7  8  9   " << endl;
    cout << "   -------------------------------------" << endl;

    int dividerCount = 0;

    //for loop for each row
    for (int i = 0; i < N; i++)
    {
        if (dividerCount % 3 == 0 && i > 0)
            cout << "   |-----------------------------------|" << endl;
            
        //prints row number
        cout << i + 1;

        //printing array items per row
        for (int j = 0; j < N; j++)
        {
            if (j % 3 == 0)
                cout << "  |";
                
            cout << "  " << arr[i][j];
        }

        cout << "  |" << endl;
            
        if ((i + 1) % 3 != 0)
            cout << "   |           |           |           |" << endl;

        dividerCount++;
    }

    cout << "   -------------------------------------" << endl;
}

/*
 * function_identifier: isValidBoard
 * Checks if the board is valid
 * parameters: int arr[][N]
 * return value: bool
 */
bool isValidBoard(int arr[][N])
{
    //iterating through every spot in the board
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //if the spot has no value, skip it
            if (arr[i][j] == 0)
                continue;

            //traverse through the current row to find duplicate vals
            for (int k = 0; k < N; k++)
            {
                //skip the spot we are on or skip if theres no val
                if (k == j || arr[i][k] == 0)
                    continue;

                //if it finds a duplicate, return false
                if (arr[i][k] == arr[i][j])
                    return false; 
            }
            
            //traverse through the current col to find duplicate vals
            for (int k = 0; k < N; k++)
            {
                //skip the spot we are on or skip if theres no val
                if (k == i || arr[k][j] == 0)
                    continue;

                //if it finds a duplicate, return false
                if (arr[k][j] == arr[i][j])
                    return false; 
            }
            
            //traverse through the current square to find impossible vals
            // finding which square we are currently in
            int iter1 = 0, iter2 = 0;

            if (i < 3)
                iter1 = 0;
            else if (i < 6)
                iter1 = 3;
            else
                iter1 = 6;

            if (j < 3)
                iter2 = 0;
            else if (j < 6)
                iter2 = 3;
            else
                iter2 = 6;
            
            // traversing the current square
            for (int k = iter1; k < iter1 + 3; k++)
            {
                for (int l = iter2; l < iter2 + 3; l++)
                {
                    //skip the spot we are on
                    if (k == i && l == j)
                        continue;

                    //skip if theres no value
                    if (arr[k][l] == 0)
                        continue;

                    if (arr[k][l] == arr[i][j])
                        return false; 
                }
            }
        }
    }
        
    return true;
}

/*
 * function_identifier: findUnsetLocation
 * traverses the board from (0, 0) to find the next unset location
 * returns the coordinates by reference
 * parameters: int arr[][N], int& row, int& col
 * return value: bool
 */
bool findUnsetLocation(int arr[][N], int& row, int& col)
{
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (arr[row][col]  == 0)
                return true;
        }
    }

    return false;
}

/*
 * function_identifier: solveBoard
 * recursive function solves the board from the first row
 * parameters: int arr[][N], int row, int initQ
 * return value: bool
 */
bool solveBoard(int arr[][N])
{
    //obtains next row and col through findUnsetLocation
    int row, col;

    //row and col are passed by reference
    if (!findUnsetLocation(arr, row, col))
        return true;

    //checking all possibilities [1, 9]
    for (int i = 1; i <= N; i++)
    {
        //sets the possible value
        arr[row][col] = i;

        //if this value is valid, start backtracking from here
        if (isValidBoard(arr))
        {
            if (solveBoard(arr))
                return true;
        }

        //value does not work, set 0 and try next value
        arr[row][col] = 0;
    }

    //no solution found
    return false;
}






