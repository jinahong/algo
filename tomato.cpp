/*
 코딩 50분, 디버깅 10분

 디버깅은 x,y좌표 제대로 안맞춰준거 fix

 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct pos{
    int row, col, d;
} pos;
int arr[1001][1001];
bool visited[1001][1001];
vector<pos> tomatos;
int n,m;
int dx[4]={0,-1,0,1};
int dy[4] = {-1,0,1,0};
bool safe(int row, int col)
{
    return row >= 0 && col >= 0 && row < n && col < m;
}
int bfs()
{
    queue<pos> q;
    for(int i=0;i<tomatos.size();i++)
        q.push(tomatos[i]);

    pos cur;
    while(!q.empty())
    {
        cur = q.front();q.pop();

        switch(arr[cur.row][cur.col])
        {
            case 0:
                arr[cur.row][cur.col] = 1;
            case 1:
                for(int i=0;i<4;i++)
                {
                    int tmp_r = cur.row + dx[i];
                    int tmp_c = cur.col + dy[i];
                    if(safe(tmp_r, tmp_c) 
                            && !visited[tmp_r][tmp_c]
                            && arr[tmp_r][tmp_c]==0)
                    {
                        pos pushitem = {tmp_r, tmp_c, cur.d+1};
                        visited[tmp_r][tmp_c] = true;
                        q.push(pushitem);
                    }
                }
                break;
            case -1:
                break;
        }
    }
    return cur.d;
}
void debug()
{
    cout << endl;
    for(int row = 0 ; row < n ; row++)
    {   for(int col = 0 ; col < m ; col++) 
    {
            cout << arr[row][col] << " ";
    }
        cout << endl;
    }
    cout << endl;
}
bool isOK()
{
    for(int j=0;j<m;j++)
    {
        for(int i=0;i<n;i++) 
            if(arr[i][j] == 0) return false;
    }
    return true;
}
int main()
{
    cin >> m >> n;
    for(int row = 0 ; row < n ; row++)
        for(int col = 0 ; col < m ; col++)
        {
            cin >> arr[row][col];
            if(arr[row][col] == 1)
            {
                visited[row][col] = true;
                pos tmp = {row,col,0};
                tomatos.push_back(tmp);
            }
        }
    int ans = bfs();
    if(!isOK()) ans = -1;
    cout << ans << endl;

}
