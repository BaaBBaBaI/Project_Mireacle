#include <iostream>
#include "sorts.h"
#include <chrono>
#include <ctime>    

int main() {
    int size = 10; //setsize
    std::cout << "Size of array: " << size << std::endl;
    int arr[size];
    std::cout << "Elements of array are randomly generated between 0 and 1000" << std::endl;
    for (int j = 0; j < size; j++) {
		arr[j] =  1 + rand() % 1000;
	}
    char type;
    std::cout << std::endl << "ChooseSort: B for bubble, I for insertion, S for selection, Q for quick: "; std::cin >> type;
    std::cout << "Unsorted array: \n"; printarr(arr,size); std::cout << "\nSorted array: \n";
    switch (type)
    {
    case 'B': {

        START_TIMER;
	    bubbleSort(arr, size);
	    STOP_TIMER;

	    GET_DUR;
        printarr(arr, size);
	    std::cout << "\n time:" << diff.count() << std::endl;
        return 1;
    }

    case 'I': {

        START_TIMER;
	    insertionSort(arr, size);
	    STOP_TIMER;

	    GET_DUR;
        printarr(arr, size);
	    std::cout << "\n time:" << diff.count() << std::endl;
        return 1;
    }

    case 'S': {

        START_TIMER;
	    selectionSort(arr, size);
	    STOP_TIMER;

	    GET_DUR;
        printarr(arr, size);
	    std::cout << "\n time:" << diff.count() << std::endl;
        return 1;
    }

    case 'Q': {

        START_TIMER;
	    quickSort(arr, size);
	    STOP_TIMER;

	    GET_DUR;
        printarr(arr, size);
	    std::cout << "\n time:" << diff.count() << std::endl;
        return 1;
    }

    default:
        break; 
    }

    return 0;
}