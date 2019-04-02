/*
https://www.acmicpc.net/problem/15686

도시에 있는 치킨집 중에서 최대 M개를 고르고, 나머지 치킨집은 모두 폐업시켜야 한다. 
어떻게 고르면, 도시의 치킨 거리가 가장 작게 될지 구하는 프로그램을 작성하시오.


basic: 
combination + 최소거리
solve에서 idx 추가해서 iteration회수줄임. 

detail: 
치킨집이랑 집간의 거리구하는 방법을 처음엔 bfs, 그러나 두 좌표간의 거리를 알기 때문에 이중포문이 시간적게걸린다. 


 */

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define VISITED 999
int ans=9999;

typedef struct pos{
    int x, y, d;
} pos;

bool visited[14]; //해당 bbq문 열지말지 결정!

vector<pos> bbq;
vector<pos> house;

int arr[51][51];
int n;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

bool safe(int x, int y)
{
    return x<n && y<n && x>=0 && y>=0;
}

int getDistance()
{
    int sum = 0;
    for(vector<pos>::iterator it = house.begin();it!=house.end();++it)
    {
        int minVal = 9999;
        for(vector<pos>::iterator it_bbq = bbq.begin();it_bbq!=bbq.end();++it_bbq)
        {
            int bbq_idx = it_bbq - bbq.begin();

            if(visited[bbq_idx])
                minVal = min(minVal, (abs((it->x - it_bbq->x)) + abs((it->y - it_bbq->y))));
        }
        sum += minVal;
    }
    return sum;
}
void solve(int idx, int dep)
{
    if(dep == 0) 
    {
        int distance = getDistance();
        if(ans > distance) ans = distance;
        return;
    }
    if(idx > bbq.size()) return;
    visited[idx] = true;//i번째 체인점선택!
    solve(idx+1, dep-1);

    visited[idx] = false;//i번째 체인점 안선택!  
    solve(idx+1, dep);

}

int main()
{
    cin >> n;

    int m;
    cin >> m;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin >> arr[j][i];
            if(arr[j][i] == 2)
            {
                pos tmp = {j,i, 0};
                bbq.push_back(tmp);
            }
            else if(arr[j][i] == 1)
            {
                pos tmp = {j,i, 0};
                house.push_back(tmp);
            }
        }
    }

    solve(0, m);

    cout << ans << endl;
}
