//
// Created by dhy on 17-11-19.
//
#include<string>
#include <ostream>
#include <algorithm>
#include <string>

#ifndef DBIGNUMS_DBIGINTEGER_HPP
#define DBIGNUMS_DBIGINTEGER_HPP
using namespace std;
class DBigInteger {
private:
    bool symbol = false;
    string data;
    /*
     * *
     * *
     * returns the length of data except symbol
     *
     */
    int length(){
        return data.size();
    }
public:
//    static const DBigInteger ZERO = DBigInteger("0");
//    static const DBigInteger ONE = DBigInteger("1");
//    static const DBigInteger TEN = DBigInteger("10");
    DBigInteger(string num){
        if(num.size()==0){
            throw length_error("zero length");
        }
        if(num.data()[0]=='-'){
            symbol = true;
            num = num.substr(1);
        }
            data = num;
    }
    DBigInteger(char *n) {
        string num(n);
        if(num.size()==0){
            throw length_error("zero length");
        }
        if(num.data()[0]=='-'){
            symbol = true;
            num = num.substr(1);
        }
        data = num;
    }
    DBigInteger(){
        data = "";
    }
    DBigInteger(int i){
        if(i>=0)this->data = to_string(i);
        else {this->symbol = true;data = to_string(-i);}
    }
    DBigInteger(long long i){
        if(i>=0)this->data = to_string(i);
        else {this->symbol = true;data = to_string(-i);}
    }
    DBigInteger(long i){
        if(i>=0)this->data = to_string(i);
        else {this->symbol = true;data = to_string(-i);}
    }
    DBigInteger add(DBigInteger n){
        DBigInteger bigger = n>*this?n:*this;
        DBigInteger smaller = n>*this?*this:n;
        if(bigger.symbol){
            if(smaller.symbol){
                return (bigger.opposite()+smaller.opposite()).opposite();
            }else{
                return (bigger.opposite()-smaller).opposite();
            }
        }else{
            if(smaller.symbol){
                return bigger-smaller.opposite();
            }
        }
        DBigInteger sum;
        int carry = 0;
        int diff = int(bigger.data.size() - smaller.data.size());
        smaller.data.insert(0,diff,'0');
        for(int i = bigger.data.size()-1;i>=0;--i){
            int res = (bigger[i]+smaller[i]+carry);
            carry = 0;
            if(res>=10){
                sum.data.insert(0,std::to_string(res-10));
                carry = 1;
            }else{
                sum.data.insert(0,to_string(res));
            }
        }
        if(carry==0){ return sum;}else{sum.data.insert(0,to_string(carry));}
        return sum;
    }
    DBigInteger subtract(DBigInteger n){
        if(*this==n)return *new DBigInteger("0");
        if(*this>n){
            if(symbol){
                if(n.symbol){
                    return (n.opposite()-this->opposite());
                }else{
                    return this->opposite()+n;
                }
            }else{
                if(n.symbol){
                    return *this+n.opposite();
                }
            }
        }else{//this<n
            if(symbol){
                if(n.symbol){
                    return (this->opposite()-n.opposite()).opposite();
                }else{
                    return (this->opposite()+n).opposite();
                }
            }else{
                    return (n-*this).opposite();
            }
        }

        int diff = this->length() - n.length();
        DBigInteger sum;
        n.data.insert(0,diff,'0');
        int carry = 0;
        int res = 0;
        for(int i = this->length() - 1;i>=0;i--){
            res = (*this)[i] - n[i] - carry;
            if(res>=0){
                sum.data.insert(0,to_string(res));
                carry = 0;
            }else if(res <0){
                carry = 1;
                sum.data.insert(0,to_string(10+res));
            }
        }
        int i;
        for(i = 0;i<sum.data.size();i++){
            if(sum.data.data()[i]!='0'){
                break;
            }
        }
        sum.data = sum.data.substr(i);
        return sum;
    }
    DBigInteger multiply(DBigInteger n){
        DBigInteger bigger = n>*this?n:*this;
        DBigInteger small = n>*this?*this:n;
        if(bigger.symbol){
            if(small.symbol){
                return bigger.opposite()*small.opposite();
            }else{
                return (bigger.opposite()*small).opposite();
            }
        }else{
            if(small.symbol){
                return (bigger*small.opposite()).opposite();
            }
        }
//        int diff = bigger.length() - small.length();
        int carry = 0;
        int res = 0;
        DBigInteger sum("0");
        DBigInteger temp;
//        small.data.insert(0,diff,'0');
        for(int i = small.length() - 1 ; i >= 0 ; i--){
            for(int j = bigger.length() - 1 ; j >= 0;j--){
                res = small[i] * bigger[j] + carry;
                if(res<10){
                    temp.data.insert(0,to_string(res));
                    carry = 0;
                }else{
                    temp.data.insert(0,to_string(res%10));
                    carry = (res-res%10)/10;
                }
            }
            if(carry!=0){
                temp.data.insert(0,to_string(carry));
            }
            temp.data.append(small.length()-1-i,'0');
            sum = sum.add(temp);
            temp.clear();
            carry = 0;
        }
        return sum;

    }
    DBigInteger divide(DBigInteger n){
        if(*this<n){
            return *new DBigInteger(0);
        }
        if(this->symbol){
            if(n.symbol){
                return this->opposite()/n.opposite();
            }else{
                return (this->opposite()/n).opposite();
            }
        }else{
            if(n.symbol){
                return (*this/n.opposite()).opposite();
            }
        }
        bool notZero = true;
        DBigInteger res(0);
        DBigInteger a = *this;
        while(notZero){
            if((a-n)>=0){
                a = a-n;
                res++;
            }else{
                notZero = false;
            }
        }
        return res;

    }
    DBigInteger mod(DBigInteger n){
        return *this - (*this/n)*n;
    }
    DBigInteger pow(int p){
        DBigInteger res;
        if(*this==1){
            res = 1;
            return res;
        }
        if(p == 0){
            if(*this==0){
                throw new bad_exception;
            }
            res = 0;
        }else if(p<0){
            return 0;
        }
        res = *this;
        for(int i = 1;i<p;i++){
            res *= *this;
        }
        return res;
    }
    DBigInteger opposite(){
        DBigInteger d = *this;
        if(d.symbol == true){
            d.symbol = false;
        }else{
            d.symbol = true;
        }
        return d;
    }
    DBigInteger abs(){
        DBigInteger d(*this);
        d.symbol = false;
        return d;
    }

