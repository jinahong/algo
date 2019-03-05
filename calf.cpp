/*
 
https://www.swexpertacademy.com/main/talk/solvingClub/problemView.do?solveclubId=AWgn93MasXEDFATd&contestProbId=AWkIeU76A9cDFAXC&probBoxId=AWkz_qf6IEEDFASG&type=PROBLEM&problemBoxTitle=0304&problemBoxCnt=2
3/5일 15시30분~ 15시 40분
partial sum쓰는 문제
tc마다 전역변수 초기화 신경쓰기!!
 */
#include <iostream>

using namespace std;
//p_sum[i][j] 1~i번째까지의 소의 품종을 나타냄
int p_sum[100001][3];

void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p_sum[i][0] = 0;
        p_sum[i][1] = 0;
        p_sum[i][2] = 0;
    }
}
int main()
{
    int t;
    cin >> t;
    for(int i=0;i<t;i++)
    {
        int n,q;
        cin >> n >> q;
        //소 품종
        init(n);
        for(int j=1;j<=n;j++)
        {
            p_sum[j][0] = p_sum[j-1][0];
            p_sum[j][1] = p_sum[j-1][1];
            p_sum[j][2] = p_sum[j-1][2];
            int unique_n;
            cin >> unique_n;
            p_sum[j][unique_n-1] +=1;
        }
        for(int j=0;j<q;j++)
        {
            int start;
            int end;
            scanf("%d %d", &start, &end);
            printf("%d ", p_sum[end][0] - p_sum[start-1][0]);
            printf("%d ", p_sum[end][1] - p_sum[start-1][1]);
            printf("%d\n", p_sum[end][2] - p_sum[start-1][2]);
        }
    }
}
