#ifndef TLONG_CLASS_H_INCLUDED
#define TLONG_CLASS_H_INCLUDED

#include<string>
#include<iostream>

class Tlong
{
    const static int nmax=100;
    char sign='+';
    int number[nmax]={};
    int len=1;
    void zeroing(int);
    int find_length(int) const;
    int cmp_abs(const Tlong &) const;
    Tlong add_abs(const Tlong &) const;
    Tlong sub_abs(const Tlong &) const;
    Tlong multiply(const Tlong &) const;
public:
    static int get_n_max() {return nmax;}
    Tlong(int);
    Tlong(const std::string&);
    bool is_zero() const;
    int get_length() const;
    int cmp(const Tlong &) const;
    int cmp_with_zero() const;
    bool operator<(const Tlong &) const;
    bool operator==(const Tlong &) const;
    bool operator>(const Tlong &) const;
    bool operator<=(const Tlong &) const;
    bool operator>=(const Tlong &) const;
    bool operator!=(const Tlong &) const;
    int operator[](int) const;
    Tlong operator-() const;
    Tlong operator+(const Tlong &) const;
    Tlong operator-(const Tlong &) const;
    Tlong& operator++();
    Tlong& operator--();
    Tlong operator*(int) const;
    Tlong operator*(const Tlong &) const;
    Tlong operator/(int) const;
    Tlong operator/(const Tlong &) const;
    int operator%(int) const;
    Tlong operator%(const Tlong &) const;
    Tlong& operator*=(const Tlong &);
    Tlong& operator+=(const Tlong &);
    Tlong& operator<<=(int);
    Tlong& operator>>=(int);
    std::string to_string() const;
    long double to_double() const;

    friend std::istream& operator>>(std::istream &in, Tlong &num);
    friend std::ostream& operator<<(std::ostream &out, const Tlong &num);
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

Tlong::Tlong(const std::string& S)
{
    int i=0;
    int length=S.size();
    if (S[0]=='+' || S[0]=='-')
    {
        sign=S[0];
        ++i;
        --length;
    }
    len=length;
    for (; i<len; ++i)
        number[nmax-len+i]=S[i]-48;
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

int Tlong::get_length() const
{
    return len;
}

bool Tlong::operator<(const Tlong &num) const
{
    return cmp(num)==-1;
}

bool Tlong::operator==(const Tlong &num) const
{
    return cmp(num)==0;
}

bool Tlong::operator>(const Tlong &num) const
{
    return cmp(num)==1;
}

bool Tlong::operator<=(const Tlong &num) const
{
    return cmp(num)!=1;
}

bool Tlong::operator>=(const Tlong &num) const
{
    return cmp(num)!=-1;
}

bool Tlong::operator!=(const Tlong &num) const
{
    return cmp(num)!=0;
}

int Tlong::operator[](int ind_dig) const
{
    if(ind_dig>=len) return number[nmax-1];
    if(ind_dig<0) return number[nmax-len];
    return number[nmax-len+ind_dig];
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

Tlong& Tlong::operator++()
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

Tlong& Tlong::operator--()
{
    *this=-(++(-*this));
    return *this;
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

int Tlong::operator%(int denominator) const
{
    denominator=abs(denominator);
    int remaind=0;
    for (int i=nmax-len; i<nmax; ++i)
    {
        remaind=remaind*10+number[i];
        remaind%=denominator;
    }
    if (sign=='-') return -remaind;
    return remaind;
}

Tlong Tlong::operator/(int denominator) const
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
    if(res.is_zero() || sign=='+' && denominator>0 || sign=='-' && denominator<0) return res;
    res.sign='-';
    return res;
}
Tlong Tlong::operator%(const Tlong &denominator) const
{
    Tlong remaind;
    for(int i=len; i>0; --i)
    {
        remaind<<=1;
        remaind.number[nmax-1]=number[nmax-i];
        while(remaind.cmp_abs(denominator)!=-1)
            remaind=remaind.sub_abs(denominator);
    }
    if(remaind.is_zero() || sign=='+') return remaind;
    remaind.sign='-';
    return remaind;
}

Tlong Tlong::operator/(const Tlong &denominator) const
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
    if(res.is_zero() || sign==denominator.sign) return res;
    res.sign='-';
    return res;
}

Tlong& Tlong::operator*=(const Tlong &num)
{
    *this=*this*num;
    return *this;
}

Tlong& Tlong::operator+=(const Tlong &num)
{
    *this=*this+num;
    return *this;
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

Tlong& Tlong::operator>>=(int n_shifts)
{
    for(int i=nmax-1-n_shifts; i>=nmax-len; --i)
        number[i+n_shifts]=number[i];
    for(int i=nmax-len; i<std::min(nmax-len+n_shifts, nmax-1); ++i) number[i]=0;
    len=std::max(1, len-n_shifts);
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
    int length=std::max(len,num.len), S, p=0;
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
    int length=std::max(len,num.len), S, p=0, length_res=1;
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

std::string Tlong::to_string() const
{
    std::string s;
    int i=0;
    if(sign == '-') {s.resize(len+1); s[i++] = sign;}
    else s.resize(len);
    for (int j = nmax-len; j<nmax; ++j)
        s[i++] = number[j] + '0';
    return s;
}

long double Tlong::to_double() const
{
    long double res = 0;
    for(int i=std::min(30, len); i>0; --i)
    {
        res *= 10;
        res += number[nmax-i];
    }
    if(sign == '-') return -res;
    return res;
}

std::istream& operator>>(std::istream &in, Tlong &num)
{
    int i=0;
    std::string S;
    in>>S;
    int length=S.size();
    num.zeroing(Tlong::nmax-length);
    if (S[0]=='+' || S[0]=='-')
    {
        num.sign=S[0];
        ++i;
        --length;
    }
    num.len=length;
    for (; i<num.len; ++i)
        num.number[Tlong::nmax-num.len+i]=S[i]-48;
    return in;
}

std::ostream& operator<<(std::ostream &out, const Tlong &num)
{
    if(num.sign=='-') out<<num.sign;
    for (int i=Tlong::nmax-num.len; i<Tlong::nmax; ++i)
        out<<num.number[i];
    return out;
}

Tlong operator*(int num1, const Tlong& num2)
{
    return num2*num1;
}

Tlong operator+(int num1, const Tlong& num2)
{
    return num2+num1;
}

Tlong pow(int base, int exp)
{
    int exp_len_in_bits=0, copy_exp=exp;
    if(exp==0) exp_len_in_bits=1;
    while(copy_exp)
    {
        ++exp_len_in_bits;
        copy_exp>>=1;
    }
    Tlong res(1);
    for(int i=exp_len_in_bits-1; i>=0; --i)
    {
        res=res*res;
        if(exp>>i&1) res=res*base;
    }
    return res;
}

long double operator+(const long double& a, const Tlong& b) {return a+b.to_double();}
long double operator+(const Tlong& b, const long double& a) {return a+b.to_double();}
long double operator-(const long double& a, const Tlong& b) {return a-b.to_double();}
long double operator-(const Tlong& b, const long double& a) {return b.to_double()-a;}
long double operator*(const long double& a, const Tlong& b) {return a*b.to_double();}
long double operator*(const Tlong& b, const long double& a) {return a*b.to_double();}
long double operator/(const long double& a, const Tlong& b) {return a/b.to_double();}
long double operator/(const Tlong& b, const long double& a) {return b.to_double()/a;}

#endif // TLONG_CLASS_H_INCLUDED
