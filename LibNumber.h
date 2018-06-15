#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;

int toInt(string s){
    stringstream ss;
    ss << s;
    int r;
    ss >> r;
    return r;
}
string toString(long x){ //chuyển từ số nguyên sang kiểu string
    stringstream ss;
    ss<<x;
    string res;
    ss>>res;
    return res;
}
void balance (string &a, string &b){ // làm cho 2 số thành cùng size bằng cách thêm những số 0 đàng trc số bé hơn
    int sz_a = a.size(), sz_b= b.size();
    if(sz_a == sz_b) return;
    if(sz_a > sz_b) b= string(sz_a- sz_b,'0') +b;
    else a= string(sz_b- sz_a,'0') +a;
}

