/*

https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV15QRX6APsCFAYD

출발지에서 도착지까지 가는 최소 복구시간은?

5시 42분


 */
#include <iostream>
#include <string.h>

using namespace std;
int n;
int ans;
int arr[100][100];
bool visited[100][100];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
void debug()
{
    for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                cout << dp[j][i] << " ";
            cout << endl;
        }
}
bool safe(int x, int y)
{ 
    return x >= 0 && y >=0 && x<n && y<n;
}

int min4(int x, int y)
{
    int res = 9999;
    for(int i=0;i<4;i++)
    {
        int tmpx = x + dx[i];
        int tmpy = y + dy[i];
        if(safe(tmpx, tmpy))
            if(res > dp[tmpx][tmpy]) res =  dp[tmpx][tmpy];
    }
    return res;
}
void solve()
{


}
int main()
{
    int t_tc;
    cin >> t_tc;
    for(int tc=1;tc<=t_tc;tc++)
    {
        cin >> n;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                scanf("%1d", &arr[j][i]);
        }

        solve();

       printf("#%d %d\n", tc, ans);
    }
}
