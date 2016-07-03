/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   linklist.c
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-21
 Description:   A realization of linked list.
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
#include "../include/linklist.h"
/**module headfiles**/

/*******************************************************************************
    Func Name:  SLHeadCreate
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  To create a data structure of singly linked list
        Input:  IN UINT uiType
                IN PF_COMPARE pfCompare, callback function to compare two items
                IN PF_PRINT pfPrint, callback function to print item
                IN PF_FREE pfFree, callback function to free item
       Output:  NONE  
       Return:  SLHead_S*,  the singly linked list
                NULL,     error occured
      Caution:  pfCompare can't be NULL
                pfPrint can be NULL
                pfFree can be NULL, then it's the user's responsibility to free
                the memery of items when linked list is destroyed
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
SLHead_S *SLHeadCreate(IN UINT uiType, 
                       IN PF_COMPARE pfCompare,
                       IN PF_PRINT pfPrint,
                       IN PF_FREE pfFree)
{
    SLHead_S *pstSLHead = NULL;

    if (uiType >= LNKLST_UPSPACE || NULL == pfCompare)
    {
        return NULL;
    }

    pstSLHead = (SLHead_S *)malloc(sizeof(SLHead_S));
    if (NULL == pstSLHead)
    {
        return NULL;
    }
    memset(pstSLHead, 0, sizeof(SLHead_S));

    pstSLHead->uiType = uiType;
    pstSLHead->pfCompare = pfCompare;
    pstSLHead->pfPrint = pfPrint;
    pstSLHead->pfFree = pfFree;

    return pstSLHead;
} 

/*******************************************************************************
    Func Name:  SLHeadFree
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  Free the singly linked list
        Input:  IN SLHead_S *pstSLHead
       Output:  NONE  
       Return:  NONE
      Caution:  If you have installed PF_FREE callback function, then all the itmes
                in the linked list will be freed, otherwise it's the user's 
                responsibility to free the memeries of all items
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID SLHeadFree(IN SLHead_S *pstSLHead)
{
    SLNode_S *pstNode = NULL;
    SLNode_S *pstNext = NULL;

    if (NULL == pstSLHead)
    {
        return;
    }

    pstNode = pstSLHead->pstFirst;
    while (NULL != pstNode)
    {
        pstNext = pstNode->pstNext;
        if (NULL != pstSLHead->pfFree && NULL != pstNode->pvItem)
        {
            pstSLHead->pfFree(pstNode->pvItem);
        }
        free(pstNode);
        pstNode = pstNext;
    }

    free(pstSLHead);

    return;
}

/*******************************************************************************
    Func Name:  SLHeadAdd
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  Add an item to the linked list
        Input:  IN SLHead_S *pstSLHead
                IN VOID *pvItem
       Output:  NONE  
       Return:  ULONG
                ERROR_SUCCESS, success
                ERROR_FAILED, failed
      Caution:  If it's an ordered list, the item will insert into a correct
                place, otherwise the item will just be appended to the list
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
ULONG SLHeadAdd(IN SLHead_S *pstSLHead, IN VOID *pvItem)
{
    SLNode_S *pstNode = NULL;
    SLNode_S *pstCursor = NULL;
    SLNode_S *pstTmp = NULL;;
    INT iCmpRet = 0;
    ULONG ulErrCode = ERROR_SUCCESS;

    if (NULL == pstSLHead || NULL == pvItem)
    {
        return ERROR_FAILED;
    }

    pstNode = (SLNode_S *)malloc(sizeof(SLNode_S));
    if (NULL == pstNode)
    {
        return ERROR_FAILED;
    }
    memset(pstNode, 0, sizeof(SLNode_S));
    pstNode->pstNext = NULL;
    pstNode->pvItem = pvItem;

    /**if the linked list has no order**/
    if (LNKLST_NOORDER == pstSLHead->uiType)
    {
        pstNode->pstNext = pstSLHead->pstFirst;
        pstSLHead->pstFirst = pstNode;
        return ulErrCode;
    }

    /**if it's a ordered list**/
    pstCursor = pstSLHead->pstFirst;
    while (NULL != pstCursor)
    {
        iCmpRet = pstSLHead->pfCompare(pstCursor->pvItem, pvItem);
        if ((LNKLST_MINORDER == pstSLHead->uiType && iCmpRet >= 0) ||
            (LNKLST_MAXORDER == pstSLHead->uiType && iCmpRet <= 0))
        {
            break;
        }
        pstTmp = pstCursor;
        pstCursor = pstCursor->pstNext;
    }

    if (NULL == pstTmp)
    {
        pstSLHead->pstFirst = pstNode;
    }
    else
    {
        pstTmp->pstNext = pstNode;
    }
    pstNode->pstNext = pstCursor;

    return ulErrCode;
}

