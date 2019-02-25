/*
 https://www.acmicpc.net/problem/14501
 dp안써도 백준 pass됨
 */
#include <iostream>

using namespace std;

int max (int a, int b) {return a>b?a:b;}
int arr[16][16];
int N;
//1~i일까지 상담했을 때, i+available_cnt까지 상담이 잡혀있을때에 최대 금액은?
int solve(int i, int available_cnt)
{
    if (i==N) return 0;
    if(available_cnt > 0)
        return solve(i+1, available_cnt-1);
    else if(i+arr[i][0]>N)
        return solve(i+1, available_cnt-1);
    else
        return max(solve(i+1, arr[i][0]-1) + arr[i][1], solve(i+1, 0));

}
int main()
{
    cin >> N;
    for(int i=0;i<N;i++)
    {
        cin >> arr[i][0] >> arr[i][1];
    }
    cout << solve(0, 0) << endl;

}
