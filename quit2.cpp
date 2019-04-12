/*
https://www.acmicpc.net/problem/15486

memoization하니깐 시간 진짜오래걸린다 ㅋㅋ
 */

#include <iostream>

using namespace std;

int arr[1500001][2];
int N; // 최대 1,500,000

//일할수있는 날은 최대는 1500001
int dp[1500001];


int solve(int i)
{
    if(i<N && dp[i] == 0)
    {
        if(i+arr[i][0] <= N)
            dp[i] = max(solve(i+arr[i][0])+arr[i][1], solve(i+1));
        else
            dp[i] = solve(i+1);
    }
   // cout << "i:" << i << "," << dp[i] << endl;
    return dp[i];
}
int main()
{
    cin >> N;
    for(int i=0;i<N;i++)
    {
        cin >> arr[i][0] >> arr[i][1];
    }
    cout << solve(0) << endl;

}
