/*

basic:
bfs
나도 코드 simple하게짜고싶다~~~

detail:
입력받는 배열이 약간 특이하다. row가 홀수이면, col개수가 n-1개임
start부터 end까지의 경로를 출력해줘야함. 
 - info구조체에 from을 추가해서, 이전 idx가 무엇이였는지 기록한다. 
 - stack자료구조를 이용, pop, push, top 연산만 존재
 */


#include <iostream>
#include <queue>
#include <stack>

using namespace std;
typedef struct pos{
    int x, y;
} pos;

typedef struct info{
    int f,s;
    int d;
    pos from;
} info;

int n;
int dx[2][6] = {{1,1,1,0,-1,0},{0,1,0,-1,-1,-1}};
int dy[2][6] = {{-1,0,1,1,0,-1},{-1,0,1,1,0,-1}};
info arr[501][501];

bool safe(int x, int y)
{
    if(y % 2 == 1)
        return x >=0 && x < n-1 && y >=0 && y <n;
    else
        return x >=0 && x < n && y >=0 && y <n;
}
//d: 6개의 방향중 어딘지?
//cur에서 x,y로 움직일 수 있나?
bool movable(int d, pos cur, pos next)
{
    if(d > 2)
        return arr[cur.x][cur.y].f == arr[next.x][next.y].s;
    else
        return arr[cur.x][cur.y].s == arr[next.x][next.y].f;

}

int getidx(pos cur)
{
    return cur.y * n + cur.x - cur.y/2;
}


pos getLastIdx()
{
    pos error = {-1,-1};
    for(int i=n-1 ; i>=0 ;i--)
        for(int j=n-1;j>=0;j--)
        {
            if(arr[j][i].d != 0)
            {
                pos tmp = {j,i};
                return tmp;
            }
        }
    return error;
}
stack<int> backtracking()
{
    pos dst = getLastIdx();
    int dst_idx = getidx(dst);

    stack<int> ans;
    ans.push(dst_idx);

    while(dst_idx != 0)
    {
        dst = arr[dst.x][dst.y].from;
        dst_idx = getidx(dst);
        ans.push(dst_idx);
    }
    return ans;

}
void solve()
{
    queue<pos> q;
    arr[0][0].d = 1; //처음 좌표는 거리 1
    pos init = {0,0};
    q.push(init);

    while(!q.empty())
    {
        pos cur = q.front();q.pop();
//        cout << "cur:" << cur.x << "," << cur.y << endl;
        int isRowEven = cur.y % 2 == 0 ? 1 : 0;
        for(int i=0;i<6;i++)
        {
            int tmpx = cur.x + dx[isRowEven][i];
            int tmpy = cur.y + dy[isRowEven][i];
            pos next = {tmpx, tmpy};
            if(safe(tmpx, tmpy) 
                    && movable(i, cur, next)    //cur에서 next로 이동할 수 잇는지?
                    && arr[tmpx][tmpy].d == 0) // visited체크 역할도 함. 
            {
                arr[tmpx][tmpy].d = arr[cur.x][cur.y].d + 1;
                arr[tmpx][tmpy].from = cur;
                q.push(next);
            }
        }
    }
    stack<int> ans = backtracking();
 
    cout << ans.size() << endl;
    while(!ans.empty())
    {
        cout << ans.top() + 1<< " ";
        ans.pop();

    }
}
int main()
{
    cin >> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            if(i % 2 == 1 && j == n-1) break;
            else cin >> arr[j][i].f >> arr[j][i].s;
        }

    solve();
}
