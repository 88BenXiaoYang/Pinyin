//
//  Pinyin.c
//  Aspire
//
//  Created by MaoKebing on 12/14/15.
//  Copyright © 2015 Aspire. All rights reserved.
//

#include "Pinyin.h"
#include "SearchCore.h"

static SearchTree* iSearchTree = NULL;

extern const  char *PinYinCode[];

size_t get_pinyin(unsigned short **output,
				  const unsigned short *input,
				  size_t insize)
{
	if (!input || !insize)
		return 0;
	
	pinyin_init();
	
	size_t bufferSize = 256;
	
	//输出des
	size_t outlen = 0;
	WordCode code;
	u2char des[bufferSize];
	memset(des, 0, bufferSize * 2);
	
	//查找拼音
	for(int i = 0; i < insize; i ++)
	{
		Word2Code(input[i], &code);
		
		if( code.PyCodeNum == 0)
		{
			des[outlen++] = code.Word;
		}
		else
		{
			for (int k = 0 ; k < code.PyCodeNum; k++)
			{
				const char* pyCode = PinYinCode[code.PyCodeIndex[k]];
				
				while(*pyCode)
				{
					des[outlen++] = *pyCode;
					pyCode ++;
				}
			}
		}
	}
	
	//输出的des到buffer中
	if (outlen > 0) {
		*output = malloc(outlen * 2);
		memcpy(*output, des, outlen * 2);
	}
	
	return outlen;
}


void pinyin_init()
{
	if (!iSearchTree)
	{
		iSearchTree = malloc(sizeof(SearchTree));
		SearchTreeInit(iSearchTree);
	}
}

void pinyin_free()
{
	FreeSearchTree(iSearchTree);
}
