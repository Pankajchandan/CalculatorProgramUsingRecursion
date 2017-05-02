/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Calculator.cpp
 * Author: pankaj
 * 
 * Created on April 9, 2017, 2:54 PM
 */

#include "Calculator.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <stdexcept>
using namespace std;

void Calculator::putback(Token t) {
        if (full) throw runtime_error("put back into full buffer");
        buffer = t;
        full = true;
  }
  
//Read from input stream or buffer if full
 Token Calculator::get(){
    if (full) { full = false; return buffer;}
    char ch;
    read: cin >> ch;
    switch(ch) {
      case '(': case ')': case '+': case '-': case '*': case '/': case '=':case'.': {
          Token tk;
          tk.kind=ch;
          tk.value=0;
          return tk;
      }
      //case '.': //throw WrongValueException("end");break;
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': {
      cin.putback(ch);  // put digit back into the input stream
      double val;
      cin >> val;   
      Token tk;
      tk.kind='8';tk.value=val;
      return tk;
      break;
    }
    case ' ': goto read; break;
    default: full=false;string k="*****unexpected";k=k+ch;throw runtime_error(k);break;
        
    } 
  }

double Calculator::factor() {
   Token t = this->get();
   switch (t.kind) {
   case '(': { 
      double d = this->expression();  
      t = this->get();
      if (t.kind != ')'){full=false; throw runtime_error("*****Missing )");}
      return d; 
   }
   case '8':return t.value; // ’8’ means number
   case '.':throw runtime_error("");break;
   default: full=false;string k="*****unexpected";k=k+t.kind;throw runtime_error(k);break;
   } 
}

double Calculator::term() {
   double val = this->factor();
   while (true) {
      Token t = this->get();
      switch (t.kind) {
      case '*':  val *= this->factor(); break; //multiply
      case '/':  {  
         double d = this->factor();
         if (d==0) {full=false;throw runtime_error("*****divide by zero");} //devide by zero
         val /= d;
         break;
      }
      case')': case '+': case '-': case'=': this->putback(t);return val;
      default: return val; 
     }
   }
}

double Calculator::expression(){
   double val = this->term();  // get first term
   while (true) {
      Token t = this->get();
      switch (t.kind) {
      case '+':  val += term(); break; // add
      case '-':  val -= term(); break; // subtract
      case '=':case')': this->putback(t); return val;
      default: return val;
      }  // pattern changes
   }
}


