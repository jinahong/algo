/*
   https://www.acmicpc.net/problem/15686


  -  함수 side effect항상 기억하기!!!!!!!
  
  time out
  - 치킨집이랑 집간의 거리구하로겨, bfs했는데 시간 너무걸림.. 그냥 이중포문으로 최소값 찾음
  -dfs 함수내에서 for문을 많이돌아서 시간초과. start_idx 추가해서 iteration회수줄임. 
 */

#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

#define VISITED 999
int ans=9999;

typedef struct pos{
    int x, y, d;
} pos;

bool visited[14];
vector<pos> bbq;
vector<pos> house;
int arr[51][51];
int n;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

bool safe(int x, int y)
{
    return x<n && y<n && x>=0 && y>=0;
}
void debug(int map[][51])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout << map[j][i] << " ";
        cout << endl;
    }
}
/*
   void make_bfs_map(int map[][51])
   {
   for(int i=0;i<n;i++)
   for(int j=0;j<n;j++)
   {
   map[j][i] = arr[j][i];
   }
   for(int i=0;i<bbq.size();i++) 
   if(!visited[i])
   {
   map[bbq[i].x][bbq[i].y] = 0;
   }
}
int bfs()
{
int bfs_map[51][51];
make_bfs_map(bfs_map);

int res = 0;
int bfs_housecnt = 0;

queue<pos> q;
for(int i=0;i<bbq.size();i++)
if(visited[i]) 
{
q.push(bbq[i]);
}

while(!q.empty())
{
pos tmp = q.front();q.pop();
for(int i=0;i<4;i++)
{
int tmpx = tmp.x + dx[i];
int tmpy = tmp.y + dy[i];
if(safe(tmpx, tmpy)
&& bfs_map[tmpx][tmpy] != VISITED)
{
if(arr[tmpx][tmpy] == 1)
{
bfs_housecnt++;
res += tmp.d+1;
if(ans < res) 
{
return ans;
}
bfs_map[tmpx][tmpy] = VISITED;
if(house.size() == bfs_housecnt) return res;
}
pos pushable = {tmpx, tmpy, tmp.d + 1};
bfs_map[tmpx][tmpy] = VISITED;
q.push(pushable);
}
}
}
return res;
}
 */
int getDistance()
{
    int sum = 0;
    for(vector<pos>::iterator it = house.begin();it!=house.end();++it)
    {
        int x = it->x;
        int y = it->y;
        vector <int> v;
        int minVal = 9999;

        for(vector<pos>::iterator it_bbq = bbq.begin();it_bbq!=bbq.end();++it_bbq)

            if(visited[it_bbq - bbq.begin()])
                v.push_back(abs((x - it_bbq->x)) + abs((y - it_bbq->y)));

        for (int i = 0; i < v.size(); i++)
            minVal = min(minVal, v[i]);

        sum += minVal;
    }
    return sum;
}
void solve(int start_idx, int dep)
{
    if(start_idx > bbq.size()) return;
    //visited에서 true로 남은 것들만 거리구하면됨
    if(dep == 0)
    {
        //int distance = bfs();
        int distance = getDistance();
        if(ans > distance) ans = distance;
        return;
    }
    //XXX: bbp 개수만큼 iteration
    for(int i = start_idx ; i < bbq.size() ; i++)
    {
        visited[i] = true;
        solve(i+1, dep-1);
        visited[i] = false;
    }
    
    /*
       //같은방법:
        visited[i] = true;//i번째 체인점선택!
        solve(i+1, dep-1);

        visited[i] = false;//i번째 체인점 안선택!  
        solve(i+1, dep);
        */
}

int main()
{
    cin >> n;

    int m;
    cin >> m;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin >> arr[j][i];
            if(arr[j][i] ==2)
            {
                pos tmp = {j,i, 0};
                bbq.push_back(tmp);
            }
            else if(arr[j][i] ==1)
            {
                pos tmp = {j,i, 0};
                house.push_back(tmp);
            }
        }
    }
    
    solve(0, m);
    
    cout << ans << endl;
}
