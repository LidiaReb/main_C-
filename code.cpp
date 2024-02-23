#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

void liner_finer(int long long *arr, int long long N, int long long a){
    for(int long long i=0; i != N; ++i){
        if(arr[i] == a){
            break;
        }
    }
}

void clean_file(std::string name){
    std::ofstream out;
    out.open(name);
    out << "";
    out.close(); 
}

void experiment_of_function(int long long N, std::string name){

    int long long *arr = new int long long[N];

    unsigned long long seed = time(0);

    std:: default_random_engine rng(seed);
    std:: uniform_int_distribution <int long long> dstr(-1e10, 1e10); // пределы целых чисел в массиве - (-1e10, 1e10)
    for (unsigned counter = N; counter != 0; --counter)
        arr[counter] = dstr(rng);

    // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std:: default_random_engine rng0(2*seed);
    std:: uniform_int_distribution <unsigned long long> dstr0(0, N-1);
    for (unsigned counter = 100; counter != 0; --counter){ // делаем по 100 измерений времени
        int long long find = arr[dstr0(rng0)];
        auto begin = std:: chrono :: steady_clock :: now();
        for (unsigned cnt = 1000; cnt != 0; --cnt)
        // ========= функция ==========
            liner_finer(arr, N, find);
        // ============================
        auto end = std:: chrono :: steady_clock :: now();
        auto time_span = std:: chrono :: duration_cast<std:: chrono :: milliseconds >(end - begin);
        auto time = time_span.count();
            
        std::ofstream out;
        out.open(name, std::ios::app);
        out << N << ";" << time << std:: endl;
        out.close(); 
}

}

int main() {

int long long  N_0 = 1e5; // cоздаём массив длины N
std::string name = "line.txt";

clean_file(name);
std::ofstream out;
out.open(name, std::ios::app);
out << "N;time" << std:: endl;
out.close(); 

for(int i=0; i != 10; ++i){
    int long long  N = N_0*(i+1); 
    experiment_of_function(N, name);
}

return 0;
}