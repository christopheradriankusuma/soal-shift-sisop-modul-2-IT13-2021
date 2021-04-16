/*

Pyoto: FOTO: https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download
Musyik: MUSIK: https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download
Fylm: FILM: https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <wait.h>

// fungsi untuk mendowload foto, musik, dan video
void download(char *link, char *name) {
    pid_t child_id;
    child_id = fork();

    if (child_id == 0) {
        char *argv[6] = {
            "wget", //menggunakan wget untuk mengunduh file berbanyak
            "--no-check-certificate", 
            link, //menuju ke link yang akan didownload
            "-O",
            name
        };
        
        execv("/bin/wget", argv); //mengeksekusi dengan mendowloadnya
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        wait(NULL); //parentnya nunggu
    }
}


//untuk mengunzip file yang sudah didownload
void unzip(char *name) {
    pid_t child_id;
    child_id = fork();

    if (child_id == 0) {
        char *argv[3] = {
            "unzip", //menggunakan perintah unzip untuk mengekstrak zip yng sudah dibuat
            "-q",
            name
        };

        execv("/usr/bin/unzip", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        wait(NULL); //parentnya menunggu
    }
}

//mengcopy dalam folder yang diinginkan
void copy(char *name, char *target) {
    pid_t child_id;
    child_id = fork();

    if (child_id == 0) {
        char *argv[4] = { 
            "cp", //mengcopy 
            "-R",
            name,
            target
        };

        execv("/bin/cp", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        wait(NULL);
    }
}

//menzipkan semua folder yang sudah dibuat
void zip() {
    pid_t child_id;
    child_id = fork();

    if (child_id == 0) {
        char *argv[7] = {
            "zip", 
            "-q",
            "-r", 
            "Lopyou_Stevany.zip",
            "Pyoto", 
            "Musyik", 
            "Fylm"
        };

        execv("/bin/zip", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        wait(NULL);
    }
}

//fungsi mendelete semua folder dan menyisakan zip
void delete() {
    pid_t child_id;
    child_id = fork();

    if (child_id == 0) {
        char *argv[8] = {
            "rm",
            "-rf",
            "FOTO",
            "MUSIK",
            "FILM",
            "Pyoto", 
            "Musyik", 
            "Fylm"
        };

        execv("/bin/rm", argv);
        exit(EXIT_SUCCESS);
    } else if (child_id > 0) {
        wait(NULL);
    }

}

int main() {
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

    // close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);

    char *link[3] = {
        "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
        "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
        "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
    };

    char *name[3] = {
        "Foto_for_Stevany.zip",
        "Musik_for_Stevany.zip",
        "Film_for_Stevany.zip"
    };

    struct tm bd = {0, 22, 22, 9, 3, 121};
    time_t birthday = mktime(&bd);

    while (1) {
        time_t now = time(NULL);
        double diff = difftime(birthday, now);
        if (diff > 0 && diff < 6*60*60) {
            download(link[0], name[0]);
            unzip(name[0]);
            copy("FOTO/", "Pyoto/");

            download(link[1], name[1]);
            unzip(name[1]);
            copy("MUSIK/", "Musyik/");

            download(link[2], name[2]);
            unzip(name[2]);
            copy("FILM/", "Fylm/");

            break;
        }
    }

    while(1) {
        time_t now = time(NULL);
        double diff = difftime(birthday, now);
        if (diff < 1 && diff > -1) {
            zip();

            delete();

            break;
        }
    }

    return 0;
}