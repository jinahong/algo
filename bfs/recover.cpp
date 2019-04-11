/*

https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV15QRX6APsCFAYD

출발지에서 도착지까지 가는 최소 복구시간은?

basic:

 1. dp: dp로 풀경우, dp가 stable해질때까지 최소값 계속구함..
 2. dikstra algorithm: weight이 1이 아닌 graph의 최소거리 찾는 문제이다. 
     기본적으로 priority queue를 이용한 bfs형태로 풀이함.
    ->complexity: v^2

    queue 에서 Push할때 dp를 업데이트 하는지?
    queue 에서 pop할때 dp를 업데이트 하는지? 에따라 시간차이 4배!!

detail:
    priority queue를 왜써야 하는가? 

 */

#include <iostream>
#include <queue>
#include <string.h>

using namespace std;
int n;
int arr[100][100];
bool visited[100][100];
//bfs시 필요한 자료구조
struct info{
    int x, y, d;
    info(){}
    
    info(int _x, int _y, int _d){
        x = _x;
        d = _d;
        y = _y;
    }
    //a가 작으면 true
    bool operator > (const info a) const
    {
        return d > a.d;
    }
};

//dp[src][dst], src에서 dst까지 필요한 최소 비용
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
int dp_func()
{
    memset(dp, 0, sizeof(dp));

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
    bool flag;
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

    return dp[n-1][n-1];
}
void pq_init()
{
     for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dp[i][j] = 9999;

    memset(visited, 0, sizeof(visited));

}
int pq_func()
{
   pq_init();

    priority_queue<info, vector<info>, greater<info> > pq;
    //queue<info> pq;
    info init(0,0,0);
    pq.push(init);
    dp[0][0] = 0;


    while(!pq.empty())
    {
        info cur = pq.top();pq.pop();
       
       // cout << "cur:" << cur.x << "," << cur.y  << "," <<  cur.d  << endl;

        visited[cur.x][cur.y] = true;

        if(cur.x == n-1 && cur.y == n-1) break;

        for(int i=0;i<4;i++)
        {
            int nextx = cur.x + dx[i];
            int nexty = cur.y + dy[i];

            if(safe(nextx, nexty)  && !visited[nextx][nexty])
            {
                int nextd = min(dp[nextx][nexty], cur.d + arr[nextx][nexty]);
                //최소거리 업데이트 필요없는 vertex는 push안함. 
                if(dp[nextx][nexty] != nextd)
                {
                    //push하기전에 최소 거리 업데이트 해줌. 
                    dp[nextx][nexty] = nextd;
                    info next(nextx, nexty, nextd);
                    pq.push(next);
                }
            }            
        }
    }
    return dp[n-1][n-1];

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
        //1. dp solution
   //     printf("#%d %d\n", tc, dp_func());
        //2. dikstra
        printf("#%d %d\n", tc, pq_func());
    }
}
