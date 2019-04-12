#include "MMSCompileWavelength.h"

int main(void){
	char path[] = "../MMS1";
    wavelength(path);
	path[6] = '2';
	wavelength(path);
    return 0;
}

int wavelength(char *_path){
    FILE *fp;
    DIR *dp;
	char path[255];
	strcpy(path, _path);
	strcat(path, "/Wavelength");
    struct dirent *dirp;
    dp = opendir (path);
    int measurementCount = 0;
    if(dp != NULL){
	while(dirp = readdir(dp)){
	    puts(dirp->d_name);
	    char filePath[255];
		strcat(filePath, path);
		strcat(filePath, "/");
	    strcat(filePath, dirp->d_name);
	    strcat(filePath, "/MasterSpectrumCompilation_benchtop");
	    fp = fopen(filePath,"r");
	    if(fp){
		char line[7500];
		while(fgets(line, sizeof(line), fp) != NULL){
			char *token = strtok(line, "\t");
			int tokenCounter = 1;
			int wavelengthCounter = 0;
			float maxAbsorbance = 0;
			int maxAbsorbanceWavelength = 0;
			struct Measurement measure = {0};
			while (token != NULL && wavelengthCounter < 14){
			    float currentAbsorbance = 0;
			    if (tokenCounter == 1){
				strcpy(measure.date, token);
			    }else if (tokenCounter == 4 && !strcmp(token,CRMName)){
				measurement[measurementCount++] = measure;
			    }else if ( tokenCounter == 4 && strcmp(token, CRMName)){
				break;
				
			    }else if (tokenCounter > (24 + CRM[wavelengthCounter] + 5 - 400)&&tokenCounter > 24){
				measurement[measurementCount - 1].wavelength[wavelengthCounter++] = maxAbsorbanceWavelength;
				maxAbsorbance =0;
				maxAbsorbanceWavelength = 0;
			    }else if (tokenCounter > (24 + CRM[wavelengthCounter] - 5 - 400) && tokenCounter >24){
				sscanf(token,"%f", &currentAbsorbance);
				if (currentAbsorbance > maxAbsorbance){
				    maxAbsorbance = currentAbsorbance;
				    maxAbsorbanceWavelength = tokenCounter + 400 - 24;
				}
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
	strcat(path,"/WavelengthResults.dat");
    fp = fopen(path, "w");
    fputs("Date\tExpected\tAcutal\tA-E\n", fp);
    int printCounter = 0;
    while (printCounter < measurementCount){
	for ( int i = 0; i < 14; ++i){
	    if (measurement[printCounter].wavelength[i] > 0){
		fprintf(fp, "%s\t%f\t%f\t%f\n", measurement[printCounter].date, CRMValue[i], measurement[printCounter].wavelength[i], measurement[printCounter].wavelength[i] - CRMValue[i]);
	    }
	}
	++printCounter;
    }
    fclose(fp);
}
