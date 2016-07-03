/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   stack.c
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-18
 Description:   A realization of stack.
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
#include "../include/stack.h"
/**module headfiles**/

/*******************************************************************************
    Func Name:  stack_isfull
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Exame whether the stack is full
        Input:  IN Stack_S *pstStack
       Output:  NONE  
       Return:  BOOL_T
                BOOL_TRUE, stack is full
                BOOL_FALSE, stack is not full
      Caution:  pstStack should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline BOOL_T stack_isfull(IN Stack_S *pstStack)
{
    BOOL_T bRet = BOOL_FALSE;

    assert(NULL != pstStack);

    if (pstStack->ppvTop - pstStack->ppvStack >= pstStack->uiSize)
    {
        bRet = BOOL_TRUE;
    }

    return bRet;
}

/*******************************************************************************
    Func Name:  stack_isempty
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Exame whether the stack is empty
        Input:  IN Stack_S *pstStack
       Output:  NONE  
       Return:  BOOL_T
                BOOL_TRUE, stack is empty
                BOOL_FALSE, stack is not empty
      Caution:  pstStack should not be NULL
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
static inline BOOL_T stack_isempty(IN Stack_S *pstStack)
{
    BOOL_T bRet = BOOL_FALSE;

    assert(NULL != pstStack);

    if (pstStack->ppvTop == pstStack->ppvStack)
    {
        bRet = BOOL_TRUE;
    }

    return bRet;
}

/*******************************************************************************
    Func Name:  StackCreate
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  To create a data structure of stack
        Input:  IN UINT uiSize, how many items the stack can store.
                IN PF_PRINT pfPrint, callback function to print item
                PF_FREE pfFree, callback function to free the memery of item
       Output:  NONE  
       Return:  Stack_S*,  the stack struct
                NULL,     error occured
      Caution:  pfPrint can be NULL
                pfFree can be NULL, then it's the user's responsibility to free
                the memery of items when stack is destroyed
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
Stack_S* StackCreate(IN UINT uiSize, PF_PRINT pfPrint, PF_FREE pfFree)
{
    Stack_S *pstStack = NULL;
    VOID **ppvStack = NULL;

    if (0 == uiSize)
    {
        return NULL;
    }

    pstStack = (Stack_S *)malloc(sizeof(Stack_S));
    if (NULL == pstStack)
    {
      return NULL;
    }
    memset(pstStack, 0, sizeof(Stack_S));

    ppvStack = (VOID **)malloc(sizeof(VOID *) * uiSize);
    if (NULL == ppvStack)
    {
        free(pstStack);
        return NULL;
    }
    memset(ppvStack, 0, sizeof(VOID *) * uiSize);

    pstStack->uiSize = uiSize;
    pstStack->ppvStack = ppvStack;
    pstStack->ppvTop = ppvStack;
    pstStack->pfPrint = pfPrint;
    pstStack->pfFree = pfFree;

    return pstStack;
}

/*******************************************************************************
    Func Name:  StackFree
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  To free memery of stack
        Input:  IN Stack_S *pstStack
       Output:  NONE  
       Return:  NONE
      Caution:  If you have installed PF_FREE callback function, then all the itmes
                in the stack will be freed, otherwise it's the user's responsibility
                to free the memeries of all items
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID StackFree(IN Stack_S *pstStack)
{
    VOID **ppvCursor = NULL;;

    if (NULL == pstStack)
    {
      return;
    }

    if (NULL == pstStack->ppvStack)
    {
        free(pstStack);
        return;
    }

    if (NULL != pstStack->pfFree)
    {
        ppvCursor = pstStack->ppvTop - 1;
        while (ppvCursor >= pstStack->ppvStack)
        {
            pstStack->pfFree(*ppvCursor);
            ppvCursor--;
        }
    }

    free(pstStack->ppvStack);
    pstStack->ppvStack = NULL;

    free(pstStack);

    return;
}

/*******************************************************************************
    Func Name:  StackPush
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Push an item into stack
        Input:  IN Stack_S *pstStack
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
ULONG StackPush(IN Stack_S *pstStack, IN VOID *pvItem)
{
    if (NULL == pstStack || NULL == pvItem)
    {
        return ERROR_FAILED;
    }

    if (BOOL_TRUE == stack_isfull(pstStack))
    {
        return ERROR_FAILED;
    }

    *pstStack->ppvTop = pvItem;
    pstStack->ppvTop++;

    return ERROR_SUCCESS;
}

/*******************************************************************************
    Func Name:  StackPop
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Pop an item out of stack
        Input:  IN Stack_S *pstStack
       Output:  NONE  
       Return:  VOID*, the poped out item
                NULL
      Caution:  The function only removes items from stack, but the memery is 
                left to users to free
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* StackPop(IN Stack_S *pstStack)
{
    VOID *pvItem = NULL;

    if (NULL == pstStack)
    {
        return NULL;
    }
    if (BOOL_TRUE == stack_isempty(pstStack))
    {
        return NULL;
    }

    pvItem = *(pstStack->ppvTop - 1);
    *(pstStack->ppvTop - 1) = NULL;
    pstStack->ppvTop--;

    return pvItem;
}

/*******************************************************************************
    Func Name:  StackPeek
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  look for the top item of stack
        Input:  IN Stack_S *pstStack
       Output:  NONE  
       Return:  VOID*, the first item in stack
                NULL
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* StackPeek(IN Stack_S *pstStack)
{
    VOID *pvItem = NULL;

    if (NULL == pstStack)
    {
        return NULL;
    }
    if (BOOL_TRUE == stack_isempty(pstStack))
    {
        return NULL;
    }

    pvItem = *(pstStack->ppvTop - 1);

    return pvItem;    
}

/*******************************************************************************
    Func Name:  StackPrint
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Print all items in stack from top to bottom
        Input:  IN Stack_S *pstStack
       Output:  NONE  
       Return:  NONE
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID StackPrint(IN Stack_S *pstStack)
{
    VOID **ppvCursor = NULL;

    if (NULL == pstStack || NULL == pstStack->pfPrint)
    {
        return;
    }
    if (BOOL_TRUE == stack_isempty(pstStack))
    {
        return;
    }    

    ppvCursor = pstStack->ppvTop - 1;
    while (ppvCursor >= pstStack->ppvStack)
    {
        pstStack->pfPrint(*ppvCursor);
        ppvCursor--;
    }

    return;
}

/*******************************************************************************
    Func Name:  StackNumber
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Return how many items in stack
        Input:  IN Stack_S *pstStack
       Output:  NONE
       Return:  UINT
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
UINT StackNumber(IN Stack_S *pstStack)
{
    UINT uiRet = 0;

    if (NULL == pstStack)
    {
        return 0;
    }

    uiRet = pstStack->ppvTop - pstStack->ppvStack;
    return uiRet;
}