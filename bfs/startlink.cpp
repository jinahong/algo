/*

https://www.acmicpc.net/problem/5014


basic:
 범위가 커서 쫄아서 bfs ->1억이 1초이고, 백만이면, 0.01초라서 많은건 아니래..ㅎ
 근데 그냥 for문돌려서 푸는분들 많더라.;.

detail:
-반례 스스로 생각해보자.. ans가 0이 되는 경우!

 
 */
#include <iostream>
#include <queue>

using namespace std;
bool visited[1000001];

struct info{
    int floor, depth;
    info(int _x, int _y) : floor(_x), depth(_y) {}
};
int f, s, g, u, d;
int solve()
{
    int ans = 0;
    queue<info> q;
    info tmp(s,0);
    q.push(tmp);
    visited[s]= true;
    while(!q.empty())
    {
        info elem = q.front();q.pop();
//        cout << elem.floor << endl;
        if(elem.floor == g) return elem.depth;

        visited[elem.floor]= true;
        //XXX: visited보다 범위검사가 먼저와야한다. visited에서 out of range에러날수있음
        if(!visited[elem.floor + u] && elem.floor + u <= f)
        {
            info push_elem(elem.floor + u, elem.depth + 1);
             visited[elem.floor + u]= true; 
            q.push(push_elem);
        }
        if(!visited[elem.floor - d] && elem.floor - d > 0)
        {
            info push_elem(elem.floor - d, elem.depth + 1);
            visited[elem.floor-d]= true;   
            q.push(push_elem);
        }
    }
    return -1;
}
int main()
{
    cin >> f >> s >> g >> u >> d;
    int ans = solve();
    if(ans>=0) cout << ans << endl;
    else cout << "use the stairs" << endl;
}
