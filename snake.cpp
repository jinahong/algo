/*
 
 https://www.acmicpc.net/problem/3190
 
 문제 잘읽기:
 -X초가 끝난 뒤에 왼쪽(C가 'L') 또는 오른쪽(C가 'D')로 90도 방향을 회전시킨다는 뜻
- apple입력받을 때 행,열 거꾸로 받아서 헤맴.ㅋ
 */
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

typedef struct info{
    int x, y, d;
} info;

typedef struct d_info{
    int s;
    char d;
} d_info;

int n;
////snake길이, front는 head이고, back은 tail
vector<info> snake;
//save input,  after chage the direction,  delete element 
vector<d_info> direction;
vector<pair<int, int> > apple;

bool eatApple(info cur)
{
    for(auto i = apple.begin() ; i!=apple.end() ; ++i)
    {
        if(i->first == cur.x && i->second == cur.y)
        {
  //          cout << "eat apple" << endl;
            apple.erase(i);
            return true;
        }
    }
    return false;
}
info move(info cur)
{
    info res = cur;
    switch(cur.d)
    {
        case LEFT:
            res.x -= 1;
            break;
        case RIGHT:
            res.x += 1;
            break;
        case UP:
            res.y-= 1;
            break;
        case DOWN:
            res.y += 1;
            break;
    }
   return res;
}
int getDirection(int cur_d, char d)
{
    //오른쪽
    if(d == 'D')
    {
        switch(cur_d)
        {
            case LEFT:
                return UP;
            case RIGHT:
                return DOWN;
            case UP:
                return RIGHT;
            case DOWN:
                return LEFT;
        }
    }
    else if(d == 'L')
    {
        switch(cur_d)
        {
            case LEFT:
                return DOWN;
            case RIGHT:
                return UP;
            case UP:
                return LEFT;
            case DOWN:
                return RIGHT;
        }
    }

}
bool safe(int x, int y)
{
    if(x>=0 && y>=0 && x<n && y<n)
    {
        //head는 빼주기 위해서 +1
        for(auto i = snake.begin()+1 ; i!=snake.end();++i)
        {
            if(i->x == x && i->y == y) return false;
        }
        return true;
    }
    else return false;
}
int solve()
{
    int second = 0;
    info cur = (info){ 0,0, RIGHT};
    snake.push_back(cur);

    while(1)
    {
        cur = move(cur);
        second ++;

        if(direction.front().s == second)
        {
            cur = (info){cur.x, cur.y, getDirection(cur.d, direction.front().d)};
            //해당 second가 지났기 때문에 earase해도됨.
            direction.erase(direction.begin());
        }

        //game over
        if(!safe(cur.x, cur.y))
            return second;
        else
        {
             //vector의 front에 push
            snake.insert( snake.begin(),cur);
             //사과먹었으면 tail없애지 말것
            if(!eatApple(cur))
            {
                snake.pop_back();
            }
        }
  
    }
}
int main()
{
    cin >> n;
    int k;// apple
    cin >> k;
    for(int i=0;i<k;i++)
    {
        int x, y;
        cin >> y >> x;
        apple.push_back(make_pair(x-1,y-1));
   }

    int d_cnt;
    cin >> d_cnt;
    for(int i=0;i<d_cnt;i++)
    {
        d_info tmp;
        cin >> tmp.s >> tmp.d;
        direction.push_back(tmp);
    }

    cout << solve() << endl;

}
