#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<cstdlib> // untuk fungsi atoi dan atof

using namespace std;

const int Max_Anime = 100;
const int Max_Genre = 50;
const char namafile[] = "anime_data.txt";

struct anime{
    int id;
    char judul[100];
    char genre[Max_Genre][30];
    int eps;
    float rating;
    int tahun;
    char status[20]; // Ongoing, Completed, Upcoming
};

anime daftarnimek[Max_Anime];
int jumlahanime = 0;

void simpandata() {
    ofstream file("animek.txt");
    if (!file.is_open()) {
        cout << "[ERROR] Gagal membuka file untuk menyimpan data." << endl;
        return;
    }

    file << jumlahanime << endl; // Simpan jumlah anime
    for (int i = 0; i < jumlahanime; i++) {
        file << daftarnimek[i].id << endl;
        file << daftarnimek[i].judul<< endl;
        file << daftarnimek[i].eps << endl;
        file << daftarnimek[i].rating << endl;
        file << daftarnimek[i].tahun << endl;
        file << daftarnimek[i].status << endl;
    }

    file.close();
    cout << "Data berhasil disimpan." << endl;
}

void bacafile() {
    ifstream file("animek.txt");
    if (!file.is_open()) {
        cout << "[ERROR] Gagal membuka file untuk membaca data." << endl;
        return;
    }

    file >> jumlahanime;
    file.ignore();

    for (int i = 0; i < jumlahanime; i++) {
        file >> daftarnimek[i].id;
        file.ignore();
        file.getline(daftarnimek[i].judul, 100);
        file >> daftarnimek[i].eps;
        file >> daftarnimek[i].rating;
        file >> daftarnimek[i].tahun;
        file.ignore();
        file.getline(daftarnimek[i].status, 20);
    }

    file.close();
    cout << "Data berhasil dibaca." << endl;
}

void tambahanime() {
    if (jumlahanime >= Max_Anime) {
        cout << "[ERROR] Tidak dapat menambahkan anime. Kapasitas penuh." << endl;
        return;
    }

    anime& a = daftarnimek[jumlahanime];
    a.id = (jumlahanime == 0) ? 1 : daftarnimek[jumlahanime - 1].id + 1;

    cout << "Judul anime: ";
    cin.getline(a.judul, 100);
    cout << "Genre (Max 3 genre, kosongkan untuk skip): " << endl;
    
    for (int g = 0; g < Max_Genre; g++) {
        cout << "Genre " << g + 1 << ": ";
        cin.getline(a.genre[g], 30);
        if (strlen(a.genre[g]) == 0) {
            for (int k = g + 1; k < Max_Genre; k++) {
                strcpy(a.genre[k], "");
            }
            break; // Keluar dari loop genre jika kosong
        }
    }

    cout << "Jumlah episode: "; cin >> a.eps;
    cout << "Rating (0.0 - 10.0): "; cin >> a.rating;
    cout << "Tahun rilis: "; cin >> a.tahun; cin.ignore();
    cout << "Status (Ongoing, Completed, Upcoming): "; cin.getline(a.status, 20);

    jumlahanime++;
    cout << "Anime berhasil ditambahkan! (ID: " << a.id << ")" << endl;
}

void editanime(int idx) {
    if (idx < 0 || idx >= jumlahanime) {
        cout << "[ERROR] Indeks anime tidak valid." << endl;
        return;
    }
    anime& a = daftarnimek[idx];
    char temp[100];

    cout << "Edit Anime " << a.judul << endl;
    cout << "(tekan Enter untuk mempertahankan nilai saat ini)" << endl;

    cout << "Judul (" << a.judul << "): ";
    cin.getline(temp, 100);
    if (strlen(temp) > 0) strcpy(a.judul, temp);

    for (int g = 0; g < Max_Genre; g++) {
        cout << "Genre " << g + 1 << " (" << a.genre[g] << "): ";
        cin.getline(temp, 30);
        if (strlen(temp) > 0) strcpy(a.genre[g], temp);
    }

    cout << "Jumlah episode (" << a.eps << "): ";
    cin.getline(temp, 10);
    if (strlen(temp) > 0) a.eps = atoi(temp);

    cout << "Rating (" << a.rating << "): ";
    cin.getline(temp, 10);
    if (strlen(temp) > 0) a.rating = atof(temp);

    cout << "Tahun rilis (" << a.tahun << "): ";
    cin.getline(temp, 10);
    if (strlen(temp) > 0) a.tahun = atoi(temp);

    cout << "Status (" << a.status << "): ";
    cin.getline(temp, 20);
    if (strlen(temp) > 0) strcpy(a.status, temp);

    cout << "data berhasil diupdate!" << endl;
}

