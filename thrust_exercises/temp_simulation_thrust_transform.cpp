#include <vector>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <iostream>

using namespace std;



thrust::host_vector<float> init_temp_vector(int n){
    auto randnum = [=] __host__(float){
    return 25.0f + ((static_cast<float>(rand())/RAND_MAX)*75.0f);
    };

    thrust::host_vector<float> temp_init_values(n);
    thrust::transform(temp_init_values.begin(), temp_init_values.end(),temp_init_values.begin(),randnum);

    return temp_init_values;
}

void update_temp(vector<float>& temp_curr){
    float k = 0.5f;
    float temp_room = 25.0f;
    auto op = [=] (float& temp_c){ return temp_c + k*(temp_room - temp_c);};

    transform(temp_curr.begin(),temp_curr.end(),temp_curr.begin(),op);
}

int main(){
    thrust::universal_vector<float> temp_values = init_temp_vector(3);

    int iter = 4;

    for(int i = 0; i< iter; i++){
        printf("Current temp vector:");
        for(float x:temp_values){ cout<<x<<" ";}
        cout<<endl;
        update_temp(temp_values);
    }


    return 1;

}