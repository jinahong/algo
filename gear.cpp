/*

N극: 0, S극: 1,
-1: counter-clockwise, 1: clockwise

solve:
i번째 바퀴 회전한 후, i의 3번과 i+1의 7번 확인. i의 7번과 i-1번의 3번 확인.



    gear회전 순서 과정 제대로 문제 읽기!ㅠㅠ
 */
#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

typedef struct rotation{
    int th, d;
} rotation;

void my_print() ;
int gears[4][10];
bool visited[4];

void rotate_gear(int gear_idx, int d)
{
    cout << "rotate" << gear_idx << " to " << d << endl;
    int tmp;
    ////clockwise : 1, right shift
    if(d == 1)
    {
        tmp = gears[gear_idx][7];
        for(int i=6;i>=0;i--)
            gears[gear_idx][i+1] = gears[gear_idx][i];
        gears[gear_idx][0] = tmp;
    }
    //couter-clockwise : -1
    else if (d == -1)
    {
        tmp = gears[gear_idx][0];
        for(int i=0;i<8;i++)
            gears[gear_idx][i] = gears[gear_idx][i+1];
        gears[gear_idx][7] = tmp;
    }
    my_print();

}

void solve(rotation r)
{
    queue<rotation> q;

    visited[r.th] = true;
    q.push(r);

    while(!q.empty())
    {
        rotation tmp = q.front();q.pop();

        int th = tmp.th;
        int d = tmp.d;

 //       rotate_gear(th, d);
       //오른쪽 기어랑 극확인.
        if(th>=0 && th<3 && !visited[th+1] && (gears[th][2] != gears[th+1][6]))
        {
            cout << "push right" << endl;
            visited[th+1] = true;
            q.push((rotation){th+1, d*-1});
        }
        if(th>0 && th<=3 && !visited[th-1] && (gears[th][6] != gears[th-1][2]))
        {
            cout << "push left" << endl;
            visited[th-1] = true;
            q.push((rotation){th-1, d*-1});
        }
         rotate_gear(th, d);
    }
}
void my_print()
{
    for(int j=0;j<4;j++)
    {
        for(int i=0;i<8;i++)
        {
            cout << gears[j][i];
        }
        cout << endl;
    }  
}

int calc()
{
    int sum = 0;
    for(int i=0;i<4;i++)
        sum += gears[i][0] * pow(2,i);
    return sum;
}
void init()
{
    for(int i=0;i<4;i++)
        visited[i] = false;
}
int main()
{
    for(int j=0;j<4;j++)
    {
        for(int i=0;i<8;i++)
        {
            scanf("%1d", &gears[j][i]);
        }
    }
    int rotate_cnt;
    cin >> rotate_cnt;
    for(int i=0; i< rotate_cnt; i++)
    {
        init();
        rotation r;
        cin >> r.th;
        cin >> r.d;
        //counting gears index zero-based
        r.th--;
        solve(r);
    }

    cout << calc() << endl;
}
