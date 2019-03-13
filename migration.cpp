/*
https://www.acmicpc.net/problem/16234

문제 잘읽기....ㅠㅠㅠ
며칠걸리는지 묻는 문제..

2:30분은 걸린듯 ㅠㅠ
 */

#include <iostream>

using namespace std;

int arr[101][101];
int visited[101][101];

typedef struct pos{
    int x, y;
} pos;

int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};

int n, l, r;

bool safe(pos a)
{
    return (a.x >=0 && a.y >= 0 && a.x <n && a.y<n);
}

bool openborder(pos cur, pos next)
{
    int diff = abs(arr[cur.x][cur.y] - arr[next.x][next.y]);
    return diff<=r && diff>=l;
}

int dfs(pos cur, int count)
{
    int sum = 0;
    for(int i=0;i<4;i++)
    {
        pos tmp = {cur.x + dx[i], cur.y+dy[i]};
        if(safe(tmp)
                && visited[tmp.x][tmp.y] == 0
                && openborder(cur, tmp))
        {
            visited[tmp.x][tmp.y] = count;
            sum  +=( dfs(tmp,count) + arr[tmp.x][tmp.y]);
        }
    }
    return sum;
}
int solve()
{
    int day = 0;
    while(1)
    {
        // 하루동안에 이동가능한 group 수
        int count = 1;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(visited[j][i] == 0)
                {
                    int sum = 0;
                    pos tmp = {j,i};
                    //tmp에서 시작해서, 이동가능한 인구수
                    visited[j][i] = count;
                    sum = dfs(tmp, count);

                    if(sum > 0) 
                    {
                        //평균 인구수 구하기
                        sum += arr[j][i];
                        int cnt = 0;
                        for(int i=0;i<n;i++)
                            for(int j=0;j<n;j++)
                                if(visited[j][i] == count) cnt++;
                        //map에 인구 수 조정
                        for(int i=0;i<n;i++)
                            for(int j=0;j<n;j++)
                                if(visited[j][i] == count)
                                    arr[j][i] = sum/cnt;
                        count++;
                    }


                    else visited[j][i] = 0;
                }
            }
        }
        //하루동안에 이동할 수 있는 나라관계가 없음
        if(count == 1)
            return day;
        else day++;
        //하루 종료되면, visited초기화
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                visited[j][i] = 0;
    }

    return day;
}
int main()
{
    cin >> n >> l >> r;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> arr[j][i];

    printf("%d\n", solve());

}
