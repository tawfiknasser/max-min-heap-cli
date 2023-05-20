#ifndef MAX_MIN_HEAP_H
#define MAX_MIN_HEAP_H
#include <vector>

inline constexpr auto DEBUG = 1;

class Max_Min_Heap
{
public:
    Max_Min_Heap();
    ~Max_Min_Heap();

    void Build_Heap(std::vector<int> &heap);
    void Heapify(int index);

    int get_heap_size();

    void Heap_Insert(const int value);

    void Heap_Delete(const int index);
    void Heap_Extract_Min();
    void Heap_Extract_Max();

    void Heap_sort();
    void Print();

private:
    /**
     * return heap size
     */

    /**
     * @property pointer to heap root
     */
    std::vector<int> *heap_root;

    /**
     * @return true/false if the level is max. max-min-heap start with max level.
     */
    bool is_max_level(int index);

    /**
     * @return node level in the heap
     */
    int get_level(int index);

    /**
     * @return get left or right child index
     */
    int get_left_index(int index);
    int get_right_index(int index);

    /**
     * @return true/false if child/parent exist
     */
    bool has_left_child(int index);
    bool has_right_child(int index);
    bool has_parent(int index);
    /**
     * @return index of smallest child or grandchild if any
     */
    int get_smallest_child_or_grandchild(int index);
    /**
     * @return index of largest child or grandchild if any
     */
    int get_largest_child_or_grandchild(int index);

    /**
     * @return parent index
     */
    int get_parent(int index);
    int get_grandparent(int index);

    /**
     * bubble up functions
     */
    void bubble_up(int index);
    void bubble_up_max(int index);
    void bubble_up_min(int index);

    /**
     * validate index is in correct range
     */
    void validate_index(const int index);
};

#endif