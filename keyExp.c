// Date: 26 August, 2014
// Author : Surbhi Shah
// Description : Key Expansion step of AES Algorithm
#include<stdio.h>
typedef struct word{
	char bytes[4];
}word;
/**********************************************************/
word XOR(word x,word y){
	word z;
	int i;
	for(i=0;i<4;i++){
		z.bytes[i]= x.bytes[i] ^ y.bytes[i];
	}
	return z;
}
/**********************************************************/
// n=  4 (128 bit key ) or 6 (192 bit key) or 8 (256 bit key) 
// n = number of words in a key . A word has 4 bytes so 16 bits. 
int keyExpansion(char key[], char expandedKey[], int n){
	int rounds = n+6;// rounds = number of rounds 
	if(sizeof(key) != n*4)
		return -1;
	if(sizeof(expandedKey)!= 16*(rounds+1))
		return -2;

	// Step 1 : Convert the key into word format 

	// Step 2 : Call generateNextRoundKey in a loop and populate expandedKey
	// Step 3 : return array of expanded Key
}
/**********************************************************/
word g(word w){ // function used by generateNextRoundKey
	int i=1;
	//-------------- One byte left circular rotation-----------
	char tmp = w.bytes[0];
	w.bytes[0]=w.bytes[1];
	w.bytes[1]=w.bytes[2];
	w.bytes[2]=w.bytes[3];
	w.bytes[3]=tmp;

	//-------------- Byte Substitution by the same lookup table as used in Sub Bytes step-----------
	// Use Rohit's function for Byte Sub
	// or use S Box of his code 
	// TODO

	
	//-------------- XOR with round constant-----------
	// we don't need more than 10 round constants 
	// 128 bit key requires 10 roundConstants, 192 bit key require even less
	char rcon[] = {0x01 ,0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
	word roundConstant={8,0,0,0};
	w = XOR(roundConstant, w);


}
/**********************************************************/
void generateNextRoundKey(word roundKey[], word nextRoundKey[], const int length){
	
	//-------------- Calculate nextRoundKey[0]-----------

	nextRoundKey[0] =  XOR(roundKey[0], g(roundKey[length-1])); 
	
	//-------------- Calculate nextRoundKey[1 to length-1]--------------
	
	int i =1;
	for(;i<length;i++){
		nextRoundKey[i]= XOR(nextRoundKey[i-1], roundKey[i]);
	}
	return;
}
/**********************************************************/
int main(){
	return 0;
}
/**********************************************************/



