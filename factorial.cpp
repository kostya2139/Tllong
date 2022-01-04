#include <bits/stdc++.h>
using namespace std;

const int nmax=10000;

class Tlong
{
    char sign='+';
    int number[nmax]={};
    int len=1;

    void zeroing()
    {
        sign='+';
        for (int i=nmax-len; i<nmax; ++i) number[i]=0;
        len=1;
    }

    int size()
    {
        int i=0;
        while (i<nmax && number[i]==0) ++i;
        if (i==nmax) return 1;
        return nmax-i;
    }

    Tlong add_abs(const Tlong &num) const
    {
        Tlong res;
        int length=max(len,num.len), S, p=0;
        for (int i=nmax-1; i>=nmax-length-1; --i)
        {
            S=number[i]+num.number[i]+p;
            res.number[i]=S%10;
            p=S/10;
        }
        res.len=res.size();
        return res;
    }

    friend Tlong sub_abs(const Tlong &num1, const Tlong &num2);
public:
    Tlong(int n=0)
    {
        if (n==0) 
        {
            sign='+';
            len=1;
            number[nmax-1]=0;
        }
        sign='+';
        if (n<0)
        {
            sign='-';
            n=abs(n);
        }
        if (n>0)
        {
            len=0;
            while(n!=0)
            {
                ++len;
                number[nmax-len]=n%10;
                n/=10;
            }
        }
    }

    void inp_num()
    {
        string S;
        cin>>S;
        zeroing();
        if (S[0]=='+' || S[0]=='-') 
        {
            sign=S[0];
            S.erase(0,1);
        }
        len=S.size();
        for (int i=0; i<len; ++i)
            number[nmax-len+i]=S[i]-48;
    }

    friend void out_num(const Tlong &num);

    friend int cmp_abs(const Tlong &num1, const Tlong &num2);

    friend int cmp(const Tlong &num1, const Tlong &num2);

    Tlong& operator=(const Tlong &num)
    {
        sign=num.sign;
        len=num.len;
        for (int i=0; i<nmax; ++i)
            number[i]=num.number[i];
        return *this;
    }

    Tlong operator-() const
    {
        Tlong inverse_num=*this;
        if (len == 1 && number[nmax-1] == 0 || sign == '-') inverse_num.sign='+';
        else inverse_num.sign='-';
        return inverse_num;
    }

    Tlong operator+(const Tlong &num1) const
    {
        Tlong res;
        if (sign == num1.sign)
        {
            res=add_abs(num1);
            res.sign=sign;
        }
        else
        {
            int compare_abs=cmp_abs(*this, num1), compare=cmp(*this, num1);
            if (compare_abs == -1)
                res=sub_abs(num1, *this);
            else 
                res=sub_abs(*this, num1);
            if (compare*compare_abs == -1) res.sign='-';
            else res.sign='+';
        }
        return res;
    }

    Tlong operator-(const Tlong &num1) const
    {
        Tlong res=*this+(-num1);
        return res;
    }

    Tlong& operator++()
    {
        int i=1;
        if (sign=='+')
        {
            while(number[nmax-i]==9)
            {
                number[nmax-i]=0;
                ++i;
            }
            ++number[nmax-i];
        }
        else
        {
            while (number[nmax-i]==0)
            {
                number[nmax-i]=9;
                ++i;
            }
            --number[nmax-i];
            if(len == 1 && number[nmax-1] == 0) sign='+';
        }
        if (i>len) ++len;
        return *this;
    }
    
    Tlong operator*(const Tlong &num)
    {
        Tlong res;
        int S, p=0;
        if (sign==num.sign) res.sign='+';
        else res.sign='-';
        for(int i=1; i<=len; ++i)
            for (int j=1; j<=num.len+1; ++j)
            {
                S=number[nmax-i]*num.number[nmax-j]+p+res.number[nmax+1-i-j];
                p=S/10;
                res.number[nmax+1-i-j]=S%10;
            }
        res.len=res.size();
        return res;
    }

    void operator*=(const Tlong &num)
    {
        *this=*this*num;
    }
};

Tlong sub_abs(const Tlong &num1, const Tlong &num2) 
{
    Tlong res;
    int length=max(num1.len,num2.len), S, p=0;
    for (int i=nmax-1; i>=nmax-length; --i)
    {
        S=num1.number[i]-num2.number[i]-p;
        if(S<0)
        {
            res.number[i]=S+10;
            p=1;
        }
        else
        {
            res.number[i]=S;
            p=0;
        }
    }
    res.len=res.size();
    return res;
}

void out_num(const Tlong &num)
{
    if(num.sign=='-') cout<<num.sign;
    for (int i=nmax-num.len; i<nmax; ++i)
        cout<<num.number[i];
    cout<<'\n';
}

int cmp_abs(const Tlong &num1, const Tlong &num2)
{
    if (num1.len > num2.len) return 1;
    if (num1.len < num2.len) return -1;
    for (int i=nmax-num1.len; i<nmax; ++i)
    {
        if (num1.number[i]>num2.number[i]) return 1;
        if (num1.number[i]<num2.number[i]) return -1;
    }
    return 0;
}

int cmp(const Tlong &num1, const Tlong &num2)
{
    if (num1.sign!=num2.sign)
    {
        if (num1.sign == '+') return 1;
        return -1;
    }
    if (num1.sign=='+') return cmp_abs(num1, num2);
    return -cmp_abs(num1,num2);
}

Tlong factorial(int n)
{
    Tlong res(1);
    for (int i=2; i<=n; ++i)
    {
        res=res*i;
    }
    return res;
}

int main()
{
    Tlong num1,num2,num3;
    num1.inp_num();
    num2.inp_num();
    num3.inp_num();
    out_num(num1+num2+num3);
}