#include <bits/stdc++.h>
using namespace std;

const int nmax=40000;

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

    Tlong& operator=(const Tlong &num)
    {
        sign=num.sign;
        for (int i=nmax-1; i>=nmax-max(len, num.len); --i)
            number[i]=num.number[i];
        len=num.len;
        return *this;
    }

    Tlong operator-() const
    {
        Tlong inverse_num=*this;
        if (len == 1 && number[nmax-1] == 0 || sign == '-') inverse_num.sign='+';
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

    void operator*=(const Tlong &num)
    {
        *this=*this*num;
    }
    void operator+=(const Tlong &num)
    {
        *this=*this+num;
    }
};

/*void inp_2nums(Tlong &num1, Tlong &num2)
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
}*/

Tlong factorial(int n)
{
    Tlong res(1);
    for (int i=2; i<=n; ++i)
    {
        res=res*i;
    }
    return res;
}

Tlong Fibonacci(int n)
{
    Tlong F_n1(1), F_n2(1), temp;
    if (n == 0) return Tlong(0);
    for (int i=2; i<n; ++i)
    {
        temp=F_n2;
        F_n2+=F_n1;
        F_n1=temp;
    }
    return F_n2;
}

Tlong n_permutations(int n_all, int n_permutaion)
{
    Tlong res(1);
    for (int i=n_all-n_permutaion+1; i<=n_all; ++i)
        res*=i;
    return res;
}

int main()
{
    int n_all, n_permutaion;
    cin>>n_permutaion>>n_all;
    n_permutations(n_all, n_permutaion).out_num();
    return 0;
}