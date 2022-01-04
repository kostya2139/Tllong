#include <iostream>
#include <algorithm>
using namespace std;

class A
{
    int a;
    int b;
public:
    A (int c=0, int d=0):a(c),b(d){};
    int operator[](int i){if (i==1) return a; return b;}
    void inp() {cin>>a>>b;}
    void out() {cout<<a<<' '<<b<<'\n';}
    static bool (*cmp_i)(A n1, A n2)(int i){return [int i](A n1, A n2){return n1[i]<n2[i];};}
};

class ArrA
{
    A mas[100];
    int n_el;
public:
    void inp(){cin>>n_el; for(int i=0;i<n_el;++i) mas[i].inp();}
    void out(){for(int i=0;i<n_el;++i) mas[i].out();}
    void sort(int i){bool (*cmp)(A n1, A n2)=A::cmp_i(i); sort(mas,mas+n_el,cmp);}
};

int main()
{
    ArrA mas;
    mas.inp();
    mas.sort(1);
    mas.out();
    return 0;
}
