#include <iostream>
#include "DBigInteger.hpp"
using namespace std;
int main(int argc,char *argv[]) {
    DBigInteger a(argv[1]);
    DBigInteger b(argv[2]);
    cout<<a%b;
    return 0;
}