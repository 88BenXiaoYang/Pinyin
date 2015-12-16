//
//  Pinyin.c
//  TESTC
//
//  Created by Mao on 12/14/15.
//  Copyright © 2015 00000. All rights reserved.
//

#include "SearchCore.h"
#include <string.h>
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

static SearchTree* iSearchTree = NULL;
extern const  char *PinYinCode[];

/**
 *  初始化搜索
 */


void pinyin_init()
{
	if (!iSearchTree)
	{
		iSearchTree = malloc(sizeof(SearchTree));
		SearchTreeInit(iSearchTree);
	}
}


/**
 *  获取汉字拼音
 *
 *  @param output    输出**unicode字符数组
 *  @param input     输入*unicode字符数组
 *  @param insize    输入数组长度
 *
 *  @return 输出数组长度
 */
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

/*
 * Class:     com_aspire_pinyin_Pinyin
 * Method:    getPinyin
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_aspire_pinyin_Pinyin_getPinyin
  (JNIEnv *env, jclass cls, jstring string) {
	if (string == NULL)
		return NULL;

	const jchar* src = (*env)->GetStringChars(env, string, 0);
	if (!src)
		return NULL;

	jsize size = (*env)->GetStringLength(env, string);

	unsigned short* dst = NULL;

	size_t dst_size = get_pinyin(&dst, (unsigned short*) src, size);
    (*env)->ReleaseStringChars( env, string, src);

	if (!dst || !dst_size)
		return NULL;

	jstring our_string = (*env)->NewString(env, (jchar*) dst, dst_size);
    free( dst );

	return our_string;
}

#ifdef __cplusplus
}
#endif
