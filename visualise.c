#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


//Function will convert decimals into binaryInput
void exitFunction(){
  printf("Input Error.\n");
  exit(1);
}

void decimalToBinary(bool checkUnsigned, long input, char *binaryValue,int size){
  //Sets the binary string to all 0's
  memset(binaryValue,'0',size);
  int count = size;
  if (checkUnsigned == false) {
    count -= 1;
    //count = count - 1
    if (input < 0) {
      //If the number is negative, then it sets the first bit to 1. Represents negative
      binaryValue[0] = '1';
      input += pow(2,size-1);
    }
  }
  while (count > 0){
    long result = input / (long)(pow(2,count-1));
    if (result != 0){
      binaryValue[size - count] = '1';
      input -= (long)pow(2,count-1);
    }
    count--;
  }
  //If the user didn't enter a valid input at the start, this next check catches it.
  if (input != 0) exitFunction();
  binaryValue[size] = '\0';
}

long binaryToDecimal(char *binaryInput, int size,bool unsignedCheck) {
  int count = size;
  long sum = 0;
  //If the number is positive and unsigned, then it should check the leftmost bit.
  //If number is negative, then the leftmost bit represent the sign and so shouldnt be included in while loop.
  int limit = 0;
  if ((unsignedCheck == false) && (binaryInput[0] == '1')) {
    sum = (long)-pow(2,size-1);
    limit = 1;
  }
  while (count > limit) {
    if (binaryInput[count-1] == '1') {
      sum += (long) pow(2,size-count);
    }
    count--;
  }
  return sum;
}


void printBinary(char *binaryInput, int size){
  for (int i=0; size > i; i++){
    //This creates a space so output is in nibbles.
    if ((i % 4 == 0) && (i != 0)) printf(" %c",binaryInput[i]);
    else printf("%c",binaryInput[i]);
  }
}

//This function allocates size depending on what data type is specified
int convertSize(char *argv[]){
  int dataTypeSize = 0;
  int arrayIndexNumber = 1;
  //First check is to see if the data type is unsigned or not
  if (strcmp(argv[1],"unsigned")==0) arrayIndexNumber = 2;
  if (strcmp(argv[arrayIndexNumber],"char")==0) dataTypeSize = 8;
  else if (strcmp(argv[arrayIndexNumber],"int")==0) dataTypeSize = 32;
  else if (strcmp(argv[arrayIndexNumber],"long")==0) dataTypeSize = 64;
  //If the user doesnt enter a valid dataType, size = 0 as it hasnt been changed since it was declared  Input error. is outputted.
  if (dataTypeSize == 0) exitFunction();
  return dataTypeSize;
}


bool checkBinary(int n, char *argv[]){
  int indexNumber = 2;
  //If n=4, data type specified is of form unsigned _____
  //If data type is unsigned then the binary value starts from 3rd agrument from command line arguments
  if (n >= 4) indexNumber = 3;
  for (int i = 0; i < 4 ;i++){
    if ((argv[indexNumber][i] == '0') || (argv[indexNumber][i] == '1'));
    else return false;
  }
  return true;
}

long stringToNumber(char *argv[], int arrayIndex){
  unsigned long sum = 0;
  int i = 0;
  if (argv[arrayIndex][0] == '-') i+=1;
  while (argv[arrayIndex][i] != '\0') {
    sum = (sum * 10) + (argv[arrayIndex][i] - '0');
    i++;
  }
  if (argv[arrayIndex][0] == '-') sum = sum * -1;
  return sum;
}


