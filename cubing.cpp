#include <iostream>
#include <vector>
using namespace std;

char cube[6][9];

typedef struct side_info{
    int position;
    int side;
} side_info;

#define u   0
#define f   1
#define d   2
#define b   3
#define l   4
#define r   5

void print_upper_side();

void init()
{
    for(int i=0;i<9;i++) cube[u][i] = 'w';
    for(int i=0;i<9;i++) cube[f][i] = 'r';
    for(int i=0;i<9;i++) cube[d][i] = 'y';
    for(int i=0;i<9;i++) cube[b][i] = 'o';
    for(int i=0;i<9;i++) cube[l][i] = 'g';
    for(int i=0;i<9;i++) cube[r][i] = 'b';
}

void putArr(side_info info, char* arr)
{
    int position = info.position;
    switch (info.side)
    {
        case 1:
            cube[position][0] = arr[0];
            cube[position][1] = arr[1];
            cube[position][2] = arr[2];
            break;
        case 2:
            cube[position][2] = arr[0];
            cube[position][5] = arr[1];
            cube[position][8] = arr[2];
            break;
        case 3:
            cube[position][6] = arr[0];
            cube[position][7] = arr[1];
            cube[position][8] = arr[2];
            break;
        case 4:
            cube[position][0] = arr[0];
            cube[position][3] = arr[1];
            cube[position][6] = arr[2];
            break;
    }
}
char* getArr(side_info info, char* tmp)
{
    int position = info.position;
    switch (info.side)
    {
        case 1:
            tmp[0] = cube[position][0];
            tmp[1] = cube[position][1];
            tmp[2] = cube[position][2];
            break;
        case 2:
            tmp[0] = cube[position][2];
            tmp[1] = cube[position][5];
            tmp[2] = cube[position][8];
            break;
        case 3:
            tmp[0] = cube[position][6];
            tmp[1] = cube[position][7];
            tmp[2] = cube[position][8];
            break;
        case 4:
            tmp[0] = cube[position][0];
            tmp[1] = cube[position][3];
            tmp[2] = cube[position][6];
            break;
    }
    return tmp;
}
void rotate_square(int square, char direction)
{
    vector<char> tmp;
    if(direction == '+')
    {
        for(int j=2;j>=0;j--)
            for(int i=0;i<3;i++)
                tmp.push_back(cube[square][j+i*3]);
        for(int i=8;i>=0;i--)
        {
            cube[square][i] = tmp.back();
            tmp.pop_back();
        }

    }
    else if(direction == '-')
     {
        for(int j=6;j<9;j++)
            for(int i=0;i<3;i++)
                tmp.push_back(cube[square][j-i*3]);
         for(int i=8;i>=0;i--)
        {
            cube[square][i] = tmp.back();
            tmp.pop_back();
        }
    }

}
/*a는 윗변, b,c,d는 시계방향*/
void rotate(
        side_info s1, 
        side_info s2,
        side_info s3,
        side_info s4, char direction)
{
    char tmp[3];
    //clock-wise
    if(direction == '+')
    {
        char save[3];
        memcpy(save, getArr(s1, tmp), 3);
        putArr(s1, getArr(s4, tmp));
        putArr(s4, getArr(s3, tmp));
        putArr(s3, getArr(s2, tmp));
        putArr(s2, save);
    }
    //couter clock-wise
    else if(direction == '-')
    {
        char save[3];
        memcpy(save, getArr(s4, tmp), 3);
        putArr(s4, getArr(s1, tmp));
        putArr(s1, getArr(s2, tmp));
        putArr(s2, getArr(s3, tmp));
        putArr(s3, save);
    }
}
void print_upper_side()
{
    for(int i=1;i<=9;i++)
    {
            cout << cube[u][i-1];
        if(i%3 == 0) cout << endl;
    }
}
//WTF!!! crazy...
void solve(string r_info)
{
    side_info s1; //사각형을 윗면부터 시계방향으로
    side_info s2;
    side_info s3;
    side_info s4;
    if(r_info[0] == 'F')
    {
        s1 = (side_info){u, 3}; 
        s2 = (side_info){r, 4}; 
        s3 = (side_info){d, 3}; 
        s4 = (side_info){l, 4};
        rotate_square(f, r_info[1]);
    }
    else if(r_info[0] == 'R')
    {
        s1 = (side_info){u, 2}; 
        s2 = (side_info){b, 2}; 
        s3 = (side_info){d, 2}; 
        s4 = (side_info){f, 2};
        rotate_square(r, r_info[1]);
    }
    else if(r_info[0] == 'U')
    {
        s1 = (side_info){b, 1}; 
        s2 = (side_info){r, 1}; 
        s3 = (side_info){f, 1}; 
        s4 = (side_info){l, 1};
        rotate_square(u, r_info[1]);
    }
    else if(r_info[0] == 'B')
    {
        s1 = (side_info){u, 1}; 
        s2 = (side_info){r, 2}; 
        s3 = (side_info){d, 1}; 
        s4 = (side_info){l, 2};
        rotate_square(b, r_info[1]);
    }
    else if(r_info[0] == 'L')
    {
        s1 = (side_info){u, 4};
        s2 = (side_info){b, 4}; 
        s3 = (side_info){d, 4}; 
        s4 = (side_info){f, 4};
        rotate_square(l, r_info[1]);
    }
    else if(r_info[0] == 'D')
    {
        s1 = (side_info){b, 3}; 
        s2 = (side_info){r, 3}; 
        s3 = (side_info){f, 3}; 
        s4 = (side_info){l, 3};
        rotate_square(d, r_info[1]);
    }
    rotate(s1, s2, s3, s4, r_info[1]);
}
int main()
{
    int tc;
    string r_info;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {

        int r_tc;
        cin >> r_tc;

        init();
        for(int j=0;j<r_tc;j++)
        {
            cin >> r_info;
            solve(r_info);
        }
        print_upper_side();
    }
}

