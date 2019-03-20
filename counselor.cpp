/*
 
 시간초과!! IDEA!

1. 처음에 n개에서 2개씩 pick하는 dfs
2. 인터넷참조
3. n개중 n/2개 pick하고, 나머지 n/2개순차대로, 
4. isAns optimization
 */


#include <iostream>
#include <cmath>
#include <string.h>
#include <vector>
using namespace std;

typedef struct pos{
    int x, y;
} pos;

pos arr[21];
bool visited[21];
int n;
pos g_ans;

using namespace std;
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

//src에서 dst까지의 벡터 구하기
pos getDistance(pos src, pos dst)
{
    pos tmp = {dst.x - src.x, dst.y - src.y};
    return tmp;

}
void posAssign(pos* dst, pos src)
{
    dst->x = src.x;
    dst->y = src.y;

}
//a에 b를 더함
void posAdd(pos* a, pos b)
{
    a->x = a->x + b.x;
    a->y =  a->y + b.y;
}
//a가 더 작으면 true, 아니면 fale
bool posMin(pos a, pos b)
{
    if(calc(a) < calc(b)) return true;
    else return false;

}
/*
//모두 match가 된후에 결과찾기
void isAns()
{
pos ans = (pos){0,0};
for(int i = n/2; i >0 ; i--)
{
int a, b;
for(a = 0;a<n;a++)
if(visited[a] == i) break;
for(b = a+1;b<n;b++)
if(visited[b] == i) break;
//2개중 하나 골라야함.         
pos tmpans1 = posAdd(ans, getDistance(earthwrom[a],earthwrom[b]));
pos tmpans2 = posAdd(ans, getDistance(earthwrom[b],earthwrom[a]));

//둘중 ans와 더했을 경우, 0,0 에 더가까운걸 pick!
posAssign(&ans,  posGetMin(tmpans1, tmpans2));
}
posAssign(&g_ans, posGetMin(g_ans, ans));
}

//idx: idx째와 매치시킬 지렁이 찾는중. 
//cnt: idx때는0, idx와매치시킬친구때는 1, 
//match_cnt: N개의 지렁이i 중에 현재까지 match시킨 지렁이의 개수
int getHeadIdx()
{
int i = 0;
for(;i<n;i++)
if(visited[i] == false)
return i;
return n;
}
//depth번씩 2개pick
void solve(int idx, int depth)
{
visited[idx] = depth;
for(int i=idx+1;i<n;i++)
{
if(visited[i] == 0)
{

visited[i] = depth;
//isAns(idx, i);

solve(getHeadIdx(), depth-1);
if(depth == 1)
{
for(int i=0;i<n;i++)
cout << visited[i] << " ";
cout << endl;
isAns();
}
visited[i] = 0;
}
}
visited[idx] = 0;
}
 */
/*
XXX:4,022 ms -> 382 ms

vector a,b에 각각 selected, not selected 추가해서, 2중포문.

어짜피 not selected는 minus이고, selected 는 plus이여서 tmpx, tmpy에 계산해서 바로저장

*/
void isAns()
{
//   vector<int> a;
//    vector<int> b;

    int tmpx = 0;
    int tmpy = 0;

    for(int i=0;i<n;i++)
    {
        if(visited[i])
        {
            tmpx += arr[i].x; 
            tmpy +=arr[i].y; 
        }//a.push_back(i);
        else {
            tmpx -= arr[i].x;
            tmpy -=arr[i].y;
        }// b.push_back(i);
    }
    /*
       vector<int>::iterator it_b = b.begin();
       for(vector<int>::iterator it=a.begin();it!=a.end();++it)
       {
       tmpx += arr[*it].x - arr[*it_b].x;
       tmpy += arr[*it].y - arr[*it_b].y;
       ++it_b;
       }*/
    pos tmpans = {tmpx, tmpy};
    if(g_ans > calc(tmpans))
        g_ans = calc(tmpans);

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
