#include<iostream>

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    int arr[n];
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int max_sum = arr[0];
    int current_sum = arr[0];

    for (int i = 1; i < n; i++) {
        current_sum = std::max(arr[i], current_sum + arr[i]);
        max_sum = std::max(max_sum, current_sum);
    }

    std::cout << "Maximum sum of a subarray: " << max_sum << std::endl;

    return 0;
}