#include <iostream>
#include <string.h> 
#include <stdio.h>  
#include <stdlib.h> 

using namespace std;

int jumlahPS = 3;

struct PlayStation { int kodePS; char jenisPS[10]; int stokTotal; int stokTersedia; int hargaPerJam; };
struct Transaksi { int idRental; char namaPenyewa[50]; int kodePS; char jenisPS[10]; int lamaSewa; int hargaPerJam; int totalBayar; char status[15]; };
struct NodeRental { Transaksi info; NodeRental *kiri; NodeRental *kanan; };
NodeRental *awalRental = NULL, *akhirRental = NULL;
NodeRental *awalRiwayat = NULL, *akhirRiwayat = NULL;
struct NodeAntrian { Transaksi info; NodeAntrian *next; };
NodeAntrian *kepalaAntrian = NULL;

PlayStation daftarPS[3];
int counterIDRental = 101;  
int counterIDAntrian = 501; 

void inisialisasiSistem() {
    daftarPS[0].kodePS = 1; strcpy(daftarPS[0].jenisPS, "PS3");
    daftarPS[0].stokTotal = 2; daftarPS[0].stokTersedia = 2; daftarPS[0].hargaPerJam = 5000;

    daftarPS[1].kodePS = 2; strcpy(daftarPS[1].jenisPS, "PS4");
    daftarPS[1].stokTotal = 3; daftarPS[1].stokTersedia = 3; daftarPS[1].hargaPerJam = 8000;

    daftarPS[2].kodePS = 3; strcpy(daftarPS[2].jenisPS, "PS5");
    daftarPS[2].stokTotal = 2; daftarPS[2].stokTersedia = 2; daftarPS[2].hargaPerJam = 12000;

    kepalaAntrian = new NodeAntrian;
    kepalaAntrian->info.idRental = -1;
    strcpy(kepalaAntrian->info.namaPenyewa, "DUMMY_HEAD");
    kepalaAntrian->next = kepalaAntrian; 
}

void tampilkanKatalogPS() {
    cout << "\n=======================================================\n";
    cout << "             KATALOG & TARIF RENTAL PLAYSTATION        \n";
    cout << "=======================================================\n";
    cout << "Kode\tJenis\tTarif / Jam\tKetersediaan Unit\n";
    cout << "-------------------------------------------------------\n";
    for (int i = 0; i < jumlahPS; i++) {
        cout << daftarPS[i].kodePS << "\t" << daftarPS[i].jenisPS << "\tRp " << daftarPS[i].hargaPerJam;
        if (daftarPS[i].hargaPerJam >= 10000) cout << "\t"; else cout << "\t\t";
        cout << daftarPS[i].stokTersedia << " Unit Tersedia (Dari " << daftarPS[i].stokTotal << ")\n";
    }
    cout << "=======================================================\n";
}

int main() {
    inisialisasiSistem(); 
    int pilihan;
    do {
        system("cls"); 

        cout << "\n==================================================\n";
        cout << "         SISTEM OPERASIONAL RENTAL PS             \n";
        cout << "==================================================\n";
        cout << "[1] Lihat Katalog PS, Tarif, & Ketersediaan\n";
        cout << "[2] Sewa Unit Baru / Ambil Tiket Antrian\n";
        cout << "[3] Pantau Room Rental PS\n";
        cout << "[0] Matikan Sistem\n";
        cout << "--------------------------------------------------\n";
        cout << "Pilih Menu Navigasi: "; cin >> pilihan;
        
        cout << "\n"; 
        switch (pilihan) {
            case 1: tampilkanKatalogPS(); break; 
            case 2: cout << "[Sistem]: Fitur Sewa dalam tahap pengembangan.\n"; break;
            case 3: cout << "[Sistem]: Fitur Pantau dalam tahap pengembangan.\n"; break;
            case 0: cout << "[Sistem]: Menutup aplikasi. Terimakasih.\n"; break;
            default: cout << "[Sistem]: Kode tidak terdaftar.\n";
        }
        
        if (pilihan != 0) {
            cout << "\n";
            system("pause"); 
        }
    } while (pilihan != 0);

    return 0;
}
