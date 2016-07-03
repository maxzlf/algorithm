/******************************************************************************\
Copyright(C):   Huazhong University of Science & Technology.
    FileName:   type.h
      Author:   Zhulinfeng
     Version:   2.0
        Date:   2014-9-16
 Description:   Define some most used value types, easy for coding, 
                decreasing errors.
      Others:   
    ----------------------------------------------------------------------------        
    Modification History        
    Date            Author          Modification
    ----------------------------------------------------------------------------
    YYYY-MM-DD
\******************************************************************************/

#ifndef _TYPE_H_
#define _TYPE_H_

/**IN**/
#ifndef IN
#define IN
#endif

/**OUT**/
#ifndef OUT
#define OUT
#endif

/**INOUT**/
#ifndef INOUT
#define INOUT
#endif

/**NULL**/
#ifndef NULL
#define NULL 0
#endif

/**PUBLIC**/
#ifndef PUBLIC
#define PUBLIC
#endif

/**PRIVATE**/
#ifndef PRIVATE
#define PRIVATE static
#endif

/**BOOL_FALSE**/
#ifndef BOOL_FALSE
#define BOOL_FALSE 0
#endif

/**BOOL_TRUE**/
#ifndef BOOL_TRUE
#define BOOL_TRUE 1
#endif

typedef int             BOOL_T;
typedef char            BYTE;
typedef char            CHAR;
typedef unsigned char   UCHAR;
typedef short           SHORT;
typedef unsigned short  USHORT;
typedef int             INT;
typedef unsigned int    UINT;
typedef long            LONG;
typedef unsigned long   ULONG;
typedef float           FLOAT;
typedef double          DOUBLE;
typedef long double     LDOUBLE; 
typedef void            VOID;

/*******************************************************************************
    Func Name:  PF_COMPARE
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Callback function that compare two user data.
        Input:  IN VOID *pvFirst, the first user data
                IN VOID *pvSecond, the second user data
       Output:  NONE  
       Return:  >0, pvFirst > pvSecond
                =0, pvFirst = pvSecond
                <0, pvFirst < pvSecond
      Caution:  1. The two params should never be NULL, or an assertion'll occur
                2. The two params should be the same type, or the return answer
                   can be confusing
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
typedef INT (*PF_COMPARE)(IN VOID *pvFirst, IN VOID *pvSecond);

/*******************************************************************************
    Func Name:  PF_PRINT
 Date Created:  2014-9-17
       Author:  Zhulinfeng
  Description:  Callback function that print data.
        Input:  IN VOID *pvItem
       Output:  NONE  
       Return:  NONE
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
typedef VOID (*PF_PRINT)(IN VOID *pvItem);

/*******************************************************************************
    Func Name:  PF_FREE
 Date Created:  2014-9-20
       Author:  Zhulinfeng
  Description:  Callback function that free data.
        Input:  IN VOID *pvItem
       Output:  NONE  
       Return:  NONE
      Caution:  NONE
  ----------------------------------------------------------------------------
  Modification History
  Date    Author    Modification
  ----------------------------------------------------------------------------
  YYYY-MM-DD      
*******************************************************************************/
typedef VOID (*PF_FREE)(IN VOID *pvItem);

#endif