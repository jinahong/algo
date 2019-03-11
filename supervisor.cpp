/*

   https://www.acmicpc.net/problem/13458


long long 신경쓰기

테케 좀 스스로 생각해보렴^^
 */
#include <iostream>

using namespace std;
int arr[1000001];
//int dp[1000001];

//필요한 부감독이 몇명인지 계산
int getSubSupervisor(int cnt, int c)
{
    if(cnt%c == 0)
        return cnt/c;
    else 
        return cnt/c+1;
}

//b: 응시자수
long long solve(int n, int b, int c)
{
    //sum: 필요한 감독관 수
    long long sum = 0;
    for(int i=0;i<n;i++)
    {
        //care!
        //arr[i] - b는 부감독관이 i번째방에서 감독해야할 응시자수
        //arr[i] - b이 음수이면, 총감독관만 있어도 충분
        if(arr[i] - b > 0)
            sum += getSubSupervisor(arr[i] - b, c);
    }
    return sum+n;

}
int main()
{
    int n;
    cin >> n;

    for(int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    int b, c;
    cin >> b >> c;
    cout << solve(n, b, c) << endl;
}
