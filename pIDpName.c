#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>
#define BUF_SIZE 1024


void printPidPName(long pID);

void printPidPName(long pID) {
    char path[40];
    FILE* fs;
    char buf[BUF_SIZE];

    //get the process running status as per processID
    snprintf(path, 40, "/proc/%ld/status", pID);

    fs = fopen(path, "r");
    if(NULL != fs){
        if( fgets(buf, BUF_SIZE-1, fs) == NULL ){
            fclose(fs);
        }
	fclose(fs);
        //print the processID and name of associated running process
        printf("%ld %s", pID, buf);
    } else {
        printf("ERROR: running process status is failed to get for pid: %ld\n", pID);
    }
}

int main() {
    //Open the /proc dir to read
    DIR* proc = opendir("/proc");
    struct dirent* dent;
    long pID;

    if(proc == NULL) {
        printf("ERROR: /proc opendir failed\n");
	return 0;
    }

    //read the /proc dir and check id directory name is digit
    while(dent = readdir(proc)) {
        if(!isdigit(*dent->d_name))
            continue;

        //read the processID
        pID = strtol(dent->d_name, NULL, 10);

        //print the running process Name using processID
        printPidPName(pID);
    }
    closedir(proc);
    return 0;
}
