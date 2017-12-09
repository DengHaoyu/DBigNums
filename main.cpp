#include <iostream>
#include <string>
#include "DBigInteger.hpp"
using namespace std;
int main() {
    DBigInteger a("78");
    cout<<a.pow(59);
    return 0;
}