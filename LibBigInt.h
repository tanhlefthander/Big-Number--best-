#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;
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
//So sánh
int cmp (string a, string b){ // so sánh 2 số
    // O(n)
    int szA= a.size(), szB= b.size();
    if(szA> szB) return 1;
    if(szA< szB) return -1;
    for( int i=0;i< szA;i++){
        if(a[i]> b[i]) return 1;
        if(a[i]< b[i]) return -1;
    }
    return 0;
}
string divideBy10 (string a){
    if(a.size() <= 1) return string("0");
    return string(a.begin(), a.end()-1);
}
string MulBy10(string a){
    a+='0';
    return a;
}
string randomChar( int length){
    /* initialize random seed: */
    //srand (time(NULL));
    string s;
    while(s.size() != length){
        int x= rand() % 10;
        s+= char(x+ 48);
    }

    if(s[0]=='0') s[0]='1';
    return s;
}
string randomChar( int length, bool b){
    /* initialize random seed: */
    //srand (time(NULL));
    string s;
    while(s.size() != length){
        int x= rand() % 10;
        s+= char(x+ 48);
    }
    if(s[0]=='0') s[0]='1';
    while(s[length-1] % 2 == 0 || s[length-1]=='5'){
        int x= rand() % 10;
        s[length-1]= x+ 48;
    }
    return s;
}
string Add (string a, string b){
    // O(n)
    balance(a,b);
    int sz= a.size(), flag=0;
    for(int i=sz-1; i>=0;i--){
        a[i]= a[i] + b[i] + flag - '0';
        flag =0;
        if(a[i]>'9'){
            flag= 1;
            a[i]-= 10;
        }
    }
    if(flag==1) a = string("1") + a;
    return a;
}
string Sub(string a, string b){ // trừ , mặc định trả về kết quả dương
    // O(n)
    balance(a,b);
    if(a<b) swap(a,b);
    int sz= a.size(), flag=0;
    for(int i=sz-1; i>=0;i--){
        a[i]= a[i] - b[i] - flag + '0';
        flag =0;
        if(a[i]<'0'){
            flag= 1;
            a[i]+= 10;
        }
    }
    int i=0;
    for(; i< sz; i++) if(a[i]!= '0') break;
    if(i == sz) return string("0");
    if(i != 0) return string(a.begin()+i, a.end());
    return a;
}

string MulChar(string a, char c){ // nhân 1 big number với số có 1 chữ số
    // O(n)
    if(c=='0') return string("0");
    if(c=='1') return a;
    int flag= 0;
    for(int i=a.size()-1;i>=0;i--){
        a[i]= (a[i]-'0') * (c - '0') + flag;
        flag =0;
        if(a[i]>= 10){
            flag= a[i]/10;
            a[i]= a[i]%10 + '0';
        }else a[i]+= '0';
    }
    if( flag !=0) a= char(flag + '0') + a;
    return a;
}
string Mul(string a, string b){ // thuật toán nhân
    // O(n*m)
    string kq;
    if(a.size() == 1) return MulChar(b,a[0]);
    if(b.size()== 1 ) return MulChar(a,b[0]);
    kq= Mul(a, divideBy10(b));
    kq= MulBy10(kq); // nhân 10
    kq= Add(kq,MulChar(a,b[b.size()-1]));
    return kq;
}
typedef pair< string , string > QR;
ostream & operator << (ostream &out, QR qr){
    out<<qr.first<<" "<<qr.second;
    return out;
}
QR preDivide(string a, string b) // phép chia nhanh 2 số gần bằng nhau ( a > b và a.size == b.size hoặc a.size == b.size + 1)
{
    // O(n)
    if(b == string("1")) return QR(a,string("0"));
    if(cmp(a,b)==-1) return QR(string("0"),a);
    int A,B;
    if(a.size()==b.size()) A= a[0] - 48;
    else A = (a[0] - 48)*10 + a[1] - 48;
    B= b[0] - 48;
    char c = A/B + 48;
    string r= MulChar(b,c);
    if(cmp(a,r)==-1){
        c--;
        r= Sub(r,b);
    }
    return QR(string()+c, Sub(a,r));
}
QR divide(string a, string b){
    string c, res;
    QR qr;
    for(int i=0;i<a.size();i++){
        if(c == string("0")) c= string();
        c+=a[i];
        qr= preDivide(c,b);
        res+= qr.first[0];
        c= qr.second;
    }
    int i;
    for(i=0;i< res.size()-1;i++)
        if(res[i]!= '0') break;
    if(i != 0) res= string(res.begin()+i,res.end());
    return QR(res,c);
}
string Div(string a, string b){
    string c, res;
    QR qr;
    for(int i=0;i<a.size();i++){
        if(c == string("0")) c.clear();
        c+=a[i];
        qr= preDivide(c,b);
        res+= qr.first[0];
        c= qr.second;
    }
    int i;
    for(i=0;i< res.size()-1;i++)
        if(res[i]!= '0') break;
    if(i != 0) res= string(res.begin()+i,res.end());
    return res;
}
string Mod(string a, string b){
    if(cmp(a,b) == -1) return a;
    string c;
    c.clear();
    for(int i=0;i<a.size();i++){
        if(c == string("0")) c.clear();
        c+=a[i];
        if(c.size() < b.size()) continue;
        c= preDivide(c,b).second;
    }
    return c;
}







