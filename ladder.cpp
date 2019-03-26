/*
   1시간 20분 시간초과^^

설계
dfs
arr가 true이면, 해당 위치에 사다리 설치되었음.



시작 위치를 solve의 parameter로 받아서 시간줄이는것이 핵심ㅂ!
x,y라는 명대신 col, row로 쓰자...

 */
#include <iostream>

#define ROW 30
#define COL 10

using namespace std;
typedef struct pos{
    int a, b;
}pos;

int arr[ROW+1][COL+1];
int n, m, h;
bool isAns();

bool safe(int row, int col)
{
    if(arr[row][col]) return false;
    else if(col -1 > 0  && col + 1 <=n-1)
    {
        if(!arr[row][col+1] && !arr[row][col-1])
            return true;
    }
    else if(col == 1)
    {
        if(!arr[row][col+1]) 
            return true;
    }

    else if(col == n-1)
    {
        if(!arr[row][col-1]) 
            return true;
    } 
    return false;

}
int ans = -1;

bool solve(int x, int depth, int limits)
{
    if(depth == limits) 
    {
        return isAns();
    }

    for(int i=x;i<=h;i++)
    {
        for(int j=1;j<=n-1;j++)
        {
            if(safe(i,j))
            {
                arr[i][j] = true;

                //XXX
                if(solve(i, depth+1, limits))
                    return true;

                arr[i][j] = false;
            }
        }
    }
    return false;
}

bool isAns()
{
    for(int s = 1; s <= n; s++)
    {
        int  e;
        e = s;
        for(int i=1;i<=h;i++)
        {
            if(arr[i][e] == true)
                e++;
            else if(arr[i][e-1] == true)
                e--;
        }
        if(e != s) return false;
    }
    return true;
}
int main()
{
    cin >> n >> m >> h;

    for(int i=0;i<m;i++)
    {
        int x, y;
        cin >> x >> y;
        arr[x][y] = true;
    }

    for(int i=0;i<=3;i++)
    {
        if(solve(1, 0, i)) 
        {
            cout << i << endl;
            return 0;
        }
    }

    cout << "-1" << endl;
    return 0;
}
