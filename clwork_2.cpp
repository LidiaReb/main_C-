#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

void print(int * arr, int N){
    std::cout << "[";
    for(int i = 0; i != N - 1; i++){
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[N-1] << "]" << std::endl << std::endl;
}

void buble_sort(int * arr, int N){
    for(int i = 0; i != N; i++){
        for(int j = 0; j != N-1; j++){
            if(arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

void selection_sort(int * arr, int N){
    for(int i = 0; i != N; i++){
        int min = arr[i], i_min = i;
        for(int j = i; j != N; j++){
            if(arr[j] < min) {
                min = arr[j];
                i_min = j;
            }
        }
        std::swap(arr[i], arr[i_min]);
    }    
}

void insertion_sort(int * arr, int N){
    for(int i = 1; i != N; i++){
        for(int j = i; j != 0; j--){
            if(arr[j-1] > arr[j]) {
                std::swap(arr[j], arr[j-1]);
            }
        }
    }    
}

void quick_sort(int *arr, int l, int r){
    if(l < r){
    int m = (r+l)/2, i_l = l, i_r = r; 
    while(i_l < i_r){
        while(arr[i_l] <= arr[m] && i_l < m) i_l++;
        while(arr[i_r] >= arr[m] && i_r > m) i_r--;
        std::swap(arr[i_l], arr[i_r]);
        if(i_l == m && i_r != m && m != r){
            m++; i_l++;
            std::swap(arr[i_r], arr[m]);
        } 
        if(i_r == m && i_l != m && m != l){
            m--; i_r--;
            std::swap(arr[i_l], arr[m]);
        }
    }
        quick_sort(arr, l, m);
        quick_sort(arr, m+1, r);
    } 
}

// Посмторела в интернете реализацию quicksort, однако всё равно не поняла их олгаримт, написала свой
void quicksort(int *arr, int l, int r){ 
	if(l < r){
		int i_r = r, i_l= l;
        while(i_l < i_r){
            if(arr[i_l] > arr[i_r] && i_l == i_r - 1){
                std::swap(arr[i_l], arr[i_r]);
                i_r--;
            } else if(arr[i_l] > arr[i_r]){
                std::swap(arr[i_r - 1], arr[i_r]);
                std::swap(arr[i_l], arr[i_r]);
                i_r--;
            } else i_l++;
        }
		quicksort(arr, l, i_r - 1);
		quicksort(arr, i_r + 1, r);
	}
}

void merge(int *arr, int n, int N){
    int i_l = 0, i_r = n-1;
    while(i_l < n-1){
        if(arr[i_l] < arr[i_r]) {
            i_l++;
        } else {
            std::swap(arr[i_l], arr[i_r]); 
            i_l++;
            int p=i_r;
            while(arr[p] > arr[p+1]){
                std::swap(arr[p], arr[p+1]);
                p++;
            }       
        }
    }
}

int main(){

int N = 1e2;
int *arr = new int[N];

unsigned seed = std::time(0);
std:: default_random_engine rng(seed);
std:: uniform_int_distribution <int> dstr(-1e3, 1e3); // пределы целых чисел в массиве - (-1e2, 1e2)
for(int i = 0; i != N; i++)
    arr[i] = dstr(rng);

print(arr, N);

// buble_sort(arr, N);

// selection_sort(arr, N);

// insertion_sort(arr, N);

// quick_sort(arr, 0, N-1);

quick_sort(arr, 0, N/2);
quick_sort(arr+N/2-1, 0, N/2);
print(arr, N);
merge(arr, N/2, N);

print(arr, N);

return 0;
}