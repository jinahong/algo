/*
개삽질 log
 
 -dfs fail
1. dfs 방식으로 vector에 좌표 넣는방식을 진행. dup제거, sort함수등등 만듬..
vector와 관련된 온갖 삽질과 너무 많은 함수들 때문에 코드가 복잡해짐. global변수도 관리힘든지경.
2. dfs + visited 를 쓰면서, vector가 너무 많고, dup제거, sort때문에 시간초과됨

-bfs
3. bfs + visited로 바꿈. visited에 상어와 해당 좌표간의 거리를 입력함. 
해당 좌표부터 상어까지의 거리를 계산할 필요가 없어지기 때문에 편함. 


사실 설계를 잘못함. 
거리1만큼 떨어진 위치찾기위해 dfs, 거리2만큼 떨어진 위치 찾으려고 dfs거리다보니 중복된 연산이 너무 많았음.


   -조건 확인 제대로 하기

   상어가 지나갈 수 있는 곳: 자기랑 크기가 같은 물고기칸, 혹은 빈칸
   상어가 못지나가는 곳: 자기보다 큰 물고기칸
   상어가 먹을 수 있는 고기: 크기 작은 물고기
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int arr[21][21];
int visited[21][21];

int dx[4] = {0,-1,1,0};
int dy[4] = {-1,0,0,1};

typedef struct pos{
    int x, y, time;
} pos;

int sharkAge = 2;
int ans;
int n;

bool safe(int x, int y)
{
    return (x>=0 && y>=0 && x<n && y<n);
}
bool safepass(int x, int y)
{
    return (arr[x][y] >= 0 || arr[x][y] <= sharkAge);    
}

//cnt가 0이 될때까지 shark가 이동할 수 있는 좌표들과 그 거리를 visited에 기록
void bfs(pos shark)
{
    queue<pos> q;
    q.push(shark);
    visited[shark.x][shark.y] = 1;

    while(!q.empty())
    {
        pos tmp = q.front();q.pop();
        for(int i=0;i<4;i++)
        {
            int tx = tmp.x + dx[i];
            int ty = tmp.y + dy[i];
            if(safe(tx, ty) && safepass(tx, ty) && visited[tx][ty] == 0)
            {
                visited[tx][ty] = tmp.time+1;
                pos tmp_push = {tx, ty, tmp.time+1};
                q.push(tmp_push);
            }
        }
    }
    //상어 위치는 다시 0으로 세팅해줌 ..ㅈㅅ..
    visited[shark.x][shark.y] = 0;
}

//visited를 보고, 요구사항에 맞게 가장 먼저 먹게되는 고기 찾기. 
pos searchEatableFish(pos shark)
{
    pos ans = shark;
    ans.time = 9999;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(visited[j][i] > 0  //reachable
                && arr[j][i] < sharkAge  //eatable
                && arr[j][i] > 0)
            {
                if(ans.time > visited[j][i])
                {
                    pos tmp = {j,i,visited[j][i]};
                    ans = tmp;
                }
                else if(ans.time == visited[j][i])
                {
                    if(ans.y > i || (ans.y == i && ans.x > j) )
                    {
                        pos tmp = {j,i,visited[j][i]};
                        ans = tmp;
                    }
                }

            }
        }
    }

    if(shark.x == ans.x && shark.y == ans.y) 
    {
        ans.x = -1; ans.y = -1; ans.time = -1;
    }
    return ans;
}


int main()
{
    pos shark;
    vector<pos> sharks;
    scanf("%d", &n);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d", &arr[j][i]);
            if(arr[j][i] == 9)
            {
                shark = (pos){j,i,0};
                arr[j][i] = 0;//remove shark position
            }
        }
    }
    int eatenfish = 0;
    int distance = 1;

    while(1)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                visited[i][j] = 0;

        //1. shark좌표에서 이동할 수 있는 거리 map만들기 
        bfs(shark);
        //2. 먹을 수 있는 고기찾기.
        pos it = searchEatableFish(shark);

        if(it.x != -1 && it.y != -1 && it.time != -1)
        {
            arr[it.x][it.y] = 0;
            eatenfish += 1;
            if(eatenfish == sharkAge)
            {
                eatenfish = 0;
                sharkAge += 1;
            }
            ans = it.time;
            //상어 위치 변경
            shark = it;
        }
        //도달 가능한 영역에 먹을 수 있는 고기가 없음. 
        else
            break;
    }
    printf("%d\n", ans);
}
