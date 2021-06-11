#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of process: " << endl;
    cin >> n;
    int p[n], p1[n];
    for (int i = 0; i < n; i++)
    {
        p[i] = i;
    }
    int res;
    cout << "Enter total amount of this one resource: " << endl;
    cin >> res;
    cout << "Enter max demands for every processes: " << endl;
    int max[n];
    for (int i = 0; i < n; i++)
    {
        cin >> max[i];
    }
    cout << "Enter first allocations of every processes: " << endl;
    int allo[n];
    int allo_sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> allo[i];
        allo_sum += allo[i];
    }

    int need[n];
    for (int i = 0; i < n; i++)
    {
        need[i] = max[i] - allo[i];
    }

    int avail = res - allo_sum;

    int j = 0;
    int l = 0;
    while (l < n)
    {
        int flag = 1;
        for (int i = 0; i < n; i++)
        {

            if (need[i] <= avail && need[i] != -5)
            {
                avail = avail + allo[i];

                need[i] = -5;
                p1[j++] = i;
                flag = 0;
                break;
            }
        }

        if (flag)
        {
            cout << "There is a deadlock" << endl;
            break;
        }
        l++;
    }
    cout << "Following is the SAFE Sequence" << endl;
    for (int i = 0; i < n - 1; i++)
        cout << " P" << p1[i] << " ->";
    cout << " P" << p1[n - 1] << endl;

    return 0;
}