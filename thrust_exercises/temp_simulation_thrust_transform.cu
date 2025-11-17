#include <iostream>
#include <cstdlib>
#include <thrust/universal_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/transform.h>
#include <cstdio>

using namespace std;

const float temp_room = 25.0f;
const float k = 0.5f;

thrust::universal_vector<float> init_temp_vector(int n){
    thrust::universal_vector<float> temp_init_values(n);
    for(int i =0; i<n; i++){
        temp_init_values[i] = 25.0f + ((static_cast<float>(rand())/RAND_MAX)*75.0f);
    }
    return temp_init_values;
}



int main(){
    thrust::universal_vector<float> temp_values = init_temp_vector(3);

    int iter = 4;

    auto op = [=] __host__ __device__ (float temp_c){ 
        float diff = temp_room - temp_c;
        return temp_c + k*(diff);
    };

    for(int i = 0; i< iter; i++){
        cout << "Current temp vector: ";
        for(float x: temp_values){ cout<<x<<" ";}
        cout<<endl;

        thrust::transform(thrust::device,temp_values.begin(),temp_values.end(),temp_values.begin(),op);
    }


    return 0;

}