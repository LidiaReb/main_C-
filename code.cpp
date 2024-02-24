#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

int liner_finder(int long long *arr, int long long N, int long long a){
    for(int long long i=0; i != N; ++i){
        if(arr[i] == a){
            return 0;
        }
    }
    return 0;
}

int binary_finder(int long long *arr, int long long N, int long long a){
    int long long l = 0, r = N-1;
    while (r > l) {
        int long long m = (l+r)/2;
        if (arr[m] < a) {
            l = m + 1;
        } else if (arr[m] > a) {
            r = m - 1;
        } else {
            return 0;
        }
    }
    return 0;
}

int sum(int long long *arr, int long long N, int long long a){
    for(int long long i=0; i != N; ++i){
        for(int long long j=0; j != N; ++j){
            if(arr[i]+arr[j] == a){
                return 0;
            }
        }
    }
    return 0;
}

int sum_sort(int long long *arr, int long long N, int long long a){
    int long long l = 0, r = N-1; 
    while (r > l){
        if (arr[l] + arr[r] < a) {
            l += 1;
        } else if (arr[l] + arr[r] > a) {
            r -= 1;
        } else {
            return 0;
        }
    }
    return 0;
}

void A_strategy(int long long *arr, int long long N, int long long a){
    for(int long long i=0; i != N; ++i){
        if(arr[i] == a){
			arr[i] = arr[0];
			arr[0] = a;
            break;
        }
    }
}

void B_strategy(int long long *arr, int long long N, int long long a){
    for(int long long i=0; i != N; ++i){
        if(arr[i] == a){
            if(i != 0){
                arr[i] = arr[i-1];
                arr[i-1] = a;
            }
            break;
        }
    }
}

void C_strategy(int long long *arr, int long long *k, int long long N, int long long a){
    for(int long long i=0; i != N; ++i){
        if(arr[i] == a){
            k[i]++;
            if(i != 0 && k[i] > k[i-1]){
                arr[i] = arr[i-1];
                arr[i-1] = a;
                int long long temp = k[i];
                k[i] = k[i-1];
                k[i-1] = temp;
            }
            break;
        }
    }
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

int experiment_of_function(int long long N, std::string name, bool arr_sort, bool worst){

    int long long *arr = new int long long[N];

    unsigned long long seed = time(0);
    std:: default_random_engine rng(seed);
    std:: uniform_int_distribution <int long long> dstr(-1e10, 1e10); // пределы целых чисел в массиве - (-1e10, 1e10)
    for (unsigned counter = N-1; counter != 0; --counter)
        arr[counter] = dstr(rng);
    if (arr_sort){
        sort(arr, N);
    }

    std:: default_random_engine rng0(2*seed);
    std:: uniform_int_distribution <unsigned long long> dstr0(0, N-1);
    for (unsigned counter = 100; counter != 0; --counter){ // делаем по 10 измерений времени
        auto begin = std:: chrono :: steady_clock :: now();
        for (unsigned cnt = 10000; cnt != 0; --cnt)
        // ========= функция ===================================
            sum_sort(arr, N, arr[dstr0(rng0)] + arr[dstr0(rng0)] + worst*3*1e10);
        // =======================================================
        auto end = std:: chrono :: steady_clock :: now();
        auto time_span = std:: chrono :: duration_cast<std:: chrono :: milliseconds >(end - begin);
        auto time = time_span.count();
            
        std::ofstream out;
        out.open(name, std::ios::app);
        out << N << ";" << time << std:: endl;
        out.close(); 
    }

    delete [] arr;
    return 0;
}

int experiment_of_function_new(int long long N, std::string name, bool arr_sort, bool worst, bool regular){

    int long long *arr = new int long long[N];
    int long long *k = new int long long[N];

    unsigned long long seed = time(0);
    std:: default_random_engine rng(seed);
    std:: uniform_int_distribution <int long long> dstr(-1e10, 1e10); // пределы целых чисел в массиве - (-1e10, 1e10)
    for (unsigned counter = N-1; counter != 0; --counter)
        arr[counter] = dstr(rng);
    for (unsigned counter = N-1; counter != 0; --counter)
        k[counter] = 0;
    if (arr_sort){
        sort(arr, N);
    }

    std:: default_random_engine rng0(2*seed);
    if(regular){
        std:: uniform_int_distribution <unsigned long long> dstr0(0, N-1);
        for (unsigned counter = 100; counter != 0; --counter){ // делаем по 10 измерений времени
            auto begin = std:: chrono :: steady_clock :: now();
            for (unsigned cnt = 100000; cnt != 0; --cnt)
            // ========= функция ===================================
                C_strategy(arr, k, N, arr[dstr0(rng0)] + worst*3*1e10);
            // =======================================================
            auto end = std:: chrono :: steady_clock :: now();
            auto time_span = std:: chrono :: duration_cast<std:: chrono :: milliseconds >(end - begin);
            auto time = time_span.count();
                
            std::ofstream out;
            out.open(name, std::ios::app);
            out << N << ";" << time << std:: endl;
            out.close(); 
        }
    } else {
        int long long *arr_copy = new int long long[N];
        for (unsigned counter = N-1; counter != 0; --counter)
            arr_copy[counter] = arr[counter];
        sort(arr_copy, N);

        std:: uniform_int_distribution <unsigned long long> dstr0(0, N/5);
        for (unsigned counter = 100; counter != 0; --counter){ // делаем по 100 измерений времени
            auto begin = std:: chrono :: steady_clock :: now();
            for (unsigned cnt = 100000; cnt != 0; --cnt)
            // ========= функция ===================================
                C_strategy(arr, k, N, arr_copy[dstr0(rng0)] + worst*3*1e10);
            // =======================================================
            auto end = std:: chrono :: steady_clock :: now();
            auto time_span = std:: chrono :: duration_cast<std:: chrono :: milliseconds >(end - begin);
            auto time = time_span.count();
                
            std::ofstream out;
            out.open(name, std::ios::app);
            out << N << ";" << time << std:: endl;
            out.close(); 
        }
        delete [] arr_copy;
    }
    delete [] arr;
    delete [] k;
    return 0;
}

int main() {

int long long  N_0 = 1e3; // cоздаём массив длины N
std::string name = "C_ireg.txt";

std::ofstream out;
out.open(name);
out << "N;time" << std:: endl;
out.close(); 

int long long  N = N_0;

for(int i=0; i != 10; ++i){ 
    std::cout << "Начало шага " << i << std::endl;
    experiment_of_function_new(N, name, 0, 0, 0);
    N += N_0;
}

return 0;
}