/*
long long 신경쓰기

테케 좀 스스로 생각해보렴^^
 */
#include <iostream>

using namespace std;
int arr[1000001];
//int dp[1000001];

int getSubSupervisor(int cnt, int c)
{
    if(cnt%c == 0)
        return cnt/c;
    else 
        return cnt/c+1;
}
long long solve(int n, int b, int c)
{
    long long sum = 0;
    for(int i=0;i<n;i++)
    {
        //care!
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
