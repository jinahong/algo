/*
   https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo
 
 basic:
 	permutation인줄알았으나 gridy로 가능한 문제
 detail:
 	a,b가 같은 bc사용할수있는 경우 꼼꼼하게 처리해주기.


 코딩 50분

 20분후동안 버그 찾기

20분후동안 gridy로바꿈

20분동안 디버깅. 아몰라 잘래

40분동안 디버깅해서 solve에서 (1개, 1개이상) 인 경우 찾아서 해결해줌
 */

#include <iostream>
#include <vector>
using namespace std;

int arr[2][102];
int max_time; // maxinum time
int bc_cnt; // bc의 갯수

#define STILL 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

typedef struct bc_info
{
	int x, y;
	int c; // 충전범위
	int p; // 성능
} bc_info;
bc_info bcs[9];

typedef struct pos
{
	int x, y;
}pos;

int ans; 
//a가 연결가능한 bc의 list반환
vector<bc_info> connectable_bcs(pos a)
{
	vector<bc_info> res;
	for(int i=0;i<bc_cnt;i++)
	{
		int d = abs(bcs[i].x - a.x) + abs(bcs[i].y - a.y);
		if(d <= bcs[i].c)
			res.push_back(bcs[i]);
	}
	return res;
}
pos movePos(pos a, int d)
{
	pos res = a;
	switch(d)
	{
		case STILL:
			break;
		case UP:
			res.y--;
			break;
		case RIGHT:
			res.x++;
			break;
		case DOWN:
			res.y++;
			break;
		case LEFT:
			res.x--;
			break;
	}
	return res;

}
bool isSamebc(bc_info a, bc_info b)
{
	return a.x == b.x && a.y == b.y;
}
bc_info getMaxBc(vector<bc_info> a)
{
	bc_info max_a = {0,0,0,0};
	for(int i=0;i<a.size();i++)
		if(max_a.p < a[i].p) max_a = a[i];
	return max_a;
}
bc_info getSecMaxBc(vector<bc_info> a, bc_info max_a)
{
	bc_info sec_max_a = {0,0,0,0};
	for(int i=0;i<a.size();i++)
		if(!isSamebc(max_a,a[i]) && sec_max_a.p < a[i].p) 
			sec_max_a = a[i];
	return sec_max_a;
}
int getMaxSum(vector<bc_info> a, vector<bc_info> b)
{
	int res=0;

	//a의 max값을 찾기
	bc_info max_a = getMaxBc(a);
	//b의 max값을 찾기
	bc_info max_b = getMaxBc(b);

	if(!isSamebc(max_a,max_b)) res = max_a.p + max_b.p;
	else
	{
		//a에서 second max찾기
		bc_info sec_max_a = getSecMaxBc(a, max_a);
		//b에서 second max찾기
		bc_info sec_max_b = getSecMaxBc(b, max_b);

		int pick_a_max = max_a.p + sec_max_b.p;
		int pick_b_max = max_b.p + sec_max_a.p;
		res = max(res/2, max(pick_a_max,pick_b_max));
	}

	return res;
}

int solve(pos a, pos b)
{
	int sum = 0;
	pos loc_a = a;
	pos loc_b = b;

	for(int i=0;i<=max_time;i++)
	{
		loc_a = movePos(loc_a, arr[0][i]);
		loc_b = movePos(loc_b, arr[1][i]);
		vector<bc_info> a_bc = connectable_bcs(loc_a);
		vector<bc_info> b_bc = connectable_bcs(loc_b);

		if(a_bc.size() == 0 && b_bc.size() == 0)
		{
			continue;
		}

		else if(a_bc.size() == 1 && b_bc.size() == 1) 
		{
			//a,b connect on same bc
			if(isSamebc(a_bc[0], b_bc[0]))
				sum += a_bc[0].p;
			else
				sum += a_bc[0].p + b_bc[0].p;
		}
		else if(a_bc.size() == 1 && b_bc.size() == 0)
			sum += a_bc[0].p;

		else if(a_bc.size() == 0 && b_bc.size() == 1)
			sum += b_bc[0].p;

		else if(a_bc.size() > 1 && b_bc.size() == 1)
		{
			bc_info max = getMaxBc(a_bc);
			if(!isSamebc(max, b_bc[0]))
				sum += max.p + b_bc[0].p;
			else
				sum += getSecMaxBc(a_bc,max).p + b_bc[0].p;
		}
		else if(a_bc.size() == 1 && b_bc.size() > 1)
		{
			bc_info max = getMaxBc(b_bc);
			if(!isSamebc(max, a_bc[0]))
				sum += max.p + a_bc[0].p;
			else
				sum += getSecMaxBc(b_bc,max).p + a_bc[0].p;
		}

		//a,b모두 1개이상의 연결가능한 bc가 있음.
		else
			sum += getMaxSum(a_bc,b_bc);
	}
	return sum;
}
int main()
{
	int tc;
	cin >> tc;

	for(int tc_i=1;tc_i<=tc;tc_i++)
	{

		cin >> max_time >> bc_cnt;
		//arr[][0]은 0이 될수있도록 입력받음
		for(int i=1;i<=max_time;i++)
			cin >> arr[0][i];
		for(int i=1;i<=max_time;i++)
			cin >> arr[1][i];

		for(int i=0;i<bc_cnt;i++)
		{
			cin >> bcs[i].x >> bcs[i].y >> bcs[i].c >> bcs[i].p;
		}
		pos init_a = {1,1};
		pos init_b = {10,10};
		int ans = solve(init_a,init_b) ;
		cout << "#" << tc_i <<" " << ans<< endl;
	}
}
