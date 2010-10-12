// Copyright (c) The HLSL2GLSLFork Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE.txt file.


#include "osinclude.h"

//
// string manipulation
//
static void StrToLower(char *str) 
{
   int i, length;
   
   length = strlen(str);
   
   for(i = 0;i < length;i++) 
      str[i] = tolower(str[i]);
}

int stricmp(const char *str1, const char *str2) 
{
   char *str1Copy, *str2Copy;
   int retVal;
   
   str1Copy = new char[strlen(str1) + 1];
   str2Copy = new char[strlen(str2) + 1];

   strcpy(str1Copy, str1);
   strcpy(str2Copy, str2);

   StrToLower(str1Copy);
   StrToLower(str2Copy);
   
   retVal = strcmp(str1Copy, str2Copy);
   
   delete str1Copy;
   delete str2Copy;
   
   return retVal;
}

//
// Thread Local Storage Operations
//
OS_TLSIndex OS_AllocTLSIndex()
{
    OS_TLSIndex key;
    if (pthread_key_create(&key, NULL) != 0)
    {
        assert(0 && "OS_AllocTLSIndex(): Unable to allocate Thread Local Storage");
        return 0;
    }
    
    return key;
}


bool OS_SetTLSValue(OS_TLSIndex nIndex, void *lpvValue)
{
    if (pthread_setspecific(nIndex, lpvValue) != 0)
    {
		assert(0 && "OS_SetTLSValue(): Invalid TLS Key");
		return false;
	}

	return true;
}


bool OS_FreeTLSIndex(OS_TLSIndex nIndex)
{
    if (pthread_key_delete(nIndex) != 0)
    {
		assert(0 && "OS_SetTLSValue(): Invalid TLS Index");
		return false;
	}

	return true;
}
