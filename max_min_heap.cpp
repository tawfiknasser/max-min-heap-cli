#include "max_min_heap.h"
#include <vector>
#include <cmath>
#include <unistd.h>
#include <iostream>

Max_Min_Heap::Max_Min_Heap()
{
    Max_Min_Heap::heap_root = new std::vector<int>();
}

Max_Min_Heap::~Max_Min_Heap()
{
    delete heap_root;
}

inline int Max_Min_Heap::get_heap_size()
{
    return heap_root->size();
}

void Max_Min_Heap::Heapify(int index)
{
    if (!has_left_child(index) && !has_right_child(index))
        return;

    int swap_index;
    if (is_max_level(index))
    {
        swap_index = get_largest_child_or_grandchild(index);
        if (has_parent(index) && has_parent(get_parent(index)) && get_grandparent(swap_index) == index)
        {
            if (heap_root->at(swap_index) > heap_root->at(index))
            {
                std::swap(heap_root->at(swap_index), heap_root->at(index));
                if (heap_root->at(swap_index) < heap_root->at(get_parent(swap_index)))
                {
                    std::swap(heap_root->at(swap_index), heap_root->at(get_parent(swap_index)));
                }
                Heapify(swap_index);
            }
        }
        else if (heap_root->at(swap_index) > heap_root->at(index))
        {
            std::swap(heap_root->at(swap_index), heap_root->at(index));
        }
    }
    else
    {
        swap_index = get_smallest_child_or_grandchild(index);
        if (has_parent(index) && has_parent(get_parent(index)) && get_grandparent(swap_index) == index)
        {
            if (heap_root->at(swap_index) < heap_root->at(index))
            {
                std::swap(heap_root->at(swap_index), heap_root->at(index));
                if (heap_root->at(swap_index) > heap_root->at(get_parent(swap_index)))
                {
                    std::swap(heap_root->at(swap_index), heap_root->at(get_parent(swap_index)));
                }
                Heapify(swap_index);
            }
        }
        else if (heap_root->at(swap_index) < heap_root->at(index))
        {
            std::swap(heap_root->at(swap_index), heap_root->at(index));
        }
    }
}

/**
 * Using Floyd algorithm. bottom to top heapify.
 */
void Max_Min_Heap::Build_Heap(std::vector<int> &heap)
{
    heap_root = &heap;
    int heap_size = heap.size();
    Print();

    std::swap((*heap_root)[1], (*heap_root)[2]);

    for (auto i = std::floor(heap_size / 2) - 1; i >= 0; i--)
    {
        Heapify(i);
    }

    if (DEBUG)
        Print();
}

void Max_Min_Heap::Print()
{
    std::cout << "\nPrinting heap: \n";
    for (auto num : *heap_root)
    {
        std::cout << num << ",";
    }
    std::cout << std::endl;
}

bool Max_Min_Heap::is_max_level(int index)
{
    return get_level(index) % 2 == 0;
}

inline int Max_Min_Heap::get_level(int index)
{
    return std::floor(log2(index + 1));
}

inline int Max_Min_Heap::get_left_index(int index)
{
    return (2 * index + 1);
}

inline int Max_Min_Heap::get_right_index(int index)
{
    return (2 * index + 2);
}

bool Max_Min_Heap::has_left_child(int index)
{
    return get_left_index(index) < get_heap_size();
}

bool Max_Min_Heap::has_right_child(int index)
{
    return get_right_index(index) < get_heap_size();
}

int Max_Min_Heap::get_smallest_child_or_grandchild(int index)
{
    int smallest_index = index;

    /** direct children. left and right */
    if (has_left_child(index) && heap_root->at(get_left_index(index)) < heap_root->at(smallest_index))
        smallest_index = get_left_index(index);

    if (has_right_child(index) && heap_root->at(get_right_index(index)) < heap_root->at(smallest_index))
        smallest_index = get_right_index(index);

    /** grand children of left. left left and left right */
    if (has_left_child(index) && has_left_child(get_left_index(index)) && heap_root->at(get_left_index(get_left_index(index))) < heap_root->at(smallest_index))
        smallest_index = get_left_index(get_left_index(index));

    if (has_left_child(index) && has_right_child(get_left_index(index)) && heap_root->at(get_right_index(get_left_index(index))) < heap_root->at(smallest_index))
        smallest_index = get_right_index(get_left_index(index));

    /** grand children of right. right left and right right */
    if (has_right_child(index) && has_left_child(get_right_index(index)) && heap_root->at(get_left_index(get_right_index(index))) < heap_root->at(smallest_index))
        smallest_index = get_left_index(get_right_index(index));

    if (has_right_child(index) && has_right_child(get_right_index(index)) && heap_root->at(get_right_index(get_right_index(index))) < heap_root->at(smallest_index))
        smallest_index = get_right_index(get_right_index(index));

    return smallest_index;
}

