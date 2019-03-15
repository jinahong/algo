/*
https://www.acmicpc.net/problem/15954

- long double type!!
- partial sum, 매번 구하면 시간초과!
- setprecision
- LDBL_MAX

 */
#include <iomanip>
#include <iostream>
#include <math.h>
//MAX
#include <float.h>
using namespace std;


long double arr[501];
long double ans = LDBL_MAX;//999999999999; //최소 표준편차

long double partialSum[501];
long double partialPowSum[501];

void partialSumCalc(int n)
{
    partialSum[0] = arr[0];
    partialPowSum[0] = arr[0] * arr[0];
    for(int i = 1 ; i < n;i++)
    {
        partialSum[i] = partialSum[i-1] + arr[i];
        partialPowSum[i] = partialPowSum[i-1] + arr[i] * arr[i];
    }
}

long double avgPartialSum(long double* parr, int s, int n)
{
    if(s == 0) return parr[n-1]/n;
    return (parr[s+n-1] - parr[s-1] )/n;
}

//(분산) = (제곱의 평균) - (평균) * (평균)
long double distrPartial(int s, int n)
{
    long double m = avgPartialSum(partialSum, s, n);

 //   cout << "s :" << s << "n: " << n << "avg: " << m;
    return avgPartialSum(partialPowSum, s, n) - m * m;
}
/*
//s: 시작 index, n: 크기
long double avg(int s, int n)
{
    long double sum = 0.0;
    for(int i = s ; i < s + n ; i++)
        sum += arr[i];
    return sum/n;
}
long double distr(long double m, int s, int n)
{
    long double sum = 0.0;
    for(int i=s;i<s+n;i++)
        sum += (arr[i]-m) * (arr[i]-m);
    return sum/n;
}
*/
/*
    n: 인형의 전체 갯수
    k:
 */
void solve(int n, int k)
{
    for(int s = 0 ; s < n - k + 1;s++)
    {
        for(int r = 0 ; s + k + r <= n ;r++)
        {
            long double dis = sqrtl(distrPartial(s, k+r));
           // cout << "dis: " << dis << endl;
            if(ans > dis)
            {
                ans = dis;
            }
        }
    }
}
int main()
{
    int n, k;
    cin >> n >> k;
    for(int i=0;i<n;i++)
        cin >> arr[i];
    
    //make partial sum array
    partialSumCalc(n);

    solve(n, k);

    cout << setprecision(17);
    cout << ans << endl;
    return 0;
}
