#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

vector<int> next_step;

int find_shortest()
{
    int shortest = INT_MAX;
    int idx;
    for (int i = 0; i < next_step.size(); i++)
    {
        if (next_step[i] < shortest && next_step[i] != 0)
        {
            shortest = next_step[i];
            idx = i;
        }
    }
    return idx;
}

int main()
{
    int courses, pairs;
    char start, end;
    char s_temp, e_temp;
    int d_temp;
    char position;
    int total_distance = 0;
    bool exist1, exist2;
    // bool path_exist;
    int shortest_next_idx;
    vector<char> start_vec;
    vector<char> end_vec;
    vector<int> distance_vec;
    vector<char> all_courses;
    vector<char> path;
    all_courses.clear();
    cin >> courses >> pairs;
    cin >> start;
    cin >> end;
    position = start;
    path.push_back(start);

    for (int i = 0; i < pairs; i++)
    {
        exist1 = false;
        exist2 = false;
        cin >> s_temp >> e_temp >> d_temp;
        start_vec.push_back(s_temp);
        end_vec.push_back(e_temp);
        distance_vec.push_back(d_temp);

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
        // initiallize the next_step array with INT_MAXs, and with the length of all_courses
        next_step.push_back(INT_MAX);
    }
    // for (int i = 0; i < all_courses.size(); i++)
    // {
    //     cout << "all_courses[" << i << "] = " << all_courses[i] << "\n";
    // }

    while (position != end)
    {
        // cout << "total distance before = " << total_distance << "\n";
        // fill the array of next step
        for (int i = 0; i < next_step.size(); i++)
        {
            // path_exist = false;
            if (position == all_courses[i])
            {
                next_step[i] = 0;
            }
            else
            {
                for (int j = 0; j < start_vec.size(); j++)
                {
                    if (start_vec[j] == position && end_vec[j] == all_courses[i])
                    {
                        // path_exist = true;
                        next_step[i] = distance_vec[j];
                    }
                    // else if (j == start_vec.size() - 1)
                    // {
                    //     if (start_vec[j] != position || end_vec[j] != all_courses[i])
                    //     {
                    //         next_step[i] = INT_MAX;
                    //     }
                    // }
                }
            }
        }
        shortest_next_idx = find_shortest();
        // cout << "shortest_next_idx = " << shortest_next_idx << "\n";
        total_distance += next_step[shortest_next_idx];
        position = all_courses[shortest_next_idx];
        path.push_back(position);

        // for (int i = 0; i < distance_vec.size(); i++)
        // {
        //     cout << "next_step[" << i << "] = " << next_step[i] << "\n";
        // }
        // cout << "position = " << position << "\n";
        // cout << "total_distance = " << total_distance << "\n";

        // reset the next_step array
        for (int i = 0; i < next_step.size(); i++)
        {
            next_step[i] = INT_MAX;
        }
    }
    // cout << "\n--------\nshortest length = " << total_distance << "\n";
    cout << total_distance << "\n";
    for (int i = 0; i < path.size(); i++)
    {
        if (i != 0)
            cout << " " << path[i];
        else
            cout << path[i];
    }
    return 0;
}