/*******************************************************************************
    Func Name:  SLHeadAddHead
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  Add an item to the head of linked list
        Input:  IN SLHead_S *pstSLHead
                IN VOID *pvItem
       Output:  NONE  
       Return:  ULONG
                ERROR_SUCCESS, success
                ERROR_FAILED, failed
      Caution:  If it's an ordered list, the item will insert into a correct 
                place instead.
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
ULONG SLHeadAddHead(IN SLHead_S *pstSLHead, IN VOID *pvItem)
{
    ULONG ulErrCode = ERROR_SUCCESS;
    SLNode_S *pstNode = NULL;

    if (NULL == pstSLHead || NULL == pvItem)
    {
        return ERROR_FAILED;
    }

    /**if it's an ordered list**/
    if (LNKLST_NOORDER != pstSLHead->uiType)
    {
        return SLHeadAdd(pstSLHead, pvItem);
    }

    /**it's not an ordered list**/
    pstNode = (SLNode_S *)malloc(sizeof(SLNode_S));
    if (NULL == pstNode)
    {
        return ERROR_FAILED;
    }
    memset(pstNode, 0, sizeof(SLNode_S));
    pstNode->pstNext = NULL;
    pstNode->pvItem = pvItem;

    pstNode->pstNext = pstSLHead->pstFirst;
    pstSLHead->pstFirst = pstNode;

    return ulErrCode;
}

/*******************************************************************************
    Func Name:  SLHeadAddTail
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  Add an item to the tail of linked list
        Input:  IN SLHead_S *pstSLHead
                IN VOID *pvItem
       Output:  NONE  
       Return:  ULONG
                ERROR_SUCCESS, success
                ERROR_FAILED, failed
      Caution:  If it's an ordered list, the item will insert into a correct 
                place instead.
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
ULONG SLHeadAddTail(IN SLHead_S *pstSLHead, IN VOID *pvItem)
{
    ULONG ulErrCode = ERROR_SUCCESS;
    SLNode_S *pstNode = NULL;
    SLNode_S *pstCursor = NULL;

    if (NULL == pstSLHead || NULL == pvItem)
    {
        return ERROR_FAILED;
    }

    /**if it's an ordered list**/
    if (LNKLST_NOORDER != pstSLHead->uiType)
    {
        return SLHeadAdd(pstSLHead, pvItem);
    }

    /**it's not an ordered list**/
    pstNode = (SLNode_S *)malloc(sizeof(SLNode_S));
    if (NULL == pstNode)
    {
        return ERROR_FAILED;
    }
    memset(pstNode, 0, sizeof(SLNode_S));
    pstNode->pstNext = NULL;
    pstNode->pvItem = pvItem;

    if (NULL == pstSLHead->pstFirst)
    {
        pstSLHead->pstFirst = pstNode;
        return ulErrCode;
    }

    pstCursor = pstSLHead->pstFirst;
    while (NULL != pstCursor->pstNext)
    {
        pstCursor = pstCursor->pstNext;
    }

    pstCursor->pstNext = pstNode;

    return ulErrCode;    
}

/*******************************************************************************
    Func Name:  SLHeadDelete
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  delete an item in the linked list
        Input:  IN SLHead_S *pstSLHead
                IN VOID *pvItem
       Output:  NONE  
       Return:  VOID*
                NULL
      Caution:  The function just remove the item out of list but won't free
                the memery of it, so it's the user's responsibility to free
                memery
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* SLHeadDelete(IN SLHead_S *pstSLHead, IN VOID *pvItem)
{
    VOID *pvRet = NULL;
    SLNode_S *pstCursor = NULL;
    SLNode_S *pstTmp = NULL;
    INT iCmpRet = 0;

    if (NULL == pstSLHead || NULL == pvItem)
    {
        return NULL;
    }

    /**if the list is empty**/
    if (NULL == pstSLHead->pstFirst)
    {
        return NULL;
    }


    pstCursor = pstSLHead->pstFirst;
    while (NULL != pstCursor)
    {
        iCmpRet = pstSLHead->pfCompare(pstCursor->pvItem, pvItem);
        if (0 == iCmpRet)
        {
            pvRet = pstCursor->pvItem;
            break;
        }
        pstTmp = pstCursor;
        pstCursor = pstCursor->pstNext;
    } 

    /**not found**/
    if (NULL == pstCursor)
    {
        return NULL;
    }

    if (NULL == pstTmp)
    {
        pstSLHead->pstFirst = pstCursor->pstNext;
    }
    else
    {
        pstTmp->pstNext = pstCursor->pstNext;
    }

    free(pstCursor);
    return pvRet;
}

