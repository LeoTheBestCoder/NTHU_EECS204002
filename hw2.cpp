#include <iostream>
#include <limits.h>
#include <cstdio>
#include <algorithm>
#include <iomanip>

using namespace std;

class People
{
private:
    int enter_date, row, col;
    int recovery_time;
    int days_surrounded = 0; // days_surrounded means the consecutive days surrounded by more then 3 sick people
    string name, state, next_state;
    bool place_or_not = false;
    bool added_by_left = false, added_by_right = false, added_by_up = false, added_by_down = false;
    bool in_ICU = false, alive = true;

public:
    People(int d = 0, int r = 0, int c = 0, string n = "", string s = "Healthy")
    {
        enter_date = d;
        row = r;
        col = c;
        name = n;
        state = s;
        next_state = state;
        if (state == "Sick")
            recovery_time = 14;
        else
            recovery_time = 0;
    }
    int get_row()
    {
        return row;
    }
    int get_col()
    {
        return col;
    }
    int get_enter_date()
    {
        return enter_date;
    }
    string get_name()
    {
        return name;
    }
    void set_state(string temp)
    {
        state = temp;
    }
    void update_state()
    {
        state = next_state;
    }
    string get_state()
    {
        return state;
    }
    void set_next_state(string temp)
    {
        next_state = temp;
    }
    void print()
    {
        cout << enter_date << " " << row << " " << col << " " << name << " " << state << " " << place_or_not << "\n";
    }
    void put_on()
    {
        place_or_not = true;
    }
    void take_away()
    {
        place_or_not = false;
    }
    bool get_on_sm()
    {
        return place_or_not;
    }
    int get_r_time()
    {
        return recovery_time;
    }
    void add_r_time(int t)
    {
        recovery_time = recovery_time + t;
    }

    void infected_by_left()
    {
        added_by_left = true;
    }
    bool get_infected_by_left()
    {
        return added_by_left;
    }

    void infected_by_right()
    {
        added_by_right = true;
    }
    bool get_infected_by_right()
    {
        return added_by_right;
    }

    void infected_by_up()
    {
        added_by_up = true;
    }
    bool get_infected_by_up()
    {
        return added_by_up;
    }

    void infected_by_down()
    {
        added_by_down = true;
    }
    bool get_infected_by_down()
    {
        return added_by_down;
    }
    int get_days_surrounded()
    {
        return days_surrounded;
    }
    void add_days_surrounded()
    {
        days_surrounded++;
    }
    void reset_days_surrounded()
    {
        days_surrounded = 0;
    }
    void go_to_ICU()
    {
        in_ICU = true;
    }
    bool get_in_ICU()
    {
        return in_ICU;
    }

    void die()
    {
        alive = false;
    }

    bool get_alive_or_not()
    {
        return alive;
    }

    People up(int num_of_people, People people_list[])
    {
        for (int i = 0; i < num_of_people; i++)
        {
            if (people_list[i].get_on_sm() && people_list[i].get_row() == row - 1 && people_list[i].get_col() == col)
            {
                return people_list[i];
            }
        }
        return People(-1, -1, -1, "Invalid", "Empty_or_out_of_range");
    }
    People down(int num_of_people, People people_list[])
    {
        for (int i = 0; i < num_of_people; i++)
        {
            if (people_list[i].get_on_sm() && people_list[i].get_row() == row + 1 && people_list[i].get_col() == col)
            {
                return people_list[i];
            }
        }
        return People(-1, -1, -1, "Invalid", "Empty_or_out_of_range");
    }
    People left(int num_of_people, People people_list[])
    {
        for (int i = 0; i < num_of_people; i++)
        {
            if (people_list[i].get_on_sm() && people_list[i].get_col() == col - 1 && people_list[i].get_row() == row)
            {
                return people_list[i];
            }
        }
        return People(-1, -1, -1, "Invalid", "Empty_or_out_of_range");
    }
    People right(int num_of_people, People people_list[])
    {
        for (int i = 0; i < num_of_people; i++)
        {
            if (people_list[i].get_on_sm() && people_list[i].get_col() == col + 1 && people_list[i].get_row() == row)
            {
                return people_list[i];
            }
        }
        return People(-1, -1, -1, "Invalid", "Empty_or_out_of_range");
    }
};

