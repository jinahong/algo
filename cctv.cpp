/*
https://www.acmicpc.net/problem/15683


많이 제거할 수 있는 거 부터 하는게 좋을 듯.
-> 카메라까리는 통과 가능해서, 의미없을듯. 
5, 4,3, 2,1 순서대로...

- 2차원 배열을 parameter로 넘기는 방법
- 알고리즘은 없음. 그냥 코딩 하는데 시간 오래걸리는 문제

 */
#include <iostream>

using namespace std;
typedef struct pos {
    int x; int y;int cctv_kind;
} pos;

int arr[8][8];
int ans = 999;
//save the position of each camera
pos cams[9];

int n;
int m;

#define EMPTY 0
#define WALL 6
#define VIEW 7

bool safe(int x, int y)
{
    if(x>=0 && x<m && y>=0 && y<n) return true;
    else return false;
}
void copy_map(int dst[][8], int src[][8])
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            dst[j][i] = src[j][i];
}
/*
 카메라 시야를 map에 체크하는 과정
 */
void rotate(int map[][8], int shadow_map[][8], int cam_idx, int* degree, int degree_size)
{
    copy_map(shadow_map, map);
    for(int i=0;i<degree_size; i++)
    {
        int x = cams[cam_idx].x;
        int y = cams[cam_idx].y;


        switch(degree[i])
        {
            case 0:
                for(x++;safe(x, y) && shadow_map[x][y] != WALL ; x++)
                    shadow_map[x][y] = VIEW;
                break;
            case 1:
                for(y++;safe(x, y)&& shadow_map[x][y] != WALL ; y++)
                    shadow_map[x][y] = VIEW;
                break;
            case 2:
                for(x--;safe(x, y) && shadow_map[x][y] != WALL ; x--)
                    shadow_map[x][y] = VIEW;
                break;
            case 3:
                for(y--;safe(x, y) && shadow_map[x][y] != WALL ; y--)
                    shadow_map[x][y] = VIEW;
        }
    }

}
void debug(int map[][8]);
void chk_blind_spot(int map[][8])
{
    int cnt = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(map[j][i] == EMPTY)
                cnt++;
    if(ans > cnt) 
    {
        debug(map);
        ans = cnt;
    }
}

void debug(int map[][8])
{
    cout << "===================" << endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout << map[j][i] << " ";
        cout << endl;
    }
    cout << "===================" << endl;
}
/*
 각 카메라 별로, 회전가능한 경우를 모두 탐색
 시야가 체크된 tmp array는 지역변수로 선언하였다
 */
void solve(int cam_idx, int map[][8])
{
    if(cam_idx<0)
    {
        chk_blind_spot(map);
        return;
    }
    int ds[4]={0,};
    int tmp[8][8];
    if(cams[cam_idx].cctv_kind == 1)
    {
        for(int d = 0 ; d < 4 ; d++)
        {
            ds[0] = d;
            rotate(map, tmp, cam_idx, ds, 1);
            debug(tmp);
            solve(cam_idx-1, tmp);
        }
    }
    else if(cams[cam_idx].cctv_kind == 2)
    {
        ds[0]=0; ds[1] = 2;
        rotate(map, tmp, cam_idx, ds, 2);
        solve(cam_idx-1, tmp);

        ds[0]=1; ds[1] = 3;
        rotate(map, tmp, cam_idx, ds, 2);
        solve(cam_idx-1, tmp);
    }
    else if(cams[cam_idx].cctv_kind == 3)
    {
        ds[0]=0; ds[1] = 3;
        rotate(map, tmp, cam_idx, ds, 2);
        solve(cam_idx-1, tmp);

        ds[0]=0; ds[1] = 1;
        rotate(map, tmp, cam_idx, ds, 2);
        solve(cam_idx-1, tmp);

        ds[0]=1; ds[1] = 2;
        rotate(map, tmp, cam_idx, ds, 2);
        solve(cam_idx-1, tmp);
        ds[0]=2; ds[1] = 3;
        rotate(map, tmp, cam_idx, ds, 2);
        solve(cam_idx-1, tmp);
    }
    else if(cams[cam_idx].cctv_kind == 4)
    {
        ds[0]=0; ds[1] = 2; ds[2] = 3;//except 1
        rotate(map, tmp, cam_idx, ds, 3);
        solve(cam_idx-1, tmp);

        ds[0]=0; ds[1] = 1; ds[2] = 3; // except 2
        rotate(map, tmp, cam_idx, ds, 3);
        solve(cam_idx-1, tmp);

        ds[0]=0; ds[1] = 1; ds[2] = 2; // except 3
        rotate(map, tmp, cam_idx, ds, 3);
        solve(cam_idx-1, tmp);

        ds[0]=1; ds[1] = 2; ds[2] =3; //decept 0
        rotate(map, tmp, cam_idx, ds, 3);
        solve(cam_idx-1, tmp);
    }
    else if(cams[cam_idx].cctv_kind == 5)
    {
        ds[0]=0; ds[1] = 1; ds[2] = 2; ds[3] = 3;
        rotate(map, tmp, cam_idx, ds, 4);
        solve(cam_idx-1, tmp);
    }

}

int main()
{
    int cam_cnt=0;
    cin >> n >> m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            cin >> arr[j][i];
            if(arr[j][i] > 0 && arr[j][i] < 6)
            {
                cams[cam_cnt++] = (pos){j, i, arr[j][i]};
            }
        }

    solve(cam_cnt-1, arr);
    cout << ans << endl;
}

