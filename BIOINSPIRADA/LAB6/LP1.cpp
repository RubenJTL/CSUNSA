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


//string input_token="riris=i+iwsws/i";
string input_token="riri$";
int i=0;

void parse_error();
void consume();

void skip();

void match(char expected);
void program();
void stmt_list();

void stmt();
void expr();

void term_tail();

void term();

void factor_tail();

void factor();

void add_op();

void mult_op();

int main(){
	program();
    return 0;
}



void parse_error(){
	cout<<"error en codigo";
}
void consume(){
	cout<<"consume ";
	i++;
}

void skip(){
	cout<<"termino";
}

void match(char expected){
	cout<<"match ";
	if(input_token[i]==expected){
		consume();
	}else{
		parse_error();
	}
}
void program(){
	cout<<"programa ";
	if(input_token[i]=='i' or input_token[i]=='r' or input_token[i]=='w' or input_token[i]=='$'){
		stmt_list();
		match('$');
	}else{
		parse_error();
	}
}
void stmt_list(){
	cout<<"stmt_list ";
	if (input_token[i]=='i' or input_token[i]=='r' or input_token[i]=='w' ){
		stmt();stmt_list();
	}else if(input_token[i]=='$'){
		skip();
	}else{
		parse_error();
	}

}

void stmt(){
	cout<<"stmt ";
	if (input_token[i]=='i')  
	{
		match('i');match('=');expr();
	}else if(input_token[i]=='r')
	{
		match('r');match('i');
	}else if(input_token[i]=='w'){
		match('w');expr();
	}else{
		parse_error();
	}
}
void expr(){
	cout<<"expr ";
	if (input_token[i]=='i' or input_token[i]=='n' or input_token[i]=='(')
	{
		term();term_tail();
	}else{
		parse_error();
	}
}

void term_tail(){
	cout<<"term_tail ";
	if(input_token[i]=='+' or input_token[i]=='-' ){
		add_op();term();term_tail();
	}else if(input_token[i]==')' or input_token[i]=='i' or input_token[i]=='r' or input_token[i]=='w' or input_token[i]=='$' ){
		skip();
	}else{
		parse_error();
	}
}

void term(){
	cout<<"term ";
	if(input_token[i]=='i' or input_token[i]=='n' or input_token[i]=='('){
		factor();factor_tail();
	}else{
		parse_error();
	}
}


void factor_tail(){
	cout<<"factor_tail ";
	if(input_token[i]=='*' or input_token[i]=='/'){
		mult_op();factor();factor_tail();
	}
	if(input_token[i]=='+' or input_token[i]=='-' or input_token[i]=='i' or input_token[i]=='r' or input_token[i]=='w' or input_token[i]=='$'){
		skip();
	}
}

void factor(){
	cout<<"factor ";
	if(input_token[i]=='i') match('i');
	else if(input_token[i]=='n')match('n');
	else if(input_token[i]=='('){
		match('(');expr();match(')');
	}else{
		parse_error();
	}
}

void add_op(){
	cout<<"add_op ";
	if(input_token[i]=='+'){
		match('+');
	}else if(input_token[i]=='-'){
		match('-');
	}else{
		parse_error();
	}
}

void mult_op(){
	cout<<"mult_op ";
	if(input_token[i]=='*'){
		match('*');
	}
	else if(input_token[i]=='/'){
		match('/');
	}else{
		parse_error();
	}
}
