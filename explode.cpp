/*
solve:구슬 떨어트리는 위치를 dfs로 했다가 시간초과되서 for문으로 만듬. 
explode: 처음엔 dfs로 했는데 그냥 queue써서바꿈. 시간에 끼치는 영향은 체크안해봄.


c++문법
array를 reference로 넘겨줌. 
reference리턴하는 방법은 모르겠다. 그냥 모를래


같은코드를 실행할따마다 소요시간이 다름...ㅁㅊㅁㅊ
*/
#include <queue>
#include <utility>
#include <iostream>
#include <string.h>
using namespace std;

int n, w, h;

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

//void explode(int x_arg, int y_arg, int map[][16])
void explode(int x, int map[][16])
{
    bool visited[13][16] = {0,};

    queue<pair<int, int> > q;

     q.push(make_pair(x,getRoof(x, map)));
     visited[x][getRoof(x, map)]=true;

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
                    int tmpy =  y + j * dy[i];
                    if(safe(tmpx, tmpy) && map[tmpx][tmpy]!=0 && !visited[tmpx][tmpy])
                    {
                        if(map[tmpx][tmpy]>1)
                        {
                            q.push(make_pair(tmpx, tmpy));
                            visited[tmpx][tmpy]=true;
                    //        cout << "push" << tmpx << "," << tmpy << endl;
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
        if(idx!=i)for(;idx>=0;idx--) map[j][idx] =0;
    }
}

int ans = 99999;

int getBlock(int map[][16])
{
    int res = 0;
    for(int b=0;b<h;b++)
        for(int a=0;a<w;a++)
            if(map[a][b]!=0) res++;
    return res;
}
/*
void solve_dfs(int map[][16], int depth)
{
    
    if(depth == 0)
    {
        int res = getBlock(map);
        if(res < ans) ans = res;
        return;
    }

    int mapTmp[13][16];
   
    for(int i=0;i<w;i++)
    {
        int y=0;for(;y<h;y++) if(map[i][y]>0) break;
        memcpy(mapTmp,map,sizeof(mapTmp));
        //mapTmp = 
        explode(i,y,mapTmp);
      //  cout << "explode" << i << "," << y << endl;
       // debug(mapTmp);
        update(mapTmp);
      //  cout << "update" << endl;
       // debug(mapTmp);
        solve_dfs(mapTmp, depth-1);
    }

}

*/
void solve_iter(int map[][16], int depth)
{
    int mapTmp[13][16];
    for(int a=0;a<w;a++)
    {
        for(int b=0;b<w;b++)
        {
            for(int c=0;c<w;c++)
            {
                for(int d=0;d<w;d++)
                {
                    int abcd[4] = {a,b,c,d};
                    
                    memcpy(mapTmp,map,sizeof(mapTmp));
                    for(int i=0;i<depth;i++)
                    {
                        explode(abcd[i], mapTmp);
                    //   debug(mapTmp);

                        update(mapTmp);
                     //   cout << "update" << endl;
                    //    debug(mapTmp);
                    }

                    int res = getBlock(mapTmp);
                    if(res < ans) ans = res;
                    if(ans == 0)return;

                    if(depth<4)break;
                }
                if(depth<3)break; 
            }
            if(depth<2)break;
        }

    }
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

        solve_iter(arr,  n);
        printf("#%d %d\n", i+1, ans);
    }
}

