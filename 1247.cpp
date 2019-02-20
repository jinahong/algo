/*
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV15OZ4qAPICFAYD

이 문제는 가장 짧은 경로를 ‘효율적으로’ 찾는 것이 목적이 아니다.
여러분은 모든 가능한 경로를 살펴서 해를 찾아도 좋다.
모든 경우를 체계적으로 따질 수 있으면 정답을 맞출 수 있다

문제에 저런 문장이 있길래, 어떻게 풀까 고민하다가
gridy로 하면 안될꺼 같아서 backtracking으로 풀었음. 
 */

#include <iostream>
using namespace std;

typedef struct pos {
    int x;
    int y;
} pos;

pos arr[13];
bool visited[21];

int ans;
int n;

int dis(pos a, pos b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}
/*
start: 방문할 좌표의 index값
cnt: 방문한 좌표의 개수
path: 그동안 방문하면서 이동한 거리 총합계
 */
void solve(int start, int cnt, int path)
{
    //집이랑 start거리 구한 후, 해당 거리가 최소값이 되는지 확인
    if(cnt == n)
    {
        int ans_tmp = path + dis(arr[start], arr[n+1]);
        if(ans_tmp < ans)
        {
            ans = ans_tmp;
        }
    }
    else
    {
        //pruning!: 방문한 거리가 ans보다 크면, 더이상 search할 필요 없음
        if(path > ans) return;
    }

    for(int i = 1 ; i <= n ; i++)
    {
        if(visited[i] == false)
        {
            visited[i] = true;
            solve(i, cnt+1, path + dis(arr[start], arr[i]));
            visited[i] = false;
        }
    }
}

void init()
{
    ans = 9999;
}

int main(){
    int tc;
    cin >> tc ;

    for (int i = 1 ; i <= tc ; i++)
    {
        
        cin >> n;
        cin >> arr[0].x >> arr[0].y; // start, position of company
        cin >> arr[n+1].x >> arr[n+1].y; //last, position of home

        init();

        for(int j = 1 ; j <= n ; j++)
            cin >> arr[j].x >> arr[j].y;

        solve(0, 0, 0);

        cout << "#" << i << " " << ans << endl;
    }
}


