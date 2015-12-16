//
//  MISPinyin.m
//  0000
//
//  Created by Mao on 12/16/15.
//  Copyright © 2015 00000. All rights reserved.
//

#import "MISPinyin.h"
#include "SearchCore.h"

static SearchTree* iSearchTree = NULL;

extern const  char *PinYinCode[];

@implementation MISPinyin


+ (void)initialize {
	if (self == [MISPinyin class]) {
		iSearchTree = malloc(sizeof(SearchTree));
		SearchTreeInit(iSearchTree);
	}
}

/**
 *  获取汉字拼音
 *
 *  @param hanzi 输入汉字
 *
 *  @return 拼音
 */
+ (NSString *)pinyinWithHanzi:(NSString *)hanzi {
	NSString* outstring = @"";
	
	if (hanzi.length == 0) {
		return outstring;
	}
	
	size_t bufferSize = 256;
	
	//输出des
	size_t outlen = 0;
	WordCode code;
	u2char des[bufferSize];
	memset(des, 0, bufferSize * 2);
	
	//查找拼音
	for(int i = 0; i < hanzi.length; i ++)
	{
		unichar ch = [hanzi characterAtIndex:i];
		
		Word2Code(ch, &code);
		
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
		outstring = [NSString stringWithCharacters:des length:outlen];
	}
	
	return outstring;
}


@end
