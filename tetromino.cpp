/*
basic:
O(17nm) 이고, nm이 작아서 전체탐색해도 괜찮다. 
4번 이동가능한 모든 거리를 탐색

detail:
ㅗ모양은 dfs로 탐색불가. 
*/

#include <iostream>

using namespace std;
int arr[501][501];
bool visited[501][501];
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
int n;
int m;
int ans = -9999;

bool safe(int x, int y)
{
    return x < m && x >= 0 && y < n && y >=0;
}
void solve2(int x, int y, int depth, int sum)
{
    if(depth == 4)
    {
        ans = ans > sum ? ans : sum;
        return;
    }
    if(!safe(x, y)) return;
    if(visited[x][y]) return;
    visited[x][y] = true;
    for(int i=0;i<4;i++)
    {
        solve2(x + dx[i], y + dy[i], depth+1, sum + arr[x][y]);
    }
    visited[x][y] = false;
}
void excep()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            solve2(j, i, 0, 0);

            if(safe(j, i+2))
            {
                int sum = arr[j][i] + arr[j][i+1] + arr[j][i+2];
                if(safe(j+1, i+1))
                {
                    int block = arr[j+1][i+1];
                    ans = ans > sum + block ? ans: sum + block;
                }
                if(safe(j-1, i+1))
                {
                    int block = arr[j-1][i+1];
                    ans = ans > sum + block ? ans: sum + block;
                }
            }
            if(safe(j+2,i))
            {
                int sum = arr[j][i] + arr[j+1][i] + arr[j+2][i];
                if(safe(j+1, i+1))
                {
                    int block = arr[j+1][i+1];
                    ans = ans > sum + block ? ans: sum + block;
                }
                if(safe(j+1, i-1))
                {
                    int block = arr[j+1][i-1];
                    ans = ans > sum + block ? ans: sum + block;
                }
            }
        }
    }
}
int main()
{
    cin >> n >> m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> arr[j][i];
    excep();
    cout << ans << endl;
}


