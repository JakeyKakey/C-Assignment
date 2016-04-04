/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   header.h
 * Author: jakey
 *
 * Created on 30 November 2015, 20:27
 */

#ifndef HEADER_H
#define HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

 typedef struct competitor{
        char name [60];
        char address[100];
        char phone[30];
        int num;
        double cucumber;
        double carrot;
        double bean;
        double total;
        
      struct competitor * left;
      struct competitor * right;
        
    } node;

    
    node * createNode(char [60],char[100],char[30],int,double,double,double);
    void insertNode(node * current, node * newN);
    void inOrder(node * current, void (*print)(node * n));
    void printA(node * n);
    void printB(node * n);
    void(*print)(node * n); // actually compiles and works commented out, but leaving it there because better safe than sorry.
    
#ifdef __cplusplus
}
#endif

#endif /* HEADER_H */

