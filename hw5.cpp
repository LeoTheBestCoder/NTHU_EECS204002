#include <iostream>
#include <string>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

vector<int> row_of_fork;
vector<int> col_of_fork;
vector<int> row_of_dead_end;
vector<int> col_of_dead_end;
vector<int> incorrect_path;
int tmp_length;

class Maze
{
private:
    int serial;
    int width, height;
    int fork, dead_end, correct_length, medium_of_incorrect_path;
    int total;
    vector<string> pattern;

public:
    Maze(int s, int w, int h, vector<string> &p)
    {
        serial = s;
        width = w;
        height = h;
        pattern = p;
        fork = 0;
        dead_end = 0;
        correct_length = 0;
        medium_of_incorrect_path = 0;
        total = 0;
    }
    Maze(const Maze &m2)
    {
        serial = m2.serial;
        width = m2.width;
        height = m2.height;
        pattern = m2.pattern;
        fork = m2.fork;
        dead_end = m2.dead_end;
        correct_length = m2.correct_length;
        medium_of_incorrect_path = m2.medium_of_incorrect_path;
        total = m2.total;
    }
    int get_height()
    {
        return height;
    }
    int get_width()
    {
        return width;
    }
    void print()
    {
        cout << "width = " << width << " , height = " << height << "\n";
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                cout << pattern[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    int get_serial()
    {
        return serial;
    }
    char get_item(int row, int col)
    {
        return pattern[row][col];
    }
    void set_item(int row, int col, char ch)
    {
        pattern[row][col] = ch;
    }
    void calc_correct_length()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (pattern[i][j] == 'V')
                    correct_length++;
            }
        }
        correct_length--;
    }
    int get_correct_length()
    {
        return correct_length;
    }
    void set_correct_length(int l)
    {
        correct_length = l;
    }
    void calc_dead_end()
    {
        int wall_around;
        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                wall_around = 0;
                if (pattern[i][j] == '.')
                {
                    // cout << "fuck\n";
                    if (pattern[i - 1][j] == 'N')
                        wall_around++;
                    if (pattern[i + 1][j] == 'N')
                        wall_around++;
                    if (pattern[i][j - 1] == 'N')
                        wall_around++;
                    if (pattern[i][j + 1] == 'N')
                        wall_around++;

                    if (wall_around == 3)
                    {
                        row_of_dead_end.push_back(i);
                        col_of_dead_end.push_back(j);
                        dead_end++;
                    }
                }
            }
        }
    }
    int get_dead_end()
    {
        return dead_end;
    }
    void set_dead_end(int d)
    {
        dead_end = d;
    }
    void calc_fork()
    {
        for (int i = 1; i < height; i++)
        {
            for (int j = 1; j < width; j++)
            {
                if (pattern[i][j] == 'V')
                {
                    if (pattern[i - 1][j] == '.' || pattern[i + 1][j] == '.' || pattern[i][j - 1] == '.' || pattern[i][j + 1] == '.')
                    {
                        row_of_fork.push_back(i);
                        col_of_fork.push_back(j);
                    }
                    if (pattern[i - 1][j] == '.')
                        fork++;
                    if (pattern[i + 1][j] == '.')
                        fork++;
                    if (pattern[i][j - 1] == '.')
                        fork++;
                    if (pattern[i][j + 1] == '.')
                        fork++;
                }
            }
        }
    }
    int get_fork()
    {
        return fork;
    }
    void set_fork(int f)
    {
        fork = f;
    }
    void reset_correct_length()
    {
        correct_length = 0;
    }
    void reset_the_maze()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (pattern[i][j] == 'V')
                    pattern[i][j] = '.';
            }
        }
    }
    void set_medium_of_incorrect_path(int med)
    {
        medium_of_incorrect_path = med;
    }
    int get_medium_of_incorrect_length()
    {
        return medium_of_incorrect_path;
    }
    void calc_total()
    {
        // printf("fork = %d, dead_end = %d, c_len = %d, med = %d\n", fork, dead_end, correct_length, medium_of_incorrect_path);
        total = (fork + dead_end) * (correct_length + medium_of_incorrect_path);
    }
    void set_total(int t)
    {
        total = t;
    }
    int get_total()
    {
        return total;
    }
};

bool up_valid(Maze &m, int row, int col)
{
    if (row == 0)
        // out of boundary
        return false;
    else if (m.get_item(row - 1, col) == '.')
        return true;
    else
        return false;
}

bool down_valid(Maze &m, int row, int col)
{
    if (row == m.get_height() - 1)
        // out of boundary
        return false;
    else if (m.get_item(row + 1, col) == '.')
        return true;
    else
        return false;
}

bool left_valid(Maze &m, int row, int col)
{
    if (col == 0)
        // out of boundary
        return false;
    else if (m.get_item(row, col - 1) == '.')
        return true;
    else
        return false;
}

