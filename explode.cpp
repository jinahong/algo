/*

https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo

basic:
구슬의 위치는 중복이 가능한 permutation
구슬 터지는 것은 bfs로 구현, explode는 처음엔 dfs로 했는데, bfs가 더 직관적이고 쉬운거 같음. 

detail: 
bfs시 map을 reference로 넘겨줌. reference리턴하는 방법은 모르겠다. 그냥 모를래
bfs시 visited는 필수적인듯..

*/

#include <queue>
#include <utility>
#include <iostream>
#include <string.h>
using namespace std;

int n, w, h;
int ans;
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};

void debug(int arr[][16])
{
    for(int j=0;j<h;j++)
    {
        for(int i=0;i<w;i++)

            cout << arr[i][j] << " ";
        cout << endl;
    }
}

bool safe(int x, int y)
{
    return x>=0 && x < w && y>=0 && y< h;
}

int getRoof(int i, int map[][16])
{
    int y=0;for(;y<h;y++) if(map[i][y]>0) break;
    return y;
}

void explode(int drop, int roof, int map[][16])
{
    bool visited[13][16] = {0,};

    queue<pair<int, int> > q;

     q.push(make_pair(drop, roof));
     visited[drop][roof] = true;

    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
         
        q.pop();
        int size = map[x][y];
        map[x][y] = 0;

        if(size>1)
        {
            for(int i=0;i<4;i++)
            {
                for(int j=1;j<size;j++)
                {
                    int tmpx = x + j * dx[i];
                    int tmpy = y + j * dy[i];
                    if(safe(tmpx, tmpy) && map[tmpx][tmpy]!=0 && !visited[tmpx][tmpy])
                    {
                        if(map[tmpx][tmpy]>1)
                        {
                            q.push(make_pair(tmpx, tmpy));
                            visited[tmpx][tmpy] = true;
                        }
                        else
                            map[tmpx][tmpy] = 0;
                    }
                }
            }
        }
    }
}
void update(int map[][16])
{  
    for(int j=0;j<w;j++)
    {
        int idx = h-1;
        int i = h-1;
        for(;i>=0;i--)
        {
            if(map[j][i] > 0) 
            {
                map[j][idx] = map[j][i];
                idx--;
            }
        }
        if(idx!=i) for(;idx>=0;idx--) map[j][idx] =0;
    }
}

int getBlock(int map[][16])
{
    int res = 0;
    for(int b=0;b<h;b++)
        for(int a=0;a<w;a++)
            if(map[a][b]!=0) res++;
    return res;
}

bool solve_dfs(int map[][16], int depth)
{
    int res = getBlock(map);
    if(res == 0) 
    {
        ans = res;
        return true; //이미 ans나옴
    }
    if(depth == 0)
    {
        if(res < ans) ans = res;
        return false; //계속 탐색필요
    }

    //XXX:dfs에서 사용될 map
    int mapTmp[13][16];
   
    for(int drop = 0 ; drop < w ; drop++)
    {
        int roof = getRoof(drop, map); //0이면 처음부터 꽉차있는경우

        if(roof >= 0 && roof < h)
        {
            memcpy(mapTmp,map,sizeof(mapTmp));

            explode(drop, roof, mapTmp);
            update(mapTmp);
            if(solve_dfs(mapTmp, depth-1)) return true;
        }
    }
    return false;
}

int main()
{
    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        int arr[13][16];
        cin >> n >> w >> h;

        for(int b=0;b<h;b++)
            for(int a=0;a<w;a++)
            {
                cin >> arr[a][b];
            }

        ans = 99999;

        solve_dfs(arr,  n);
        printf("#%d %d\n", i+1, ans);
    }
}

