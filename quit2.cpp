/*
https://www.acmicpc.net/problem/15486

memoization하니깐 시간 진짜오래걸린다 ㅋㅋ
 */
#include <iostream>

using namespace std;

int max (int a, int b) {return a>b?a:b;}
int arr[1500001][2];
long long N;

//i 최대는 1500001, available_cnt최대는 51
int dp[1500001][51];

//1~i일까지 상담했을 때, i+available_cnt까지 상담이 잡혀있을때에 최대 금액은?
int solve(int i, int available_cnt)
{
    if (i==N) return 0;
    if(dp[i][available_cnt] == 0)
    {
        if(available_cnt > 0)
            dp[i][available_cnt] = solve(i+1, available_cnt-1);
        else if(i+arr[i][0]>N)
            dp[i][available_cnt] = solve(i+1, available_cnt-1);
        else
            dp[i][available_cnt] = max(solve(i+1, arr[i][0]-1) + arr[i][1], solve(i+1, 0));
    }
    return dp[i][available_cnt];
}
int main()
{
    cin >> N;
    for(long long i=0;i<N;i++)
    {
        cin >> arr[i][0] >> arr[i][1];
    }
    cout << solve(0, 0) << endl;

}
