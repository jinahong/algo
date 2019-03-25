/*
   1시간 20분 시간초과^^

 */
#include <iostream>

using namespace std;
typedef struct pos{
    int a, b;
}pos;
//n*h/2
bool arr[11][32];
int n, m, h;
bool isAns();
bool safe(int x, int y)
{
    if(arr[x][y]) return false;
    else if(y-1 > 0  && y+1 <=h-1)
    {
        if(!arr[x][y+1] && !arr[x][y-1])
            return true;
    }
    else if(y == 1)
    {if(!arr[x][y+1]) return true;}
    else if(y == n-1)
    {if(!arr[x][y-1]) return true;} 
    return false;

}
int ans = -1;
void solve(int x, int y, int depth, int limits)
{
    if(depth == limits) 
    {
        if(isAns()) ans = depth;
        return;
    }
    for(int i=x;i<=h;i++)
    {
        for(int j=1;j<=n-1;j++)
        {
            cout << "i:" << i << "j:" <<j<< ":" << arr[i][j] << endl;
            if(safe(i,j))
            {
                cout << "i:" << i << "j:" <<j<< "depth" << depth << endl;

                arr[i][j] = true;
                solve(i, j, depth+1, limits);
                arr[i][j] = false;
            }
            //        if(ans>0) break;
        }
        //  if(ans>0)break;
    }
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
    if(isAns())
    {
        cout << "0"<< endl;
        return 0;
    }
    for(int i=1;i<=3;i++)
    {
        solve(1, 1, 0,i);
        if(ans > 0) 
        {
            cout << ans << endl;
            return 0;
        }
    }

    cout << ans << endl;
}
