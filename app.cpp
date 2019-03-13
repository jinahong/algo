/*
https://www.acmicpc.net/problem/7579
memory는 최대로, cost는 최소ㅑ 

상향식 dp

XXX point가 많다...ㅠㅠ
 - getAns :dp[N][0~max] 까지 중에서 max값 찾으면됨. 열값은 N!!
 - maxcost값 잘못계산
 - int type도 충분, 10^7

 */

#include <iostream>
//XXX
#define MAXCOST 10001

using namespace std;
int mem[101];
int cost[101];
int dp[101][MAXCOST];
int dst_mem;
int N;

void solve()
{
    //XXX: app이 1개일때 처리
    for(int j=1;j<MAXCOST;j++)
    {
        if(j-cost[0] < 0)
            dp[0][j] = 0;
        else 
        {
            for(;j<MAXCOST;j++)
                dp[0][j] = mem[0];
            break;
        }
    }
     //1~i번째까지 app중에서 cost j로 사용할수 있는 최대 메모리는?
    for(int i=1;i<N;i++)
    {
        for(int j=1;j<MAXCOST;j++)
        {
            //i번째 app선택 못함
            if(j-cost[i]<0)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-cost[i]]+ mem[i]);
        }
    }
}
//최소 cost구하
int getAns()
{
    int ans = 9999;
    //XXX
    //for(int i=0;i<N;i++)
    {
        for(int j=1;j<MAXCOST;j++)
        {
            //XXX: M 바이트 이상의 메모리를 추가로 확보
            if(dp[N-1][j] >= dst_mem)
            {
                if(ans > j) ans = j;
            }

        }
    }
    return ans;
}
int main()
{
    cin >> N >>dst_mem;
    for(int i=0;i<N;i++)
        scanf("%d", &mem[i]);
    for(int i=0;i<N;i++)
        scanf("%d", &cost[i]);
    solve();
    cout << getAns() << endl;
    return 0;
}

