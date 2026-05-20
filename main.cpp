#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

// --- DEKLARASI KONSTANTA & VARIABEL GLOBAL ---

const int MAX_ANIME = 100;

// Struct menggunakan char array[] untuk teks
struct Anime {
    int id;
    char judul[100];
    char studio[50];
    int episode;
    float rating;
    
    // 2. Array Multi Dimensi (2D Char Array) untuk kategori
    // Satu anime bisa memiliki beberapa kategori (maksimal 3 kategori)
    // Setiap kategori maksimal 20 karakter
    int jumlahKategori;
    char kategori[3][20]; 
};

// 1. Array 1 Dimensi sebagai Database Utama
Anime daftarAnime[MAX_ANIME];
int jumlahAnime = 0;


// --- FUNGSI FILE I/O (TUGAS ANGGOTA 1) ---

void simpanData(const char* namaFile) {
    ofstream file(namaFile);
    if (!file.is_open()) {
        cerr << "Error: Gagal membuka file untuk menyimpan data!\n";
        return;
    }

    // Menyimpan data dengan format CSV (dipisahkan oleh tanda titik koma ';')
    for (int i = 0; i < jumlahAnime; ++i) {
        file << daftarAnime[i].id << ";"
             << daftarAnime[i].judul << ";"
             << daftarAnime[i].studio << ";"
             << daftarAnime[i].episode << ";"
             << daftarAnime[i].rating << ";"
             << daftarAnime[i].jumlahKategori;
        
        // Menyimpan semua kategori yang ada di dalam array 2D
        for (int k = 0; k < daftarAnime[i].jumlahKategori; ++k) {
            file << ";" << daftarAnime[i].kategori[k];
        }
        file << "\n";
    }
    file.close();
    cout << "Data berhasil disimpan ke " << namaFile << "\n";
}

void muatData(const char* namaFile) {
    ifstream file(namaFile);
    if (!file.is_open()) {
        cout << "File tidak ditemukan, memulai dengan database kosong.\n";
        return;
    }

    jumlahAnime = 0;
    char line[512]; // Kapasitas buffer diperbesar untuk menampung banyak kategori

    // Membaca file baris per baris
    while (file.getline(line, sizeof(line))) {
        if (jumlahAnime >= MAX_ANIME) break;

        // Parsing baris teks menggunakan strtok
        char* token = strtok(line, ";");
        if (token) daftarAnime[jumlahAnime].id = atoi(token);

        token = strtok(NULL, ";");
        if (token) strcpy(daftarAnime[jumlahAnime].judul, token);

        token = strtok(NULL, ";");
        if (token) strcpy(daftarAnime[jumlahAnime].studio, token);

        token = strtok(NULL, ";");
        if (token) daftarAnime[jumlahAnime].episode = atoi(token);

        token = strtok(NULL, ";");
        if (token) daftarAnime[jumlahAnime].rating = atof(token);

        token = strtok(NULL, ";");
        if (token) {
            daftarAnime[jumlahAnime].jumlahKategori = atoi(token);
            // Membaca setiap kategori ke dalam array 2D
            for (int k = 0; k < daftarAnime[jumlahAnime].jumlahKategori; ++k) {
                char* tokenKategori = strtok(NULL, ";");
                if (tokenKategori) {
                    strcpy(daftarAnime[jumlahAnime].kategori[k], tokenKategori);
                }
            }
        }

        jumlahAnime++;
    }
    file.close();
    cout << "Data berhasil dimuat dari " << namaFile << " (Total: " << jumlahAnime << " data)\n";
}


// --- FUNGSI MAIN (UNTUK TESTING) ---

int main() {
    // Memuat data di awal jika ada
    muatData("anime.txt");

    int pilihan;
    do {
        cout << "\n=== MENU SEMENTARA (ANGGOTA 1) ===\n";
        cout << "1. Tambah Data Anime\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Simpan Data ke File\n";
        cout << "4. Muat Data dari File\n";
        cout << "0. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        if (pilihan == 1) {
            if (jumlahAnime >= MAX_ANIME) {
                cout << "Kapasitas penuh!\n";
            } else {
                cout << "\n--- Tambah Anime ---\n";
                cout << "ID       : "; cin >> daftarAnime[jumlahAnime].id;
                cin.ignore(); // Membersihkan buffer newline agar cin.getline bisa bekerja
                cout << "Judul    : "; cin.getline(daftarAnime[jumlahAnime].judul, 100);
                cout << "Studio   : "; cin.getline(daftarAnime[jumlahAnime].studio, 50);
                cout << "Episode  : "; cin >> daftarAnime[jumlahAnime].episode;
                cout << "Rating   : "; cin >> daftarAnime[jumlahAnime].rating;
                
                cout << "Jumlah Kategori (maks 3): "; 
                cin >> daftarAnime[jumlahAnime].jumlahKategori;
                if (daftarAnime[jumlahAnime].jumlahKategori > 3) daftarAnime[jumlahAnime].jumlahKategori = 3;
                cin.ignore(); // Membersihkan buffer
                
                // Input masing-masing kategori
                for (int k = 0; k < daftarAnime[jumlahAnime].jumlahKategori; ++k) {
                    cout << "Kategori ke-" << (k+1) << " : ";
                    cin.getline(daftarAnime[jumlahAnime].kategori[k], 20);
                }
                jumlahAnime++;
                cout << "Data berhasil ditambahkan (Jangan lupa pilih menu 3 untuk menyimpan!)\n";
            }
        } 
        else if (pilihan == 2) {
            cout << "\n--- Daftar Anime (" << jumlahAnime << " Data) ---\n";
            for (int i = 0; i < jumlahAnime; ++i) {
                cout << "ID       : " << daftarAnime[i].id << "\n"
                     << "Judul    : " << daftarAnime[i].judul << "\n"
                     << "Studio   : " << daftarAnime[i].studio << "\n"
                     << "Episode  : " << daftarAnime[i].episode << "\n"
                     << "Rating   : " << daftarAnime[i].rating << "\n"
                     << "Kategori : ";
                     
                for (int k = 0; k < daftarAnime[i].jumlahKategori; ++k) {
                    cout << daftarAnime[i].kategori[k];
                    if (k < daftarAnime[i].jumlahKategori - 1) cout << ", ";
                }
                cout << "\n-------------------------------\n";
            }
        }
        else if (pilihan == 3) {
            simpanData("anime.txt");
        }
        else if (pilihan == 4) {
            muatData("anime.txt");
        }

    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}
