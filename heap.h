#ifndef __HEAP_H
#define __HEAP_H

// Define MIN_HEAP to compile min-heap and MAX_HEAP otherwise
#define MIN_HEAP
//#define MAX_HEAP

// Define heap comparable type
typedef long hp_heap_type;

// Define size of heap buffer
#define HP_HEAP_MAX_CAPACITY 100

// Return codes
#define HP_SUCCESS 0
#define HP_HEAP_EMPTY -1
#define HP_INDEX_OUT_OF_RANGE -2
#define HP_INVALID_KEY -3
#define HP_BUFFER_OVERFLOW -4

typedef struct
{
    long size;
    hp_heap_type buffer[HP_HEAP_MAX_CAPACITY];
} HEAP;

// Compare function
#ifdef MIN_HEAP
#define hp_compare(heap,a,b) (a < b)
#else
#define hp_compare(heap,a,b) (a > b)
#endif

#define hp_empty(heap) (!(heap)->size)

#define hp_size(heap) (heap)->size

#define hp_in_heap(heap,i) (i < hp_size(heap))

#define hp_left_child(i) (2*i+1)
#define hp_right_child(i) (2*i+2)
#define hp_parent(i) ((i-1)/2)

#define hp_value(heap,i) (heap)->buffer[i]

#define hp_swap(heap,i,j)                               \
            hp_heap_type c;                             \
            c = hp_value(heap,i);                       \
            hp_value(heap,i) = hp_value(heap,j);        \
            hp_value(heap,j) = c;

#define hp_init(heap) (heap)->size = 0;

#define hp_root_ind 0

#define hp_root_value(heap) (heap)->buffer[hp_root_ind]

// Restore heap properties of subtree with root 'i'
static inline int hp_heapify(HEAP* heap, long i)
{
    if(hp_empty(heap)) return HP_HEAP_EMPTY;
    if(i >= hp_size(heap)) return HP_INDEX_OUT_OF_RANGE;
    while(1)
    {
        hp_heap_type largest = i;
        if(hp_in_heap(heap,hp_left_child(i)) && hp_compare(heap,hp_value(heap,hp_left_child(i)),hp_value(heap,largest)))
            largest = hp_left_child(i);
        if(hp_in_heap(heap,hp_right_child(i)) && hp_compare(heap,hp_value(heap,hp_right_child(i)),hp_value(heap,largest)))
            largest = hp_right_child(i);
        if(largest != i)
        {
            hp_swap(heap,largest,i)
            i = largest;
        }
        else
            break;
    }

    return HP_SUCCESS;
}

// Increases (MAX_HEAP) or decreases (MIN_HEAP) value of i-th element 
static inline int hp_change_key(HEAP* heap, long i, hp_heap_type key)
{
    if(!hp_in_heap(heap,i)) return HP_INDEX_OUT_OF_RANGE;
    if(hp_compare(heap,hp_value(heap,i),key) && i != (hp_size(heap)-1)) return HP_INVALID_KEY;
    heap->buffer[i] = key;
    while(i > 0 && hp_compare(heap,hp_value(heap,i),hp_value(heap,hp_parent(i))))
    {
        hp_swap(heap,i,hp_parent(i))
        i = hp_parent(i);
    }

    return HP_SUCCESS;
}

// Inserts new element with value=key
static inline int hp_insert(HEAP* heap, hp_heap_type key)
{
    if(hp_size(heap) >= HP_HEAP_MAX_CAPACITY) return HP_BUFFER_OVERFLOW;
    hp_size(heap)++;
    hp_value(heap,hp_size(heap)-1) = key;
    hp_change_key(heap,hp_size(heap)-1,key);

    return HP_SUCCESS;
}

// Removes max (MAX_HEAP) or min (MIN_HEAP) element from heap and puts it in 'out'
static inline int hp_pop(HEAP* heap, hp_heap_type* out)
{
    if(hp_empty(heap)) return HP_HEAP_EMPTY;
    *out = hp_root_value(heap);
    hp_size(heap)--;
    hp_root_value(heap) = heap->buffer[hp_size(heap)];
    hp_heapify(heap,hp_root_ind);

    return HP_SUCCESS;
}

#endif