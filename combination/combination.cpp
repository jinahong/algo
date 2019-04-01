/*
https://www.acmicpc.net/problem/2407

combination문제
일반적인 풀이방법: 
    n개중 k개를 고르는 방법
    1) n-1개에서 k개를 다 고른다. 
    2) n-1개에서 k-1개를 고르고, 마지막 n번째 항목을 추가하는 방법
    
memoization필요



max인 00C50은 100,891,344,545,564,193,334,812,497,256
unsigned long long 범위는 0 ~ 18,446,744,073,709,551,615

즉, 새로운 구조체를 만들어주어야 한다. 

*/

#include <stdio.h>

const long long unsigned maximum = 1e18;
bigInt mem[101][101];

typedef struct bigInt
{  
    //각각 18자리
    long long unsigned high = 0;
    long long unsigned low = 0;
} bigInt;

bigInt plus_bigInt(bigInt a, bigInt b)
{
    bigInt c;
    c.high = a.high + b.high;
    if(a.low + b.low > maximum)
    {
        c.low = a.low + b.low - maximum;
        c.high++;
    }
    else
        c.low = a.low + b.low;
    return c;
}
bool isZero_bigInt(bigInt a)
{
    return (a.high == 0 && a.low == 0);
}

void print_bigInt(bigInt a)
{
    //항상 출력할 경우, 앞에 0붙기 때문에 if문 필요
    if(a.high != 0)
        printf("%llu", a.high); 
    printf("%llu\n", a.low);    
}

bigInt func(int n, int k)
{
   // printf("%d %d\n", n,k);
    if(isZoer_bigInt(mem[n][k]))
    {
        if(n==k) 
            mem[n][k].low = 1;
        else if(k==1) 
            mem[n][k].low = n;
        else 
        {
            mem[n][k] = plus_bigInt( func(n-1,k) , func(n-1,k-1) ); 
        }
    }
    return mem[n][k];
}
int main()
{
    int n,k;
    scanf("%d %d", &n, &k);

    func(n,k);

    print_bigInt(mem[n][k]);
}