bool right_valid(Maze &m, int row, int col)
{
    if (col == m.get_width() - 1)
        // out of boundary
        return false;
    else if (m.get_item(row, col + 1) == '.')
        return true;
    else
        return false;
}

bool solve(Maze &m, int start_row, int start_col, int end_row, int end_col)
{
    // if (m.get_item(start_row, start_col) != 'V') // which means that this point hasn't been visited yet
    // {
    m.set_item(start_row, start_col, 'V');
    if (start_row == end_row && start_col == end_col)
    {
        // we reach our destination
        // cout << "finish! \n";
        // m.print();
        return true;
    }

    if (up_valid(m, start_row, start_col))
    {
        // cout << "solving (" << start_row << ", " << start_col << ") now...\n";
        if (solve(m, start_row - 1, start_col, end_row, end_col))
            return true;
        // else
        //     return false;
    }
    if (down_valid(m, start_row, start_col))
    {
        // cout << "solving (" << start_row << ", " << start_col << ") now...\n";
        if (solve(m, start_row + 1, start_col, end_row, end_col))
            return true;
        // else
        //     return false;
    }
    if (left_valid(m, start_row, start_col))
    {
        // cout << "solving (" << start_row << ", " << start_col << ") now...\n";
        if (solve(m, start_row, start_col - 1, end_row, end_col))
            return true;
        // else
        //     return false;
    }
    if (right_valid(m, start_row, start_col))
    {
        // cout << "solving (" << start_row << ", " << start_col << ") now...\n";
        if (solve(m, start_row, start_col + 1, end_row, end_col))
            return true;
        // else
        //     return false;
    }

    m.set_item(start_row, start_col, '.');
    return false;

    // m.set_item(start_row, col, '.');
}

bool solve_incorrect(Maze &m, int start_row, int start_col)
{
    m.set_item(start_row, start_col, 'X');
    // m.print();
    if (m.get_item(start_row + 1, start_col) == 'V' || m.get_item(start_row - 1, start_col) == 'V' || m.get_item(start_row, start_col + 1) == 'V' || m.get_item(start_row, start_col - 1) == 'V')
    {
        // we reach the correct path
        tmp_length = 0;
        // cout << "fuck yo\n";
        for (int i = 0; i < m.get_height(); i++)
        {
            for (int j = 0; j < m.get_width(); j++)
            {
                if (m.get_item(i, j) == 'X')
                {
                    tmp_length++;
                    m.set_item(i, j, '.');
                }
            }
        }

        return true;
    }

    if (up_valid(m, start_row, start_col))
    {
        if (solve_incorrect(m, start_row - 1, start_col))
            return true;
    }
    if (down_valid(m, start_row, start_col))
    {
        if (solve_incorrect(m, start_row + 1, start_col))
            return true;
    }
    if (left_valid(m, start_row, start_col))
    {
        if (solve_incorrect(m, start_row, start_col - 1))
            return true;
    }
    if (right_valid(m, start_row, start_col))
    {
        if (solve_incorrect(m, start_row, start_col + 1))
            return true;
    }

    m.set_item(start_row, start_col, '.');
    return false;

    // m.set_item(start_row, col, '.');
}

void calc_medium_of_incorrect_path(Maze &m)
{
    int medium = 0;
    int tmp_incorrect;
    // for (int i = 0; i<)
    for (int i = 0; i < row_of_dead_end.size(); i++)
    {
        // cout << "Back to correct path from r = " << row_of_dead_end[i] << " c = " << col_of_dead_end[i] << "\n";

        solve_incorrect(m, row_of_dead_end[i], col_of_dead_end[i]);
        // m.print();
        incorrect_path.push_back(tmp_length);
    }
    // for (int i = 0; i < incorrect_path.size(); i++)
    // {
    //     cout << "incorrect_path[" << i << "] = " << incorrect_path[i] << "\n";
    // }
    sort(incorrect_path.begin(), incorrect_path.end());
    if (incorrect_path.size() == 0)
        medium = 0;
    else if (incorrect_path.size() % 2 == 0)
    {
        medium = (incorrect_path[incorrect_path.size() / 2 - 1] + incorrect_path[incorrect_path.size() / 2]) / 2;
    }
    else if (incorrect_path.size() % 2 != 0)
    {
        medium = incorrect_path[(incorrect_path.size() - 1) / 2];
    }
    m.set_medium_of_incorrect_path(medium);
}

