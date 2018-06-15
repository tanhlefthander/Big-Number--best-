#pragma once
#include <iostream>
#include <string>
#include "LibBigInt.h"
using namespace std;
// Số lơn dương
class BigInt {
private:
    string b;
public:
    BigInt(){
        b="0";
    };
    BigInt(string x){
        b= x;
    }
    BigInt(long x){
        b= toString(x);
    }
    friend ostream & operator << (ostream & out , BigInt &x){
        out<<x.b;
        return out;
    }
    bool operator > (BigInt x){
        if(cmp(b,x.b)==1) return true;
        return false;
    }
    bool operator < (BigInt x){
        if(cmp(b,x.b)==-1) return true;
        return false;
    }
    bool operator == (BigInt x){
        if(cmp(b,x.b)==0) return true;
        return false;
    }
    bool operator != (BigInt x){
        if(cmp(b,x.b)!=0) return true;
        return false;
    }
    BigInt operator - (BigInt x){
        return BigInt(Sub(b,x.b));
    }
    BigInt operator + (BigInt x){
        return BigInt(Add(b,x.b));
    }
    void operator += (BigInt x){
        b=Add(b,x.b);
    }
    BigInt operator * (BigInt x){
        return BigInt(Mul(b,x.b));
    }
    BigInt operator / (BigInt x){
        return BigInt(Div(b,x.b));
    }
    BigInt operator % (BigInt x){
        return BigInt(Mod(b,x.b));
    }
    int size(){
        return b.size();
    }
    char operator [] (int p){
        return b[p];
    }
    void random(int length){
        b =randomChar(length);
    }
    void randomOdd(int length){
        b =randomChar(length,1);
    }
};




