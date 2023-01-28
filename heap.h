#ifndef __HEAP_H
#define __HEAP_H

// Define MIN_HEAP to compile min-heap and MAX_HEAP otherwise
#define MIN_HEAP
//#define MAX_HEAP

// Return codes
#define HP_SUCCESS 0
#define HP_HEAP_EMPTY 1
#define HP_INDEX_OUT_OF_RANGE 2
#define HP_INVALID_KEY 3

// Compare function
#ifdef MIN_HEAP
#define hp_compare(a,b) (a < b)
#else
#define hp_compare(a,b) (a > b)
#endif

#define hp_empty(heap) (heap[0] == 0)

#define hp_size(heap) heap[0]

#define hp_in_heap(heap,i) ((i <= hp_size(heap)) && (i > 0))

#define hp_left_child(i) (2*i)
#define hp_right_child(i) (2*i+1)
#define hp_parent(i) (i/2)
#define hp_root 1

#define hp_swap(heap,i,j)                                                                                       \
            heap[i] = heap[i] + heap[j];                                                                        \
            heap[j] = heap[i] - heap[j];                                                                        \
            heap[i] = heap[i] - heap[j];

#define hp_init(heap) heap[0] = 0;

// Restore heap properties of subtree with root 'i'.
#define hp_heapify(heap,ind,ret)                                                                                \
{                                                                                                               \
    long i = ind;                                                                                               \
    ret = HP_SUCCESS;                                                                                           \
    if(hp_empty(heap)) ret = HP_HEAP_EMPTY;                                                                     \
    if(!hp_in_heap(heap,i) && ret == HP_SUCCESS) ret = HP_INDEX_OUT_OF_RANGE;                                   \
    if(ret == HP_SUCCESS)                                                                                       \
        while(1)                                                                                                \
        {                                                                                                       \
            long largest = i;                                                                                   \
            if(hp_in_heap(heap,hp_left_child(i)) && hp_compare(heap[hp_left_child(i)],heap[largest]))           \
                largest = hp_left_child(i);                                                                     \
            if(hp_in_heap(heap,hp_right_child(i)) && hp_compare(heap[hp_right_child(i)],heap[largest]))         \
                largest = hp_right_child(i);                                                                    \
            if(largest != i)                                                                                    \
            {                                                                                                   \
                hp_swap(heap,largest,i)                                                                         \
                i = largest;                                                                                    \
            }                                                                                                   \
            else                                                                                                \
                break;                                                                                          \
        }                                                                                                       \
}

// Increases (MAX_HEAP) or decreases (MIN_HEAP) value of i-th element.
#define hp_change_key(heap,ind,key,ret)                                                                         \
{                                                                                                               \
    long i = ind;                                                                                               \
    ret = HP_SUCCESS;                                                                                           \
    if(!hp_in_heap(heap,i)) ret = HP_INDEX_OUT_OF_RANGE;                                                        \
    if(hp_compare(heap[i],key) && i != (hp_size(heap)) && ret == HP_SUCCESS) ret = HP_INVALID_KEY;              \
    if(ret == HP_SUCCESS)                                                                                       \
    {                                                                                                           \
        heap[i] = key;                                                                                          \
        while(i > hp_root && hp_compare(heap[i],heap[hp_parent(i)]))                                        \
        {                                                                                                       \
            hp_swap(heap,i,hp_parent(i))                                                                        \
            i = hp_parent(i);                                                                                   \
        }                                                                                                       \
    }                                                                                                           \
}

// Inserts new element with value=key
#define hp_insert(heap,key,ret)                                                                                 \
    hp_size(heap)++;                                                                                            \
    heap[hp_size(heap)] = key;                                                                                  \
    hp_change_key(heap,hp_size(heap),key,ret);

// Removes max (MAX_HEAP) or min (MIN_HEAP) element from heap and puts it in 'out'
#define hp_pop(heap,out,ret)                                                                                    \
    ret = HP_SUCCESS;                                                                                           \
    if(hp_empty(heap)) ret = HP_HEAP_EMPTY;                                                                     \
    if(ret == HP_SUCCESS)                                                                                       \
    {                                                                                                           \
        out = heap[hp_root];                                                                                \
        heap[hp_root] = heap[hp_size(heap)];                                                                \
        hp_size(heap)--;                                                                                        \
        if(!hp_empty(heap))                                                                                     \
        {                                                                                                       \
            hp_heapify(heap,hp_root,ret);                                                                   \
        }                                                                                                       \
    }

#endif