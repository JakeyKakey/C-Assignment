/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jakey
 *
 * Created on 30 November 2015, 20:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <error.h>
#include <errno.h>
#include "header.h"

//const double inch = 2.54;




//creates, populates and returns a node. self-explanatory.

node * createNode(char n[60], char a[100], char p[30],int tempNum, double cuc, double car, double tBean){
 
    errno = 0;
    
    node * tempNode;
    tempNode = malloc(sizeof (struct competitor));
    if(tempNode == NULL)
	   {
	      if(errno == ENOMEM) printf("Error ENOMEM: Insufficient memory available\n");
	   }
    
    strcpy(tempNode->address, a);
    strcpy(tempNode->name, n);
    strcpy(tempNode->phone, p);
    tempNode->num = tempNum;
    tempNode->cucumber = cuc;
    tempNode->carrot = car;
    tempNode->bean = tBean;
    tempNode->total = cuc + car + tBean;
    tempNode->left = NULL;
    tempNode->right = NULL;
    

    return tempNode;
}

// if greater and right child is null, put it in - else, recursive downwards
// same applies to the lesser & left respectively.

void insertNode(node * current, node * newN){
    
    if (newN->total >= current->total){ 
    
        if (current->right == NULL){ 
            current->right = newN;   
        } else {
            insertNode(current->right,newN);
        }
    } else if (newN->total < current->total){
        
        if (current->left == NULL){
         current->left = newN;   
        } else {
         insertNode(current->left,newN);   
        }
    }
    
}
        

    void print(node * n){
        
        char cuc[10];
        char car[10];
        char bean[10];
        char total[10];

        /* I was going to refactor this into a separate method, but honestly, returning strings/char arrays in C from a function I'm going to call 
         * 4 times in the entire program is more hassle than just copy pasting three of code three times.   
         * */
        
        //cucumber
        double f = 0; double i; int q; // feet and inches
        double temp = n->cucumber; // safer practice since I may need the values stored in the struct later;
        f = floor(temp/12);
        i = fmod(temp,12);
        q = sprintf(cuc,"%.fft %4.1fin",f, i);
         //carrot
        temp = n->carrot;
        f = floor(temp/12);
        i = fmod(temp,12);
        q = sprintf(car,"%.fft %4.1fin",f, i);
        //bean
        temp = n->bean;
        f = floor(temp/12);
        i = fmod(temp,12); 
        q = sprintf(bean,"%.fft %4.1fin",f, i);
        //total
        temp = n->total;
        f = floor(temp/12);
        i = fmod(temp,12);
        q = sprintf(total,"%.fft %4.1fin",f, i);
        
        printf("%s\t\t%2d\t\t%11s\t%11s\t%11s\t%11s\n", n->name,n->num,cuc,car,bean,total);

    }
    
    void inOrder(node * current){ //standard in-order traversal as found online
        
        if(current->left != NULL) {
         inOrder(current->left);   
        }
        
        print(current);
        
        if(current->right != NULL){
         inOrder(current->right);   
        }
    }

/*
 * 
 */
int main(int argc, char** argv) {

    // basic vars;
    char path[256];
    char name[60];
    char date[25];
    
    //temporary vars to store;
        char tName[60];
        char tAddress[100];
        char tPhone[30];
        int tNum = 0;
        double tCucumber;
        double tCarrot;
        double tBean;
        double total;
        double f;
        double i;
    
        
        
    FILE * file;

     do {
           
        printf("Please specify the file path for the competitions file: ");
        scanf("%s", path);
        //printf("%s", path);
        file = fopen(path, "r");
    } while (NULL == file);
    
    
    fgets(name, 60, file); // gets first two lines out of the way
    fgets(date, 60, file);
    

    
    node * head = 0;
    node * temp;
    
    while (!feof(file)){ 
     
        if (feof(file)){ // avoids the extra 'empty' loop at the end
         break;   
        }
        
        //reads in blocks of six
        
        //user personal
        fscanf(file, "%[a-zA-Z ] ", tName);
        fscanf(file, "%[a-zA-Z,.0-9/- ] ", tAddress);
        fscanf(file, "%[a-zA-Z0-9 ] ", tPhone);
        //lengths
        fscanf(file, "%lf %lf ", &f, &i);
        tCucumber = (f*12)+i;
        fscanf(file, "%lf %lf ", &f, &i);
        tCarrot = (f*12)+i;
        fscanf(file, "%lf %lf ", &f, &i);
        tBean = (f*12)+i;
        tNum++;
        
        temp = createNode(tName,tAddress,tPhone,tNum,tCucumber,tCarrot,tBean);
        
      if (head == 0){
        head = temp;   
        } else {
         insertNode(head,temp);   
        }
    }
    fclose(file);
  
    
    name[ strlen(name) - 1 ] = '\0'; //removes the newline char from 'name' so that 'name' and date line up on a single line. Classic C being C aka dumb.

    printf("\n\n");  
    printf("Competition:  %s  Date:  %s", name, date);
    
    printf("NAME\t\tcompetitor number\tCucumber\tCarrot\t\tRunnerBean\tTotal Length\n");
    printf("============================================================================================\n");
    
    inOrder(head);
    
    return (EXIT_SUCCESS);
}



