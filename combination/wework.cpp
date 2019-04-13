/*
https://www.acmicpc.net/problem/14238

 basic:
 완탐, 가능한게 나오기만 하면 정답임. 
 n-dimension visited.
 
 detail:
 s배열을 정답을 저장하는 방식은 처음봄. S[0~n-1]까지 저장. 
 chk배열로 완탐의 시간 절약해야함. 
 종료조건 파악하기. 
 */

 #include <iostream>
using namespace std;
char s[51];
bool chk[51][51][51][3][3];

#define A 0
#define B 1
#define C 2

int a_max, b_max, c_max;

bool solve(int a, int b, int c, int p, int pp)
{
    //답 찾음
    if(a == a_max &s& b == b_max && c == c_max) return true;
    else if(a > a_max || b > b_max || c > c_max) return false;

    if(!chk[a][b][c][p][pp])
    {
        chk[a][b][c][p][pp] = true;
        if(a+1<=a_max)
        {
            
            if(solve(a+1, b, c, A, p)) 
            {
                s[a+b+c] = 'A';
                return true;
            }
        }
        if(b + 1 <= b_max && p != B)
        {
            
            if(solve(a, b+1, c, B, p))
            {
                s[a+b+c] = 'B'; 
                return true;
            }
        }
        if(c + 1 <= c_max && p != C && pp != C)
        {
            if(solve(a, b, c+1, C, p))
            {
                s[a+b+c] = 'C'; 
                return true;
            }
        }
    }
    return false;
}
int main()
{
    string str;
    cin >> str;

    for(int i=0;i<str.length();i++)
    {
        if(str[i] == 'A')
            a_max++;
        else if(str[i] == 'B')
            b_max++;
        else if(str[i] == 'C')
            c_max++;

    }
    //AA는 dummy값
    if(solve(0,0,0,A,A)){
        for(int i=0;i<str.length();i++)
            cout << s[i];
        cout << endl;
    }
    else cout << "-1" << endl;

}
