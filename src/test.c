/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   sort.c
      Author:   Zhulinfeng
     Version:   1.0
        Date:   2014-9-16
 Description:   sort algorithms.
      Others:   
    ----------------------------------------------------------------------------        
    Modification History        
    Date            Author          Modification
    ----------------------------------------------------------------------------
    YYYY-MM-DD
\******************************************************************************/

/**include system headfiles**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>    
#include <assert.h>

/**include public headfiles**/
#include "../include/type.h"
#include "../include/err.h"
#include "../include/length.h"

/**include module headfiles**/
#include "../include/heap.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/linklist.h"

static INT compare(IN VOID *puiFirst, IN VOID *puiSecond)
{
    assert(NULL != puiFirst);
    assert(NULL != puiSecond);

    return *(UINT *)puiFirst - *(UINT *)puiSecond;
}

static VOID print(IN VOID *puiNum)
{
    assert(NULL != puiNum);
    printf("%u\n", *(UINT *)puiNum);
    return;
}

int main()
{ 
    UINT uiCount = 100;
    UINT *puiNum = NULL;

    SLHead_S *pstSL = SLHeadCreate(LNKLST_NOORDER, compare, print, free);
    if (NULL == pstSL)
    {
        printf("create linked list failed\n");
        return 0;
    }

    for (uiCount = 0; uiCount < 100; uiCount++)
    {
        puiNum = (UINT *)malloc(sizeof(UINT));
        *puiNum = uiCount;
        SLHeadAddHead(pstSL, puiNum);
    }

    for (uiCount = 30; uiCount > 0; uiCount--)
    {
        SLHeadDelHead(pstSL);
    }

    SLHeadPrint(pstSL);
    printf("total number : %d\n", SLHeadNumber(pstSL));

    SLHeadFree(pstSL);

    return 0;
}