bool comp(Maze &m1, Maze &m2)
{
    if (m1.get_total() == m2.get_total())
    {
        if (m1.get_fork() == m2.get_fork())
        {
            if (m1.get_dead_end() == m2.get_dead_end())
            {
                if (m1.get_correct_length() == m2.get_correct_length())
                {
                    if (m1.get_medium_of_incorrect_length() == m2.get_medium_of_incorrect_length())
                    {
                        return m1.get_serial() < m2.get_serial();
                    }
                    else
                    {
                        return m1.get_medium_of_incorrect_length() < m2.get_medium_of_incorrect_length();
                    }
                }
                else
                {
                    return m1.get_correct_length() < m2.get_correct_length();
                }
            }
            else
            {
                return m1.get_dead_end() < m2.get_dead_end();
            }
        }
        else
        {
            return m1.get_fork() < m2.get_fork();
        }
    }
    else
    {
        return m1.get_total() < m2.get_total();
    }
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int num_of_maze, serial;
    int width, height;
    int N1, N2, L1, L2, total;
    bool result;

    vector<Maze> all_maze;

    string tmp;
    vector<string> pattern;
    cin >> num_of_maze;
    for (int i = 0; i < num_of_maze; i++)
    {
        cin >> serial;
        cin >> width >> height;
        for (int j = 0; j < height; j++)
        {
            cin >> tmp;
            pattern.push_back(tmp);
        }
        Maze m = Maze(serial, width, height, pattern);
        result = solve(m, 1, 0, height - 2, width - 1);
        // m.print();
        // if (result)
        // {
        //     cout << "finish!\n";
        //     m.print();
        // }
        m.calc_correct_length();
        L1 = m.get_correct_length();
        // m.set_correct_length(m.get_correct_length());
        // cout << "m.get_correct_length() L1 = " << m.get_correct_length() << "\n";

        m.calc_dead_end();
        // m.set_dead_end(m.get_dead_end());
        N2 = m.get_dead_end();
        // cout << "m.get_dead_end() N2 = " << m.get_dead_end() << "\n";

        m.calc_fork();
        // m.set_fork(m.get_fork());
        N1 = m.get_fork();
        // cout << "m.get_fork() N1 = " << m.get_fork() << "\n";

        // for (int j = 0; j < row_of_fork.size(); j++)
        //     cout << "row_of_fork[" << j << "] = " << row_of_fork[j] << ", "
        //          << "col_of_fork[" << j << "] = " << col_of_fork[j] << "\n";
        // for (int k = 0; k < row_of_dead_end.size(); k++)
        //     cout << "row_of_dead_end[" << k << "] = " << row_of_dead_end[k] << ", "
        //          << "col_of_dead_end[" << k << "] = " << col_of_dead_end[k] << "\n";

        // for (int l = 0; l < row_of_dead_end.size(); l++)
        // {
        //     incorrect_path.push_back(INT_MAX);
        // }

        calc_medium_of_incorrect_path(m);
        // m.set_medium_of_incorrect_path(m.get_medium_of_incorrect_length());
        // all_maze.push_back(m);
        L2 = m.get_medium_of_incorrect_length();
        // cout << "m.get_medium_of_incorrect_length() L2 = " << m.get_medium_of_incorrect_length() << "\n";

        // m.calc_total();
        // T.push_back((N1[i] + N2[i]) * (L1[i] + L2[i]));

        // cout << "m.get_total() = " << m.get_total() << "\n";
        Maze temp = Maze(serial, width, height, pattern);
        temp.set_fork(N1);
        temp.set_dead_end(N2);
        temp.set_correct_length(L1);
        temp.set_medium_of_incorrect_path(L2);
        temp.set_total((N1 + N2) * (L1 + L2));
        all_maze.push_back(temp);

        pattern.clear();
        row_of_fork.clear();
        col_of_fork.clear();
        row_of_dead_end.clear();
        col_of_dead_end.clear();
        incorrect_path.clear();
    }

    // for (int i = 0; i < all_maze.size(); i++)
    // {
    //     cout << "Maze " << i + 1 << ":\n";
    //     printf("tot = %d, N1 = %d, N2 = %d, L1 = %d, L2 = %d\n", all_maze[i].get_total(), all_maze[i].get_fork(), all_maze[i].get_dead_end(), all_maze[i].get_correct_length(), all_maze[i].get_medium_of_incorrect_length());
    // }
    sort(all_maze.begin(), all_maze.end(), comp);
    // cout << "After sort...\n";
    for (int i = 0; i < all_maze.size(); i++)
    {
        // cout << "Maze " << all_maze[i].get_serial() << ":\n";
        // cout << all_maze[i].get_medium_of_incorrect_length();
        // printf("tot = %d, N1 = %d, N2 = %d, L1 = %d, L2 = %d\n", all_maze[i].get_total(), all_maze[i].get_fork(), all_maze[i].get_dead_end(), all_maze[i].get_correct_length(), all_maze[i].get_medium_of_incorrect_length());
        cout << all_maze[i].get_serial() << "\n";
        cout << all_maze[i].get_total() << " " << all_maze[i].get_fork() << " " << all_maze[i].get_dead_end() << " " << all_maze[i].get_correct_length() << " " << all_maze[i].get_medium_of_incorrect_length() << "\n";
        // all_maze[i].print();
    }

    return 0;
}