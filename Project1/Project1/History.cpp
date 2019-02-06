// History.cpp

#include <iostream>

#include "History.h"
#include "globals.h"

using namespace std;

History::History(int nRows, int nCols) {
    //Initializes a History object that corresponds to an Arena with nRows rows and nCols columns
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            m_grid[row][col] = 0;
        }
    }
    
    //Sets how many rows and cols this History obj will have
    m_rows = nRows;
    m_cols = nCols;
}

/* bool record(int r, int c):
 Notify the History object that a zombie has died at the indicated location in the Arena that the History object corresponds to.
 The function returns false if row r, column c is not within bounds.
 Otherwise, it returns true after recording what it needs to.
 NOTE: This function expects its parameters to be expressed in the same coordinate system as the Arena (e.g., row 1, column 1 is the upper-left-most position).
*/

bool History::record(int r, int c) {
    if (r > MAXROWS || c > MAXCOLS || r <= 0 || c <= 0) {
        return false;
    }
    
    else {
        // Position (row,col) of the arena coordinate system is represented in
        // the array element grid[row-1][col-1]
        m_grid[r-1][c-1] += 1;
        return true;
    }
    
    return false;
}

/* void display() const:
 Clears the screen and displays the history grid as the posted programs do.
 This function does clear the screen, display the history grid, and write an empty line after the history grid.
 NOTE: it does not print the Press enter to continue.
 */
void History::display() const
{
    clearScreen();

    // Fill the grid with the appropriate char
    //Dot means 0
    //Letter character A through Y means 1 through 25 (A means 1, B means 2, etc.)
    //Z means 26 or more.
    
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            int num = m_grid[r][c]; //checks for how many zombies have died at (r,c)
            char ch;
            
            //matches num with corresponding char
            
            if (num <= 0) {
                ch = '.';
            }
            
            else if (num >= 26) {
                ch = 'Z';
            }
            
            else {
                ch = 'A'+ (num-1);
            }
            
            //print letter
            cout << ch;
        }
        
        //end of a row
        cout << endl;
    }
    cout << endl;
}

