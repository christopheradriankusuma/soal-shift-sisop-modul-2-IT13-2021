# soal-shift-sisop-modul-2-IT13-2021

### <b> Nama Anggota Kelompok: </b>
#### 1. Asiyah Hanifah (05311940000002)
#### 2. Muhammad Yasykur Rafii (05311940000017)
#### 3. Christopher Adrian Kusuma (05311940000022)
---

## Soal 1

Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya.</br>
</br>
Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany. </br>
</br>
Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.

(a) Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg.

(b) untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).

(c) Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta 

(d) memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).

(e) Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany). (f) Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).
Kemudian Steven meminta bantuanmu yang memang sudah jago sisop untuk membantunya mendapatkan hati Stevany. Bantu Woy!!

### <b>Note:</b>
- Ulang Tahun Stevany : 09 April Pukul 22.22 WIB
- Semua poin dijalankan oleh 1 script di latar belakang, termasuk mendownload file zip-nya. Jadi cukup jalankan script 1x serta ubah time dan date untuk check hasilnya.

> Preview:
https://drive.google.com/drive/folders/1NzRiPPoVlR_H8P51cxN4jaceeFQGk4un
- Tidak boleh menggunakan fungsi system(), mkdir(), dan rename() (Yang di bahasa C) .... FORBIDDENNN!!
- Tidak boleh pake cron !!!
- Menggunakan fork dan exec.
- Link

> Foto: https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view </br>
Musik: https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view </br>
Film: https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view </br>

### <b>Tips: </b>


- Gunakan fungsi wait() dan sleep() untuk memperlancarrr..
- untuk mendownload zip yang dibutuhkan bisa menggunakan command :
> wget --no-check-certificate "https://drive.google.com/uc?id=ID-FILE&export=download" -O Nama_untuk_filenya.ext

> Contoh: Wget --no-check-certificate "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download" -O Musik_for_Stevany.zip


## Penyelesaian:

### Code:
``` C
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
            "-q",
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
```
### Penjelasan Code:

## Kendala yang Dihadapi: 
ini kendala

## Screeshoot Hasil:

<img src= "./Pictures/ss soal1.png">


---

## Soal 2

Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.

(a) Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.

(b) Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.

(c) Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan. Contoh: “/petshop/cat/joni.jpg”.

(d) Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”

(e) Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. <b>Format harus sesuai contoh.</b>

> nama : joni </br>
umur  : 3 tahun </br>
>nama : miko </br>
umur  : 2 tahun </br>

Loba sangat mengapresiasi bantuanmu, minggu depan ia akan mentraktir makan malam! 

### <b>Note: </b>

- Setiap data peliharaan disimpan sebagai nama foto dengan format [jenis peliharaan]:[nama peliharaan]:[umur peliharaan dalam tahun]. Jika terdapat lebih dari satu peliharaan, data dipisahkan menggunakan underscore(_).
- Tidak boleh menggunakan fungsi system(), mkdir(), dan rename().
- Menggunakan fork dan exec.


## Penyelesaian:

ya gtu blm

## Kendala yang Dihadapi: 
ini kendala

## Screeshoot Hasil:



---

## Soal 3

Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.

(a) Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

(b) Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

(c) Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

(d) Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.

(e) Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

Ranora meminta bantuanmu untuk membantunya dalam membuat program tersebut. Karena kamu anak baik dan rajin menabung, bantulah Ranora dalam membuat program tersebut!

### <b>Note: </b>

- Tidak boleh menggunakan system() dan mkdir()
- Program utama merupakan SEBUAH PROGRAM C
- Wajib memuat algoritma Caesar Cipher pada program utama yang dibuat

## Penyelesaian:
### Code:

### Penjelasan

## Kendala yang Dihadapi: 
ini kendala

## Screeshoot Hasil:



---