    DBigInteger operator+(DBigInteger s){
        return add(s);
    }
    void operator++(int){
        *this += *new DBigInteger(1);
    }
    DBigInteger operator-(DBigInteger s){
        return subtract(s);
    }
    void operator-=(DBigInteger s){
        DBigInteger res;
        res = *this-s;
        this->symbol = res.symbol;
        this->data = res.data;
    }
    DBigInteger operator*(DBigInteger s){
        return multiply(s);
    }
    DBigInteger operator/(DBigInteger s){
        return this->divide(s);
    }
    bool operator!=(DBigInteger s) {
        return toStringValue()!=s.toStringValue();
    }
    DBigInteger operator%(DBigInteger s){
        return mod(s);
    }
    bool operator==(DBigInteger s) {
        return toStringValue()==s.toStringValue();
    }
    bool operator==(int p){
        return to_string(p)==this->data;
    }
    void operator+=(DBigInteger s){
        *this = *this+s;
    }
    bool operator>=(DBigInteger s) {
        if(*this>s||*this==s){return true;}
        return false;
    }
    void operator*=(DBigInteger s){
        DBigInteger res = *this;
        res = res * s;
        *this = res;
    }
    bool operator<=(DBigInteger s) {
        if(*this<s||*this==s){return true;}
        return false;
    }

    bool operator>(DBigInteger s) {
        if(symbol){
            if(s.symbol){
                return this->opposite()>s.opposite();
            }else{
                return false;
            }
        }else{
            if(s.symbol)return true;
        }

        if(this->length()>s.length()){
            return true;
        }else if(this->length()<s.length()){
            return false;
        }else{
            return this->toStringValue()>s.toStringValue();
        }
    }

    bool operator<(DBigInteger s){
        if(*this>s){return false;}
        if(*this==s){return false;}
        return true;
    }
     void operator=(DBigInteger s){
        this->symbol = s.symbol;
        this->data = s.data;
    }
     void operator=(int s){
        if(s<=0){
            this->data = to_string(-s);
            this->symbol = true;
            return;
        }
        this->data = to_string(s);
        this->symbol = false;
    }
    int operator[](int i){
        return (int)data.data()[i]-'0';
    }

//    bool operator=(DBigInteger);
    string toStringValue() {
        string a = data;
        if(symbol){
            a.insert(0,"-");
        }
        return a;
    }
    

    void clear(){this->data = "";}

    friend ostream & operator<< (ostream &out,DBigInteger num){
       out<<num.toStringValue();
        return out;
    }
    long long toLongLong(){}
};


#endif //DBIGNUMS_DBIGINTEGER_HPP
