/*
https://www.acmicpc.net/problem/14502

basic:
bfs+dfs이다보니 time complexity제대로 계산해봐야함. 

detail:

 */
#include <iostream>
#include <queue>
using namespace std;
int arr[10][10];
int spread_arr[10][10];

int ans = -9999;
int n, m;

#define WALL 1
#define EMPTY 0
#define VIRUS 2

struct pos{
    int x, y;
    pos(int _x, int _y) : x(_x), y(_y) {}
};

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

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


//bfs, 안전 영역크기 구하기.
void spread_virus()
{
    queue<pos> q;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            //spread_arr에 copy하기.
            spread_arr[j][i] = arr[j][i];
            if(spread_arr[j][i] == VIRUS)
                q.push(pos(j,i));
        }

    while(!q.empty())
    {
        int x = q.front().x;
        int y = q.front().y;
        q.pop();
        
        for(int i=0;i<4;i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i]; 
            if(safe(nx, ny) && spread_arr[nx][ny] == EMPTY)
            {
                spread_arr[nx][ny] = VIRUS;
                q.push(pos(nx, ny));
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

void solve(int cnt)
{
    if(cnt == 3)
    {
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
                solve(cnt+1);
                arr[j][i] = EMPTY;
            }
        }
    }
}

int main()
{
    cin >> n >> m;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> arr[j][i];

    solve(0);
    cout << ans << endl;
}
