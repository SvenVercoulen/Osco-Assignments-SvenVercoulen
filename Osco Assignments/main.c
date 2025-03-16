#include <stdio.h>

// First approach: Using array size
int countOccurrencesWithSize(int arr[], int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            count++;
        }
    }
    return count;
}

// Second approach: Using sentinel value (-1 as the end marker)
int countOccurrencesWithSentinel(int arr[], int target) {
    int count = 0;
    int i = 0;
    while (arr[i] != -1) {
        if (arr[i] == target) {
            count++;
        }
        i++;
    }
    return count;
}

int main() {
    // Test for size-based approach
    int arr1[] = { 1, 2, 3, 4, 2, 2, 5 ,7 ,7 ,2 ,4 ,7};
    int size = sizeof(arr1) / sizeof(arr1[0]);
    printf("Occurrences of 2 (with size): %d\n", countOccurrencesWithSize(arr1, size, 2));

    // Test for sentinel-based approach
    int arr2[] = { 1, 2, 3, 4, 2, 2, 5, -1 }; // Sentinel value -1 at the end
    printf("Occurrences of 2 (with sentinel): %d\n", countOccurrencesWithSentinel(arr2, 2));

    return 0;
}
