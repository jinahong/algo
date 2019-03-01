/*
 https://www.swexpertacademy.com/main/solvingProblem/solvingProblem.do
 
 나는 배열 인덱스가 싫어요
 
 */
#include <iostream>

using namespace std;
int arr[50][50];
/*
 n이 5일경우. 
i : 0, 1
j: 2, 1
k: 0,...

 */
int solve(int n)
{
    int sum = 0;
    for(int i = 0, j=n/2 ; i < n/2 ; i++, j--)
    {
        {
            for(int k = 0; k<i*2+1; k++)
            {
                sum += arr[j+k][i];
                sum += arr[j+k][n-i-1];
            }
        }
    }
    for(int i=0;i<n;i++)
        sum += arr[i][n/2];

    return sum;
}

int main()
{
    int tc;
    cin >> tc;
    for(int i_tc = 1 ; i_tc <= tc; i_tc++)
    {
        int n;
        cin >> n;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%1d",&arr[j][i]);

    cout <<"#" << i_tc << " "<< solve(n) << endl; 
    }
}
