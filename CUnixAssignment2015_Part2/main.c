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
void (*print)(node * n); // actually compiles and works commented out, but leaving it there because better safe than sorry.


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

//see equivalent method in Part 1.

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
        

    void printA(node * n){ // prints results
        
        char cuc[10];
        char car[10];
        char bean[10];
        char total[10];

        /* BAD CODE AHEAD. I was going to refactor this into a separate method, but honestly, returning strings/char arrays in C from a function I'm going to call 
         * 4 times in the entire program is more hassle than just copy pasting three of code three times.   
         *  
         * 12 oughta be a constant under proper practices, but as with above case, it feels a bit excessive here.
         * 
         */
        
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
        
        //I'm combining and casting them to four char arrays because that way I only have to format six values into printf
        //as opposed to ten individual values which is bound to be more of a headache to actually sort correctly into a table.
        
        //the statement below does not need to be any more messy than it currently is.
        printf("%s\t\t%2d\t\t%11s\t%11s\t%11s\t%11s\n", n->name,n->num,cuc,car,bean,total);
        
    }
    
    void printB(node * n){ // prints details
          
        printf("Competitor Name: %s\n", n->name);
        printf("Postal Address: %s\n", n->address);
        printf("Telephone: %s\n", n->phone);
        printf("\n");
        
        
    }
    
    void inOrder(node * current, void (*print)(node * n)){ // tree traversal
        
        if(current->left != NULL) {
         inOrder(current->left,print);   
        }
        
        (*print)(current);
        
        if(current->right != NULL){
         inOrder(current->right,print);   
        }
    }


    
/*
 * 
 */
int main(int argc, char** argv) {

    // basic vars
    char path[256];
    char name[60];
    char date[25];
    
    //temporary vars plan to remove/refractor
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
     
        if (feof(file)){ // avoids the extra loop
         break;   
        }
                //should theoretically read the data in blocks of six lines
        
        //user personal
        fscanf(file, "%[a-zA-Z ] ", tName);
        fscanf(file, "%[a-zA-Z,.0-9/- ] ", tAddress);
        fscanf(file, "%[a-zA-Z0-9 ] ", tPhone);
        //
        fscanf(file, "%lf %lf ", &f, &i);
        tCucumber = (f*12)+i;
        fscanf(file, "%lf %lf ", &f, &i);
        tCarrot = (f*12)+i;
        fscanf(file, "%lf %lf ", &f, &i);
        tBean = (f*12)+i;
        tNum++;
        
        temp = createNode(tName,tAddress,tPhone,tNum,tCucumber,tCarrot,tBean);
        
      if (head == 0){ //sets start;
        head = temp;   
        } else {
         insertNode(head,temp);   
        }
     
    }
    fclose(file);
  
    
    name[ strlen(name) - 1 ] = '\0'; //removes the newline char from 'name' so that 'name' and date line up on a single line. Classic C being dumb.


    char c;
    c = '0';
    int a = 0;
    
    while (a == 0){ //a poor man's do...until loop
        printf("Competition Results (R) or Competitor Details(D) ");
        getchar();
        scanf("%c", &c);
    
        if (c == 'R' || c == 'D'){
         a = 1;   
        }
 }  
        
    printf("\n\n");  

    /*
     
     I'm not sure if this is what's expected from Part 2 since I thought it wasn't entirely explained, 
     but the output does change depending on whether printA or printB is attached and those point to a function pointer. 

     */
    
    if (c == 'R') {

        printf("Competition:  %s  Date:  %s", name, date);
        printf("NAME\t\tcompetitor number\tCucumber\tCarrot\t\tRunnerBean\tTotal Length\n");
        printf("====================================================================================================\n");    
        inOrder(head, printA);
    }
    
    if (c == 'D') {
    
        printf("Competition:  %s  Date:  %s", name, date);
        printf("Competitor contact details: \n");
        printf("\n");
        inOrder(head, printB);
    }
    
    
    
    return (EXIT_SUCCESS);
}



