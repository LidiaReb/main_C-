#include <iostream>
#include <cmath>
#include <random>

struct DyArray {
    unsigned size;
    unsigned len;
    int *arr;
};

void print(DyArray a){
    std::cout << "Accessible length " << a.len << std:: endl << '[';
    if(a.size != 0) {
        for(int i = 0; i != a.size-1; ++i){
            std::cout << *(a.arr+i) << ", ";
        }
        std::cout << *(a.arr+a.size-1);
    }
    std::cout << ']' << std:: endl;
}

unsigned size_of(DyArray a){
    return a.size;
}

void push(DyArray &a, int elem, int index = -1){
    if(a.size == a.len){
        a.len++;
        int *arr_new = new int[a.len];
        int *copy = a.arr;
        a.arr = arr_new;
        for(int i = 0; i != a.size; i++){
            *(a.arr+i) = *(copy+i);
        }
        delete[] copy;
    }

    if(index == -1){
        *(a.arr+a.size) = elem;
    } else {
        for(int i = a.size; i != index-1; --i){
            *(a.arr+i) = *(a.arr+i-1);
        }
        *(a.arr+index) = elem;
    }
    a.size++;
}

int main(){

DyArray a = {0, 3, new int[3]};

std::cout << size_of(a) << std::endl;

push(a, 5);
push(a, 6);
push(a, 7);

print(a);

push(a, 8, 0);
push(a, 9);

print(a);

return 0;
}