/*******************************************************************************
    Func Name:  SLHeadDelHead
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  delete the first item in the linked list
        Input:  IN SLHead_S *pstSLHead
       Output:  NONE  
       Return:  VOID*
                NULL
      Caution:  The function just remove the item out of list but won't free
                the memery of it, so it's the user's responsibility to free
                memery
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* SLHeadDelHead(IN SLHead_S *pstSLHead)
{
    VOID *pvRet = NULL;
    SLNode_S *pstTmp = NULL;

    if (NULL == pstSLHead || NULL == pstSLHead->pstFirst)
    {
        return NULL;
    }

    pstTmp = pstSLHead->pstFirst;
    pvRet = pstTmp->pvItem;
    pstSLHead->pstFirst = pstTmp->pstNext;

    free(pstTmp);
    return pvRet;
}

/*******************************************************************************
    Func Name:  SLHeadDelTail
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  delete the last item in the linked list
        Input:  IN SLHead_S *pstSLHead
       Output:  NONE  
       Return:  VOID*
                NULL
      Caution:  The function just remove the item out of list but won't free
                the memery of it, so it's the user's responsibility to free
                memery
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* SLHeadDelTail(IN SLHead_S *pstSLHead)
{
    VOID *pvRet = NULL;
    SLNode_S *pstCursor = NULL;
    SLNode_S *pstTmp = NULL;

    if (NULL == pstSLHead || NULL == pstSLHead->pstFirst)
    {
        return NULL;
    }

    pstCursor = pstSLHead->pstFirst;
    while (NULL != pstCursor->pstNext)
    {
        pstTmp = pstCursor;
        pstCursor = pstCursor->pstNext;
    }

    pvRet = pstCursor->pvItem;

    if (NULL == pstTmp)
    {
        pstSLHead->pstFirst = NULL;
    }
    else 
    {
        pstTmp->pstNext = NULL;
    }

    free(pstCursor);

    return pvRet;
}

/*******************************************************************************
    Func Name:  SLHeadGetFirst
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  get the first item in the linked list
        Input:  IN SLHead_S *pstSLHead
       Output:  NONE  
       Return:  VOID*
                NULL
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* SLHeadGetFirst(IN SLHead_S *pstSLHead)
{
    if (NULL == pstSLHead || NULL == pstSLHead->pstFirst)
    {
        return NULL;
    }

    return pstSLHead->pstFirst->pvItem;
}

/*******************************************************************************
    Func Name:  SLHeadGetLast
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  get the last item in the linked list
        Input:  IN SLHead_S *pstSLHead
       Output:  NONE  
       Return:  VOID*
                NULL
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* SLHeadGetLast(IN SLHead_S *pstSLHead)
{
    SLNode_S *pstCursor = NULL;

    if (NULL == pstSLHead || NULL == pstSLHead->pstFirst)
    {
        return NULL;
    }

    pstCursor = pstSLHead->pstFirst;
    while (NULL != pstCursor->pstNext)
    {
        pstCursor = pstCursor->pstNext;
    }

    return pstCursor->pvItem;
}

/*******************************************************************************
    Func Name:  SLHeadGetItem
 Date Created:  2014-9-20
       Author:  Zhulinfeng
  Description:  get a matched item in the linked list
        Input:  IN SLHead_S *pstSLHead
                IN VOID *pvItem
       Output:  NONE  
       Return:  VOID*
                NULL
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID* SLHeadGetItem(IN SLHead_S *pstSLHead, IN VOID *pvItem)
{
    VOID *pvRet = NULL;
    SLNode_S *pstCursor = NULL;
    INT iCmpRet = 0;

    if (NULL == pstSLHead || NULL == pvItem || NULL == pstSLHead->pstFirst)
    {
        return NULL;
    }

    pstCursor = pstSLHead->pstFirst;
    while (NULL != pstCursor)
    {
        iCmpRet = pstSLHead->pfCompare(pstCursor->pvItem, pvItem);
        if (0 == iCmpRet)
        {
            pvRet = pstCursor->pvItem;
            break;
        }
        pstCursor = pstCursor->pstNext;
    }

    return pvRet;
}

/*******************************************************************************
    Func Name:  SLHeadNumber
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  get how many items in the linked list
        Input:  IN SLHead_S *pstSLHead
       Output:  NONE  
       Return:  UINT
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
UINT SLHeadNumber(IN SLHead_S *pstSLHead)
{
    UINT uiCount = 0;
    SLNode_S *pstCursor = NULL;

    if (NULL == pstSLHead || NULL == pstSLHead->pstFirst)
    {
        return 0;
    }

    pstCursor = pstSLHead->pstFirst;
    while (NULL != pstCursor)
    {
        uiCount++;
        pstCursor = pstCursor->pstNext;
    }

    return uiCount;
}

/*******************************************************************************
    Func Name:  SLHeadPrint
 Date Created:  2014-9-20 
       Author:  Zhulinfeng
  Description:  print all items in the linked list
        Input:  IN SLHead_S *pstSLHead
       Output:  NONE  
       Return:  UINT
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID SLHeadPrint(IN SLHead_S *pstSLHead)
{
    SLNode_S *pstCursor = NULL;

    if (NULL == pstSLHead ||
        NULL == pstSLHead->pstFirst ||
        NULL == pstSLHead->pfPrint)
    {
        return;
    }

    pstCursor = pstSLHead->pstFirst;
    while (NULL != pstCursor)
    {
        pstSLHead->pfPrint(pstCursor->pvItem);
        pstCursor = pstCursor->pstNext;
    }

    return;
}
