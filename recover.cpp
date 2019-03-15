/*
1:20분
   dfs로 했다가 컴퓨터 죽으려고해서, 
   dp로 바꿈.
   [debug]4방향으로 움직일 수 잇어서, dp가 stable해질때까지 최소값 계속구함..
 */
#include <iostream>
#include <string.h>

using namespace std;
int n;
int ans;
int arr[100][100];
bool visited[100][100];

int dp[100][100];
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
void dp_func()
{
    for(int i=1;i<n;i++)
    {
        dp[0][i] = dp[0][i-1] + arr[0][i];
        dp[i][0] = dp[i-1][0] + arr[i][0]; 
    }
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<n;j++)
        {
            dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + arr[i][j];
        }
    }
    bool flag = false;
    do
    {
        flag = false;  
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i == 0 && j == 0) continue;
                int tmp  = min4(i,j) + arr[i][j];
                if(dp[i][j]!=tmp) 
                {
                    dp[i][j] = tmp;
                    flag = true;
                }
            }
        }
//        cout << "reset" << endl;
//        debug();
    } while(flag);
}
void dfs(int x, int y, int recover)
{
    if(x == n-1 && y == n-1)
    {
        if(ans > recover) ans = recover;
        return;
    }
    for(int i=0;i<4;i++)
    {
        int tmpx = x + dx[i];
        int tmpy = y + dy[i];
        if(safe(tmpx, tmpy) && !visited[tmpx][tmpy])
        {
            visited[tmpx][tmpy] = true;
            dfs(tmpx, tmpy, recover + arr[tmpx][tmpy]);
            visited[tmpx][tmpy] =  false;
        }
    }
}
void solve()
{
    /*
       ans = 999999;
       memset(visited, 0, sizeof(visited));
       visited[0][0] = true;
       dfs(0,0, 0);
     */
    memset(dp, 0, sizeof(dp));
    dp_func();
    ans = dp[n-1][n-1];
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
