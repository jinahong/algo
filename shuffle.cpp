#include <iostream>

using namespace std;
string arr[1001];

void solve(int n)
{
    if(n&2 == 0)
    {
        int p1 =0;
        int p2 = n/2;
        for(int i=0;i<n/2;i++)
        {
            cout << arr[p1++] <<" ";
            cout << arr[p2++] <<" ";
        }
    }
    else
    {
        int p1 =0;
        int p2 = n/2+1;
        for(int i=0;i<n/2;i++)
        {
            cout << arr[p1++] <<" ";
            cout << arr[p2++] <<" ";
        }
        cout << arr[p1++];
    }
}

int main()
{
    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        int iter;
        cin >> iter;
        for(int j=0;j<iter;j++)
            cin >> arr[j];
        cout << "#" << i+1 << " ";
        solve(iter);
        cout << endl;
    }
}
