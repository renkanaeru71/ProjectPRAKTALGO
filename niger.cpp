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
    char title[100];
    char genre[Max_Genre][30];
    int eps;
    float rating;
    int tahun;
    char status[20]; // Ongoing, Completed, Upcoming
};