int Max_Min_Heap::get_largest_child_or_grandchild(int index)
{
    int largest_index = index;

    /** direct children. left and right */
    if (has_left_child(index) && heap_root->at(get_left_index(index)) > heap_root->at(largest_index))
        largest_index = get_left_index(index);

    if (has_right_child(index) && heap_root->at(get_right_index(index)) > heap_root->at(largest_index))
        largest_index = get_right_index(index);

    /** grand children of left. left left and left right */
    if (has_left_child(index) && has_left_child(get_left_index(index)) && heap_root->at(get_left_index(get_left_index(index))) > heap_root->at(largest_index))
        largest_index = get_left_index(get_left_index(index));

    if (has_left_child(index) && has_right_child(get_left_index(index)) && heap_root->at(get_right_index(get_left_index(index))) > heap_root->at(largest_index))
        largest_index = get_right_index(get_left_index(index));

    /** grand children of right. right left and right right */
    if (has_right_child(index) && has_left_child(get_right_index(index)) && heap_root->at(get_left_index(get_right_index(index))) > heap_root->at(largest_index))
        largest_index = get_left_index(get_right_index(index));

    if (has_right_child(index) && has_right_child(get_right_index(index)) && heap_root->at(get_right_index(get_right_index(index))) > heap_root->at(largest_index))
        largest_index = get_right_index(get_right_index(index));

    return largest_index;
}

int Max_Min_Heap::get_parent(int index)
{
    int possible_parent = (index - 1) / 2;

    assert((possible_parent >= 0) && "no parent");

    return possible_parent;
}

inline bool Max_Min_Heap::has_parent(int index)
{
    return index > 0;
}

int Max_Min_Heap::get_grandparent(int index)
{
    return get_parent(get_parent(index));
}

void Max_Min_Heap::bubble_up(int index)
{
    if (index == 0)
        return;

    if (is_max_level(index))
    {
        if (heap_root->at(index) < heap_root->at(get_parent(index)))
        {
            std::swap(heap_root->at(index), heap_root->at(get_parent(index)));
            bubble_up_min(get_parent(index));
        }
        else
        {
            bubble_up_max(index);
        }
    }
    else
    {
        if (heap_root->at(index) > heap_root->at(get_parent(index)))
        {
            std::swap(heap_root->at(index), heap_root->at(get_parent(index)));
            bubble_up_max(get_parent(index));
        }
        else
        {
            bubble_up_min(index);
        }
    }
}

void Max_Min_Heap::bubble_up_max(int index)
{
    if (!has_parent(index) || !has_parent(get_parent(index)))
        return;

    if (heap_root->at(index) <= heap_root->at(get_parent(get_parent(index))))
        return;

    std::swap(heap_root->at(index), heap_root->at(get_parent(get_parent(index))));
    bubble_up_max(get_parent(get_parent(index)));
}

void Max_Min_Heap::bubble_up_min(int index)
{
    if (!has_parent(index) || !has_parent(get_parent(index)))
        return;

    if (heap_root->at(index) >= heap_root->at(get_parent(get_parent(index))))
        return;

    std::swap(heap_root->at(index), heap_root->at(get_parent(get_parent(index))));
    bubble_up_min(get_parent(get_parent(index)));
}

void Max_Min_Heap::Heap_Insert(const int value)
{
    heap_root->push_back(value);
    bubble_up(heap_root->size() - 1);
}

void Max_Min_Heap::Heap_Delete(const int index)
{
    validate_index(index);
    std::swap(heap_root->at(heap_root->size() - 1), heap_root->at(index));
    heap_root->pop_back();
    Heapify(index);
}

void Max_Min_Heap::Heap_Extract_Max()
{
    if (heap_root->size() > 0)
        Heap_Delete(0);
}

void Max_Min_Heap::Heap_Extract_Min()
{
    if (heap_root->size() == 0)
        return;

    if (heap_root->size() == 1)
    { /* special case heap with only one node */
        Heap_Extract_Max();
        return;
    }

    int min_index = get_left_index(0);

    if (has_right_child(0) && heap_root->at(get_right_index(0)) >= heap_root->at(get_left_index(0)))
    {
        min_index = get_right_index(0);
    }

    Heap_Delete(min_index);
}

void Max_Min_Heap::validate_index(const int index)
{
    assert(index < heap_root->size() && index >= 0 && "invalid index");
}

void Max_Min_Heap::Print_Max()
{
    std::cout << heap_root->at(0);
}
void Max_Min_Heap::Heap_sort()
{
    Max_Min_Heap *max_min_heap = new Max_Min_Heap();
    std::vector<int> new_heap_root(*heap_root);

    max_min_heap->Build_Heap(new_heap_root);

    while (max_min_heap->get_heap_size() > 0)
    {
        max_min_heap->Print_Max();
        std::cout << ',';
        max_min_heap->Heap_Extract_Max();
    }
    std::cout << "\n";
}