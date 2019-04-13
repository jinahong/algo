/*
basic:
dfs, bfs모두가능

detail:

*/

#include <iostream>
#include <queue>
using namespace std;

bool chk[1501][1501];

struct info{
    int x, y;
    info(int x,int y) : x(x),y(y){}
};


bool safe(int a, int b, int c)
{
    return a>0 && b>0 && a<=1500 && b <= 1500 && c >0 && c <= 1500;
}
int sum;

//a, b값 교환하기
void solve(int a, int b)
{
    cout << "a:" << a << ", b: " << b << endl;
    int c = sum - a - b;
    if(!safe(a,b,c)) return;
    //답찾음
    if(a == sum/3 && b == sum/3)
    {
        chk[a][b] = true;
        return;
    }
    else if(a == b)
        return;
    
    if(!chk[a][b])
    {
        chk[a][b] = true;
        chk[b][a] = true;
        if(a> b)
        {
            solve(a-b, b*2);
            solve(a-b, c);
            solve(b*2, c);
        }
        else if(a < b)
        {
            solve(b-a, a*2);
            solve(b-a, c);
            solve(a*2, c);
        }
    }
}
void bfs(int x, int y, int z)
{
    queue<info> q;
    q.push(info(x,y));
    q.push(info(y,z));
    q.push(info(x,z));

    while(q.empty())
    {
        int a = q.front().x;
        int b = q.front().y;
        q.pop();
        int c = sum - a - b;
        if(a==sum/3 && b == sum/3)
        {
            chk[a][b] = true;
            return;
        }
        if(!safe(a,b,c)) continue;
        if(chk[a][b]) continue;
        chk[a][b] = true;
        chk[b][a] = true;
        if(a > b)
        {
            q.push(info(a-b, b*2));
            q.push(info(a-b, c)); 
            q.push(info(b*2, c));
        }
        else if(a < b)
        {
            q.push(info(b-a, a*2));
            q.push(info(b-a, c)); 
            q.push(info(a*2, c));
        }
    }
}

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    sum = (a+b+c);
    if(sum%3 != 0) 
    {
        cout << "0" << endl;
    }
    else
    {
//        solve(a,b);
 //       solve(b,c);
  //      solve(a,c);
        bfs(a, b, c);
        cout << chk[sum/3][sum/3] << endl;
    }
    return 0;
    
}
