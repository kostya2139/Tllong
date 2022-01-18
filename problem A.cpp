#include <bits/stdc++.h>
using namespace std;

class Tlong
{
public:
    const static int nmax=10000;
    Tlong(int);
    bool is_zero() const;
    int get_length() const;
    int cmp(const Tlong &) const;
    int cmp_with_zero() const;
    Tlong operator-() const;
    Tlong operator+(const Tlong &) const;
    Tlong operator-(const Tlong &) const;
    Tlong operator*(int) const;
    Tlong operator*(const Tlong &) const;
    Tlong operator/(const Tlong &) const;
    Tlong operator%(const Tlong &) const;
    Tlong& operator<<=(int);

    friend istream& operator>>(istream &in, Tlong &num);
    friend ostream& operator<<(ostream &out, const Tlong &num);

private:
    char sign='+';
    int number[nmax]={};
    int len=1;
    void zeroing(int);
    int find_length(int) const;
    Tlong add_abs(const Tlong &) const;
    int cmp_abs(const Tlong &) const;
    Tlong sub_abs(const Tlong &) const;
    Tlong multiply(const Tlong &) const;
    Tlong divide_abs(const Tlong &) const;
    Tlong remaind_abs(const Tlong &denominator) const;
};

Tlong::Tlong(int n=0)
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

int Tlong::cmp(const Tlong &num) const
{
    if (sign!=num.sign)
    {
        if (sign == '+') return 1;
        return -1;
    }
    if (sign=='+') return cmp_abs(num);
    return -cmp_abs(num);
}

int Tlong::cmp_with_zero() const
{
    if (len == 1 && number[nmax-1] == 0) return 0;
    if (sign=='-') return -1;
    return 1;
}

bool Tlong::is_zero()const
{
    return (len == 1 && number[nmax-1] == 0);
}

Tlong Tlong::operator-() const
{
    Tlong inverse_num=*this;
    if (is_zero() || sign == '-') inverse_num.sign='+';
    else inverse_num.sign='-';
    return inverse_num;
}
Tlong Tlong::operator+(const Tlong &num) const
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

Tlong Tlong::operator-(const Tlong &num) const
{
    return *this+(-num);
}

Tlong Tlong::operator*(int num) const
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

Tlong Tlong::operator*(const Tlong &num) const
{
    if(num.len<len) return multiply(num);
    return num.multiply(*this);
}

Tlong Tlong::operator/(const Tlong &denominator) const
{
    Tlong res(divide_abs(denominator));
    if(res.is_zero() || sign==denominator.sign) return res;
    res.sign='-';
    return res;
}

Tlong Tlong::operator%(const Tlong &denominator) const
{
    Tlong res(remaind_abs(denominator));
    if(res.is_zero() || sign=='+') return res;
    res.sign='-';
    return res;
}

Tlong& Tlong::operator<<=(int n_shifts)
{
    if(is_zero()) return *this;
    for(int i=nmax-len; i<nmax; ++i)
        number[i-n_shifts]=number[i];
    for(int i=nmax-n_shifts; i<nmax; ++i) number[i]=0;
    len+=n_shifts;
    return *this;
}

void Tlong::zeroing(int n_end=nmax)
{
    sign='+';
    for (int i=nmax-len; i<n_end; ++i) number[i]=0;
    len=1;
}

int Tlong::find_length(int indent_from_right_edge=nmax) const
{
    int ind_start=nmax-indent_from_right_edge;
    while (ind_start<nmax && number[ind_start]==0) ++ind_start;
    if (ind_start==nmax) return 1;
    return nmax-ind_start;
}

Tlong Tlong::add_abs(const Tlong &num) const
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

int Tlong::cmp_abs(const Tlong &num) const
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

Tlong Tlong::sub_abs(const Tlong &num) const
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

Tlong Tlong::multiply(const Tlong &num) const
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

Tlong Tlong::divide_abs(const Tlong &denominator) const
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

Tlong Tlong::remaind_abs(const Tlong &denominator) const
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

istream& operator>>(istream &in, Tlong &num)
{
    string S;
    in>>S;
    int length=S.size();
    num.zeroing(Tlong::nmax-length);
    if (S[0]=='+' || S[0]=='-')
    {
        num.sign=S[0];
        S.erase(0,1);
        --length;
    }
    num.len=length;
    for (int i=0; i<num.len; ++i)
        num.number[Tlong::nmax-num.len+i]=S[i]-48;
    return in;
}

ostream& operator<<(ostream &out, const Tlong &num)
{
    if(num.sign=='-') out<<num.sign;
    for (int i=Tlong::nmax-num.len; i<Tlong::nmax; ++i)
        out<<num.number[i];
    return out;
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
