/*
https://www.acmicpc.net/problem/16234

basic: 
이주할 수 있는 국경찾는 bfs

detail:
하루동안에 여러번의 bfs가 가능하며, 정답은 bfs횟수가 아니며 몇일이 걸리는지를 묻는다.


etc:
2:30분은 걸린듯 ㅠㅠ
 */

#include <iostream>
#include <utility>
#include <queue>
#include <string.h>
using namespace std;

int arr[101][101];
int visited[101][101];

struct pos{
    int x, y;
    pos(int _x, int _y) : x(_x), y(_y) {}
};

int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};

int n;
int l, r; //인구이동 여부 결정

bool safe(int x, int y)
{
    return x >=0 && y >= 0 && x <n && y < n;
}

bool openborder(pos cur, pos next)
{
    int diff = abs(arr[cur.x][cur.y] - arr[next.x][next.y]);
    return diff<=r && diff>=l;
}

pair<int, vector<pos> > bfs(pos cur, const int count)
{
    int sum = arr[cur.x][cur.y];
   // int country_cnt = 1;

    queue<pos> q;
    vector<pos> track;
    q.push(cur);
    visited[cur.x][cur.y] = count;

    while(!q.empty())
    {
        pos tmp = q.front();q.pop();
      //  cout << "pop" << tmp.x << "," << tmp.y << endl;
        for(int i=0;i<4;i++)
        {
            int nx = tmp.x + dx[i];
            int ny = tmp.y + dy[i];
            if(safe(nx, ny)
                    && visited[nx][ny] == -1
                    && openborder(tmp, pos(nx,ny)))
            {
                visited[nx][ny] = count;
                q.push(pos(nx, ny));
                track.push_back(pos(nx,ny));

                sum += arr[nx][ny];
            }
        }
    }
    //migration 수행 안했으므로, 초기화해주기.
    if(sum == arr[cur.x][cur.y])
    {
        visited[cur.x][cur.y] = -1;
        return make_pair(0, track);
    }
    else
    {
        track.push_back(cur);
        return make_pair(sum, track);

    }
    
}
int migrations()
{
    //하루에 몇번 migration을 하는지 저장
    int aday_cnt = 0;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(visited[j][i] == -1)
            {
                pair<int, vector<pos> > res = bfs(pos(j, i), aday_cnt);

                if(res.second.size() > 0) 
                {
                   // cout << "did migration" << j << "," << i << ",ocuntrycnt : " <<res.second.size()<<endl;
                    int avg = res.first / res.second.size();
                    for(int k = 0 ; k<res.second.size();k++)
                    {
                        arr[res.second[k].x][res.second[k].y] = avg;
                    }
                    aday_cnt++;
                }
            }
        }
    }
    return aday_cnt;
}
int solve()
{
    int day = 0;
    //하루동안에 이동한 적이 있음.
    while(migrations() > 0)
    {
        day++;
        memset(visited, -1, sizeof(visited)); 
    }

    return day;
}

int main()
{
    cin >> n >> l >> r;

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> arr[j][i];
    
    memset(visited, -1, sizeof(visited)); 
    printf("%d\n", solve());

}
