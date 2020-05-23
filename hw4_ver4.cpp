#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

vector<char> start_vec;
vector<char> end_vec;
vector<int> distance_vec;
vector<char> all_courses;
vector<char> previous;
vector<int> distance_from_start;
char start_pt, end_pt;

void solve(char tmp_start)
{
    int idx_of_tmp_start;
    // find idx_of_tmp_start
    for (int i = 0; i < all_courses.size(); i++)
    {
        if (all_courses[i] == tmp_start)
            idx_of_tmp_start = i;
    }

    // if (!visited[idx_of_tmp_start])
    // {
    // cout << "solving " << tmp_start << ": \n";
    for (int i = 0; i < distance_from_start.size(); i++)
    {
        // calculate every value of distance_from_start
        for (int j = 0; j < start_vec.size(); j++)
        {
            if (start_vec[j] == tmp_start && end_vec[j] == all_courses[i])
            {
                //the path exists
                if (distance_from_start[idx_of_tmp_start] + distance_vec[j] < distance_from_start[i])
                {
                    // a shorter path is found
                    distance_from_start[i] = distance_from_start[idx_of_tmp_start] + distance_vec[j];
                    previous[i] = tmp_start;
                    solve(end_vec[j]);
                }
            }
        }
        // }

        // visited[idx_of_tmp_start] = true;
    }
    for (int i = 0; i < distance_from_start.size(); i++)
    {
        // cout << "distance_from_start[" << i << "] = " << distance_from_start[i] << "\n";
    }
    // cout << "\n";
}

int main()
{
    int courses, pairs;
    char s_temp, e_temp;
    int d_temp;
    bool exist1, exist2;
    int idx_of_real_end;

    vector<char> reversed_path;
    char tmp_char;
    int idx_of_tmp_char;

    cin >> courses >> pairs;
    cin >> start_pt;
    cin >> end_pt;

    for (int i = 0; i < pairs; i++)
    {
        exist1 = false;
        exist2 = false;
        cin >> s_temp >> e_temp >> d_temp;
        start_vec.push_back(s_temp);
        end_vec.push_back(e_temp);
        distance_vec.push_back(d_temp);

        // construct all_course vector, which will not change after completely constructed
        for (int j = 0; j < all_courses.size(); j++)
        {
            if (all_courses[j] == s_temp)
                exist1 = true;
            if (all_courses[j] == e_temp)
                exist2 = true;
        }
        if (exist1 == false)
            all_courses.push_back(s_temp);
        if (exist2 == false)
            all_courses.push_back(e_temp);
    }
    for (int i = 0; i < all_courses.size(); i++)
    {
        previous.push_back('X');
        if (all_courses[i] == end_pt)
        {
            idx_of_real_end = i;
        }
        if (all_courses[i] == start_pt)
        {
            distance_from_start.push_back(0);
        }
        else
            distance_from_start.push_back(INT_MAX);
    }

    for (int i = 0; i < all_courses.size(); i++)
    {
        // cout << "all_courses[" << i << "] = " << all_courses[i] << "\n";
    }
    for (int i = 0; i < start_vec.size(); i++)
    {
        // cout << "start_vec, end_vec, distance_vec [" << i << "] = " << start_vec[i] << ", " << end_vec[i] << ", " << distance_vec[i] << "\n";
    }

    solve(start_pt);
    cout << distance_from_start[idx_of_real_end] << "\n";
    for (int i = 0; i < previous.size(); i++)
    {
        // cout << "previous[" << i << "] = " << previous[i] << "\n";
    }

    tmp_char = end_pt;
    while (1)
    {
        if (tmp_char == 'X')
            break;
        reversed_path.push_back(tmp_char);
        for (int i = 0; i < all_courses.size(); i++)
        {
            if (all_courses[i] == tmp_char)
                idx_of_tmp_char = i;
        }
        tmp_char = previous[idx_of_tmp_char];
    }
    for (int i = reversed_path.size() - 1; i >= 0; i--)
    {
        // cout << "path[" << reversed_path.size() - i - 1 << "] = " << reversed_path[i] << "\n";
        if (i == 0)
            cout << reversed_path[i];
        else
            cout << reversed_path[i] << " ";
    }

    return 0;
}