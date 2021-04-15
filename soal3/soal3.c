#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <wait.h>

int x_signal = 0;
char *mode;

void killer(){
    FILE *target;
    target = fopen("killer.sh", "w");
    int status;

    fprintf(target, "pkill -10 soal3\nrm killer.sh");

    pid_t pid;
    pid = fork();

    if (pid == 0) {
        char *argv[4] = {
            "chmod",
            "+x",
            "killer.sh"
        };
        
        execv("/bin/chmod", argv);
    } else if (pid > 0) {
        wait(NULL);
        fclose(target);
    }
}

char* encrypt(char *text, int shift) {
    int len = strlen(text);
    char *res, new;
    res = (char*)malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; ++i) {
        char now = *(text + i);
        if ('a' <= now && now <= 'z') {
            new = ((*(text + i) - 'a' + shift) % 26) + 'a';
        } else if ('A' <= now && now <= 'Z') {
            new = ((*(text + i) - 'A' + shift) % 26) + 'A';
        } else if ('0' <= now && now <= '0') {
            new = ((*(text + i) - '0' + shift) % 10) + '0';
        } else {
            new = *(text + i);
        }
        *(res + i) = new;
    }

    return res;
}

void download(char *link, char *name) {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        char *argv[7] = {
            "wget",
            "--no-check-certificate",
            "-q",
            link,
            "-O",
            name
        };
        
        execv("/bin/wget", argv);
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        wait(NULL);
    }
}

char *get_time() {
    time_t now = time(NULL);
    struct tm *ptm = localtime(&now);

    char *formatted_time;
    formatted_time = (char *)malloc(20 * sizeof(char));
    sprintf(formatted_time, "%04d-%02d-%02d_%02d:%02d:%02d", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    return formatted_time;
}

void create_dir(char *name) {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        char *argv[3] = {
            "mkdir",
            name
        };

        if(execv("/bin/mkdir", argv) == -1) {
            printf("mkdir %s\n", name);
        }
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        wait(NULL);
    }
}

void zip(char *name) {
    char zip_name[25];
    sprintf(zip_name, "%s.zip", name);

    pid_t pid;
    pid = fork();

    if (pid == 0) {
        char *argv[6] = {
            "zip",
            "-q",
            "-r",
            zip_name,
            name
        };

        if(execv("/bin/zip", argv) == -1) {
            printf("zip -q -r %s %s\n", zip_name, name);
        }
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        wait(NULL);
    }
}

void delete_dir(char *name) {
    char target[25];
    sprintf(target, "%s/", name);

    pid_t child_id;
    child_id = fork();

    if (child_id == 0) {
        char *argv[4] = {
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

void sigterm_handler(int signal) {
    if (strcmp(mode, "-z") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(mode, "-x") == 0) {
        x_signal = 1;
    }
}

int main(int argc, char *argv[]) {
    signal(10, sigterm_handler);
    mode = argv[1];

    killer();

    if (argc != 2) {
        printf("Required argument! -x / -z\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(mode, "-z") != 0 && strcmp(mode, "-x") != 0) {
        printf("Unknown argument %s. available -x / -z\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    pid_t pid, sid;

	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	umask(0);

	sid = setsid();
	if (sid < 0) {
		exit(EXIT_FAILURE);
	}

	if ((chdir("/home/kali/modul2")) < 0) {
		exit(EXIT_FAILURE);
	}

    close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

    char *link = "https://picsum.photos/";
    
    char *dir;
    dir = (char *)malloc(20 * sizeof(char));

    char *name;
    name = (char *)malloc(42 * sizeof(char));

    while (1) {
        dir = get_time();
        create_dir(dir);

        chdir(dir);

        for (int i = 0; i < 10; ++i) {
            name = get_time();

            time_t t = time(NULL);

            char *pic;
            pic = (char *)malloc(30 * sizeof(char));
            sprintf(pic, "%s%d", link, (t%1000)+50);

            download(pic, name);
            sleep(5);
        }

        char *enc = encrypt("Download Success", 5);

        FILE *fptr;
        fptr = fopen("status.txt", "w");
        fprintf(fptr, "%s", enc);
        fclose(fptr);

        chdir("..");
        zip(dir);
        delete_dir(dir);

        if (argc > 1) {
            if (strcmp(argv[1], "-x") == 0) {
                if (x_signal == 1) {
                    exit(EXIT_SUCCESS);
                    break;
                }
            }
        }

        sleep(40);
    }

    return 0;
}