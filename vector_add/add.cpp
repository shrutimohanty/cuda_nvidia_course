#include <stdio.h>
#include <vector>
#include <thread>
#include <cstdlib>
#include <x86intrin.h>
#include <chrono>
#include <iostream>

using namespace std;

int __MFLOPS = 1024*1024;
int __GFLOPS = 1024*1024*1024;

void add_op(const float* A, const float* B, float* C, int start_idx, int stride, int n){
    int i = 0;
    while(start_idx<n && i < stride){
        C[start_idx+i] = A[start_idx+i] + B[start_idx+i];
        i++;
    }
    
}

int main(int argc,char* argv[]){
    int num = atoi(argv[1]);
    int n = num*__GFLOPS; //number of flops = 10^6 FLOPs

    float* A = new float[n];
    float* B = new float[n];
    float* C = new float[n];
    
    //initialize it
    for (int i = 0; i<n; i++){
        A[i] = 1.0f;
        B[i] = 2.0f;
        C[i] = 0.0f;
    }

    int nproc = 64;
    int thread_stride = (n+(nproc - 1))/nproc;

    //create parallel works
    vector<thread> threads;

    auto start_time = chrono::high_resolution_clock::now();
    for(int i = 0; i < nproc; i++){
        int start_idx = i * thread_stride;
        threads.emplace_back(add_op, A, B, C, start_idx, thread_stride, n);
    }

    //join parallel works
    for (auto& t : threads) {
        t.join();
    }

    auto end_time = chrono::high_resolution_clock::now();

    // for (int i = 0; i<n; i++){
    //     printf("C[%d]=%.1f\n", i, C[i]);
    // }

    double ms = chrono::duration<double, milli>(end_time - start_time).count();

    
    cout << "C[0] = " << C[0] << ", C[last] = " << C[n - 1] << "\n";
    cout << "GFLOPs: "<< n/(__GFLOPS);
    cout << " Time taken: " << ms << " ms\n";

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}