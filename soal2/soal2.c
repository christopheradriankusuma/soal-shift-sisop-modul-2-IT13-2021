#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <wait.h>

void unzip(char *name, char *target) {
    pid_t child_id;
    int status;
    child_id = fork();

    if (child_id == 0) {
        char *argv[4] = {
            "unzip",
            name,
            "-d",
            target
        };

        execv("/usr/bin/unzip", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void deleteFiles(char *name) {
    char target[20];
    sprintf(target, "%s/", name);

    pid_t child_id;
    child_id = fork();

    if (child_id == 0) {
        char *argv[3] = {
            "rm",
            "-rf",
            target
        };

        execv("/bin/rm", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        wait(NULL);
    }
}

void createDir(char *name) {
    char target[20];
    sprintf(target, "%s", name);

    DIR *dir = opendir(name);
    if (dir) {
        return;
    }

    pid_t child_id;
    int status;
    child_id = fork();

    if (child_id == 0) {
        char *argv[3] = {
            "mkdir",
            target
        };

        execv("/bin/mkdir", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void copyFile(char *dir, char *init_name, char *pet_name) {
    char source[30];
    sprintf(source, "%s", init_name);

    char target[40];
    sprintf(target, "%s/%s.jpg", dir, pet_name);

    pid_t child_id;
    int status;
    child_id = fork();

    if (child_id == 0) {
        char *argv[3] = {
            "cp",
            source,
            target
        };

        execv("/bin/cp", argv);
        exit(EXIT_SUCCESS); 
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void write_keterangan(char *dir, char *pet_name, char *pet_age) {
    char file[50];
    sprintf(file, "%s/keterangan.txt", dir);

    pid_t child_id;
    int status;
    child_id = fork();

    if (child_id == 0) {
        FILE *fptr;
        fptr = fopen(file, "a");
        fprintf(fptr, "nama : %s\numur : %s\n\n", pet_name, pet_age);
        fclose(fptr);

        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        while(wait(&status) > 0);
    }
}

void process(char *name) {
    char init_name[40];
    sprintf(init_name, "%s", name);
    
    DIR *dir = opendir(name);

    if (dir) {
        deleteFiles(init_name);
    } else {
        char *pch;
        char *dir_name_age[3];
        pch = strtok(name, ";_");
        while (pch != NULL) {
            for (int i = 0; i < 3; ++i) {
                dir_name_age[i] = pch;
                pch = strtok(NULL, ";_");
            }
            
            char *pet_dir = dir_name_age[0];
            char *pet_name = dir_name_age[1];
            char *pet_age = dir_name_age[2];

            char *dot_jpg;
            dot_jpg = strstr(pet_age, ".jpg");
            if (dot_jpg != NULL) {
                int pos = dot_jpg - pet_age;
                sprintf(pet_age, "%.*s", pos, pet_age);
            }

            createDir(pet_dir);
            copyFile(pet_dir, init_name, pet_name);
            write_keterangan(pet_dir, pet_name, pet_age);
        }
    }

    closedir(dir);
}

int main() {
    char zipname[9] = "pets.zip";
    char dirname[8] = "petshop";

    chdir("/home/kali/modul2/");

    unzip(zipname, dirname);

    struct dirent *dp;
    DIR *dir = opendir(dirname);

    if (!dir) {
        exit(EXIT_FAILURE);
    }

    chdir("petshop");

    while (dp = readdir(dir)) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            process(dp->d_name);
        }
    }


    return 0;
}