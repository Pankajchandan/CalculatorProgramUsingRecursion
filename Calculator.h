/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Calculator.h
 * Author: pankaj
 *
 * Created on April 9, 2017, 2:54 PM
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

// Token keeps the tokens read from input
struct Token {
  char kind;
  double value;
};


class Calculator{
bool full=false; // is there a Token in the buffer?
Token buffer; // keep put-back Token here
public:
    double factor() ;
    double term() ;
    double expression() ;
    Token get();
    void putback(Token t); //putback function to put a token into buffer
  };

#endif /* CALCULATOR_H */

