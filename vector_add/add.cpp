#include <stdio.h>
#include <vector>
#include <thread>
#include <cstdlib>

using namespace std;


void add_op(const float* A, const float* B, float* C, int start_idx, int stride, int n){
    int i = 0;
    while(start_idx<n && i < stride){
        C[start_idx+i] = A[start_idx+i] + B[start_idx+i];
        i++;
    }
    
}

int main(){
    int n = 1024;

    float* A = new float[n];
    float* B = new float[n];
    float* C = new float[n];
    
    //initialize it
    for (int i = 0; i<n; i++){
        A[i] = 1.0f;
        B[i] = 2.0f;
        C[i] = 0.0f;
    }

    int nproc = 8;
    int thread_stride = (n+(nproc - 1))/nproc;

    //create parallel works
    vector<thread> threads;
    for(int i = 0; i < nproc; i++){
        int start_idx = i * thread_stride;
        threads.emplace_back(add_op, A, B, C, start_idx, thread_stride, n);
    }

    //join parallel works
    for (auto& t : threads) {
        t.join();
    }

    for (int i = 0; i<n; i++){
        printf("C[%d]=%.1f\n", i, C[i]);
    }
    

    delete[] A;
    delete[] B;
    delete[] C;

    return 1;
}