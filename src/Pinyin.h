//
//  Pinyin.h
//  Aspire
//
//  Created by MaoKebing on 12/14/15.
//  Copyright © 2015 Aspire. All rights reserved.
//

#ifndef Pinyin_h
#define Pinyin_h

#include <stdio.h>

typedef struct PyStr
{
	unsigned short *u2char;                                  //字符数组
	size_t len;                                              //个数
	
}PyStr;

typedef struct PyIds
{
	size_t *id;                                              //字符数组
	size_t len;                                              //个数
	
}PyIds;


/**
 *  获取汉字拼音
 *
 *  @param output    输出**unicode字符数组
 *  @param input     输入*unicode字符数组
 *  @param insize    输入数组长度
 *
 *  @return 输出数组长度
 */
size_t get_pinyin(unsigned short **output, const unsigned short *input, size_t insize);


void add_contact(size_t id, PyStr name, PyStr phone);
void replace_contact(size_t id, PyStr name, PyStr phone);
void delete_contact(size_t id);
void search_contact(PyStr keywords, PyIds* name_matches, PyIds* phone_matches);


/**
 *  初始化搜索
 */
void pinyin_init();

/**
 *  释放搜索
 */
void pinyin_free();

#endif /* Pinyin_h */
