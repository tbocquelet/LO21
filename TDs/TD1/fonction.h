#ifndef fonction_h
#define fonction_h

#include<iostream>
#include<string>
#include<stdio.h> 

#include "essai.h"

// permet de ne pas declarer plusieurs fois la meme fonction

// exercice 1
void bonjour();

// exercice 5
void exerciceA();

// exercice 9
int fct(int x);
int fct(float y);
int fct(int x, float y);
float fct(float x, int y);
void exercice_surcharge();

#endif /* fonction_h */

