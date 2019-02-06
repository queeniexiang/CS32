#include <stack>
#include <string>
#include <iostream>
using namespace std;


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    const char ENCOUNTERED = 'e';
    
    stack<Coord> coordStack;
    
    /*Push the starting coordinate (sr,sc) onto the coordinate stack and
    update maze[sr][sc] to indicate that the algorithm has encountered
    it (i.e., set maze[sr][sc] to have a value other than '.'). */
    
    //Change starting position to show that it has been encountered
    Coord startingPos(sr, sc);
    coordStack.push(startingPos);
    maze[sr][sc] = ENCOUNTERED;
    
    while (!coordStack.empty()) {
        Coord currentPos = coordStack.top();
        /*
        cerr << "row: " << currentPos.r() << endl;
        cerr << "col: " << currentPos.c() << endl;
        cerr << "****" << endl;
        */
        
        /*Pop the top coordinate off the stack. This gives you the current
        (r,c) location that your algorithm is exploring.*/
        coordStack.pop();
        
        int curr_R = currentPos.r();
        int curr_C = currentPos.c();
        
        /* If the current (r,c) coordinate is equal to the ending coordinate,
         then we've solved the maze so return true! */
        if (curr_R == er && curr_C == ec) {
            return true;
        }
        
        //Check each place you can move from the current cell as follows:
        //Go North
        /* If you can move NORTH and haven't encountered that cell yet,
         then push the coordinate (r-1,c) onto the stack and update
         maze[r-1][c] to indicate the algorithm has encountered it. */
        if (maze[curr_R-1][curr_C] == '.') {
            Coord newPos(curr_R-1, curr_C);
            coordStack.push(newPos);
            maze[curr_R-1][curr_C] = ENCOUNTERED;
        }
        
        //Go south
        /* If you can move SOUTH and haven't encountered that cell yet,
         then push the coordinate (r+1,c) onto the stack and update
         maze[r+1][c] to indicate the algorithm has encountered it.*/
        if (maze[curr_R+1][curr_C] == '.') {
            Coord newPos(curr_R+1, curr_C);
            coordStack.push(newPos);
            maze[curr_R+1][curr_C] = ENCOUNTERED;
        }
        
        //Go West
        /*If you can move WEST and haven't encountered that cell yet,
         then push the coordinate (r,c-1) onto the stack and update
         maze[r][c-1] to indicate the algorithm has encountered it.*/
        if (maze[curr_R][curr_C-1] == '.') {
            Coord newPos(curr_R, curr_C-1);
            coordStack.push(newPos);
            maze[curr_R][curr_C-1] = ENCOUNTERED;
        }
        
        //Go East
        /* If you can move EAST and haven't encountered that cell yet,
         then push the coordinate (r,c+1) onto the stack and update
         maze[r][c+1] to indicate the algorithm has encountered it. */
        if (maze[curr_R][curr_C+1] == '.') {
            Coord newPos(curr_R, curr_C+1);
            coordStack.push(newPos);
            maze[curr_R][curr_C+1] = ENCOUNTERED;
            
        }
    }
    //There was no solution, so return false
    return false;
}

/*
int main()
{
    stack<Coord> coordStack;     // declare a stack of Coords
    
    Coord a(5,6);
    coordStack.push(a);             // push the coordinate (5,6)
    coordStack.push(Coord(3,4));    // push the coordinate (3,4)
    ...
    Coord b = coordStack.top();     // look at top item in the stack
    coordStack.pop();               // remove the top item from stack
    if (coordStack.empty())         // Is the stack empty?
        cout << "empty!" << endl;
    cout << coordStack.size() << endl;  // num of elements
}
*/


/*
int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
*/
