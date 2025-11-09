#include <vector>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>

using namespace std;

float temp_room = 25;
float k = 0.5;

vector<float> init_temp_vector(int n){
    vector<float> temp_init_values(n);
    for(int i =0; i<n; i++){
        temp_init_values[i] = 25.0f + ((static_cast<float>(rand())/RAND_MAX)*75.0f);
    }
    return temp_init_values;
}

auto op = [=] (float temp_c){ 
    float diff = temp_room - temp_c;
    return temp_c + k*(diff);
};


int main(){
    vector<float> temp_values = init_temp_vector(3);

    int iter = 4;

    for(int i = 0; i< iter; i++){
        printf("Current temp vector:");
        for(float x:temp_values){ cout<<x<<" ";}
        cout<<endl;

        transform(temp_values.begin(),temp_values.end(),temp_values.begin(),op);
    }


    return 1;

}