int ICU_capacity;

bool comp(People a, People b)
{
    if (a.get_row() != b.get_row())
        return a.get_row() < b.get_row();
    else if (a.get_row() == b.get_row())
    {
        return a.get_col() < b.get_col();
    }
    return a.get_row() < b.get_row();
}

void calc(int day, int output_day, int num_of_people, People people_list[])
{
    // cout << "day " << day << ": \n";
    int sick_people_around;

    for (int i = 0; i < num_of_people; i++)
    {
        people_list[i].update_state();
        if (people_list[i].get_enter_date() == day)
        {
            people_list[i].put_on();

            // cout << people_list[i].get_name() << " is put on the sm.\n";
            // cout << "His up neighbor is ";
            // people_list[i].up(num_of_people, people_list).print();
            // cout << "His down neighbor is ";
            // people_list[i].down(num_of_people, people_list).print();
            // cout << "His left neighbor is ";
            // people_list[i].left(num_of_people, people_list).print();
            // cout << "His right neighbor is ";
            // people_list[i].right(num_of_people, people_list).print();
        }
        if (people_list[i].get_r_time() == 0 && people_list[i].get_state() != "Masked")
        {
            people_list[i].set_state("Healthy");
        }
    }
    // for (int i = 0; i < num_of_people; i++)
    // {
    // if (people_list[i].get_on_sm())
    // {
    // cout << people_list[i].get_name() << " is put on the sm.\n";
    // cout << "His up neighbor is ";
    // people_list[i].up(num_of_people, people_list).print();
    // cout << "His down neighbor is ";
    // people_list[i].down(num_of_people, people_list).print();
    // cout << "His left neighbor is ";
    // people_list[i].left(num_of_people, people_list).print();
    // cout << "His right neighbor is ";
    // people_list[i].right(num_of_people, people_list).print();
    // }
    // }
    for (int i = 0; i < num_of_people; i++)
    {
        // People center = people_list[i];
        // People up_neighbor = people_list[i].up(num_of_people, people_list);
        // People down_neighbor = people_list[i].down(num_of_people, people_list);
        // People left_neighbor = people_list[i].left(num_of_people, people_list);
        // People right_neighbor = people_list[i].right(num_of_people, people_list);
        sick_people_around = 0;
        if (people_list[i].get_state() == "Healthy")
        {
            if (people_list[i].up(num_of_people, people_list).get_enter_date() == day && people_list[i].up(num_of_people, people_list).get_state() == "Sick")
            {
                people_list[i].set_next_state("Sick");
                people_list[i].add_r_time(14);
            }
            else if (people_list[i].down(num_of_people, people_list).get_enter_date() == day && people_list[i].down(num_of_people, people_list).get_state() == "Sick")
            {
                people_list[i].set_next_state("Sick");
                people_list[i].add_r_time(14);
            }
            else if (people_list[i].left(num_of_people, people_list).get_enter_date() == day && people_list[i].left(num_of_people, people_list).get_state() == "Sick")
            {
                people_list[i].set_next_state("Sick");
                people_list[i].add_r_time(14);
            }
            else if (people_list[i].right(num_of_people, people_list).get_enter_date() == day && people_list[i].right(num_of_people, people_list).get_state() == "Sick")
            {
                people_list[i].set_next_state("Sick");
                people_list[i].add_r_time(14);
            }
        }

        if (people_list[i].up(num_of_people, people_list).get_state() == "Sick" && people_list[i].get_infected_by_up() == false)
        {
            people_list[i].add_r_time(7);
            people_list[i].infected_by_up();
            // sick_people_around++;
        }
        if (people_list[i].down(num_of_people, people_list).get_state() == "Sick" && people_list[i].get_infected_by_down() == false)
        {
            people_list[i].add_r_time(7);
            people_list[i].infected_by_down();
            // sick_people_around++;
        }
        if (people_list[i].left(num_of_people, people_list).get_state() == "Sick" && people_list[i].get_infected_by_left() == false)
        {
            people_list[i].add_r_time(7);
            people_list[i].infected_by_left();
            // sick_people_around++;
        }
        if (people_list[i].right(num_of_people, people_list).get_state() == "Sick" && people_list[i].get_infected_by_right() == false)
        {
            people_list[i].add_r_time(7);
            people_list[i].infected_by_right();
            // sick_people_around++;
        }

        if (people_list[i].up(num_of_people, people_list).get_state() == "Sick" && people_list[i].up(num_of_people, people_list).get_enter_date() != day)
        {
            sick_people_around++;
        }
        if (people_list[i].down(num_of_people, people_list).get_state() == "Sick" && people_list[i].down(num_of_people, people_list).get_enter_date() != day)
        {
            sick_people_around++;
        }
        if (people_list[i].left(num_of_people, people_list).get_state() == "Sick" && people_list[i].left(num_of_people, people_list).get_enter_date() != day)
        {
            sick_people_around++;
        }
        if (people_list[i].right(num_of_people, people_list).get_state() == "Sick" && people_list[i].right(num_of_people, people_list).get_enter_date() != day)
        {
            sick_people_around++;
        }

        if (sick_people_around == 4)
        {
            people_list[i].add_days_surrounded();
        }
        else
        {
            people_list[i].reset_days_surrounded();
        }
    }

    for (int i = 0; i < num_of_people; i++)
    {
        if (people_list[i].get_r_time() > 28 && ICU_capacity > 0 && people_list[i].get_on_sm())
        {
            // send the patient to ICU
            people_list[i].go_to_ICU();
            people_list[i].take_away();
            ICU_capacity--;
        }

        if (people_list[i].get_days_surrounded() > 7 && people_list[i].get_on_sm())
        {
            // die
            people_list[i].die();
            people_list[i].take_away();
        }

        if (people_list[i].get_r_time() > 0 && people_list[i].get_on_sm() && people_list[i].get_state() == "Sick")
        {
            people_list[i].add_r_time(-1);
        }
    }

    // for checking propose

    cout << "day " << day << ": \n";
    cout << "name\tstate\t r_time\t \tsurrounded_days on_sm\t in_ICU\t alive:\t \n";

    for (int i = 0; i < num_of_people; i++)
    {
        cout << people_list[i].get_name() << " \t" << people_list[i].get_state() << "\t  ";
        cout << people_list[i].get_r_time() << "\t\t" << people_list[i].get_days_surrounded() << "\t\t" << people_list[i].get_on_sm() << "\t";
        cout << people_list[i].get_in_ICU() << "\t" << people_list[i].get_alive_or_not() << "\n";
    }
    cout << "\n";

    // if (day == output_day - 1)
    // {
    //     int alive_num = 0;
    //     int people_on_map = 0;
    //     // cout << "People alive at last: \n";
    //     for (int i = 0; i < num_of_people; i++)
    //     {
    //         if (people_list[i].get_alive_or_not() == true)
    //         {
    //             alive_num++;
    //             // cout << people_list[i].get_name() << "\n";
    //         }
    //         if (people_list[i].get_on_sm())
    //         {
    //             people_on_map++;
    //         }
    //     }

    //     survive_rate = (double)alive_num / num_of_people * 100;
    //     cout << fixed << setprecision(2) << survive_rate << "%\n";

    // sort(people_list, people_list + num_of_people, comp);
    // int print_time = 1;
    // for (int i = 0; i < num_of_people; i++)
    // {
    //     if (people_list[i].get_on_sm() && print_time != alive_num)
    //     {
    //         cout << people_list[i].get_name() << " ";
    //         print_time++;
    //     }
    //     else if (people_list[i].get_on_sm() && print_time == alive_num)
    //     {
    //         cout << people_list[i].get_name();
    //     }
    // }

    // for (int r = 0; r < 5000; r++)
    // {
    //     for (int c = 0; c < 5000; c++)
    //     {
    //         for (int i = 0; i < num_of_people; i++)
    //         {
    //             if (people_list[i].get_row() == r && people_list[i].get_col() == c && people_list[i].get_on_sm())
    //             {
    //                 if (print_time != people_on_map)
    //                     cout << people_list[i].get_name() << " ";
    //                 if (print_time == people_on_map)
    //                 {
    //                     cout << people_list[i].get_name();
    //                 }
    //             }
    //         }
    //     }
    // }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // #ifdef DEBUG
    //     freopen("COVID-19_sample_in.txt"."r", stdin);
    // #endif
    People *people_list;
    People *ans_list;
    int idx = 0;
    int sm_row, sm_col, output_day, num_of_people; // sm stands for sparse matrix
    int enter_date, row, col;
    int alive_num = 0, people_on_map = 0;
    double survive_rate;
    string name, state;

    cin >> sm_row >> sm_col >> ICU_capacity >> output_day;
    cin >> num_of_people;
    people_list = new People[num_of_people];
    ans_list = new People[num_of_people];
    for (int i = 0; i < num_of_people; i++)
    {
        cin >> enter_date >> row >> col >> name >> state;
        people_list[i] = People(enter_date, row, col, name, state);
    }

    // for (int i = 0; i < num_of_people; i++)
    // {
    //     people_list[i].print();
    // }
    for (int i = 0; i < output_day; i++)
    {
        calc(i, output_day, num_of_people, people_list);
    }
    // sort(people_list, people_list + num_of_people, comp);

    for (int i = 0; i < num_of_people; i++)
    {
        if (people_list[i].get_alive_or_not())
        {
            alive_num++;
        }
        if (people_list[i].get_on_sm())
        {
            ans_list[idx] = people_list[i];
            idx++;
            people_on_map++;
        }
    }

    // sort the ans_list
    // People temp;
    // for (int i = 0; i < people_on_map; i++)
    // {
    //     for (int j = i; j < people_on_map; j++)
    //     {
    //         if (ans_list[i].get_row() > ans_list[j].get_row())
    //         {
    //             temp = ans_list[i];
    //             ans_list[i] = ans_list[j];
    //             ans_list[j] = temp;
    //         }
    //         if (ans_list[i].get_row() == ans_list[j].get_row())
    //         {
    //             if (ans_list[i].get_col() > ans_list[i].get_col())
    //             {
    //                 temp = ans_list[i];
    //                 ans_list[i] = ans_list[j];
    //                 ans_list[j] = temp;
    //             }
    //         }
    //     }
    // }

    survive_rate = (double)alive_num / num_of_people * 100;
    cout << fixed << setprecision(2) << survive_rate << "%\n";
    // int print_time = 1;
    // for (int i = 0; i < idx; i++)
    // {
    //     if(i != idx - 1){
    //         // cout << ans_list[i].get_name() << " row = " << ans_list[i].get_row() << " col = " << ans_list[i].get_col() << "\n";
    //         cout << ans_list[i].get_name() << " ";
    //     }
    //     else{
    //         // cout << ans_list[i].get_name() << " row = " << ans_list[i].get_row() << " col = " << ans_list[i].get_col() << "\n";
    //         cout << ans_list[i].get_name();
    //     }
    // }
    int format = 0;
    for (int r = 0; r < 5000; r++)
    {
        for (int c = 0; c < 5000; c++)
        {
            for (int i = 0; i < people_on_map; i++)
            {
                if (ans_list[i].get_row() == r && ans_list[i].get_col() == c)
                {
                    if (format != idx - 1)
                    {
                        cout << ans_list[i].get_name() << " ";
                        format++;
                    }
                    else
                    {
                        cout << ans_list[i].get_name();
                    }
                }
            }
        }
    }
    return 0;
}