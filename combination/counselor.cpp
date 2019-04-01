/*
 https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWlQUD2qtysDFAVS


 시간초과!! IDEA!

1. 처음에 n개에서 2개씩 pick하는 dfs
2. 인터넷참조

아무튼 결국 출제자가 원하는 바는,
벡터의 합의 제곱을 구하기 때문에 모든 쌍을 구하는 게 아니라는 점이다.
즉, 움직이는 절반의 지렁이만 정하고, 움직이는 지렁이와 움직이지 않는 지렁이를 
아무렇게나 매치해도 결국 벡터값은 같다.


3. n개중 n/2개 pick하고, 나머지 n/2개순차대로, 
4. isAns optimization
 */


#include <iostream>
#include <cmath> //pow
#include <climits> //MAX
#include <string.h> // meset

using namespace std;

typedef struct pos{
    int x, y;
} pos;

pos arr[21];
bool visited[21];
int n;
pos g_ans;

void init()
{
    g_ans.x = INT_MAX;
    g_ans.y = INT_MAX;
    memset(visited, 0, sizeof(visited));
}

//vector의 크기계산
long long calc(pos a)
{
    return pow(a.x, 2) + pow(a.y, 2);
}

/*
XXX:4,022 ms -> 382 ms
*/
void isAns()
{
    /*
    처음엔 iteration해줫는데, 어짜피 전체 최종 벡터를 구하는 문제이기 떄문에
    지렁이들간의 순서는 의미가 없음.
       vector<int> a;
       vector<int> b;

       vector<int>::iterator it_b = b.begin();
       for(vector<int>::iterator it=a.begin();it!=a.end();++it)
       {
       tmpx += arr[*it].x - arr[*it_b].x;
       tmpy += arr[*it].y - arr[*it_b].y;
       ++it_b;
       }
       */
    int tmpx = 0;
    int tmpy = 0;

    for(int i=0;i<n;i++)
    {
        if(visited[i])
        {
            tmpx += arr[i].x; 
            tmpy += arr[i].y; 
        }
        else 
        {
            tmpx -= arr[i].x;
            tmpy -= arr[i].y;
        }
    }

    pos tmpans = {tmpx, tmpy};
    if(calc(g_ans) > calc(tmpans))
        g_ans = tmpans;

}
//pick n/2
void solve2(int idx, int depth)
{
    if(depth == 0)
    {
        isAns();
        return;
    }
    for(int i=idx;i<n-1;i++)
    {
        if(visited[i] == false)
        {
            visited[i] = true;
            solve2(i,depth-1);
            visited[i] = false;
        }
    }

    /*
    XXX: 똑같은 결과, 근데 시간은 아래가 더 많이걸림
    visited[idx] = true;
       solve2(idx+1, depth-1);
    visited[idx] = false;
    solve2(idx+1, depth);

    */

      /*
    이건 틀림
   
    visited[idx] = false;
    solve2(idx+1, depth);


        visited[idx] = true;
       solve2(idx+1, depth-1);
    */


}
int main()
{
    int tc;
    cin >> tc;

    for(int t_tc = 0; t_tc < tc; t_tc++)
    {
        cin >> n;
        for(int i=0;i<n;i++)
            cin >> arr[i].x >> arr[i].y;
        init();
        solve2(0,n/2);
        printf("#%d %lld\n",t_tc+1, calc(g_ans));
    }
}

