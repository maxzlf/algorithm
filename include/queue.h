/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   queue.h
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-17
 Description:   Interface of queue.
      Others:   
    ----------------------------------------------------------------------------        
    Modification History        
    Date            Author          Modification
    ----------------------------------------------------------------------------
    YYYY-MM-DD
\******************************************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct tagQueue_S
{
    UINT uiSize;
    VOID **ppvQueue;
    VOID **ppvHead;
    VOID **ppvTail;
    PF_PRINT pfPrint;
    PF_FREE pfFree;
}Queue_S;

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
Queue_S* QueueCreate(IN UINT uiSize, PF_PRINT pfPrint, IN PF_FREE pfFree);

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
VOID QueueFree(IN Queue_S *pstQueue); 

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
ULONG QueueAdd(IN Queue_S *pstQueue, IN VOID *pvItem);

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
VOID* QueueRemoveFirst(IN Queue_S *pstQueue);

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
VOID* QueueGetFirst(IN Queue_S *pstQueue);

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
VOID QueuePrint(IN Queue_S *pstQueue);

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
UINT QueueNumber(IN Queue_S *pstQueue);

#endif