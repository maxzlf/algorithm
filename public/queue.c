/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   queue.c
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-19
 Description:   A realization of queue.
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
#include "../include/queue.h"
/**module headfiles**/

/*******************************************************************************
    Func Name:  queue_isfull
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  Exame whether the queue is full
        Input:  IN Queue_S *pstQueue
       Output:  NONE  
       Return:  BOOL_T
                BOOL_TRUE, queue is full
                BOOL_FALSE, queue is not full
      Caution:  pstQueue should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline BOOL_T queue_isfull(IN Queue_S *pstQueue)
{
    BOOL_T bRet = BOOL_FALSE;

    assert(NULL != pstQueue);

    if (pstQueue->ppvTail > pstQueue->ppvHead)
    {
        if (1 == pstQueue->ppvHead + pstQueue->uiSize - pstQueue->ppvTail)
        {
            bRet = BOOL_TRUE;
        }
    }
    else
    {
        if (1 == pstQueue->ppvHead - pstQueue->ppvTail)
        {
            bRet = BOOL_TRUE;
        }
    }

    return bRet;
}

/*******************************************************************************
    Func Name:  queue_isempty
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  Exame whether the queue is empty
        Input:  IN Queue_S *pstQueue
       Output:  NONE  
       Return:  BOOL_T
                BOOL_TRUE, queue is empty
                BOOL_FALSE, queue is not empty
      Caution:  pstQueue should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline BOOL_T queue_isempty(IN Queue_S *pstQueue)
{
    BOOL_T bRet = BOOL_FALSE;

    assert(NULL != pstQueue);

    if (pstQueue->ppvHead == pstQueue->ppvTail)
    {
        bRet = BOOL_TRUE;
    }

    return bRet;
}

/*******************************************************************************
    Func Name:  QueueCreate
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  To create a data structure of queue
        Input:  IN UINT uiSize, how many items the queue can store.
                IN PF_PRINT pfPrint, callback function to print item
                IN PF_FREE pfFree, callback function to free item
       Output:  NONE  
       Return:  Queue_S*,  the queue struct
                NULL,     error occured
      Caution:  pfPrint can be NULL
                pfFree can be NULL, then it's the user's responsibility to free
                the memery of items when queue is destroyed
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
Queue_S* QueueCreate(IN UINT uiSize, PF_PRINT pfPrint, IN PF_FREE pfFree)
{
    Queue_S *pstQueue = NULL;
    VOID **ppvQueue = NULL;

    if (0 == uiSize)
    {
        return NULL;
    }

    pstQueue = (Queue_S *)malloc(sizeof(Queue_S));
    if (NULL == pstQueue)
    {
      return NULL;
    }
    memset(pstQueue, 0, sizeof(Queue_S));

    ppvQueue = (VOID **)malloc(sizeof(VOID *) * (uiSize + 1));
    if (NULL == ppvQueue)
    {
        free(pstQueue);
        return NULL;
    }
    memset(ppvQueue, 0, sizeof(VOID *) * (uiSize + 1));

    pstQueue->uiSize = uiSize + 1;
    pstQueue->ppvQueue = ppvQueue;
    pstQueue->ppvHead = ppvQueue;
    pstQueue->ppvTail = ppvQueue;
    pstQueue->pfPrint = pfPrint;
    pstQueue->pfFree = pfFree;

    return pstQueue;
}

/*******************************************************************************
    Func Name:  QueueFree
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  To free memery of queue
        Input:  IN Queue_S *pstQueue
       Output:  NONE  
       Return:  NONE
      Caution:  If you have installed PF_FREE callback function, then all the itmes
                in the queue will be freed, otherwise it's the user's responsibility
                to free the memeries of all items
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID QueueFree(IN Queue_S *pstQueue)
{
    VOID **ppvCursor = NULL;

    if (NULL == pstQueue)
    {
      return;
    }

    if (NULL == pstQueue->ppvQueue)
    {
        free(pstQueue);
        return;
    }

    if (NULL != pstQueue->pfFree)
    {
        ppvCursor = pstQueue->ppvHead;
        while (ppvCursor != pstQueue->ppvTail)
        {
            pstQueue->pfFree(*ppvCursor);
            ppvCursor++;
            if (ppvCursor - pstQueue->ppvQueue >= pstQueue->uiSize)
            {
                ppvCursor = pstQueue->ppvQueue;
            }
        }
    }

    free(pstQueue->ppvQueue);
    pstQueue->ppvQueue = NULL;

    free(pstQueue);

    return;
}

/*******************************************************************************
    Func Name:  QueueAdd
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  Add an item into queue
        Input:  IN Queue_S *pstQueue
                IN VOID *pvItem
       Output:  NONE  
       Return:  ULONG
                ERROR_SUCCESS, success
                ERROR_FAILED, failed
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
ULONG QueueAdd(IN Queue_S *pstQueue, IN VOID *pvItem)
{
    if (NULL == pstQueue || NULL == pvItem)
    {
        return ERROR_FAILED;
    }

    if (BOOL_TRUE == queue_isfull(pstQueue))
    {
        return ERROR_FAILED;
    }

    *pstQueue->ppvTail = pvItem;
    pstQueue->ppvTail++;
    if (pstQueue->ppvTail - pstQueue->ppvQueue >= pstQueue->uiSize)
    {
        pstQueue->ppvTail = pstQueue->ppvQueue;
    }

    return ERROR_SUCCESS;
}

/*******************************************************************************
    Func Name:  QueueRemoveFirst
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  Remove the first item in queue
        Input:  IN Queue_S *pstQueue
       Output:  NONE  
       Return:  VOID*, the first item in queue
                NULL, failed
      Caution:  The function only removes items from queue, but the memery is 
                left to users to free
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* QueueRemoveFirst(IN Queue_S *pstQueue)
{
    VOID *pvRet = NULL;

    if (NULL == pstQueue)
    {
        return NULL;
    }
    if (BOOL_TRUE == queue_isempty(pstQueue))
    {
        return NULL;
    }

    pvRet = *pstQueue->ppvHead;
    *pstQueue->ppvHead = NULL;
    pstQueue->ppvHead++;
    if (pstQueue->ppvHead - pstQueue->ppvQueue >= pstQueue->uiSize)
    {
        pstQueue->ppvHead = pstQueue->ppvQueue;
    }   

    return pvRet;
}

/*******************************************************************************
    Func Name:  QueueGetFirst
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  look for the first item in queue
        Input:  IN Queue_S *pstQueue
       Output:  NONE  
       Return:  VOID*, the first item in queue
                NULL, failed
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* QueueGetFirst(IN Queue_S *pstQueue)
{
    VOID *pvRet = NULL;

    if (NULL == pstQueue)
    {
        return NULL;
    }
    if (BOOL_TRUE == queue_isempty(pstQueue))
    {
        return NULL;
    }

    pvRet = *pstQueue->ppvHead;

    return pvRet;    
}

/*******************************************************************************
    Func Name:  QeueuePrint
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  Print all items in queue from head to tail
        Input:  IN Queue_S *pstQueue
       Output:  NONE  
       Return:  NONE
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID QueuePrint(IN Queue_S *pstQueue)
{
    VOID **ppvCursor = NULL;

    if (NULL == pstQueue || NULL == pstQueue->pfPrint)
    {
        return;
    }
    if (BOOL_TRUE == queue_isempty(pstQueue))
    {
        return;
    }

    ppvCursor = pstQueue->ppvHead;
    while (ppvCursor != pstQueue->ppvTail)
    {
        pstQueue->pfPrint(*ppvCursor);
        ppvCursor++;
        if (ppvCursor - pstQueue->ppvQueue >= pstQueue->uiSize)
        {
            ppvCursor = pstQueue->ppvQueue;
        }   
    }

    return;
}

/*******************************************************************************
    Func Name:  QueueNumber
 Date Created:  2014-9-19
       Author:  Zhulinfeng
  Description:  Return how many items in queue
        Input:  IN Queue_S *pstQueue
       Output:  NONE
       Return:  UINT
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
UINT QueueNumber(IN Queue_S *pstQueue)
{
    UINT uiRet = 0;

    if (NULL == pstQueue)
    {
        return 0;
    }

    if (pstQueue->ppvHead < pstQueue->ppvTail)
    {
        uiRet = pstQueue->ppvTail - pstQueue->ppvHead;
    }
    else if (pstQueue->ppvHead > pstQueue->ppvTail)
    {
        uiRet = pstQueue->ppvTail - pstQueue->ppvHead + pstQueue->uiSize;
    }
    else
    {
        uiRet = 0;
    }

    return uiRet;
}