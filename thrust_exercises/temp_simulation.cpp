#include <vector>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>

using namespace std;



vector<float> init_temp_vector(int n){
    auto randnum = [=] (float){
    return 25 + ((rand()/RAND_MAX)*75);
    };

    vector<float> temp_init_values(n);
    transform(temp_init_values.begin(), temp_init_values.end(),temp_init_values.begin(),randnum);

    return temp_init_values;
}

void update_temp(vector<float>& temp_curr){
    int k = 0.5;
    int temp_room = 25;
    auto op = [=] (float& temp_c){ temp_c = temp_c + k*(temp_room - temp_c);};

    transform(temp_curr.begin(),temp_curr.end(),temp_curr.begin(),op);
}

int main(){
    vector<float> temp_values = init_temp_vector(3);

    int iter = 4;

    for(int i = 0; i< iter; i++){
        update_temp(temp_values);
    }


    return 1;

}