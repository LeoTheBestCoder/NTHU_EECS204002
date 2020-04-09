/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 107061218
 * 3. OJ ID: leo
 * 4. OJ SID: 2135112
 * 5. OJ Score: 10/10
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
    int items, capacity;
    cin >> items >> capacity;
    int value[items], weight[items];
    int best_case[capacity + 1]; //discard first element best_case[0]
    for (int i = 0; i <= capacity; i++)
    {
        best_case[i] = 0; //initialize the best case array with all 0s
    }
    /*
    printf("items = %d, capacity = %d\n", items, capacity);
    for(int i=0; i<=capacity; i++){
        printf("best_case[%d] = %d\n", i, best_case[i]);
    }
    */
    // just for debugging propose

    for (int i = 0; i < items; i++)
    {
        cin >> value[i] >> weight[i];
    }

    for (int i = 0; i < items; i++)
    {
        for (int j = capacity; j >= weight[i]; j--)
        {
            //this code decide whether put the item in is more valuable or not
            //In other words, if I want to put this item in,
            //I will have to make room for it
            //So, we should move back to best_case[j - weight[i]]
            if (best_case[j] < best_case[j - weight[i]] + value[i])
            {
                best_case[j] = best_case[j - weight[i]] + value[i];
            }
            //If it is more valuable to put the item in, then we update the best_case value
            //if not, just remain the same
            //these comments are all edited by 107061218 ���M�a
        }
        /*
        for(int k=0; k<=capacity; k++){
            printf("best_case[%d] = %d\n", k, best_case[k]);
        }
        */
        //just for debugging propose
    }
    cout << best_case[capacity];
    return 0;
}
