#include "CompileAbsorbance.h"

int main(void){
	char path[] = "../Agilent1";
	absorbance(path, 200, 1);
	path[10] = '2';
	absorbance(path, 200, 1);
	char mmsPath[] = "../MMS1";
	absorbance(mmsPath, 400, 1);
	path[6] = '2';
	absorbance(mmsPath, 400, 1);
	char mtPath[] = "../MT1";
	absorbance(mtPath, 386, 0.25);
    return 0;
}

int absorbance(char *_path, int startingWavelength, int increment){
    FILE *fp;
    DIR *dp;
	char path[255];
	strcpy(path, _path);
	strcat(path, "/Absorbance");
    struct dirent *dirp;
    dp = opendir (path);
	int measureCounter = 0;
    if(dp != NULL){
	while(dirp = readdir(dp)){
	    puts(dirp->d_name);
	    char filePath[255];
		strcpy(filePath, path);
		strcat(filePath, "/");
	    strcat(filePath, dirp->d_name);
	    strcat(filePath, "/MasterSpectrumCompilation_benchtop");
	    fp = fopen(filePath,"r");
	    if(fp){
			char line[7500];
			while(fgets(line, sizeof(line), fp) != NULL){
				char *token = strtok(line, "\t");
				int tokenCounter = 1;
				int tokenValue = -1;
				int currentCRM = -1;
				int wavelengthCounter = 0;
				struct Measurement measure = {0};				
				while (token != NULL){
					if (tokenCounter == 1){
						strcpy(measure.date, token);
					}else if (tokenCounter == 4){
						for ( int i = 0; i < sizeof(crm)/sizeof(struct Crm); ++i){
							if (!strcmp(token, crm[i].name)){
								strcpy(measure.name, token);
								currentCRM = i;
								tokenValue = (CrmWavelength[wavelengthCounter++] - startingWavelength) * increment + 24;
								measurement[measureCounter++] = measure;
							}
						}
					}else if (tokenCounter == tokenValue){
						sscanf(token, "%f", &measurement[measureCounter-1].actual[wavelengthCounter-1]);
						measurement[measureCounter-1].expected[wavelengthCounter-1] = crm[currentCRM].absorbance[wavelengthCounter-1];
						tokenValue = (CrmWavelength[wavelengthCounter] - startingWavelength) * increment + 24;
						++wavelengthCounter;
					}
					token = strtok(NULL, "\t"); 
					++tokenCounter;
					
				}
			}
			fclose(fp);
	    }
	}
    }
    closedir(dp);
	strcpy(path, _path);
	strcat(path,"/AbsorbanceResults.dat");
    fp = fopen(path, "w");
    fputs("Name\tDate\tWavelength\tExpected\tAcutal\tA-E\n", fp);
    int printCounter = 0;
    while (printCounter < measureCounter){
		for ( int i = 0; i < 5; ++i){
			fprintf(fp, "%s\t%s\t%i\t%f\t%f\t%f\n", measurement[printCounter].name, measurement[printCounter].date, CrmWavelength[i], measurement[printCounter].expected[i],measurement[printCounter].actual[i], measurement[printCounter].actual[i] - measurement[printCounter].expected[i]);
		}
		++printCounter;
    }
    fclose(fp);
}
