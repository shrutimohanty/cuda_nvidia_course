#include <stdio.h>
#include <vector>
#include <thread>
#include <malloc>

using namespace std;

vector<float> init_vector(int n){
    vector<float> init_values(n);
    for(int i =0; i<n; i++){
        init_values[i] = 1;
    }
    return init_values;
}

void add_op(const float* A, const float* B, float* C, int start_idx, int stride, int n){
    int i = 0;
    while(start_idx<n && i < stride){
        C[start_idx+i] = A[start_idx+i] + B[start_idx+i];
    }
    
}

int main(){
    int n = 1024;

    vector<float> A = malloc(n*(sizeof(float)));
    vector<float> B = malloc(n*(sizeof(float)));
    vector<float> C = malloc(n*(sizeof(float)));

    //initialize it
    for (int i = 0; i<n; i++){
        A[i] = 1;
        B[i] = 2;
        C[i] = 0;
    }

    int nproc = 8;
    int thread_stride = (n+(nproc - 1))/nproc;

    //create parallel works
    vector<thread> threads;
    for(int i = 0; i < nproc; i++){
        int start_idx = i*thread_stride;
        threads.emplace_back(add_op,A,B,C,start_idx,thread_stride,n)
    }

    //join parallel works
    for (auto& t : threads) {
        t.join();
    }

    printf("C[0]=%.1f C[last]=%.1f\n", C.front(), C.back());
    return 1;
}