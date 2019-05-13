/*

   https://www.acmicpc.net/problem/16197

basic:
bfs

detail:
visited를 4차원으로 했음. 
입력은 1개의 character씩 읽어야 함. 
 */

#include <iostream>
#include <queue>

using namespace std;

int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int n;
int m;
char arr[22][22];
bool visited[22][22][22][22];
struct info{

    int x1 , x2, y1, y2, cnt;
    info(){}
    info(int _x1, int _x2, int _y1, int _y2, int _cnt) : x1(_x1), x2(_x2), y1(_y1), y2(_y2), cnt(_cnt) {}
};
bool safe(int x, int y)
{
    return x >=0 && x < m && y >=0 && y < n;
}
//둘중하나만 fail
bool isAns(int nx1, int nx2, int ny1, int ny2)
{
    return (!safe(nx1, ny1) && safe(nx2, ny2)) || (safe(nx1, ny1) && !safe(nx2, ny2));
}
int solve(info init)
{
    queue<info> q;

    q.push(init);

    while(!q.empty())
    {
        info tmp = q.front();q.pop();

        for(int i=0;i<4;i++)
        {
            int nx1 = tmp.x1 + dx[i];
            int nx2 = tmp.x2 + dx[i];
            int ny1 = tmp.y1 + dy[i];
            int ny2 = tmp.y2 + dy[i];

            if(safe(nx1, ny1) && arr[ny1][nx1] == '#')
            {
                nx1 = tmp.x1;
                ny1 = tmp.y1;
            }
            if(safe(nx2, ny2) && arr[ny2][nx2] == '#')
            {
                nx2 = tmp.x2;
                ny2 = tmp.y2;
            }
            if(tmp.cnt+1 > 10 ) continue; 
            if(isAns(nx1, nx2, ny1, ny2)) return tmp.cnt+1;
            if(safe(nx1, ny1) && safe(nx2, ny2) && !visited[nx1][ny1][nx2][ny2])
            {
                visited[nx1][ny1][nx2][ny2] = true;
                q.push(info(nx1, nx2, ny1, ny2, tmp.cnt+1));
            }
        }
    }
    return -1;
}
int main()
{
    cin >> n>> m;
    bool flag = false;
    info init;
    init.cnt = 0;
    for(int row = 0 ; row < n ; row++)
    {
        for(int col = 0 ; col < m ; col++)
        {
            scanf("%1s", &arr[row][col]);
            if(arr[row][col] == 'o' && !flag)
            {
                init.x1 = col;
                init.y1 = row;
                flag = true;
            }
            else if(arr[row][col] == 'o' && flag)
            {
                init.x2 = col;
                init.y2 = row;
            }
        }
    }
    visited[nx1][ny1][nx2][ny2] = true;
    cout << solve(init) << endl;

}
