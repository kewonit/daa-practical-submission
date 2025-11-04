#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class NQueens
{
private:
    int n;
    vector<vector<int>> solutions;
    vector<int> board; // board[i] = column position of queen in row i

    // Check if placing a queen at (row, col) is safe
    bool isSafe(int row, int col)
    {
        for (int i = 0; i < row; i++)
        {
            // Check if queens are in same column or diagonal
            if (board[i] == col ||
                abs(board[i] - col) == abs(i - row))
            {
                return false;
            }
        }
        return true;
    }

    // Backtracking function to place queens
    void solve(int row)
    {
        if (row == n)
        {
            // Found a valid solution
            solutions.push_back(board);
            return;
        }

        // Try placing queen in each column of current row
        for (int col = 0; col < n; col++)
        {
            if (isSafe(row, col))
            {
                board[row] = col;
                solve(row + 1);
                // Backtrack (implicit - will be overwritten in next iteration)
            }
        }
    }

    // Display a single solution board
    void displayBoard(const vector<int> &solution, ostream &out)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (solution[i] == j)
                {
                    out << "Q ";
                }
                else
                {
                    out << ". ";
                }
            }
            out << endl;
        }
        out << endl;
    }

public:
    NQueens(int size) : n(size), board(size) {}

    void findAllSolutions()
    {
        solutions.clear();
        solve(0);
    }

    void printResults(ostream &out)
    {
        out << "N-Queens Problem for N = " << n << endl;
        out << "Total number of solutions: " << solutions.size() << endl;
        out << "\n========================================\n"
            << endl;

        if (solutions.empty())
        {
            out << "No solutions found!" << endl;
            return;
        }

        // Print first few solutions (to avoid overwhelming output for large N)
        int maxDisplay = min(4, (int)solutions.size());
        for (int i = 0; i < maxDisplay; i++)
        {
            out << "Solution " << (i + 1) << ":" << endl;
            displayBoard(solutions[i], out);
        }

        if (solutions.size() > maxDisplay)
        {
            out << "... and " << (solutions.size() - maxDisplay)
                << " more solutions" << endl;
        }

        // Print all solutions in compact format
        out << "\n========================================" << endl;
        out << "All solutions in compact format [row -> column]:" << endl;
        out << "========================================\n"
            << endl;

        for (size_t i = 0; i < solutions.size(); i++)
        {
            out << "Solution " << (i + 1) << ": ";
            for (int j = 0; j < n; j++)
            {
                out << solutions[i][j];
                if (j < n - 1)
                    out << " ";
            }
            out << endl;
        }
    }

    int getSolutionCount() const
    {
        return solutions.size();
    }
};

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input.is_open())
    {
        cerr << "Error: Could not open input.txt" << endl;
        return 1;
    }

    int n;
    input >> n;
    input.close();

    if (n < 1 || n > 20)
    {
        cerr << "Error: N must be between 1 and 20" << endl;
        output << "Error: N must be between 1 and 20" << endl;
        output.close();
        return 1;
    }

    cout << "Solving N-Queens problem for N = " << n << endl;
    cout << "Please wait..." << endl;

    NQueens solver(n);
    solver.findAllSolutions();

    // Print to console
    cout << "\nTotal solutions found: " << solver.getSolutionCount() << endl;

    // Print to file
    solver.printResults(output);

    output.close();

    cout << "\nResults written to output.txt" << endl;

    return 0;
}
