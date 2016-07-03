/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   heap.h
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-17
 Description:   Interface of heap.
      Others:   
    ----------------------------------------------------------------------------        
    Modification History        
    Date            Author          Modification
    ----------------------------------------------------------------------------
    YYYY-MM-DD
\******************************************************************************/

#ifndef _HEAP_H_
#define _HEAP_H_

#define HEAP_MINI     0
#define HEAP_MAXI     1
#define HEAP_UPSPACE  2

typedef struct tagHeap_S
{
    UINT uiSize;
    VOID **ppvHeap;
    VOID **ppvTail;
    UINT uiType;
    PF_COMPARE pfCompare;
    PF_PRINT pfPrint;
    PF_FREE pfFree;
}Heap_S;

  /*******************************************************************************
    Func Name:  HeapCreate
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  To create a data structure of heap
        Input:  IN UINT uiSize, how many items the heap can store.
                IN UINT uiType, HEAP_MINI for minimal heap, HEAP_MAXI for maximum heap 
                IN PF_COMPARE pfCompare, callback function to compare two items
                IN PF_PRINT pfPrint, callback function to print item
                IN PF_FREE pfFree, callback function to free item
       Output:  NONE  
       Return:  Heap_S*,  the heap struct
                NULL,     error occured
      Caution:  pfCompare should not be NULL,
                pfPrint can be NULL
                pfFree can be NULL if you don't want your data to be freed when deleting
                the heap
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
Heap_S* HeapCreate(IN UINT uiSize, IN UINT uiType,
                   IN PF_COMPARE pfCompare,
                   IN PF_PRINT pfPrint,
                   IN PF_FREE pfFree);

/*******************************************************************************
    Func Name:  HeapFree
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  To free a given heap
        Input:  IN Heap_S *pstHeap, the heap to be freed
       Output:  NONE
       Return:  NONE
      Caution:  If you have installed PF_FREE callback function, then all the itmes
                in the heap will be freed, otherwise it's the user's responsibility
                to free the memeries of all items
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID HeapFree(IN Heap_S *pstHeap);

/*******************************************************************************
    Func Name:  HeapAdd
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Add an item to heap
        Input:  IN Heap_S *pstHeap
                IN VOID *pvItem, item to be added
       Output:  OUT Heap_S *pstHeap
       Return:  LUONG
                ERROR_SUCCESS,  success
                ERROR_FAILED,   failed, the heap is full
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
ULONG HeapAdd(INOUT Heap_S *pstHeap, IN VOID *pvItem);

/*******************************************************************************
    Func Name:  HeapSearch
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Search an item in a heap
        Input:  IN Heap_S *pstHeap
                IN VOID *pvItem, the item to be searched
       Output:  NONE
       Return:  VOID*, the item found
                NULL,  not found
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* HeapSearch(IN Heap_S *pstHeap, IN VOID *pvItem);

/*******************************************************************************
    Func Name:  HeapRemoveRoot
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  remove the root item from heap
        Input:  IN Heap_S *pstHeap
       Output:  NONE
       Return:  VOID*, the item removed out
                NULL, failed, the heap is empty
      Caution:  The function only removes items from heap, but the memery is 
                left to users to free
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* HeapRemoveRoot(IN Heap_S *pstHeap);

/*******************************************************************************
    Func Name:  HeapRemoveTail
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  remove the tail item from heap
        Input:  IN Heap_S *pstHeap
       Output:  NONE
       Return:  VOID*, the item removed out
                NULL, failed, the heap is empty
      Caution:  The function only removes items from heap, but the memery is 
                left to users to free
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* HeapRemoveTail(IN Heap_S *pstHeap);

/*******************************************************************************
    Func Name:  HeapRemoveItem
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  remove the match item from heap
        Input:  IN Heap_S *pstHeap
                IN VOID *pvItem, the item to be removed
       Output:  NONE
       Return:  VOID*, the item removed out
                NULL, not found
      Caution:  The function only removes items from heap, but the memery is 
                left to users to free
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* HeapRemoveItem(IN Heap_S *pstHeap, IN VOID *pvItem);

/*******************************************************************************
    Func Name:  HeapPrint
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  print all items in heap
        Input:  IN Heap_S *pstHeap
       Output:  NONE
       Return:  NONE
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID HeapPrint(IN Heap_S *pstHeap);

/*******************************************************************************
    Func Name:  HeapNumber
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Return how many items in heap
        Input:  IN Heap_S *pstHeap
       Output:  NONE
       Return:  UINT
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
UINT HeapNumber(IN Heap_S *pstHeap);

/*******************************************************************************
    Func Name:  HeapMax
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  Return the max item in heap
        Input:  IN Heap_S *pstHeap
       Output:  NONE
       Return:  VOID*, the max item
                NULL, failed
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* HeapMax(IN Heap_S *pstHeap);

/*******************************************************************************
    Func Name:  HeapMin
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  Return the minimal item in heap
        Input:  IN Heap_S *pstHeap
       Output:  NONE
       Return:  VOID*, the minimal item
                NULL, failed
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* HeapMin(IN Heap_S *pstHeap);

#endif