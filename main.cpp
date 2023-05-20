#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "max_min_heap.h"

int main(int argc, char *argv[])
{
    std::vector<int> inputs;
    std::string file_path;
    std::ifstream streamed_file;

    std::cout << "Welcome to Max-Min-Heap CLI!!" << std::endl;
    int tmp_single_value;
    char option;

    while (true)
    {
        std::cout << "Enter the file path for heap values: " << std::endl;
        std::cin >> file_path;

        streamed_file.open(file_path);

        if (!streamed_file.is_open())
        {
            std::cout << "Failed to open this file! Try Again!" << std::endl;
            continue;
        }

        while (streamed_file >> tmp_single_value)
        {
            inputs.push_back(tmp_single_value);
        }
        streamed_file.close();

        Max_Min_Heap *max_min_heap = new Max_Min_Heap();
        max_min_heap->Build_Heap(inputs);

        while (true)
        {
            std::cout << "\nPlease select an option: \n";

            std::cout << "(1) for heap insert \n";
            std::cout << "(2) for heap delete \n";
            std::cout << "(3) for heap extract max \n";
            std::cout << "(4) for heap extract min \n";
            std::cout << "(5) for heap sort \n";
            std::cout << "(6) for printing the heap \n";
            std::cout << "(7) for printing heap size \n";
            std::cout << "(8) for building new heap \n";
            std::cout << "(9) exit program \n";

            std::cin >> option;

            switch (option)
            {
            case '1':
                std::cout << "Insert the key you want to add: \n";
                std::cin >> tmp_single_value;
                max_min_heap->Heap_Insert(tmp_single_value);
                break;
            case '2':
                std::cout << "Insert the index you want to delete: \n";
                std::cin >> tmp_single_value;
                max_min_heap->Heap_Delete(tmp_single_value);
                break;
            case '3':
                max_min_heap->Heap_Extract_Max();
                break;
            case '4':
                max_min_heap->Heap_Extract_Min();
                break;
            case '5':
                max_min_heap->Heap_sort();
                break;
            case '6':
                max_min_heap->Print();
                break;
            case '7':
                std::cout << "heap size is ";
                std::cout << max_min_heap->get_heap_size() << std::endl;
                break;
            case '8':
                goto exit_inner_loop;
            case '9':
                std::cout << "\nGood Bye!\n";
                exit(0);
            default:
                std::cout << "You did not choose a number between 1-6. \n";
                break;
            }
        }
    exit_inner_loop:
        delete max_min_heap;
    }
    return 0;
}