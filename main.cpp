#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Number.h"
#include "BigInt.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
int main(){
    srand (time(NULL));
    clock_t start,finish;
    string a = randomChar(8000);
    string b = randomChar(8000);
    string A,B;
    Number x(a), y(b);
    start= clock();
    A = Mul(a,b);
    finish = clock();// ham đếm thời gian kết thúc
	double durX = (double)(finish - start) / CLOCKS_PER_SEC;
	start= clock();
    B = x.mul(y).getStr();
    finish = clock();
    double durY = (double)(finish - start) / CLOCKS_PER_SEC;
    cout<<A<<endl<<B<<endl<<endl;
    if( A == B ) cout<<"Giong nhau"<<endl;
    else  cout<<"Khong giong nhau"<<endl;
    cout<<endl<<durX<<" "<<durY<<endl;
    //Number a("1000000012300123");
    //cout<<a.size()<<endl;
    //cout<<a.getStr()<<endl;
    //Number x("111111111"),y("999999999");
    //cout<<x.mul(y).getStr()<<endl;


    return 0;
}
