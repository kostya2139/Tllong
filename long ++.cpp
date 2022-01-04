#include <bits/stdc++.h> 
using namespace std; 
 
const int nmax=1000000; 
 
class Tlong 
{ 
    char sign='+'; 
    short number[nmax]={0}; 
    int len=1; 
 
    void zeroing() 
    { 
        sign='+'; 
        for (int i=nmax-len; i<nmax; ++i) number[i]=0; 
        len=1; 
    } 
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
}; 
 
void out_num(const Tlong &num) 
{ 
    if(num.sign=='-') cout<<num.sign; 
    for (int i=nmax-num.len; i<nmax; ++i) 
        cout<<num.number[i]; 
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
}