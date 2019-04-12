#ifndef CompileAbsorbance_H
#define CompileAbsorbance_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <sys/types.h>
#include <stddef.h>
#include <string.h>

int absorbance(char *_path, int startingWavelength, int increment);

int CrmWavelength[] = {440, 465, 546, 590, 635}; 

struct Crm{
	char name[5];
	float absorbance[5];
};
struct Crm crm[9] = {
	{"76358", {3.2996, 3.0663, 3.0377, 3.1317, 2.9508}},
	{"76347", {2.7965, 2.5985, 2.5719, 2.6501, 2.4969}},
	{"78606", {2.1243, 1.9764, 1.9971, 2.0366, 1.9267}},
	{"76237", {1.6242, 1.5117, 1.5272, 1.5571, 1.4735}},
	{"79074", {1.0236, 0.9628, 0.9998, 1.0949, 1.0746}},
	{"79082", {0.5651, 0.5252, 0.5227, 0.5566, 0.5642}},
	{"60923", {0.2385, 0.2175, 0.2255, 0.2502, 0.2709}},
	{"52790", {0.1660, 0.1502, 0.1529, 0.1654, 0.1739}},
	{"78584", {0.0567, 0.0534, 0.0515, 0.0512, 0.0510}},
};

struct Measurement{
    char date[24];
	char name[5];
	float expected[5];
    float actual[5];
} measurement[500]; 

#endif
