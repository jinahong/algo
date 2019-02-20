#include <iostream>
#include <queue>

using namespace std;

char arr[101][101];
bool visited[101][101];
int dx[4]={1,0,-1,0}, dy[4]={0,1,0,-1};

typedef struct pos{
    int x, y;
} pos;


bool safe(int a, int b)
{
    return (0<=a && a<100) && (0<=b && b<100);
}
bool isWall(int x, int y)
{
    if (arr[y][x] == '1') return true;
    else return false;
}
bool solve(pos start, pos end)
{
    queue<pos> q;
    q.push(start);
    visited[start.x][start.y] = true;

    while(!q.empty())
    {
        pos cur = q.front(); q.pop();
        if(cur.x == end.x && cur.y == end.y) return true;
        for(int i=0;i<4;i++)
        {
            int x = cur.x + dx[i];
            int y = cur.y + dy[i];
            if(safe(x,y) && !visited[x][y] && !isWall(x,y))
            {
                pos tmp = {x,y};
                visited[x][y] = true;
                q.push(tmp);

            }
        }
    }
    return false;
}
void init()
{
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            visited[i][j] = false;
        }
    }

}
int main()
{
    pos start; 
    pos end;
    int tc_num;
    for(int tc = 1 ; tc <= 10 ; tc++)
    {
        cin >> tc_num;
        init();
        for(int i=0;i<100;i++)
            scanf("%s", arr[i]);
        for(int i = 0 ; i < 100 ; i++)
        {
            for(int j=0;j<100;j++)
            {
                if(arr[j][i] == '2'){
                    start.x = i; start.y = j;
                }
                else if (arr[j][i] == '3') {
                     end.x = i; end.y = j;}
            }
        }
        cout <<"#" << tc << " " << solve(start, end) << endl;

    }


}
