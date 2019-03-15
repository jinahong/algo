/*
 입력의 1-based와 idx의 0-based 신경써주기
 */
#include <iostream>

using namespace std;
int a[22];
int b[32];

int count_a[6] = {1, 2, 3, 4, 5, 6};
int reward_a[6]={500,300,200,50,30,10};
int count_b[6] = {1, 2, 4, 8, 16};
int reward_b[6] = {512,256,128,64,32};

int main()
{
    int idx = 0;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<count_a[i];j++)
            a[idx++] = reward_a[i];
    }
    idx = 0;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<count_b[i];j++)
            b[idx++] = reward_b[i];
    }

    int tc;

    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        int ans = 0;
        int tmp_a, tmp_b;
        cin >> tmp_a >> tmp_b;
        tmp_a--;tmp_b--;
        if(tmp_a<22 && tmp_a>=0) ans += a[tmp_a];
        if(tmp_b<32 && tmp_b>=0) ans+= b[tmp_b];
        printf("%d\n", ans*10000);
    }
}
