/*
basic:
최대 D개만큼 선택하는 combination
solve: 택X, A, B 3개로나눠서 d개 선택한 경우에 답 구하기. 2,566 ms
solve1: 택X, A, B 3개로나눠서 1~d개 선택한 경우에 답 구하기. 1,715 ms
solve2: A, B 나눠서 택할때마다 답구하기. 1,781 ms

detail:

etc:
처음엔 visited생각을 못함 ㅠㅠ, vector로 택한거 저장했더니 시간초과
*/

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

typedef struct info{
    int idx;
    int chem;
} info;
#define NA 2
#define A 0
#define B 1

int d;//두께
int w;  //가로
int k; // 합격기준

int arr[21][14];
int visited[14];

//visited에서 0~idx까지만 살펴보면됨. 
bool isAns()
{
    int fake[21][14];
    memcpy(fake, arr, sizeof(arr));

    //약품 투여정보 세팅해주기. 
    for(int i=0;i<d;i++)
    {
        if(visited[i] == A || visited[i] == B )
            for(int j=0;j<w;j++)
            {
                fake[j][i] = visited[i];
            }
    }
 
    int j=0;
    //Col iter
    for(;j<w;j++)
    {
        bool plzend = false;

        for(int i=0;i<=d-k;i++)
        {
            plzend = false;
            for(int q = 1;q<k;q++)
            {
                if(fake[j][i] == fake[j][i+q])
                    plzend = true;
                else
                {
                    plzend = false;
                    break;
                }
            }
            //해당 col에서 답 찾았으므로, 이후 row조사할필요없음
            if(plzend) break;
        }
        //해당 col에서 답 못찾았으므로, 이후 col조사할필요없음
        if(!plzend) break;
    }
    if(j == w) return true;
    else return false;
}

int ans;
void solve(int idx, int depth)
{
    if(depth > ans) return;

    if(idx == d)
    {
        if(isAns())
            ans = min(ans, depth);
        return;
    }

    visited[idx] = NA;
    solve(idx+1, depth);

    visited[idx] = A;
    solve(idx+1, depth+1);

    visited[idx] = B;
    solve(idx+1, depth+1);
}
//답만 찾으면 바로 리턴가능. 
bool solve1(int idx, int depth, int limits)
{
    if(depth == limits)
    {
        return isAns();
    }
    
    for(int i = idx ; i < d ; i++)
    {
        visited[i] = A;
        if(solve1(i+1, depth+1, limits))
            return true;

        visited[i] = B;
        if(solve1(i+1, depth+1, limits))
            return true;

        visited[i] = NA;     
    }
    return false;
}
int solve1Main()
{
    int ans = 1; 
    for(;ans<=d;ans++)
    {
        for(int i=0;i<d;i++)
            visited[i] = NA;

        bool flag = solve1(0, 0, ans);

        if(flag) return ans;
    }
    return -1;
}


void solve2(int idx, int depth)
{
    if(depth >= ans || idx > d) return;
    
    if(isAns())
    {
        ans = min(ans, depth);
        return;
    }
    
    for(int i = idx ; i < d ; i++)
    {
        visited[i] = A;
        solve2(i+1, depth+1);

        visited[i] = B;
        solve2(i+1, depth+1);

        visited[i] = NA;     
    }
}



int main()
{
    int tc;
    cin >> tc;

    for(int tc_i = 0 ; tc_i < tc ; tc_i++)
    {
        cin >> d >> w >> k;

        memset(arr, 0, sizeof(arr));
        for(int i=0;i<d;i++)
            visited[i] = NA;
        ans = 15;

        for(int i=0;i<d;i++)
            for(int j=0;j<w;j++)
                cin >> arr[j][i];


        //처음 주어진 맵에서 확인하기
        if(isAns() || k == 1) 
             printf("#%d %d\n", tc_i+1, 0); 
        else
        {
           // solve(0, 0);
           // printf("#%d %d\n", tc_i+1, ans); 
            
            printf("#%d %d\n", tc_i+1, solve1Main()); 

        }
    }
}