void runInputs(int n, char *argv[], int size, char *binaryInput, long *input){
  // array index is where the values start being entered from
  int arrayIndex = 2;
  bool unsignedCheck = false;
  if (strcmp(argv[1],"unsigned")==0){
    arrayIndex = 3;
    unsignedCheck = true;
  }
  int i = arrayIndex;
  if (checkBinary(n,argv) == true){
    strcpy(binaryInput,argv[i]);
    i++;
    while (i < n){
      strcat(binaryInput,argv[i]);
      i++;
    }
    binaryInput[size] = '\0';
    long decValue = binaryToDecimal(binaryInput,size,unsignedCheck);
    printf("%ld\n",decValue);
  }
  else {
    *input = stringToNumber(argv,arrayIndex);
    decimalToBinary(unsignedCheck, *input, binaryInput, size);
    printBinary(binaryInput, size);
  }
}


void assert(int line, bool b){
  if (b) return;
  printf("The test on line %d fails\n",line);
  exit(1);
}


void testDecimalToBinaryChar() {
  int size = 8;
  char binary[9];

  decimalToBinary(false,-128,binary,size);
  assert(__LINE__, (strcmp(binary,"10000000")==0));


  decimalToBinary(false,-100,binary,size);
  assert(__LINE__, (strcmp(binary,"10011100")==0));

  decimalToBinary(false,-1,binary,size);
  assert(__LINE__, (strcmp(binary,"11111111")==0));

  decimalToBinary(false,0,binary,size);
  assert(__LINE__, (strcmp(binary,"00000000")==0));

  decimalToBinary(false,1,binary,size);
  assert(__LINE__, (strcmp(binary,"00000001")==0));

  decimalToBinary(false,89,binary,size);
  assert(__LINE__, (strcmp(binary,"01011001")==0));

  decimalToBinary(false,127,binary,size);
  assert(__LINE__, (strcmp(binary,"01111111")==0));

}


void testDecimalToBinaryUnsignedChar() {
  int size = 8;
  char binary[9];

  decimalToBinary(true, 0,binary,size);
  assert(__LINE__, (strcmp(binary,"00000000")==0));

  decimalToBinary(true,255,binary,size);
  assert(__LINE__, (strcmp(binary,"11111111")==0));

  decimalToBinary(true,8,binary,size);
  assert(__LINE__, (strcmp(binary,"00001000")==0));

  decimalToBinary(true,99,binary,size);
  assert(__LINE__, (strcmp(binary,"01100011")==0));

  decimalToBinary(true,250,binary,size);
  assert(__LINE__, (strcmp(binary,"11111010")==0));


}


void testDecimalToBinaryInt() {
  int size = 32;
  char binary[33];

  decimalToBinary(false,-2147483648,binary,size);
  assert(__LINE__, (strcmp(binary,"10000000000000000000000000000000")==0));

  decimalToBinary(false,-1409437577,binary,size);
  assert(__LINE__, (strcmp(binary,"10101011111111011011000001110111")==0));

  decimalToBinary(false,-1,binary,size);
  assert(__LINE__, (strcmp(binary,"11111111111111111111111111111111")==0));

  decimalToBinary(false,0,binary,size);
  assert(__LINE__, (strcmp(binary,"00000000000000000000000000000000")==0));

  decimalToBinary(false,1,binary,size);
  assert(__LINE__, (strcmp(binary,"00000000000000000000000000000001")==0));

  decimalToBinary(false,302015425,binary,size);
  assert(__LINE__, (strcmp(binary,"00010010000000000110001111000001")==0));

  decimalToBinary(false,1982778738,binary,size);
  assert(__LINE__, (strcmp(binary,"01110110001011101100110101110010")==0));

  decimalToBinary(false,2147483647,binary,size);
  assert(__LINE__, (strcmp(binary,"01111111111111111111111111111111")==0));
}

void testDecimalToBinaryUnsignedInt(){
  int size = 32;
  char binary[33];

  decimalToBinary(true,1,binary,size);
  assert(__LINE__, (strcmp(binary,"00000000000000000000000000000001")==0));

  decimalToBinary(true,302015425,binary,size);
  assert(__LINE__, (strcmp(binary,"00010010000000000110001111000001")==0));

  decimalToBinary(true,1982778738,binary,size);
  assert(__LINE__, (strcmp(binary,"01110110001011101100110101110010")==0));

  decimalToBinary(true,4294967295,binary,size);
  assert(__LINE__, (strcmp(binary,"11111111111111111111111111111111")==0));

}


