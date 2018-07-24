#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <limits>
#include <bitset>

using namespace std;
int ACC;
int num;
string numS;
vector<string> Memory(255);
std::stringstream HEX;

int iterador=0;
char read;


int bin_to_int(string n1)
{
    int decimalNumber = 0, i = 0, remainder;
    int n=atoi( n1.c_str() );
    while (n!=0)
    {
        remainder = n%10;
        n = n/10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

string int_to_bin(int val)
{
   return bitset<8>(val).to_string() ;
}

string int_to_hex( int i )
{
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(int)*2) 
         << std::hex << i;
  return stream.str();
}
int hex_to_int( string i )
{
   int dirInt;
   std::stringstream ss;
   ss << std::hex << i;
   ss >> dirInt;
   //std::stringstream stream;
  return static_cast<int>(dirInt);
}

int complemento(string i){
   int tam=i.length();
   int num=bin_to_int(i);
   int num2=pow(2,tam);
   return num2-num;  
}

void MLOAD(int value){
   ACC=value;
   iterador++;
}

void DLOAD(int dir){
   ACC=hex_to_int(Memory[dir]);  
   iterador++;
}

void ILOAD(int dir){
   printf(" dir ==== %d \n",hex_to_int(Memory[dir]));
   printf(" dir ==== %d \n",hex_to_int(Memory[hex_to_int(Memory[dir])]));
   ACC+=hex_to_int(Memory[hex_to_int(Memory[dir])]);
   iterador++;
}

void DSTORE(int dir){
   Memory[dir]=int_to_hex(ACC);
   iterador++;
}

void ISTORE(int dir){
   Memory[hex_to_int(Memory[dir])]=int_to_hex(ACC);
   iterador++;
}

void HALT(){
   printf("FINISH\n");
   iterador++;
}

void JMP(int dir){
   iterador=dir;
   //cout<<"JUMP"<<endl;

}

void JZ(int dir){
   if(ACC==0){
      iterador=dir;
      printf("JUMPZ \n");
     // cout<<"JUMPZ"<<endl;
   }else{
      iterador++;
      printf("\n");   
   }
   
}

void JP(int dir){
   if(ACC>0){
      iterador=dir;
      printf("JUMPP \n");
      //cout<<"JUMPP"<<endl;
   }else{
      iterador++;
      printf("\n");
   }
}

void JN(int dir){
   if (ACC<0)
   {
      printf("JUMPN\n");
      iterador=dir;
      //cout<<"JUMPN"<<endl;
   }else{
      printf("\n");
      iterador++;
   }
}

void ADD(int dir){
   ACC=ACC+hex_to_int(Memory[dir]);
   //cout<<"ADD"<<endl;
   iterador++;
}

void NEGATE(){
   ACC=ACC*(-1);
   //cout<<"NEGATE"<<endl;
   iterador++;
   //ACC=complemento(int_to_bin(ACC));
}
int main(int argc, char* argv[]) {
   
   char problem;
   

   cout<<"Que funcion desea usar Multiplicacion(M),Factorial(F)"<<endl;
   cin>>problem;
   vector<string> lectura;
   string dirS;   
 //  vector<string> lectura={"1000","4010","1020","4011","1022","0001","A011","700F","3011","A010","4010","1001","A011","4011","6004","0000"};
  //PARA MULTIPLICACION 
   if (problem=='M')
   {
      lectura={"1000","4011","1000","4012","0001","A011","400A","0000"};
      //lectura={"1000","4011","1000","4012","1000","4013","2012","7010","2011","A013","4013","1001","0001","A012","4012","6006","0000"};
   //cout<<int_to_hex(-255)<<endl;
      int num1;
      int num2;
      do{
         cout<<"escoger los valores de multiplicando y multiplicador sus valores pueden ir de 0-positivos"<<endl;
         cin>>num1;
         cin>>num2;
      }while(num1<0 or num2<0);
      string var1=int_to_hex(num1);
      string var2=int_to_hex(num2);
      for (int i = 1; i < 4; ++i)
      {
         lectura[0][i]=var1[5+i];
         lectura[2][i]=var2[5+i];
      }  
   }
   else if(problem=='F'){
      lectura={"1001","401A","1007","401B","1001","0001","A01A","7019","401A","401C","1000","401D","201C","7016","201B","A01D","401D","1001","0001","A01C","401C","600C","201D","401B","6004","0000"};
      int num;
      do{
         cout<<"escoger el faltorial de q numero desea que sea positivo"<<endl;
         cin>>num;
      }while(num<=0);
      string var1=int_to_hex(num);
      for (int i = 1; i < 4; ++i)
      {
         
         lectura[0][i]=var1[5+i];
         lectura[2][i]=var1[5+i];
      }
   }
   if(problem=='M' or problem =='F'){
   for (int i = 0; i < lectura.size(); ++i)
   {
      Memory[i]=lectura[i];
   }


   unsigned int dirInt;
   int count=0;
   do{
      
      read=(Memory[iterador])[0];
      dirS=Memory[iterador].substr(1);
      dirInt=hex_to_int(dirS);
      /*cout<<ACC<<endl;
      cout<<read<<"  "<<dirInt<<endl;*/
      printf("read %c ==== direccion %s ==== ACC %d ====",read,int_to_hex(dirInt).c_str(),ACC );
      if (read=='0')
      {
         if(Memory[iterador]=="0001"){
            printf("NEGATE \n");
            NEGATE();
         }
         if(Memory[iterador]=="0000"){
            printf("HALT \n");
            HALT();
            break;
         }
      }else if (read=='1')
      {
         printf("MLOAD \n");
         MLOAD(static_cast<int>(dirInt));
      }else if(read=='2'){
         printf("DLOAD \n");
         DLOAD(static_cast<int>(dirInt));
      }else if(read=='3'){
         printf("ILOAD ");
         ILOAD(static_cast<int>(dirInt));
      }else if(read=='4'){
         printf("DSTORE \n");
         DSTORE(static_cast<int>(dirInt));
      }
      else if(read=='5'){
         printf("ISTORE \n");
         ISTORE(static_cast<int>(dirInt));
      }
      else if(read=='6'){
         printf("JMP \n");
         JMP(static_cast<int>(dirInt));
      }
      else if(read=='7'){
         JZ(static_cast<int>(dirInt));
      }
      else if(read=='8'){
         JP(static_cast<int>(dirInt));
      }
      else if(read=='9'){
         JN(static_cast<int>(dirInt));
      }
      else if(read=='A'){
         printf("ADD \n");
         ADD(static_cast<int>(dirInt));
      }
      count++;
      }while(Memory[iterador]!="0000" /*count<80*/);//Memory[iterador]!="0000");
      }
   /*   for (int i = 0; i < 33; ++i)
      {
         cout<<Memory[i]<<endl;
      }
   */      
      cout<<ACC<<endl;
      if (problem=='F')
      {
         cout<<hex_to_int(Memory[hex_to_int("00A")]);
      }else if(problem=='M'){
         cout<<hex_to_int(Memory[hex_to_int("013")]);
      }
      
      //PARA QUE MIRES LOS NUMEROS PARA LAS DIRECCIONES
   /*   for (int i = 0; i < 50; ++i)
      {
         cout<<int_to_hex(i)<<endl;
      }*/
}

// SISTEMAS DE TRANSICION principals model checking