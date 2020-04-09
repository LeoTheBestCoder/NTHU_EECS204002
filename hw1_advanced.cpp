/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 107061218
 * 3. OJ ID: leo
 * 4. OJ SID: 2155367
 * 5. OJ Score: 12
 */

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstdio>

using namespace std;

class Piece
{
private:
    vector<string> pattern;
    int width, height;

public:
    Piece(int w, int h, vector<string> &p)
    {
        width = w;
        height = h;
        pattern = p;
    }
    Piece(const Piece &p2)
    {
        width = p2.width;
        height = p2.height;
        pattern = p2.pattern;
    }
    void print()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                cout << pattern[i][j] << " ";
            }
            cout << endl;
        }
    }
    int get_width()
    {
        return width;
    }
    int get_height()
    {
        return height;
    }
    char get_item(int row, int col)
    {
        return pattern[row][col];
    }
    Piece turn_left()
    {
        vector<string> new_pattern;
        string temp = "";
        for (int col = width - 1; col >= 0; col--)
        {
            for (int row = 0; row < height; row++)
            {
                temp += pattern[row][col];
            }
            new_pattern.push_back(temp);
            temp = "";
        }
        return Piece(height, width, new_pattern);
    }
    Piece turn_right()
    {
        vector<string> new_pattern;
        string temp = "";
        for (int col = 0; col < width; col++)
        {
            for (int row = height - 1; row >= 0; row--)
            {
                temp += pattern[row][col];
            }
            new_pattern.push_back(temp);
            temp = "";
        }
        return Piece(height, width, new_pattern);
    }
    Piece upside_down()
    {
        vector<string> new_pattern;
        string temp = "";
        for (int row = height - 1; row >= 0; row--)
        {
            for (int col = width - 1; col >= 0; col--)
            {
                temp += pattern[row][col];
            }
            new_pattern.push_back(temp);
            temp = "";
        }
        return Piece(width, height, new_pattern);
    }
    Piece flip()
    {
        vector<string> new_pattern;
        string temp = "";
        for (int row = 0; row < height; row++)
        {
            for (int col = width - 1; col >= 0; col--)
            {
                temp += pattern[row][col];
            }
            new_pattern.push_back(temp);
            temp = "";
        }
        return Piece(width, height, new_pattern);
    }
};

vector<Piece> piece_list;

class Map
{
private:
    vector<string> pattern;
    int width, height;

public:
    Map(int w, int h, vector<string> &p);
    Map(const Map &m2);
    void print();
    int get_width();
    int get_height();
    char get_item(int row, int col);
    void set_item(int row, int col, char ch);
};

Map::Map(int w, int h, vector<string> &p)
{
    width = w;
    height = h;
    pattern = p;
}

Map::Map(const Map &m2)
{
    width = m2.width;
    height = m2.height;
    pattern = m2.pattern;
}

void Map::print()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << pattern[i][j] << " ";
        }
        cout << endl;
    }
}

int Map::get_height()
{
    return height;
}

int Map::get_width()
{
    return width;
}

char Map::get_item(int row, int col)
{
    return pattern[row][col];
}

void Map::set_item(int row, int col, char ch)
{
    pattern[row][col] = ch;
}

bool place(int row, int col, Map &map_now, Piece &piece_now)
{

    bool can_put;
    can_put = true;
    // can put or not
    for (int row_of_piece = 0; row_of_piece < piece_now.get_height(); row_of_piece++)
    {
        for (int col_of_piece = 0; col_of_piece < piece_now.get_width(); col_of_piece++)
        {
            if (map_now.get_item(row + row_of_piece, col + col_of_piece) == 'O' && piece_now.get_item(row_of_piece, col_of_piece) == 'O')
            {
                can_put = false;
            }
        }
    }

    if (can_put == true)
    {
        for (int row_of_piece = 0; row_of_piece < piece_now.get_height(); row_of_piece++)
        {
            for (int col_of_piece = 0; col_of_piece < piece_now.get_width(); col_of_piece++)
            {
                if (map_now.get_item(row + row_of_piece, col + col_of_piece) == '-' && piece_now.get_item(row_of_piece, col_of_piece) == 'O')
                {
                    map_now.set_item(row + row_of_piece, col + col_of_piece, 'O');
                }
            }
        }
    }
    return can_put;
}

stack<Map> map_history;

bool solve(int idx)
{

    if (idx == piece_list.size())
    {
        return true;
    }

    Map map_now = map_history.top();
    vector<Piece> all_shape;
    Piece origin = piece_list[idx];
    Piece flipped = piece_list[idx].flip();

    all_shape.push_back(origin);
    all_shape.push_back(origin.turn_left());
    all_shape.push_back(origin.turn_right());
    all_shape.push_back(origin.upside_down());
    all_shape.push_back(flipped);
    all_shape.push_back(flipped.turn_left());
    all_shape.push_back(flipped.turn_right());
    all_shape.push_back(flipped.upside_down());

    bool is_valid;
    for (int shape = 0; shape < 8; shape++)
    {
        for (int row_of_map = 0; row_of_map + all_shape[shape].get_height() <= map_now.get_height(); row_of_map++)
        {
            for (int col_of_map = 0; col_of_map + all_shape[shape].get_width() <= map_now.get_width(); col_of_map++)
            {
                Map map_to_solve = map_history.top();
                is_valid = place(row_of_map, col_of_map, map_to_solve, all_shape[shape]);
                if (is_valid == true)
                {
                    map_history.push(map_to_solve);
                    if (solve(idx + 1))
                    {
                        // map_to_solve.print();
                        // cout << "\n";

                        return true;
                    }
                    map_history.pop();
                }
            }
        }
    }

    return false;
}

vector<Map> map_list;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int num_of_pieces, num_of_maps;
    int w, h;
    vector<string> p;
    bool result;
    string input;
    cin >> num_of_pieces;
    for (int i = 0; i < num_of_pieces; i++)
    {
        p.clear();
        cin >> w >> h;
        for (int i = 0; i < h; i++)
        {
            cin >> input;
            p.push_back(input);
        }
        piece_list.push_back(Piece(w, h, p));
    }
    cin >> num_of_maps;
    for (int i = 0; i < num_of_maps; i++)
    {
        p.clear();
        cin >> w >> h;
        for (int i = 0; i < h; i++)
        {
            cin >> input;
            p.push_back(input);
            map_list.push_back(Map(w, h, p));
        }

        while (!map_history.empty())
        {
            // clear the stack
            map_history.pop();
        }

        map_history.push(Map(w, h, p));
        result = solve(0);
        if (result == true)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}