#include <iostream>
#include <omp.h>

using namespace std;

void merge(int *, int, int, int);
void merge_sort(int *arr, int low, int high);

void merge_sort(int *arr, int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_sort(arr, low, mid);
            }
            #pragma omp section
            {
                merge_sort(arr, mid + 1, high);
            }
        }
        merge(arr, low, high, mid);
    }
}

void merge(int *arr, int low, int high, int mid) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int main() {
    omp_set_num_threads(4);
    int myarray[30], num;

    cout << "\nEnter number of elements to be sorted : ";
    cin >> num;

    cout << "\nEnter elements : ";
    for (int i = 0; i < num; i++) {
        cin >> myarray[i];
    }

    #pragma omp parallel
    {
        #pragma omp single
        merge_sort(myarray, 0, num - 1);
    }

    cout << "\nSorted array :" << " ";
    for (int i = 0; i < num; i++) {
        cout << myarray[i] << " ";
    }

    return 0;
}
