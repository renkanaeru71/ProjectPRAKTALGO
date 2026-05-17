#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
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
    if (file.is_open()) {
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
};

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
};

void tambahanime() {
    if (jumlahanime >= Max_Anime) {
        cout << "[ERROR] Tidak dapat menambahkan anime. Kapasitas penuh." << endl;
        return;
    }

    anime& a = daftarnimek[jumlahanime];
    a.id = (jumlahanime == 0) ? 1 : daftarnimek[jumlahanime - 1].id + 1;

    cout << "Judul anime: ";
    cout << "judul :";
    cin.getline(a.judul, 100);
    cout << "Genre (Max 3 genre, kosongkan untuk skip): ";
    for (int g = 0; g < Max_Genre; g++) {
        cout << "Genre " << g + 1 << ": ";
        cin.getline(a.genre[g], 30);
        if (strlen(a.genre[g]) == 0) {
            for (int k = g + 1; k < Max_Genre; k++) {
                strcpy(a.genre[k], "");
            break;
        }
    }

    cout << "Jumlah episode: "; cin >> a.eps;
    cout << "Rating (0.0 - 10.0): "; cin >> a.rating;
    cout << "Tahun rilis: "; cin >> a.tahun; cin.ignore();
    cout << "Status (Ongoing, Completed, Upcoming): "; cin.getline(a.status, 20);

    jumlahanime++;
    cout << "Anime berhasil ditambahkan! (ID: " << a.id << ")" << endl;
}




};