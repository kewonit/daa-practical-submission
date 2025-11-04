#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Solution
{
    vector<int> board;
};

vector<Solution> allSolutions;
vector<int> board;
int n;

// Checks if queen can be placed at given position
bool isSafe(int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

// Recursive backtracking to place queens row by row
void placeQueens(int row)
{
    if (row == n)
    {
        Solution s;
        s.board = board;
        allSolutions.push_back(s);
        return;
    }
    for (int col = 0; col < n; col++)
    {
        if (isSafe(row, col))
        {
            board[row] = col;
            placeQueens(row + 1);
        }
    }
}

// Prints a single board configuration
void printBoard(const vector<int> &b)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (b[i] == j)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << '\n';
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded input data
    n = 8;

    board.resize(n);

    placeQueens(0);

    cout << "N-Queens Problem for N = " << n << '\n';
    cout << "Total solutions found: " << allSolutions.size() << "\n\n";

    // Display first 4 solutions
    int display = min(4, (int)allSolutions.size());
    for (int i = 0; i < display; i++)
    {
        cout << "Solution " << (i + 1) << ":\n";
        printBoard(allSolutions[i].board);
    }

    if (allSolutions.size() > display)
        cout << "... and " << (allSolutions.size() - display) << " more solutions\n\n";

    // Print all solutions in compact format
    cout << "All solutions in compact format:\n";
    for (size_t i = 0; i < allSolutions.size(); i++)
    {
        cout << "Solution " << (i + 1) << ": ";
        for (int j = 0; j < n; j++)
        {
            cout << allSolutions[i].board[j];
            if (j < n - 1)
                cout << " ";
        }
        cout << '\n';
    }

    return 0;
}
