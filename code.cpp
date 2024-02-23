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

void binary_finder(int long long *arr, int long long N, int long long a){
    int long long l = 0, r = N-1;
    while (r > l) {
        int long long m = (l+r)/2;
        if (arr[m] < a) {
            l = m + 1;
        } else if (arr[m] > a) {
            r = m - 1;
        } else {
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

void sort(int long long *arr, int long long N){
for(int long long i = 1; i != N; ++i){
	for(int long long j = 0; j != N-i; ++j){
		if(arr[j] < arr[j+1]){
			int long long temp = arr[j];
			arr[j] = arr[j+1];
			arr[j+1] = temp;
		}
	}
}    

}

void experiment_of_function(int long long N, std::string name, bool arr_sort, bool worst){

    int long long *arr = new int long long[N];

    unsigned long long seed = time(0);
    std:: default_random_engine rng(seed);
    std:: uniform_int_distribution <int long long> dstr(-1e10, 1e10); // пределы целых чисел в массиве - (-1e10, 1e10)
    for (unsigned counter = N; counter != 0; --counter)
        arr[counter] = dstr(rng);
    if (arr_sort){
        sort(arr, N);
    }

    std:: default_random_engine rng0(2*seed);
    std:: uniform_int_distribution <unsigned long long> dstr0(0, N-1);
    for (unsigned counter = 100; counter != 0; --counter){ // делаем по 100 измерений времени
        auto begin = std:: chrono :: steady_clock :: now();
        for (unsigned cnt = 10000000; cnt != 0; --cnt)
        // ========= функция ===================================
            binary_finder(arr, N, arr[dstr0(rng0)]+ worst*3*1e10);
        // =======================================================
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

int long long  N_0 = 1e3; // cоздаём массив длины N
std::string name = "binary_worst.txt";

clean_file(name);
std::ofstream out;
out.open(name, std::ios::app);
out << "N;time" << std:: endl;
out.close(); 

int long long  N = N_0;

for(int i=0; i != 10; ++i){ 
    std::cout << "Начало шага " << i << std::endl;
    experiment_of_function(N, name, 1, 1);
    N += 1e3;
}

return 0;
}