package com.aspire.pinyin;

public class Pinyin{
	/**
	 * 获取汉字pinyin的方法
	 * @param input 输入汉字的char[]
	 * @return pinyin的char[]
	 */
	public static native String getPinyin(String input);
	
	static {
		System.loadLibrary("pinyin");
	}
}
