#include <iostream>

using namespace std;

typedef struct line{
    int a; int b;
}line;

line lines[501];
int solve(int stopNum, int n)
{
    int sum = 0;
    for(int i=0;i<n;i++)
    {
        if(stopNum >= lines[i].a  && lines[i].b >= stopNum)
            sum++;
    }
    return sum;
}
int main()
{
    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        int n;
        cin >> n;
        for(int j=0;j<n;j++)
        {
            cin >> lines[j].a >> lines[j].b;
        }

        int p;
        cin >> p;

        cout << "#" << i+1 << " ";
        for(int j=0;j<p;j++)
        {
            int a;
            cin >> a;
            cout << solve(a, n) << " ";
        }
        cout << endl;
    }
}
