/*
 * email: 
 * File: main.cpp
 */
#include <iostream>
#include "ac/MyContainer.hpp"
int main(){
    ac::MyContainer<int> c;
    for(int v: {7,15,6,1,2}) c.add(v);
    std::cout<<"Container: "<<c<<"\nAscending: ";
    for(auto it=c.beginAscending(); it!=c.endAscending(); ++it) std::cout<<*it<<" ";
    std::cout<<"\nDescending: ";
    for(auto it=c.beginDescending(); it!=c.endDescending(); ++it) std::cout<<*it<<" ";
    std::cout<<"\nSideCross: ";
    for(auto it=c.beginSideCross(); it!=c.endSideCross(); ++it) std::cout<<*it<<" ";
    std::cout<<"\nReverse: ";
    for(auto it=c.rbegin(); it!=c.rend(); ++it) std::cout<<*it<<" ";
    std::cout<<"\nMiddleOut: ";
    for(auto it=c.beginMiddle(); it!=c.endMiddle(); ++it) std::cout<<*it<<" ";
    std::cout<<"\n";
    return 0;
}
