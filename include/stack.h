/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   stack.h
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-17
 Description:   Interface of stack.
      Others:   
    ----------------------------------------------------------------------------        
    Modification History        
    Date            Author          Modification
    ----------------------------------------------------------------------------
    YYYY-MM-DD
\******************************************************************************/

#ifndef _STACK_H_
#define _STACK_H_

typedef struct tagStack_S
{
    UINT uiSize;
    VOID **ppvStack;
    VOID **ppvTop;
    PF_PRINT pfPrint;
    PF_FREE pfFree;
}Stack_S;

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
Stack_S* StackCreate(IN UINT uiSize, PF_PRINT pfPrint, PF_FREE pfFree);

/*******************************************************************************
    Func Name:  StackFree
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  To free memery of stack
        Input:  IN Stack_S *pStack_S
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
VOID StackFree(IN Stack_S *pStack_S);

/*******************************************************************************
    Func Name:  StackPush
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Push an item into stack
        Input:  IN Stack_S *pStack_S
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
ULONG StackPush(IN Stack_S *pStack_S, IN VOID *pvItem);

/*******************************************************************************
    Func Name:  StackPop
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Pop an item out of stack
        Input:  IN Stack_S *pStack_S
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
VOID* StackPop(IN Stack_S *pStack_S);

/*******************************************************************************
    Func Name:  StackPeek
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  look for the top item of stack
        Input:  IN Stack_S *pStack_S
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
VOID* StackPeek(IN Stack_S *pStack_S);

/*******************************************************************************
    Func Name:  StackPrint
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Print all items in stack from top to bottom
        Input:  IN Stack_S *pStack_S
       Output:  NONE  
       Return:  NONE
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
VOID StackPrint(IN Stack_S *pStack_S);


/*******************************************************************************
    Func Name:  StackNumber
 Date Created:  2014-9-18
       Author:  Zhulinfeng
  Description:  Return how many items in stack
        Input:  IN Stack_S *pStack_S
       Output:  NONE
       Return:  UINT
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
UINT StackNumber(IN Stack_S *pStack_S);

#endif