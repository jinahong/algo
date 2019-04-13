/*
 
https://www.acmicpc.net/problem/12969


 basic:
 완탐, 가능한게 나오기만 하면 정답임. 
 n-dimension visited.
 
 detail:
 s배열을 정답을 저장하는 방식은 처음봄. 
 chk배열로 완탐의 시간 절약해야함. 

 */

#include <iostream>
#include <string.h>
using namespace std;
int N;
int K;
char s[51];
bool chk[31][31][31][451];
// S[i] < S[j]를 만족하는 (i, j) 쌍이 K개
//a, b, c의 개수
bool solve(int a, int b, int c, int k)
{
    if((a+b+c > N) || k > K) return false;
    if(a+b+c == N && k == K) return true;

    if(!chk[a][b][c][k])
    {
        chk[a][b][c][k] = true;

        if(solve(a+1, b, c, k))
        {
            s[a+b+c]= 'A';
            return true;
        }
        else if(solve(a, b+1, c, k+a))
        {
            s[a+b+c] = 'B';
            return true;
        }
        else if(solve(a, b, c+1, k+a+b))
        {
            s[a+b+c] = 'C';
            return true;
        }
    }
 return false;

}

int main()
{
    cin >> N >> K;

    if(solve(0,0,0,0))
    {
        for(int i=0;i<N;i++)
            cout << s[i];
        cout << endl;
    }
    else cout << "-1" << endl;
}
