#include <iostream>
#include <vector>

using namespace std;

struct Solution
{
    vector<int> queen_positions;
};

vector<Solution> all_solutions;
vector<int> board_state;
int board_size;

// check if queen placement is valid
bool isSafe(int current_row, int current_col)
{
    for (int previous_row = 0; previous_row < current_row; previous_row++)
    {
        int previous_col = board_state[previous_row];
        if (previous_col == current_col || abs(previous_col - current_col) == abs(previous_row - current_row))
            return false;
    }
    return true;
}

// place queens row by row
void placeQueens(int current_row)
{
    if (current_row == board_size)
    {
        Solution new_solution;
        new_solution.queen_positions = board_state;
        all_solutions.push_back(new_solution);
        return;
    }

    for (int col = 0; col < board_size; col++)
    {
        if (isSafe(current_row, col))
        {
            board_state[current_row] = col;
            placeQueens(current_row + 1);
        }
    }
}

// print one board solution
void printBoard(const vector<int> &positions)
{
    for (int row = 0; row < board_size; row++)
    {
        for (int col = 0; col < board_size; col++)
        {
            if (positions[row] == col)
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
    board_size = 8;
    board_state.resize(board_size);

    placeQueens(0);

    cout << "N-Queens Problem for N = " << board_size << '\n';
    cout << "Total solutions found: " << all_solutions.size() << "\n\n";

    int solutions_to_show = min(4, (int)all_solutions.size());
    for (int i = 0; i < solutions_to_show; i++)
    {
        cout << "Solution " << (i + 1) << ":\n";
        printBoard(all_solutions[i].queen_positions);
    }

    if (all_solutions.size() > solutions_to_show)
        cout << "... and " << (all_solutions.size() - solutions_to_show) << " more solutions\n\n";

    cout << "All solutions in compact format:\n";
    for (int i = 0; i < all_solutions.size(); i++)
    {
        cout << "Solution " << (i + 1) << ": ";
        for (int j = 0; j < board_size; j++)
        {
            cout << all_solutions[i].queen_positions[j];
            if (j < board_size - 1)
                cout << " ";
        }
        cout << '\n';
    }

    return 0;
}
