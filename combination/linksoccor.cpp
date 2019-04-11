/*
basic:
n명을 2팀으로나누는 combination

detail:
 solve에서 재귀를 for문으로 바꿔서 시간 단축. 
 ans가 0일때는 재귀종료해서 시간 단축. 
 */

#include <iostream>
using namespace std;
int n;
int ans = 99999;
bool visited[21];
int arr[21][21];
bool isAns()
{
    int sum = 0;
    for(int i=0;i<n;i++) if(visited[i]) sum+= visited[i];
    if(sum == n || sum ==0) return false;

    int a_score = 0;
    int b_score = 0;
    for(int i=0;i<n-1;i++)
        for(int j=i;j<n;j++)
        {
            if(visited[i] == visited[j])
            {
                if(visited[i])
                    a_score += arr[i][j] + arr[j][i];
                else
                    b_score += arr[i][j] + arr[j][i];  
            }
        }
    if(ans > abs(a_score - b_score)) ans = abs(a_score - b_score);
    if(ans == 0) return true;
    else return false;
}
void solve(int idx)
{
    if(idx == n) return;
    //ans가 0이면 최소값에 도달했기 때문에 더이상 연산 필요없음.    
    if(isAns())
        return;
    
    for(int i = idx;i<n;i++)
    {
        visited[i] = true;//a
        solve(i+1);
        visited[i] = false;//b
    }
   // solve(idx+1);
}
int main()
{
    cin >> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> arr[j][i];
    solve(0);
    cout << ans << endl;
}
