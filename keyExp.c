// Date: 26 August, 2014
// Author : Surbhi Shah
// Description : Key Expansion step of AES Algorithm
#include<stdio.h>
#include<stdlib.h>	
/**********************************************************/

/*  This function is used by key expansion method and g
 *	It returns the sbox substitution for "byte"
 *  Input : byte : the byte whose sbox value is required
 *  Output : sbox value
 */
unsigned char sbox(unsigned char byte){
	unsigned char s[256] = 	
	{
	   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
	};
	return s[byte];	
}
/**********************************************************/
/*  This function is used by key expansion method
 *	It performs following transformations on a word
 *		1. One Byte Left circular rotation
 *		2. Byte Substitution using sbox
 *		3. XOR first byte with RCON Value
 *  Input:  word : 4 byte array of bytes 
 *			iteration: function uses rcon value which depends on iteration value
 *			NOTE: iteration value starts with zero 
 *	Output: void , operations are carried out on word itself
*/
void g(unsigned char *word, int iteration){ 
	int i;
	//-------------- One byte left circular rotation-----------
	unsigned char tmp = word[0];
	word[0]=word[1];
	word[1]=word[2];
	word[2]=word[3];
	word[3]=tmp;
	//-------------- Byte Substitution by the same lookup table as used in Sub Bytes step-----------
	for(i=0;i<4;i++){
		word[i]= sbox(word[i]);
	}
	
	//-------------- XOR with round constant-----------
	// we don't need more than 10 round constants 
	// 128 bit key requires 10 roundConstants, 192 bit key variant requires 8 and 256 bit variant requires 7
	unsigned char rcon[] = {0x01 ,0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
	word[0]= rcon[iteration] ^ word[0];
	
}
/**********************************************************/
// n = number of bytes in a key .
// n =16 for 128 bit key, 24 for 192 bit key and 32 for 256 bit key
/*
 *	Input: 
 *	key: user specified key 
 *	expandedKey: array of unsigned chars for expanded key 
 *				NOTE: function does not check the size of expandedKey
 *						It should be according to n
 *						if n = 16 size of expandedKey >= 176
 *						if n = 24 size of expandedKey >= 208
 *						if n = 32 size of expandedKey >= 240
 *	n = size of key (in bytes)
 *	Output:
 *	void, function works on expandedKey  
*/
void keyExpansion(unsigned char key[], unsigned char expandedKey[], const int n){
	int rounds = n/4 +6;// rounds = number of rounds 
	int sizeExpandedKey = 16*(rounds+1);// expected size of expandedKey
	int iteration=0;// for round constants // should start with zero
	int i;
	int sizeCurrent=0;// current size of expanded key
	//-------------- First n bytes of expanded key are same as those of original key, so copy--------------
	for(i=0;i<n;i++){
		expandedKey[i]= key[i];	
	}
	sizeCurrent = n;// we already have n bytes in the expanded key 
	
	unsigned char tmp[4];
	while(sizeCurrent < sizeExpandedKey){
		// copy previous 4 bytes in tmp .. If key = (w1 w2 w3 w4), tmp will contain w1
		for(i=0;i<4;i++){
			tmp[i]= expandedKey[( sizeCurrent - 4 ) + i ];
		}
		// apply g every n bytes 
		if(sizeCurrent % n ==0){
			g(tmp, iteration);
			iteration++;

		}
		// Special case for 256 bit key 
		// Why is this added?? TODO
		if( n==32 &&   ((sizeCurrent % 32) == 16)){
			for(i=0;i<4;i++){
				tmp[i]= sbox(tmp[i]);
			}
		}
		// XOR with "word" n bytes before this one
		for(i=0;i<4;i++){
			expandedKey[sizeCurrent] = expandedKey[sizeCurrent - n] ^ tmp[i];
			sizeCurrent++;
		}
	}
}
/**********************************************************/
