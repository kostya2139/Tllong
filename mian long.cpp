//ok code

#include <bits/stdc++.h>
using namespace std;

const int nmax=1000;

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
    void out_num() 
    {
        if(sign=='-') cout<<sign;
        for (int i=nmax-len; i<nmax; ++i)
            cout<<number[i];
        cout<<'\n';
    }

    int cmp(const Tlong &num) const
    {
        if (sign!=num.sign)
        {
            if (sign == '+') return 1;
            return -1;
        }
        if (sign=='+') return cmp_abs(num);
        return -cmp_abs(num);
    }
    
    int cmp_abs(const Tlong &num) const
    {
        if (len > num.len) return 1;
        if (len < num.len) return -1;
        for (int i=nmax-len; i<nmax; ++i)
        {
            if (number[i]>num.number[i]) return 1;
            if (number[i]<num.number[i]) return -1;
        }
        return 0;
    }

    void operator=(const Tlong &num)
    {
        sign=num.sign;
        for (int i=nmax-1; i>=nmax-max(len, num.len); --i)
            number[i]=num.number[i];
        len=num.len;
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
            int compare_abs=cmp_abs(num1), compare=cmp(num1);
            if (compare_abs == -1)
                res=sub_abs(num1, *this);
            else 
                res=sub_abs(*this, num1);
            if (compare*compare_abs == -1) res.sign='-';
            else res.sign='+';
        }
        return res;
    }
    
    friend void inp_2nums(Tlong &num1, Tlong &num2);

};

void inp_2nums(Tlong &num1, Tlong &num2)
{
    string S;
    cin>>S;
    num1.zeroing();
    num2.zeroing();
    int n1_len=0, n2_len=0;
    num1.sign='+';
    if (S[0]=='+' || S[0]=='-') 
    {
        num1.sign=S[0];
        S.erase(0,1);
    }
    int i=1;
    int len_S=S.size();
    while (S[len_S-i]!='+' && S[len_S-i]!='-')
    {
        ++n2_len;
        num2.number[nmax-n2_len]=S[len_S-i]-48;
        ++i;
    }
    num2.sign=S[len_S-i];
    ++i;
    while (i<=len_S)
    {
        ++n1_len;
        num1.number[nmax-n1_len]=S[len_S-i]-48;
        ++i;
    }
    num1.len=n1_len;
    num2.len=n2_len;
}

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

int main()
{
    Tlong num1, num2;
    int n;
    cin>>n;
    for(int i=0; i<n; ++i)
    {
        inp_2nums(num1, num2);
        (num1+num2).out_num();
    }
    return 0;
}