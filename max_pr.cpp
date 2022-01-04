#include <bits/stdc++.h>
using namespace std;

const int nmax=600;

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
        for (int i=nmax-1; i>=nmax-length-1; --i)
        {
            S=number[i]+num.number[i]+p;
            res.number[i]=S%10;
            p=S/10;
        }
        if(res.number[nmax-length-1]) ++length;
        res.len=length;
        return res;
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
    
    Tlong sub_abs(const Tlong &num) const
    {
        Tlong res;
        int length=max(len,num.len), S, p=0, length_res=1;
        if(cmp_abs(num)>=0)
        {
            for (int i=nmax-1; i>=nmax-length; --i)
            {
                S=number[i]-num.number[i]-p;
                res.number[i]=(S+10)%10;
                p=1-(S+10)/10;
                if (res.number[i]) length_res=nmax-i;
            }
        }
        else
        {
            for (int i=nmax-1; i>=nmax-length; --i)
            {
                S=num.number[i]-number[i]-p;
                res.number[i]=(S+10)%10;
                p=1-(S+10)/10;
                if (res.number[i]) length_res=nmax-i;
            }
        }
        res.len=length_res;
        return res;
    }

    Tlong divide(int denominator) const
    {
        Tlong res;
        char sign_divide, sign_denominator;
        if (denominator>0) sign_denominator='+';
        else sign_denominator='-';
        denominator=abs(denominator);
        if (sign==sign_denominator) sign_divide='+';
        else sign_divide='-';
        int remaind=0;
        for (int i=nmax-len; i<nmax; ++i)
        {
            remaind*=10;
            remaind+=number[i];
            res.number[i]=remaind/denominator;
            remaind%=denominator;
        }
        res.len=res.size(nmax-len);
        if (res.is_zero()) res.sign='+';
        else res.sign=sign_divide;
        return res;
    }

    int divide_ost(int denominator) const
    {
        char sign_divide, sign_denominator;
        if (denominator>0) sign_denominator='+';
        else sign_denominator='-';
        denominator=abs(denominator);
        if (sign==sign_denominator) sign_divide='+';
        else sign_divide='-';
        int remaind=0;
        for (int i=nmax-len; i<nmax; ++i)
        {
            remaind=remaind*10+number[i];
            remaind%=denominator;
        }
        if (sign_divide == '-') remaind*=-1;
        return remaind;
    }
public:
    Tlong(int n=0)
    {
        sign='+';
        len=0;
        if (n<0)
        {
            sign='-';
            n=abs(n);
        }
        if (n==0) ++len;
        while(n)
        {
            number[nmax-++len]=n%10;
            n/=10;
        }
    }

    bool is_zero() const
    {
        return (len == 1 && number[nmax-1] == 0);
    }

    int size(int ind_start=0)
    {
        int i=ind_start;
        while (i<nmax && number[i]==0) ++i;
        if (i==nmax) return 1;
        return nmax-i;
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

    void out_num() 
    {
        if(sign=='-') cout<<sign;
        for (int i=nmax-len; i<nmax; ++i)
            cout<<number[i];
    }

    int cmp(const Tlong &num1) const
    {
        if (sign!=num1.sign)
        {
            if (sign == '+') return 1;
            return -1;
        }
        if (sign=='+') return cmp_abs(num1);
        return -cmp_abs(num1);
    }

    Tlong operator-() const
    {
        Tlong inverse_num=*this;
        if (is_zero() || sign == '-') inverse_num.sign='+';
        else inverse_num.sign='-';
        return inverse_num;
    }

    Tlong operator+(const Tlong &num) const
    {
        Tlong res;
        if (sign == num.sign)
        {
            res=add_abs(num);
            res.sign=sign;
            return res;
        }
        int compare_abs=cmp_abs(num), compare=cmp(num);
        res=sub_abs(num);
        if (compare*compare_abs == -1) res.sign='-';
        else res.sign='+';
        return res;
    }

    Tlong operator-(const Tlong &num) const
    {
        Tlong res=*this+(-num);
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
            if(is_zero()) sign='+';
        }
        if (i>len) ++len;
        return *this;
    }
    
    Tlong operator*(const Tlong &num)
    {
        Tlong res;
        if (is_zero() || num.is_zero()) return res;
        int S, p=0;
        if (sign==num.sign) res.sign='+';
        else res.sign='-';
        for(int i=1; i<=num.len; ++i)
            for (int j=1; j<=len+1; ++j)
            {
                S=num.number[nmax-i]*number[nmax-j]+p+res.number[nmax+1-i-j];
                p=S/10;
                res.number[nmax+1-i-j]=S%10;
            }
        int length=len+num.len-1;
        if (res.number[nmax-length-1]) ++length;
        res.len=length;
        return res;
    }

    int operator%(long long denominator) const
    {
        return divide_ost(denominator);
    }

    Tlong operator/(int denominator)
    {
        return divide(denominator);
    }

    Tlong& operator*=(const Tlong &num)
    {
        *this=*this*num;
        return *this;
    }

    Tlong& operator+=(const Tlong &num)
    {
        *this=*this+num;
        return *this;
    }
};

Tlong max_pr(int sum)
{
    if (sum==1) return 1;
    int n_2, n_3;
    if (sum%3==0)
    {
        n_2=0;
        n_3=sum/3;
    }
    if (sum%3==1)
    {
        n_2=2;
        n_3=sum/3-1;
    }
    if (sum%3==2)
    {
        n_2=1;
        n_3=sum/3;
    }
    Tlong res(1);
    for(int i=0; i<n_2; ++i)
        res*=2;
    for(int i=0; i<n_3; ++i)
        res*=3;
    return res;
}

int main()
{
    int sum;
    cin>>sum;
    max_pr(sum).out_num();
    return 0;
}