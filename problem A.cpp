#include <bits/stdc++.h>
using namespace std;

const int nmax=10000;

class Tlong
{
    char sign='+';
    int number[nmax]={};
    int len=1;

    void zeroing(int n_end=nmax)
    {
        sign='+';
        for (int i=nmax-len; i<n_end; ++i) number[i]=0;
        len=1;
    }

    int find_length(int indent_from_right_edge=nmax) const
    {
        int ind_start=nmax-indent_from_right_edge;
        while (ind_start<nmax && number[ind_start]==0) ++ind_start;
        if (ind_start==nmax) return 1;
        return nmax-ind_start;
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

    Tlong half_divide_abs(int denominator) const
    {
        Tlong res;
        denominator=abs(denominator);
        int remaind=0;
        for (int i=nmax-len; i<nmax; ++i)
        {
            remaind*=10;
            remaind+=number[i];
            res.number[i]=remaind/denominator;
            remaind%=denominator;
        }
        res.len=res.find_length(len);
        return res;
    }

    int half_divide_ost_abs(int denominator) const
    {
        denominator=abs(denominator);
        int remaind=0;
        for (int i=nmax-len; i<nmax; ++i)
        {
            remaind=remaind*10+number[i];
            remaind%=denominator;
        }
        return remaind;
    }

    Tlong multiply(const Tlong &num) const
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

    Tlong divide_abs(const Tlong &denominator) const
    {
        Tlong remaind;
        Tlong res;
        int dig=0;
        for(int i=len; i>0; --i)
        {
            remaind<<=1;
            remaind.number[nmax-1]=number[nmax-i];
            while(remaind.cmp_abs(denominator)!=-1)
            {
                remaind=remaind.sub_abs(denominator);
                ++dig;
            }
            res.number[nmax-i]=dig;
            dig=0;
        }
        if(len<=denominator.len)
        {
            res.len=1;
            return res;
        }
        res.len=len-denominator.len;
        if (res.number[nmax-res.len-1]) ++res.len;
        return res;
    }

    Tlong remaind_abs(const Tlong &denominator) const
    {
        Tlong remaind;
        for(int i=len; i>0; --i)
        {
            remaind<<=1;
            remaind.number[nmax-1]=number[nmax-i];
            while(remaind.cmp_abs(denominator)!=-1)
                remaind=remaind.sub_abs(denominator);
        }
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

    int get_length() const
    {
        return len;
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

    int cmp_with_zero() const
    {
        if (sign=='-') return -1;
        if (is_zero()) return 0;
        return 1;
    }

    bool operator<(const Tlong &num) const
    {
        return cmp(num)==-1;
    }

    bool operator==(const Tlong &num) const
    {
        return cmp(num)==0;
    }

    bool operator>(const Tlong &num) const
    {
        return cmp(num)==1;
    }

    bool operator<=(const Tlong &num) const
    {
        return cmp(num)!=1;
    }

    bool operator>=(const Tlong &num) const
    {
        return cmp(num)!=-1;
    }

    bool operator!=(const Tlong &num) const
    {
        return cmp(num)!=0;
    }

    /*int operator[](int n_dig) const
    {
        return number[nmax-len-1+n_dig];
    }*/

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
        return *this+(-num);
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
            if (i>len) ++len;
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
            len=find_length(len);
        }
        return *this;
    }

    Tlong& operator--()
    {
        *this=-(++(-*this));
        return *this;
    }

    Tlong operator*(int num) const
    {
        Tlong res;
        if (is_zero() || num==0) return res;
        int S, p=0;
        if (sign=='+' && num>0 || sign=='-' && num<0) res.sign='+';
        else res.sign='-';
        for(int i=1; i<=len+11; ++i)
        {
            S=num*number[nmax-i]+p;
            p=S/10;
            res.number[nmax-i]=S%10;
        }
        res.len=res.find_length(len+11);
        return res;
    }

    Tlong operator*(const Tlong &num) const
    {
        if(num.len<len) return multiply(num);
        return num.multiply(*this);
    }

    int operator%(int denominator) const
    {
        int ost=half_divide_ost_abs(denominator);
        if (sign=='-') return -ost;
        return ost;
    }

    Tlong operator/(int denominator) const
    {
        Tlong res(half_divide_abs(denominator));
        if(res.is_zero() || sign=='+' && denominator>0 || sign=='-' && denominator<0) return res;
        res.sign='-';
        return res;
    }

    Tlong operator/(const Tlong &denominator) const
    {
        Tlong res(divide_abs(denominator));
        if(res.is_zero() || sign==denominator.sign) return res;
        res.sign='-';
        return res;
    }

    Tlong operator%(const Tlong &denominator) const
    {
        Tlong res(remaind_abs(denominator));
        if(res.is_zero() || sign=='+') return res;
        res.sign='-';
        return res;
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

    Tlong& operator<<=(int n_shifts)
    {
        if(is_zero()) return *this;
        for(int i=nmax-len; i<nmax; ++i)
            number[i-n_shifts]=number[i];
        for(int i=nmax-n_shifts; i<nmax; ++i) number[i]=0;
        len+=n_shifts;
        return *this;
    }

    Tlong& operator>>=(int n_shifts)
    {
        for(int i=nmax-1-n_shifts; i>=nmax-len; --i)
            number[i+n_shifts]=number[i];
        for(int i=nmax-len; i<min(nmax-len+n_shifts, nmax-1); ++i) number[i]=0;
        len=max(1, len-n_shifts);
        return *this;
    }

    friend istream& operator>>(istream &in, Tlong &num);

    friend ostream& operator<<(ostream &out, const Tlong &num);
};

istream& operator>>(istream& in, Tlong &num)
{
    string S;
    in>>S;
    int length=S.size();
    num.zeroing(nmax-length);
    if (S[0]=='+' || S[0]=='-')
    {
        num.sign=S[0];
        S.erase(0,1);
        --length;
    }
    num.len=length;
    for (int i=0; i<num.len; ++i)
        num.number[nmax-num.len+i]=S[i]-48;
    return in;
}

ostream& operator<<(ostream &out, const Tlong &num)
{
    if(num.sign=='-') out<<num.sign;
    for (int i=nmax-num.len; i<nmax; ++i)
        out<<num.number[i];
    return out;
}

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

void print_math_problem(const Tlong &a, const Tlong &b, char sign)
{
    cout<<a<<sign;
    if(b.cmp_with_zero()==-1) cout<<'('<<b<<')';
    else cout<<b;
    cout<<'=';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Tlong a, b; int c;
    cin>>a>>b>>c;
    print_math_problem(a, b, '+');
    cout<<a+b<<'\n';
    print_math_problem(a, b, '-');
    cout<<a-b<<'\n';
    print_math_problem(a, b, '*');
    cout<<a*b<<'\n';
    if(b.cmp_with_zero())
    {
        print_math_problem(a, b, '/');
        cout<<a/b<<" ("<<a%b<<")\n";
    }
    else cout<<"Division by zero.\n";
    cout<<c<<"!="<<factorial(c);
    return 0;
}
