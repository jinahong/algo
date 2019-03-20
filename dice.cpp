/*
   1시간경과: tc는 맞는데, 틀렸다 ㅂㄷㅂㄷ ㅠㅠㅠㅠ
   문제풀이 찾아봄, x,y잘못받음:ㅈ:
 */

#include <iostream>
#include <string.h>

using namespace std;

typedef struct pos{
    int x, y;
} pos;

int dice[7];
int arr[21][21];
int n,m;
pos dicePos;
//동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4
#define EAST 1
#define WEST 2
#define NORTH 3
#define SOUTH 4

bool safe(int x, int y)
{
    return x <m && x>=0 && y < n && y >=0;
}
bool rotate(int direc)
{
    bool flag = false;
    int tmpDice[7];
    memcpy(tmpDice, dice, 7*4);
    switch(direc)
    {
        case EAST:
            if(safe(dicePos.x+1, dicePos.y))
            {
                dice[1] = tmpDice[4];
                dice[3] = tmpDice[1];
                dice[6] = tmpDice[3];
                dice[7] = tmpDice[6];
                dicePos.x+=1;
                flag = true;
            }
            break;
        case WEST:
            if(safe(dicePos.x-1, dicePos.y))
            {
                dice[1] = tmpDice[3];
                dice[3] = tmpDice[6];
                dice[6] = tmpDice[4];
                dice[4] = tmpDice[1];

                dicePos.x -=1;
                flag = true;
            }
            break;

        case SOUTH:
            if(safe(dicePos.x, dicePos.y+1))
            {
                dice[1] = tmpDice[2];
                dice[5] = tmpDice[1];
                dice[6] = tmpDice[5];
                dice[2] = tmpDice[6];
                dicePos.y += 1;
                flag = true;
            }
            break;

        case NORTH:
            if(safe(dicePos.x, dicePos.y-1))
            {
                dice[1] = tmpDice[5];
                dice[5] = tmpDice[6];
                dice[6] = tmpDice[2];
                dice[2] = tmpDice[1];
                dicePos.y-=1;
                flag = true;
            }
            break;
    }
    //이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다. 0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.
    if(flag)
    {
        if(arr[dicePos.x][dicePos.y] == 0)
            arr[dicePos.x][dicePos.y] = dice[6];
        else
        {
            dice[6] = arr[dicePos.x][dicePos.y];
            arr[dicePos.x][dicePos.y] =0;
        }
    }
    return flag;
}

int main()
{
    cin >> n >> m;

    cin >> dicePos.y >> dicePos.x;
    int k;
    cin >> k;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> arr[j][i];

    for(int i=0;i<k;i++)
    {
        int direc;
        cin >> direc;
        if(rotate(direc))
            cout << dice[1] << endl;
    }
}