void hapusanime(int idx) {
    if (idx < 0 || idx >= jumlahanime) {
        cout << "[ERROR] Indeks anime tidak valid." << endl;
        return;
    }

    cout << "menghapus: " << daftarnimek[idx].judul << endl;
    for (int i = idx; i < jumlahanime - 1; i++) {
        daftarnimek[i] = daftarnimek[i + 1];
    }

    jumlahanime--;
    cout << "anime berhasil dihapus!" << endl;
}

void tampilanime(int idx) {
    anime& a = daftarnimek[idx];
    cout << "ID: " << a.id << endl;
    cout << "Judul: " << a.judul << endl;
    cout << "Genre: ";
    string genreStr = "";
    for (int g = 0; g < Max_Genre; g++) {
        if (strlen(a.genre[g]) > 0) {
            if (!genreStr.empty()) genreStr += ", ";
            genreStr += a.genre[g];
        }
    }
    cout << "----------------------------------------" << endl;
    cout << setw(24) << left << genreStr << endl;
    cout << "| Eps: " << setw(24) << left << a.eps << endl;
    cout << "| Rating: " << setw(24) << left << a.rating << endl;
    cout << "| Tahun: " << setw(24) << left << a.tahun << endl;
    cout << "| Status: " << setw(24) << left << a.status << endl;
    cout << "----------------------------------------" << endl;
}

void menuAnggota1() {
    int pilihan;
    do {
        cout << "\n╔══════════════════════════════╗\n";
        cout << "║   MENU DATA & FILE           ║\n";
        cout << "╠══════════════════════════════╣\n";
        cout << "║ 1. Tambah anime              ║\n";
        cout << "║ 2. Edit anime                ║\n";
        cout << "║ 3. Hapus anime               ║\n";
        cout << "║ 4. Lihat detail satu anime   ║\n";
        cout << "║ 5. Simpan ke file            ║\n";
        cout << "║ 0. Kembali                   ║\n";
        cout << "╚══════════════════════════════╝\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();
 
        int idx;
        switch (pilihan) {
            case 1:
                tambahanime(); // Diselaraskan menjadi huruf kecil semua
                break;
            case 2:
                if (jumlahanime == 0) { cout << "  Data kosong!\n"; break; } // Menggunakan jumlahanime
                cout << "Masukkan nomor anime (1-" << jumlahanime << "): ";
                cin >> idx; cin.ignore();
                editanime(idx - 1); // Diselaraskan menjadi huruf kecil semua
                break;
            case 3:
                if (jumlahanime == 0) { cout << "  Data kosong!\n"; break; } // Menggunakan jumlahanime
                cout << "Masukkan nomor anime yang dihapus (1-" << jumlahanime << "): ";
                cin >> idx; cin.ignore();
                hapusanime(idx - 1); // Diselaraskan menjadi huruf kecil semua
                break;
            case 4:
                if (jumlahanime == 0) { cout << "  Data kosong!\n"; break; } // Menggunakan jumlahanime
                cout << "Masukkan nomor anime (1-" << jumlahanime << "): ";
                cin >> idx; cin.ignore();
                if (idx >= 1 && idx <= jumlahanime) tampilanime(idx - 1); // Menggunakan nama fungsi yang benar
                else cout << "  Nomor tidak valid!\n";
                break;
            case 5:
                simpandata(); // Menggunakan nama fungsi yang benar
                break;
            case 0:
                break;
            default:
                cout << "  Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}