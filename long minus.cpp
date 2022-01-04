#include <bits/stdc++.h>
using namespace std;

const int nmax=100000;

class Tlong
{
    char sign='+';
    int number[nmax]={0};
    int len=1;

    void zeroing()
    {
        sign='+';
        for (int i=nmax-len; i<nmax; ++i) number[i]=0;
        len=1;
    }

    Tlong add_abs(const Tlong &num) const
    {
        Tlong res;
        int length=max(len,num.len), S, p=0;
        for (int i=nmax-1; i>=nmax-length; --i)
        {
            S=number[i]+num.number[i]+p;
            res.number[i]=S%10;
            p=S/10;
        }
        res.number[nmax-length-1]=p;
        if (p) ++length; 
        res.len=length;
        return res;
    }

    friend Tlong sub_abs(const Tlong &num1, const Tlong &num2);
public:
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

    void operator=(const Tlong &num)
    {
        sign=num.sign;
        len=num.len;
        for (int i=0; i<nmax; ++i)
            number[i]=num.number[i];
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

    void operator++()
    {
        int p=0,i=1;
        if (sign=='+')
        {
            p=++number[nmax-i]/10;
            number[nmax-i]%=10;
            ++i;
            while(p) 
            {
                p=++number[nmax-i]/10;
                number[nmax-i]%=10;
                ++i;
            }
        }
        else 
        {
            while (--number[nmax-i]<0)
            {
                number[nmax-i]+=10;
                ++i;
            }
            if(len == 1 && number[nmax-1] == 0) sign='+';
        }
        return *this;
    }
};
Tlong sub_abs(const Tlong &num1, const Tlong &num2) 
{
    Tlong res;
    int length=max(num1.len,num2.len), S, p=0, length_res=1;
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
        if (res.number[i]!=0) length_res=nmax-i;
    }
    res.len=length_res;
    return res;
}

void out_num(const Tlong &num)
{
    if(num.sign=='-') cout<<num.sign;
    for (int i=nmax-num.len; i<nmax; ++i)
        cout<<num.number[i];
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

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Tlong num;
    int n;
    cin>>n;
    for (int i=0; i<n; ++i)
    {
        num.inp_num();
        out_num(++num);
        cout<<'\n';
    }
    return 0;
}