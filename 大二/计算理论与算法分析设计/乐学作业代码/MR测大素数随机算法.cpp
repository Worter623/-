#include <stdio.h>
#include <iostream>
using namespace std;
typedef long long ll;
const int repeat = 50;

ll mul(ll a, ll b, ll m)
//��a*b%m
{
    ll ans = 0;
    a %= m;
    while (b)
    {
        if (b & 1) 
            ans = (ans + a) % m;
        b /= 2;
        a = (a + a) % m;
    }
    return ans;
}

ll pow(ll a, ll b, ll m)
//a^b % m
{
    ll ans = 1;
    a %= m;
    while (b)
    {
        if (b & 1)
            ans = mul(a, ans, m);
        b /= 2;
        a = mul(a, a, m);
    }
    ans %= m;
    return ans;
}

bool MillerRabin(ll n)//n�ǲ��ԵĴ�����repeat�ǲ����ظ�����
{
    if (n == 2 || n == 3)return true;
	if (!(n & 1))return false;
    ll d = n - 1;//��n-1�ֽ��2^s*d
    int s = 0;
    while (!(d & 1)) ++s, d >>= 1;
    for (int i = 0; i < repeat; i++)//�ظ�repeat��
    {
        ll a = rand() % (n - 3) + 2;//ȡһ�������,[2,n-1)
        ll x = pow(a, d, n),y = 0;
        for (int j = 0; j < s; j++)
        {
            y = mul(x, x, n);
            if (y == 1 && x != 1 && x != (n - 1))return false;
            x = y;
        }
		if (y != 1)return false;//����С����
    }
    return true;
}

int main()
{
    ll n;
    cin >> n;
    if (MillerRabin(n))
        cout << "Prime" << endl;
    else
        cout << "Composite" << endl;
}
