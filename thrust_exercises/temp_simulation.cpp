#include <vector>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>

using namespace std;



vector<float> init_temp_vector(int n){
    auto randnum = [=] (float){
    return 25 + ((rand()/RAND_MAX)*100 );
    };

    vector<float> temp_init_values(n);
    transform(temp_init_values.begin(), temp_init_values.end(),temp_init_values.begin(),randnum);

    return temp_init_values;
}