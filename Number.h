#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
/**
eg: string s = "1234567890";
    if BASE = 3;
        => v={890, 567, 234, 1};
**/
const int BASE = 9; // 10^BASE

class Number{

private:

    vector< long long int > v;

    long long int toInt(string s){
        stringstream ss;
        ss << s;
        long long int r;
        ss >> r;
        return r;
    }

    string toString(long long int x){ //chuyển từ số nguyên sang kiểu string
        stringstream ss;
        ss<<x;
        string res;
        ss>>res;
        return res;
    }

    void stand(){ // xoá thành phần 0 dư thừa
        while(v.back()==0 && v.size() != 1)
            v.pop_back();
    }

public:

    Number(){
        v.push_back(0);
    }

    Number(string s){
        setStr(s);
    }
    void setStr(string s){
        string x;
        for(int i=s.size();i>0;i-=BASE){
            int b = i-BASE;
            if(b<0)
                b=0;
            x= string(s.begin()+ b, s.begin()+i);
            v.push_back(toInt(x));
        }
        stand();
    }

    int size(){
        return v.size();
    }

    void printf(){
        cout<<"{";
        for(int i=0;i<v.size();i++)
            cout<<v[i]<<" ";
        cout<<"}";
    }

    string getStr(){
        string r,x;
        for(int i=v.size()-1;i>=0;i--){
            x= toString(v[i]);
            if(i!= v.size() -1 ) x= string(BASE-x.size(),'0').append(x);
            r.append(x);
        }
        return r;
    }

    int cmp(Number n){
        if(size() > n.size()) return 1;
        if(size() < n.size()) return -1;
        for(int i=size()-1;i>=0;i--){
            if(v[i]>n.v[i]) return 1;
            if(v[i]<n.v[i]) return -1;
        }
        return 0;
    }

    Number add(Number n){
        // câm bằng băng cách resize sẽ tạo thêm nhưng phần tử mới = 0
        vector< long long int > t = v; //copy
        if(size() > n.size()) n.v.resize(size());
        else t.resize(n.size());
        long long int base = pow(10,BASE),flat = 0;
        //cout<<base<<endl;
        for(int i=0;i<n.size();i++){
            n.v[i]= n.v[i] + t[i] + flat;
            flat = 0;
            if(n.v[i]>= base){
                n.v[i]-=base;
                flat = 1;
            }
        }
        if(flat == 1) n.v.push_back(1);
        //n.printf();
        //cout<<endl<<n.getStr()<<endl;
        return n;
    }

    Number sub(Number n){ // mặc định là lớn trừ bé
        n.v.resize(size());
        long long int base = pow(10,BASE),flat = 0;
        for(int i=0;i<n.size();i++){
            n.v[i]= v[i] - n.v[i] - flat;
            flat = 0;
            if(n.v[i] < 0){
                n.v[i]+=base;
                flat = 1;
            }
        }
        n.stand();
        return n;
    }

    Number mul(int n){
        if(n==0) return Number();
        Number t;
        t.v= v;
        long long int base = pow(10,BASE),flat = 0;
        //cout<<t.size()<<endl;
        for(int i=0;i<t.size();i++){
            //cout<<i<<endl;
            t.v[i]= t.v[i]*n + flat;
            flat = 0;
            if(t.v[i]>= base){
                flat = t.v[i] / base;
                t.v[i]= t.v[i] % base;
            }
        }
        //t.printf();
        if(flat > 0) t.v.push_back(flat);
        //n.printf();
        //cout<<endl<<n.getStr()<<endl;
        return t;
    }
    long long int divBase(){ // chia cho base trả về số dư
        long long int r = v[0];
        if(v.size()==1) v[0] = 0;
        else v.erase(v.begin());
        return r;
    }
    void mulBASE(){
        v.insert(v.begin(),0);
        stand();
    }
    Number mul (Number n){
        // a,b cùng hệ base => a*b = base * a * (b/base) + a*(b%base)
        if(n.size() == 1) return mul(n.v[0]);
        long long int d = n.divBase(); // n /= BASE;
        //cout<<"d: "<<d<<endl;
        Number r = mul(n);
        //cout<<"r: "<<r.getStr()<<endl;
        r.mulBASE();
        //cout<<"r: "<<r.getStr()<<endl;
        //cout<<d<<endl;
        //cout<<mul(d).getStr()<<endl;
        r = r.add(mul(d));
        //cout<<"r: "<<r.getStr()<<endl;
        return r;
    }
};