void testDecimalToBinaryLong() {
  int size = 64;
  char binary[65];

  decimalToBinary(false,-9223372036854775807-1,binary,size);
  assert(__LINE__, (strcmp(binary,"1000000000000000000000000000000000000000000000000000000000000000")==0));

  decimalToBinary(false,9223372036854775807,binary,size);
  assert(__LINE__, (strcmp(binary,"0111111111111111111111111111111111111111111111111111111111111111")==0));

  decimalToBinary(false,9223371486559935991,binary,size);
  assert(__LINE__, (strcmp(binary,"0111111111111111111111110111111111011111110111110001110111110111")==0));

  decimalToBinary(false,6518238630696132087,binary,size);
  assert(__LINE__, (strcmp(binary,"0101101001110101011011110111111111011111110111110001110111110111")==0));

  decimalToBinary(false,9213519862374276535,binary,size);
  assert(__LINE__, (strcmp(binary,"0111111111011100111111110111111111011111110100110001110110110111")==0));

}

void testBinaryToDecimalChar(){
  int size = 8;
  long decValue = binaryToDecimal("10000000",size,false);
  if (decValue != -128 ) printf("Line fails on line 259");

  decValue = binaryToDecimal("01111111",size,false);
  if (decValue != 127 ) printf("Line fails on line 262");

  decValue = binaryToDecimal("10011100",size,false);
  if (decValue != -100 ) printf("Line fails on line 265");

}

void testBinaryToDecimalUnsignedChar(){
  int size = 8;
  long decValue = binaryToDecimal("11111111",size,true);
  if (decValue != 255 ) printf("Line fails on line 268");

  decValue = binaryToDecimal("01100011",size,true);
  if (decValue != 99 ) printf("Line fails on line 270");
}

void testBinaryToDecimalInt(){
  int size = 32;
  long decValue = binaryToDecimal("10000000000000000000000000000000",size,false);
  if (decValue != -2147483648 ) printf("Line fails on line 277");

  decValue = binaryToDecimal("01111111111111111111111111111111",size,false);
  if (decValue != 2147483647 ) printf("Line fails on line 280");
}

void testBinaryToDecimalUnsignedInt(){
  int size = 32;
  long decValue = binaryToDecimal("11111111111111111111111111111111",size,true);
  if (decValue != 4294967295 ) printf("Line fails on line 286");

  decValue = binaryToDecimal("01110110001011101100110101110010",size,true);
  if (decValue != 1982778738 ) printf("Line fails on line 289");
}

void testBinaryToDecimalLong(){
  int size = 64;
  long decValue = binaryToDecimal("0111111111111111111111111111111111111111111111111111111111111111",size,false);
  if (decValue != 9223372036854775807 ) printf("Line fails on line 295");

  decValue = binaryToDecimal("1000000000000000000000000000000000000000000000000000000000000000",size,false);
  if (decValue != (-9223372036854775807-1)) printf("Line fails on line 298");
}

int main(int n, char *argv[n]){
  if (n == 1){
  testBinaryToDecimalChar();
  testBinaryToDecimalUnsignedChar();
  testBinaryToDecimalInt();
  testBinaryToDecimalUnsignedInt();
  testBinaryToDecimalLong();
  testDecimalToBinaryChar();
  testDecimalToBinaryUnsignedChar();
  testDecimalToBinaryInt();
  testDecimalToBinaryUnsignedInt();
  testDecimalToBinaryLong();
  printf("All tests passed\n");
}
  else{
  int size = convertSize(argv);
  char binary[size+1];
  long decimalValue = 0;
  long *pointerValue = &decimalValue;
  runInputs(n,argv,size,binary,pointerValue);
  return 0;
  }
}
