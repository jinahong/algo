/*
 2번째 문제 풀었지만, 
 여전히 디버깅하고, 문제푸는데 2시간은 걸린거 같다. ㅠㅠㅠㅠㅠ:

 priority queue를 써서 구현하기!

 */

#include <iostream>
#include <queue>
#include <climits>
//고기 먹는 순서 bfs만 신경써줌
//nofish 고민
//상어는 언제 나이를 먹는가?

using namespace std;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int arr[21][21];
int n;

struct info{
    int x, y, d;
    info(){}
    info(int _x, int _y, int _d){
        x = _x;
        d = _d;
        y = _y;
    }

    bool operator > (const info a) const
    {
        if(d > a.d) return true;
        else if(a.d == d)
        {
            if(y > a.y)  return true;
            else if(y == a.y)
            {
                if(x > a.x) return true;
            }
        }
        return false;
    }
};

int sharkAge = 2;

//x, y위치를 현재 shark가 지나갈 수 있는지?
bool safe(int x, int y)
{
    return (arr[x][y] <= sharkAge && x >= 0 && x < n && y < n && y>=0);
}
//bfs
info eatFish(int x, int y)
{
    bool visited[21][21] = {0,};
    priority_queue<info, vector<info>, greater<info> > q;
    //첫 시작 depth는 0으로!
    q.push(init(x,y,0));
    
    visited[init.x][init.y] = true;

    //이번 함수에서 먹을 고기 저장!!
    info error(INT_MAX, INT_MAX, 0);

    while(!q.empty())
    {
        info loc = q.top();q.pop();

        //상어가 먹을 수 있는 고기인지 확인
        if(arr[loc.x][loc.y] < sharkAge
                && arr[loc.x][loc.y] > 0)
        {
            arr[loc.x][loc.y] = 0;
            return loc; 
        }

        for(int i=0;i<4;i++)
        {
            int tmpx = loc.x + dx[i];
            int tmpy = loc.y + dy[i];
            if(safe(tmpx, tmpy) && !visited[tmpx][tmpy])
            {
            //    cout << "push:" << tmpx <<"," << tmpy << "," << loc.d+1 << endl;
                info tmp(tmpx, tmpy, loc.d + 1);
                q.push(tmp);
                visited[tmpx][tmpy] = true;
            }
        }
    }
    return error;

}
bool nofish()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(arr[j][i] > 0) return false;
    return true;

}
//그동안 먹은 fish개수 저장하려면, iteration으로 하는게 좋음.
int solve(int x, int y)
{
    int eatenx = x;
    int eateny = y;
    int ans = 0;
    int local_ans = 0;//sharkAge 증가 시키기 전까지 먹은 고기의 수:
    while(1)
    {
        if(sharkAge == local_ans)
        {
            sharkAge++;
            local_ans = 0;
        }
        
        info eaten = eatFish(eatenx, eateny);
        eatenx = eaten.x;
        eateny = eaten.y;
        //dfs결과 먹을 고기 없음.
        if(eaten.d == 0) break;
        //고기하나먹은후 처리해야할 일들
        ans += eaten.d;
        local_ans++;
       
       //먹고나니 고기가 없거나, 
        if(nofish()) break;

    }
    return ans;
}
int main()
{
    int getx, gety;
    cin >> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            cin >> arr[j][i];
            if(arr[j][i] == 9)
            {
                getx = j; gety = i;
                arr[j][i] = 0;
            }

        }
    cout << solve(getx, gety) << endl;
}
