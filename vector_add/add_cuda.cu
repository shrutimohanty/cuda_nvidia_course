#include <stdio.h>
#include <vector>
#include <thread>
#include <cstdlib>
#include <x86intrin.h>
#include <chrono>
#include <iostream>
#include <cuda_runtime.h>


using namespace std;

int __MFLOPS = 1024*1024;
int __GFLOPS = 1024*1024*1024;

__global__ void add_op(const float* A, const float* B, float* C, int n){
    int i = 0;
    while(i < n){ //boundry check
        C[i] = A[i] + B[i];
    }
    
}

int main(int argc,char* argv[]){
    int num = atoi(argv[1]);
    // int n = num*__GFLOPS; //number of flops = 10^9 FLOPs
    int n = num*__MFLOPS; //number of flops = 10^9 FLOPs


    float* A = new float[n];
    float* B = new float[n];
    float* C = new float[n];
    
    //initialize it
    for (int i = 0; i<n; i++){
        A[i] = 1.0f;
        B[i] = 2.0f;
        C[i] = 0.0f;
    }

    auto start_time = chrono::high_resolution_clock::now();
    //alloc mem in GPU dev
    float* dA,dB,dC;
    int arr_size = n * sizeof(float);
    cudaMalloc(&dA,arr_size);
    cudaMalloc(&dB,arr_size);
    cudaMalloc(&dC,arr_size);

    //copy data into the memory
    cudaMemcpy(dA,A,arr_size,cudaMemcpyHostToDevice);
    cudaMemcpy(dB,B,arr_size,cudaMemcpyHostToDevice);

   

    int block = 256;
    int grid = static_cast<int>((n+block-1)/block);

    add_op<<<grid,block>>>(dA,dB,dC,n);

    //copy result back from device to host
    cudaMemcpy(C,dC,arr_size,cudaMemcpyDeviceToHost);
    
    auto end_time = chrono::high_resolution_clock::now();

    // for (int i = 0; i<n; i++){
    //     printf("C[%d]=%.1f\n", i, C[i]);
    // }

    double ms = chrono::duration<double, milli>(end_time - start_time).count();

    
    cout << "C[0] = " << C[0] << ", C[last] = " << C[n - 1] << "\n";
    cout << "MFLOPs: "<< n/(__MFLOPS);
    cout << " Time taken: " << ms << " ms\n";

    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dC);
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}