#include <iostream>
#include <cmath>

void print_arr(int *arr, int N){
    int cnul = 0;
    for(int i = N-1; arr[i] == 0; --i){
        cnul++;
    } 
    for(int i= N-1-cnul; i != -1; i--){
        std:: cout << arr[i];
    }
    std:: cout << std::endl;
}

void plas_one(int *arr, int N){
    for(int i=0; i != N; ++i){
        if(arr[i] != 9){
            arr[i]++;
            for(int j=0; j != i; ++j){
                arr[j]=0;
            }
            break;
        }
    }
}

void addition(int *a, int *b, int *c, int N){
    for(int i=0; i != N; i++){
        if(a[i]+b[i] < 10){
            c[i] = a[i]+b[i];
        }else{
            c[i] = a[i]+b[i] - 10;
            a[i+1]++;
        }
    }
}

int main(){

    int n, N, m;
    char c;

    std::cin >> n >> m; 

    if(m > n){
        N = m+1;
    } else {
        N = n+1;
    }

    int *sum = new int[N];
    for(int i=0; i != N; i++){
        sum[i] = 0;}

    int *first = new int[N];
    for(int i=0; i != N; i++){
        first[i] = 0;} 
    int *second = new int[N]; 
    for(int i=0; i != N; i++){
        second[i] = 0;} 

    for(int i=n-1; i != -1; i--){
        std::cin >> c;
        first[i] = c - '0';
    }

    for(int i=m-1; i != -1; i--){
        std::cin >> c;
        second[i] = c - '0';
    }
    std:: cout << "Ввод: " << std::endl;

    print_arr(first, N);
    print_arr(second, N);

    std:: cout <<  "Результат: " << std::endl;

    // plas_one(ptr_arr, N);

    addition(first, second, sum, N);
    print_arr(sum, N);


    return 0;
}