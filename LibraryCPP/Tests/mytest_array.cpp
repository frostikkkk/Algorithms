#include "lab1.h"
#include <iostream>
#include <cstdio>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout<<"ARGC < 2";
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        std::cout<<"input not open"<<"Home folder is"<<argv[0]<<"trying to open"<<argv[1];
        return 1;
    }

    int size;
    
    Array *arr = array_create_and_read(input);

    int sum = task1(arr, input);

    int expected_sum;
    fscanf(input, "%d", &expected_sum);

    if (sum != expected_sum) {
        array_delete(arr);
        fclose(input);
        std::cout<<"TEST 1 FAIL: expected = "<<expected_sum<<",result = "<<sum;
        return 1;
    }

    Array *expected_result = array_create_and_read(input); 

    size_t result_size;
    Array *result = task2(arr, result_size);

    if (result_size != array_size(expected_result)) {
        std::cout<<"TEST 2 FAIL: expected size = "<<result_size<<",result_size = "<<array_size(expected_result);
        array_delete(arr);
        array_delete(expected_result);
        array_delete(result);
        fclose(input);
        return 1;
    }

    for (size_t i = 0; i < result_size; ++i) {
        if (array_get(result, i) != array_get(expected_result, i)) {
            std::cout<<"TEST 2 FAIL: expected contents for element"<<i<<" = "<<array_get(expected_result, i)<<",result = "<<array_get(result, i);
            array_delete(arr);
            array_delete(expected_result);
            array_delete(result);
            fclose(input);
            return 1;
        }
    }
    array_delete(arr);
    array_delete(expected_result);
    array_delete(result);
    fclose(input);
    return 0;
}
