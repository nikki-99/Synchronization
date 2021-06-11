// Banker's Algorithm
#include <iostream>
using namespace std;

int main()
{

    int n, m, i, j, k;

    cout << "Enter the number of process: " << endl;
    cin >> n;
    cout << "Enter the number of resources: " << endl;
    cin >> m;
    int tot[m];
    cout << "Enter total amount of each resources: " << endl;
    for (int i = 0; i < m; i++)
    {
        cin >> tot[i];
    }
    int max[n][m];
    for (i = 0; i < n; i++)
    {
        cout << "Enter max needs from"
             << " " << m << " "
             << "resources for"
             << " " << i << " th process: " << endl;
        for (j = 0; j < m; j++)
        {
            cin >> max[i][j];
        }
    }
    int alloc[n][m];
    for (i = 0; i < n; i++)
    {
        cout << "Enter first allocations from "
             << " " << m << " "
             << "resources for"
             << " " << i << " th process: " << endl;
        for (j = 0; j < m; j++)
        {
            cin >> alloc[i][j];
        }
    }
    int total;
    int avail[m];
    for (i = 0; i < m; i++)
    {
        total = 0;
        for (j = 0; j < n; j++)
        {
            total += alloc[j][i];
        }
        avail[i] = tot[i] - total;
    }

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int ch;
    cout << "Is there any process requesting for resources?(if Yes enter 1 or else 0)" << endl;
    cin >> ch;
    if (ch)
    {
        int num;
        cout << "Enter the number of process: " << endl;
        cin >> num;
        int dem[m];
        cout << "Enter the demands for process number "
             << " " << num << endl;
        for (int i = 0; i < m; i++)
        {
            cin >> dem[i];
            if (dem[i] > avail[i])
            {
                cout << "Deadlock Occurs" << endl;
                exit(1);
            }
            avail[i] = avail[i] - dem[i];
        }
    }
    else
    {
        cout << "Continue process" << endl;
    }
    int y = 0;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    cout << "Following is the SAFE Sequence" << endl;
    for (i = 0; i < n - 1; i++)
        cout << " P" << ans[i] << " ->";
    cout << " P" << ans[n - 1] << endl;

    return (0);
}
