#include <iostream>
using namespace std;
int amout[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//시작날 m, d
//마지막날 get_m, get_d
int getRange(int m, int d, int get_m, int get_d)
{
    if(m == get_m) 
    {
        return get_d - d;
    }
    int sum = 0;
    for(int i=m+1;i<get_m;i++)
    {   
        sum += amout[i-1];
    }
    sum += get_d;
    sum += amout[m-1] - d ;
    return sum;
}
int main()
{

    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++)
    {
        int s;
        int m = 1; //month
        int d = 1; //day

        int get_m, get_d;
        scanf("%d %d", &get_m, &get_d);

        s = getRange(1,1,get_m, get_d);
        printf("#%d %d\n", i+1, (s+4)%7);
    }
}
