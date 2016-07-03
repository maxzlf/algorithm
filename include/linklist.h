/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   linklist.h
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-19
 Description:   Interface of linked list.
      Others:   
    ----------------------------------------------------------------------------        
    Modification History        
    Date            Author          Modification
    ----------------------------------------------------------------------------
    YYYY-MM-DD
\******************************************************************************/

#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#define LNKLST_NOORDER  0   /*linked list have no order*/
#define LNKLST_MINORDER 1   /*linked list is ordered*/
#define LNKLST_MAXORDER 2   /*linked list is reversly ordered*/
#define LNKLST_UPSPACE  3   

typedef struct tagSLNode_S
{
    struct tagSLNode_S *pstNext;
    VOID *pvItem;
}SLNode_S;

typedef struct tagSLHead_S
{
    SLNode_S *pstFirst;
    UINT uiType;
    PF_COMPARE pfCompare;
    PF_PRINT pfPrint;
    PF_FREE pfFree;
}SLHead_S;

#define SLHEAD_FOREACH(pstSLHead, pvItem, pstSLNode) \  
        for(pstSLNode=pstSLHead->pstFirst, NULL==pstSLNode?pvItem=NULL:pvItem=pstSLNode->pvItem; \
            NULL!=pvItem; \
            pstSLNode=pstSLNode->pstNext, NULL==pstSLNode?pvItem=NULL:pvItem=pstSLNode->pvItem) \

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
      Caution:  pfPrint can be NULL
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
                       IN PF_FREE pfFree);

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
VOID SLHeadFree(IN SLHead_S *pstSLHead);

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
                place, otherwise the item will just be appended to the tail
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
ULONG SLHeadAdd(IN SLHead_S *pstSLHead, IN VOID *pvItem);

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
ULONG SLHeadAddHead(IN SLHead_S *pstSLHead, IN VOID *pvItem);

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
ULONG SLHeadAddTail(IN SLHead_S *pstSLHead, IN VOID *pvItem);

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
VOID* SLHeadDelete(IN SLHead_S *pstSLHead, IN VOID *pvItem);

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
VOID* SLHeadDelHead(IN SLHead_S *pstSLHead);

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
VOID* SLHeadDelTail(IN SLHead_S *pstSLHead);

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
VOID* SLHeadGetFirst(IN SLHead_S *pstSLHead);

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
VOID* SLHeadGetLast(IN SLHead_S *pstSLHead);

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
VOID* SLHeadGetItem(IN SLHead_S *pstSLHead, IN VOID *pvItem);

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
UINT SLHeadNumber(IN SLHead_S *pstSLHead);

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
VOID SLHeadPrint(IN SLHead_S *pstSLHead);

#endif
