
#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;


//string input_token="i&i$";
//string input_token="i|i$";
//string input_token="(i&i)$";
//string input_token="~(i-i&(i|(i&~i)))&i$";
//string input_token="~(i-i&(i|(i&~i))))&i$";
string input_token="~((i-i&(i|(i&~i)))&i$";

int i=0;

void parse_error();
void consume();
void programa();
void match(char expected);

void expresion();

int main(){
	cout<<input_token<<endl;
	programa();
    return 0;
}

void programa(){
	
	expresion();
	match('$');
	//cout<<"Semantica Correcta"<<endl;
}
void expresion(){

	if(input_token[i]=='$' or input_token[i]==')')
		return;
	if(input_token[i]=='('){
		match('(');
		expresion();
		match(')');
		expresion();
	}else if(input_token[i]=='i'){
		match('i');
		expresion();	
	}else if(input_token[i]=='~'){
		match('~');
		expresion();	
	}else if(input_token[i]=='&' or input_token[i]=='|' or input_token[i]=='>' or input_token[i]=='-' or input_token[i]=='X'){
			match(input_token[i]);			
			expresion();
	}else{
		parse_error();	
	}
}

void parse_error(){
	cout<<" error en semantica"<<endl;
}
void consume(){
	//cout<<"consume "<<endl;
	i++;
}

void match(char expected){
	//cout<<"match "<<endl;
	//cout<<input_token[i]<<" esperado  "<<expected<<endl;	
	if(input_token[i]==expected){
					
		consume();
	}else{
		cout<<input_token[i];
		parse_error();
	}
}

