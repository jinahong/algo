/*

https://www.acmicpc.net/problem/14502

0:빈칸, 1:wall, 2: virus


벽의 개수는 3개

 */
#include <iostream>

using namespace std;
int arr[10][10];
int spread_arr[10][10];
int ans=-9999;
int n, m;

#define WALL 1
#define EMPTY 0
#define VIRUS 2

void debug(int dis)
{
    for(int i=0;i<n;i++)
    {

        for(int j=0;j<m;j++)
        {
            if(dis ==0)
                cout << arr[j][i] << " ";
            else if(dis == 1)
                cout << spread_arr[j][i] << " ";
        }
        cout << endl;
    }
}

bool safe(int x,int y)
{
    return (x < m && x >= 0 && y < n && y >= 0);
}

void dfs(int x, int y)
{
    if(spread_arr[x][y] == EMPTY && safe(x, y))
    {
        spread_arr[x][y]= VIRUS;
    }
    else return;

    dfs(x+1, y);
    dfs(x,y+1);
    dfs(x-1, y);
    dfs(x, y-1);

}

void copy_arr()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            spread_arr[j][i] = arr[j][i];
}

void spread_virus()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(spread_arr[j][i] == VIRUS)
            {
                int x = j;
                int y = i;

                dfs(x+1, y);
                dfs(x,y+1);
                dfs(x-1, y);
                dfs(x, y-1);
            }
        }
    }
}
void get_safe_space()
{
    int cnt = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(spread_arr[j][i] == EMPTY)
                cnt++;
    if(ans < cnt)
    {
        ans = cnt;
    }
}

void build_wall(int cnt)
{
    if(cnt == 3)
    {
        copy_arr();
        spread_virus();
        get_safe_space();
        return;
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(arr[j][i] == EMPTY)
            {
                arr[j][i] = WALL;
                build_wall(cnt+1);
                arr[j][i] = EMPTY;
            }
        }
    }
}

void solve()
{
    build_wall(0);
}

int main()
{
    cin >> n >> m;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> arr[j][i];

    solve();
    cout << ans << endl;
}
