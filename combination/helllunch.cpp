/*
basic:
2개의 문에 사람 조합하기. 

detail:
window_Calc함수 짜는게 어려웠따. 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

#define FIRST 0
#define SECOND 1
typedef struct pos{
    int x, y;
} pos;

int ans = 99999;

pos people[11];
pos door1;
int stair1;
pos door2;
int stair2;

int arr[11][11];
int n;

int people_cnt;
bool visited[11];

int getDist(pos a, pos b)
{
    return abs(a.x-b.x) + abs(a.y-b.y);
}
//vec: i번째 사람이 내려가기 시작할 수 았는 시간
int window_calc(vector<int> vec, int stair_size)
{
    if(vec.size() == 0) return 0;

    int iter = 0;
    queue<pair<int, int> > q;

    int time = vec[iter];
    iter++;
    q.push(make_pair(time, time + stair_size));
    while(iter < vec.size())
    {     
        while(time == q.front().second && !q.empty())
        {
         //   cout << "pop at time: " << time << "q.size: " << q.size() << endl;
            q.pop();
        }

        // push하는 경우
        while(iter < vec.size() 
            && q.size() < 3 
            && time >= vec[iter])
        {
      //      cout << "push at time: " << time << "~" << time+stair_size <<  "iter:" << iter << endl;
            q.push(make_pair(time, time + stair_size));
            ++iter;
        }

        //마지막사람까지 queue에 Push했음, iter가 끝까지 돌았으면 time++하지말자
        if(iter < vec.size()) time++;
    }
    return time + stair_size;
}

int calc()
{
    vector<int> vec1;
    vector<int> vec2;
    //1. dist구하기.
    for(int i=0;i<people_cnt;i++)
    {
        if(visited[i] == FIRST)
            vec1.push_back(getDist(people[i],door1) + 1);
        else
            vec2.push_back(getDist(people[i], door2) + 1);
    }

    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());
/*
    for(int i=0;i<vec1.size();i++)
        cout << vec1[i] << " ";
    cout << endl;

for(int i=0;i<vec2.size();i++)
        cout << vec2[i] << " ";
    cout << endl;
*/

    int time1 = 0;//문1 사람처리하는데 걸리는 시간
    int time2 = 0;//문2 사람처리하는데 걸리는 시간

    if(!vec1.empty())
        time1 = window_calc(vec1, stair1);
    if(!vec2.empty())
        time2 = window_calc(vec2, stair2);

    return max(time1, time2);

}
//idx번째 사람을 어느 문으로 보낼것인가?
void solve(int idx)
{
    if(idx < 0)
    {
        int tmp = calc();
        if(ans > tmp)ans = tmp;
        return;
    }
    visited[idx] = FIRST;
    solve(idx-1);
    visited[idx] = SECOND;
    solve(idx-1);
}

void init()
{
    ans = 99999;
    door1.x = door2.x = door1.y = door2.y = -1;
    people_cnt = 0;
}
int main()
{
    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        init();
        cin >> n;

        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
            {
                cin >> arr[k][j];
                pos tmp = {k,j};
                //사람좌표
                if(arr[k][j] == 1)
                    people[people_cnt++] = tmp;
                //문1좌표
                if(arr[k][j] > 1 && door1.x == -1 && door1.y == -1)
                {
                    stair1 = arr[k][j];
                    door1 = tmp;
                }
                //문2좌표
                else if(arr[k][j] > 1)
                {
                    door2 = tmp;
                    stair2 = arr[k][j];
                }
            }

        solve(people_cnt-1);

        cout <<"#" << i+1 << " " <<  ans << endl;
    }
}
