#include <iostream>
#include "ListElement.cpp"
using namespace std;

void l_init();

int main(){
    l_init();
    return 0;
}

void l_init(ListElementInfo &list_info){
    list_info.head = NULL;
    list_info.tail = NULL;
    list_info.count = 0;
}