#include <stdio.h>
#include <stdlib.h>

typedef struct Vec 
{
    int * data;
    int size;
    int count;
}vec_t;
void swap(int * current, int * next)
{
    int tmp = *current;
    *current = *next;
    *next = tmp;
}
void print_arr(int * arr,int n)
{
    for (int i = 0; i<n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int * arr_resize(int * arr, int size, int increment)
{
    int *tmp = (int *) calloc(size+increment,(size+increment)*sizeof(int));
    for (int i = 0; i<size; i++)
    {
        tmp[i] = arr[i];
    }
    free(arr);
    arr = tmp;
    tmp = NULL;
    return arr;
}
void vec_resize(vec_t * vec,int increment)
{
    vec->data = arr_resize(vec->data,vec->size,increment);
    vec->size+=increment;
}
void vec_pushback(vec_t * vec, int key)
{
    if (vec->count == vec->size) {
        vec_resize(vec,vec->size);
    }
    vec->data[vec->count] = key;
    vec->count++;
}
int vec_pop(vec_t * vec)
{
    int val = vec->data[vec->count-1];
    vec->data[vec->count-1] = 0;
    vec->count--;

    if (vec->size > 5)
    {
        if (vec->size/3 == vec->count)
        {
            vec_resize(vec,-(vec->size/2));
        }
    }
    return val;
}
void destroy_vec(vec_t * vec)
{
    // for (int i = 0; i<vec->size; i++)
    // {
    //     free((int *)vec->data[i]);
    // }
    free(vec->data);
    free(vec);
}
void init_empty_vec_of_size(vec_t ** vec, int size)
{
    vec_t * new = (vec_t *) malloc(sizeof(vec_t));
    new->size = size;
    new->count = 0;
    new->data = (int *) calloc(new->size,sizeof(int)*new->size);
    *vec = new;
}
int parent(int i)
{
    return (i-1)/2;
}
int left_child(int i)
{
    return i*2+1;
}
int right_child(int i)
{
    return i*2+2;
}
void sift_up(vec_t * heap,int key)
{
    vec_pushback(heap,key);
    int i = heap->count-1;
    while (i>0 && heap->data[parent(i)]<heap->data[i])
    {
        swap(&heap->data[i],&heap->data[parent(i)]);
        i = parent(i);
    }
}
vec_t * heapify(int *arr,int size)
{
    vec_t * heap;
    init_empty_vec_of_size(&heap,size);
    for (int i = 0; i<size; i++)
    {
        sift_up(heap,arr[i]);
    }
    return heap;
}
void sift_down(vec_t * heap,int i)
{
    int m;
    if (left_child(i) <= heap->count-1)
    {
        if (right_child(i) > heap->count-1 || heap->data[left_child(i)] >= heap->data[right_child(i)])
        {
            m = left_child(i);
        } 
        else 
        {
            m = right_child(i);
        }
        if (heap->data[m] > heap->data[i])
        {
            swap(&heap->data[m],&heap->data[i]);
            sift_down(heap,m);
        }
    }
}
void delete_max(vec_t * heap)
{
    printf("max: %d\n",heap->data[0]);
    heap->data[0] = heap->data[heap->count-1];
    heap->data[heap->count-1] = 0;
    heap->count -= 1;
    sift_down(heap,0);
}
vec_t * build(int * arr, int n)
{
    vec_t * heap = (vec_t *) malloc(sizeof(vec_t));
    heap->data = arr;
    heap->count = n;
    heap->size = n;

    for (int i = (heap->count-1)/2; i >= 0; i--)
    {
        sift_down(heap,i);
    }
    return heap;    
}
void helper_heapsort(vec_t * heap, int * arr)
{
    for (int i = heap->count-1; i >= 0; i--)
    {
        arr[i] = heap->data[0];
        delete_max(heap);
    }
}
// void heapsort(int * arr,int n)
// {
//     vec_t * heap = build(arr,n);
//     helper_heapsort(heap,arr);
// }

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,0};
    vec_t * test = heapify(arr,10);
    // print_arr(test->data,test->size);
    vec_t * heap;
    init_empty_vec_of_size(&heap,5);
    sift_up(heap,2);
    sift_up(heap,5);
    sift_up(heap,10);
    // print_arr(heap->data,heap->size);
    delete_max(heap);


    // test
    int sort[5] = {0};
    sift_up(heap,8);
    sift_up(heap,1);
    helper_heapsort(heap,sort);
    print_arr(sort,5);
    printf("\nheapsort\n");
    // test

    // print_arr(heap->data,heap->size);
    int arr2[10] = {1,2,3,4,5,6,7,8,9,0};
    vec_t * build_test = build(arr2,10);
    print_arr(build_test->data,build_test->size);
    // heapsort(arr2,10);
    // print_arr(arr2,10);
    return 0;
}