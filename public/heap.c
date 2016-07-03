/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   heap.c
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-17
 Description:   A realization of heap.
      Others:   
    ---------------------------------------------------------------------------- 
    Modification History        
    Date            Author          Modification
    ----------------------------------------------------------------------------
    YYYY-MM-DD
\******************************************************************************/

/**system headfiles**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/**public headfiles**/
#include "../include/type.h"
#include "../include/err.h"
#include "../include/length.h"
#include "../include/heap.h"
/**module headfiles**/

/*******************************************************************************
    Func Name:  heap_swap
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  exchange to items in heap
        Input:  INOUT VOID **ppvFirst
                INOUT VOID **ppvSecond
       Output:  INOUT VOID **ppvFirst
                INOUT VOID **ppvSecond
       Return:  NONE
      Caution:  params should not be NULL
v  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline VOID heap_swap(INOUT VOID **ppvFirst, INOUT VOID **ppvSecond)
{
    VOID *pvTmp = NULL;

    assert(NULL != ppvFirst && NULL != ppvSecond);
    assert(NULL != *ppvFirst && NULL != *ppvSecond);

    pvTmp = *ppvFirst;
    *ppvFirst = *ppvSecond;
    *ppvSecond = pvTmp;

    return;
}

/*******************************************************************************
    Func Name:  heap_isfull
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Exame whether the heap is full
        Input:  IN Heap_S *pstHeap
       Output:  NONE  
       Return:  BOOL_T
                BOOL_TRUE, heap is full
                BOOL_FALSE, heap is not full
      Caution:  pstHeap should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline BOOL_T heap_isfull(IN Heap_S *pstHeap)
{
    BOOL_T bRet = BOOL_FALSE;

    assert(NULL != pstHeap);

    if (pstHeap->ppvTail - pstHeap->ppvHeap >= pstHeap->uiSize)
    {
        bRet = BOOL_TRUE;
    }

    return bRet;
}

/*******************************************************************************
    Func Name:  heap_isempty
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Exame whether the heap is empty
        Input:  IN Heap_S *pstHeap
       Output:  NONE  
       Return:  BOOL_T
                BOOL_TRUE, heap is empty
                BOOL_FALSE, heap is not empty
      Caution:  pstHeap should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline BOOL_T heap_isempty(IN Heap_S *pstHeap)
{
    BOOL_T bRet = BOOL_FALSE;

    assert(NULL != pstHeap);

    if (pstHeap->ppvTail == pstHeap->ppvHeap)
    {
        bRet = BOOL_TRUE;
    }

    return bRet;
}

/*******************************************************************************
    Func Name:  heap_parent
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Get parent item of an item
        Input:  IN Heap_S *pstHeap
                IN VOID **ppvItem
       Output:  NONE  
       Return:  VOID**, parent item
                NULL, root
      Caution:  pstHeap and pvItem should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline VOID** heap_parent(IN Heap_S *pstHeap, IN VOID **ppvItem)
{
    UINT uiIndex = 0;
    VOID **ppvRet = NULL;

    assert(NULL != pstHeap && NULL != ppvItem);
    assert(ppvItem >= pstHeap->ppvHeap && ppvItem < pstHeap->ppvTail);
    assert(NULL != *ppvItem);

    uiIndex = ppvItem - pstHeap->ppvHeap + 1;
    if (1 == uiIndex)
    {
      return NULL;
    }

    uiIndex >>= 1;
    ppvRet = pstHeap->ppvHeap + uiIndex - 1;

    return ppvRet;
}

/*******************************************************************************
    Func Name:  heap_left
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Get left child item of a parent
        Input:  IN Heap_S *pstHeap
                IN VOID **ppvItem
       Output:  NONE  
       Return:  VOID**, left child item
                NULL, leave
      Caution:  pstHeap and pvItem should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline VOID** heap_left(IN Heap_S *pstHeap, IN VOID **ppvItem)
{
    UINT uiIndex = 0;
    VOID **ppvRet = NULL;

    assert(NULL != pstHeap && NULL != ppvItem);
    assert(ppvItem >= pstHeap->ppvHeap && ppvItem < pstHeap->ppvTail);
    assert(NULL != *ppvItem);

    uiIndex = ppvItem - pstHeap->ppvHeap + 1;

    uiIndex <<= 1;
    ppvRet = pstHeap->ppvHeap + uiIndex - 1;

    if (ppvRet >= pstHeap->ppvTail)
    {
        return NULL;
    }

    return ppvRet;
}

/*******************************************************************************
    Func Name:  heap_right
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Get right child item of a parent
        Input:  IN Heap_S *pstHeap
                IN VOID **ppvItem
       Output:  NONE  
       Return:  VOID**, right child item
                NULL, leave
      Caution:  pstHeap and pvItem should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline VOID** heap_right(IN Heap_S *pstHeap, IN VOID **ppvItem)
{
    UINT uiIndex = 0;
    VOID **ppvRet = NULL;

    assert(NULL != pstHeap && NULL != ppvItem);
    assert(ppvItem >= pstHeap->ppvHeap && ppvItem < pstHeap->ppvTail);
    assert(NULL != *ppvItem);

    uiIndex = ppvItem - pstHeap->ppvHeap + 1;

    uiIndex <<= 1;
    uiIndex++;
    ppvRet = pstHeap->ppvHeap + uiIndex - 1;

    if (ppvRet >= pstHeap->ppvTail)
    {
        return NULL;
    }

    return ppvRet;
}

/*******************************************************************************
    Func Name:  heapify_one
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Keep heap healthy if one item changed
        Input:  IN Heap_S *pstHeap
                IN VOID **ppvItem
       Output:  OUT Heap_S *pstHeap 
       Return:  NONE
      Caution:  pstHeap and pvItem should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static VOID heapify_one(INOUT Heap_S *pstHeap, IN VOID **ppvItem)
{ 
    VOID **ppvParent = NULL;
    INT iCmpRet = 0;

    assert(NULL != pstHeap && NULL != ppvItem);
    assert(ppvItem >= pstHeap->ppvHeap && ppvItem < pstHeap->ppvTail);
    assert(NULL != *ppvItem);

    ppvParent = heap_parent(pstHeap, ppvItem);
    while (NULL != ppvParent)
    {
        iCmpRet = pstHeap->pfCompare(*ppvParent, *ppvItem);
        if (HEAP_MAXI == pstHeap->uiType && iCmpRet >= 0)
        {
            break;
        }
        else if (HEAP_MINI == pstHeap->uiType && iCmpRet <= 0)
        {
            break;
        }

        heap_swap(ppvParent, ppvItem);
        ppvItem = ppvParent;
        ppvParent = heap_parent(pstHeap, ppvItem);
    }

    return;
}

/*******************************************************************************
    Func Name:  heapify_all
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Keep heap healthy if all item changed
        Input:  IN Heap_S *pstHeap
       Output:  OUT Heap_S *pstHeap 
       Return:  NONE
      Caution:  pstHeap should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static VOID heapify_all(INOUT Heap_S *pstHeap)
{ 
    VOID **ppvCursor = NULL;

    assert(NULL != pstHeap);

    if (BOOL_TRUE == heap_isempty(pstHeap))
    {
        return;
    }

    ppvCursor = pstHeap->ppvTail - 1;
    while (ppvCursor >= pstHeap->ppvHeap)
    {
        heapify_one(pstHeap, ppvCursor);
        ppvCursor--;
    }

    return;
}

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
                   IN PF_FREE pfFree)
{
    Heap_S *pstHeap = NULL;
    VOID **ppvHeap = NULL;

    if (0 == uiSize || uiType >= HEAP_UPSPACE || NULL == pfCompare)
    {
        return NULL;
    }

    pstHeap = (Heap_S *)malloc(sizeof(Heap_S));
    if (NULL == pstHeap)
    {
      return NULL;
    }
    memset(pstHeap, 0, sizeof(Heap_S));

    ppvHeap = (VOID **)malloc(sizeof(VOID *) * uiSize);
    if (NULL == ppvHeap)
    {
        free(pstHeap);
        return NULL;
    }
    memset(ppvHeap, 0, sizeof(VOID *) * uiSize);

    pstHeap->uiSize = uiSize;
    pstHeap->ppvHeap = ppvHeap;
    pstHeap->ppvTail = ppvHeap;
    pstHeap->uiType = uiType;
    pstHeap->pfCompare = pfCompare;
    pstHeap->pfPrint = pfPrint;
    pstHeap->pfFree = pfFree;

    return pstHeap;
}

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
VOID HeapFree(IN Heap_S *pstHeap)
{
    VOID **ppvCursor = NULL;

    if (NULL == pstHeap)
    {
      return;
    }

    if (NULL ==pstHeap->ppvHeap)
    {
        free(pstHeap);
        return;
    }

    if (NULL != pstHeap->pfFree)
    {
        ppvCursor = pstHeap->ppvHeap;
        while (ppvCursor < pstHeap->ppvTail)
        {
            pstHeap->pfFree(*ppvCursor);
            ppvCursor++;
        }
    }

    free(pstHeap->ppvHeap);
    pstHeap->ppvHeap = NULL;

    free(pstHeap);

    return;
}

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
                ERROR_FAILED,   failed
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
ULONG HeapAdd(INOUT Heap_S *pstHeap, IN VOID *pvItem)
{
    if (NULL == pstHeap || NULL == pvItem)
    {
        return ERROR_FAILED;
    }

    if (BOOL_TRUE == heap_isfull(pstHeap))
    {
        return ERROR_FAILED;
    }

    *(pstHeap->ppvTail) = pvItem;
    (pstHeap->ppvTail)++;
    heapify_one(pstHeap, pstHeap->ppvTail - 1);

    return ERROR_SUCCESS;
}

/*******************************************************************************
    Func Name:  HeapSearch
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Search an item in a heap
        Input:  IN Heap_S *pstHeap
                 N VOID *pvItem, the item to be searched
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
VOID* HeapSearch(IN Heap_S *pstHeap, IN VOID *pvItem)
{ 
    VOID *pvRet = NULL;
    VOID **ppvCursor = NULL;
    INT iCmpRet = 0;

    if (NULL == pstHeap || NULL ==pvItem)
    {
        return NULL;
    }

    if (BOOL_TRUE == heap_isempty(pstHeap))
    {
        return NULL;
    }

    ppvCursor = pstHeap->ppvHeap;
    while (ppvCursor < pstHeap->ppvTail)
    {
        iCmpRet = pstHeap->pfCompare(*ppvCursor, pvItem);
        if (0 == iCmpRet)
        {
            pvRet = *ppvCursor;
            break;
        }
        ppvCursor++;
    }

    return pvRet;
}

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
VOID* HeapRemoveRoot(IN Heap_S *pstHeap)
{
    VOID **ppvCursor = NULL;
    VOID *pvRet = NULL;

    if (NULL == pstHeap)
    {
        return NULL;
    }
    if (BOOL_TRUE == heap_isempty(pstHeap))
    {
        return NULL;
    }

    pvRet = *pstHeap->ppvHeap;
    ppvCursor = pstHeap->ppvHeap;
    while (ppvCursor < pstHeap->ppvTail - 1)
    {
        *ppvCursor = *(ppvCursor + 1);
        ppvCursor++;
    }
    *ppvCursor = NULL;
    pstHeap->ppvTail--;

    heapify_all(pstHeap);

    return pvRet;
}

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
VOID* HeapRemoveTail(IN Heap_S *pstHeap)
{
    VOID *pvRet = NULL;

    if (NULL == pstHeap)
    {
        return NULL;
    }
    if (BOOL_TRUE == heap_isempty(pstHeap))
    {
        return NULL;
    }

    pvRet = *(pstHeap->ppvTail - 1);
    *(pstHeap->ppvTail - 1) = NULL;
    pstHeap->ppvTail--;

    return pvRet;    
}

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
VOID* HeapRemoveItem(IN Heap_S *pstHeap, IN VOID *pvItem)
{
    VOID *pvRet = NULL;
    VOID **ppvCursor = NULL;
    INT iCmpRet = 0;

    if (NULL == pstHeap || NULL ==pvItem)
    {
        return NULL;
    }

    if (BOOL_TRUE == heap_isempty(pstHeap))
    {
        return NULL;
    }

    ppvCursor = pstHeap->ppvHeap;
    while (ppvCursor < pstHeap->ppvTail)
    {
        iCmpRet = pstHeap->pfCompare(*ppvCursor, pvItem);
        if (0 == iCmpRet)
        {
            pvRet = *ppvCursor;
            break;
        }
        ppvCursor++;
    }

    if (NULL == pvRet)
    {
        return NULL;
    }

    while (ppvCursor < pstHeap->ppvTail - 1)
    {
        *ppvCursor = *(ppvCursor + 1);
        ppvCursor++;
    }
    *ppvCursor = NULL;
    pstHeap->ppvTail--;

    heapify_all(pstHeap);   

    return pvRet;    
}

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
VOID HeapPrint(IN Heap_S *pstHeap)
{
    VOID **ppvCursor = NULL;

    if (NULL == pstHeap || NULL == pstHeap->pfPrint)
    {
        return;
    }

    if (BOOL_TRUE == heap_isempty(pstHeap))
    {
        return;
    }

    ppvCursor = pstHeap->ppvHeap;
    while (ppvCursor < pstHeap->ppvTail)
    {
        pstHeap->pfPrint(*ppvCursor);
        ppvCursor++;
    }

    return;
}

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
UINT HeapNumber(IN Heap_S *pstHeap)
{
    UINT uiRet = 0;

    if (NULL == pstHeap)
    {
        return 0;
    }

    uiRet = pstHeap->ppvTail - pstHeap->ppvHeap;
    return uiRet;
}

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
VOID* HeapMax(IN Heap_S *pstHeap)
{
    VOID *pvRet = NULL;
    VOID **ppvCursor = NULL;
    VOID **ppvLeft = NULL;
    INT iCmpRet = 0;

    if (NULL == pstHeap)
    {
        return NULL;
    }

    if (BOOL_TRUE == heap_isempty(pstHeap))
    {
        return NULL;
    }

    if (HEAP_MAXI == pstHeap->uiType || 1 == HeapNumber(pstHeap))
    {
        pvRet = *pstHeap->ppvHeap;
        return pvRet;
    }

    ppvCursor = pstHeap->ppvTail - 1;
    pvRet = *ppvCursor;
    ppvLeft = heap_left(pstHeap, ppvCursor);
    while (NULL == ppvLeft)
    {
        iCmpRet = pstHeap->pfCompare(*ppvCursor, pvRet);
        if (0 < iCmpRet)
        {
            pvRet = *ppvCursor;
        }
        ppvCursor--;
        ppvLeft = heap_left(pstHeap, ppvCursor);
    }

    return pvRet;
}

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
VOID* HeapMin(IN Heap_S *pstHeap)
{
    VOID *pvRet = NULL;
    VOID **ppvCursor = NULL;
    VOID **ppvLeft = NULL;
    INT iCmpRet = 0;

    if (NULL == pstHeap)
    {
        return NULL;
    }

    if (BOOL_TRUE == heap_isempty(pstHeap))
    {
        return NULL;
    }

    if (HEAP_MINI == pstHeap->uiType || 1 == HeapNumber(pstHeap))
    {
        pvRet = *pstHeap->ppvHeap;
        return pvRet;
    }

    ppvCursor = pstHeap->ppvTail - 1;
    pvRet = *ppvCursor;
    ppvLeft = heap_left(pstHeap, ppvCursor);
    while (NULL == ppvLeft)
    {
        iCmpRet = pstHeap->pfCompare(*ppvCursor, pvRet);
        if (0 > iCmpRet)
        {
            pvRet = *ppvCursor;
        }
        ppvCursor--;
        ppvLeft = heap_left(pstHeap, ppvCursor);
    }

    return pvRet;
}
