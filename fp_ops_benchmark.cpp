#include <stdio.h>
#include <chrono>
#include <vector>
#include <random>

int main() {
    
    float sum = 0.f;
    float prod = 1.f;
    std::vector<float> number_container;
    int num_nums = 1000000000;
    number_container.reserve(num_nums);

    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0, 1.0);

    // generate inputs for benchmark
    for (int i = 0; i < num_nums; i++) {
        number_container.push_back(distribution(generator));
    }

    const auto nums = number_container;

    // computes addition 
    auto begin = std::chrono::high_resolution_clock::now();
//#pragma clang loop vectorize_width(8) //interleave_count(2)
    for (int i = 0; i < num_nums; i++) {
        sum += nums[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Sum is %.3f .\n", sum);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    
    // computes multiplication 
    begin = std::chrono::high_resolution_clock::now();
//#pragma clang loop vectorize_width(8) //interleave_count(2)
    for (int i = 0; i < num_nums; i++) {
        prod *= nums[i];
    }
    //prod = 1.f;

    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Prod is %.3f .\n", prod);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
}
