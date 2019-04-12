#ifndef CompileWavelength_H
#define CompileWavelength_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <sys/types.h>
#include <stddef.h>
#include <string.h>

int wavelength(char *_path, int startingWavelength, int increment);

float CRMValue[] = {240.97, 249.78, 278.15, 287.03, 333.48, 345.46, 361.27, 385.36, 416.02, 452.02, 467.78, 485.20, 536.42, 640.41}; 

int CRM[] = {240, 249, 278, 287, 333, 345, 361, 385, 416, 452, 467, 485, 536, 640}; 

char CRMName[] = "74184";
struct Measurement{
    char date[24];
    float wavelength[14];
} measurement[500]; 

#endif
