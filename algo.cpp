#include <iostream>
#include <string.h> 
#include <stdio.h>  
#include <stdlib.h> 

using namespace std;

int jumlahPS = 3;

struct PlayStation {
    int kodePS;
    char jenisPS[10];
    int stokTotal;
    int stokTersedia;
    int hargaPerJam;
};

struct Transaksi {
    int idRental;
    char namaPenyewa[50];
    int kodePS;
    char jenisPS[10];
    int lamaSewa;
    int hargaPerJam;
    int totalBayar;
    char status[15];
};

struct NodeRental {
    Transaksi info;
    NodeRental *kiri;
    NodeRental *kanan;
};
NodeRental *awalRental = NULL, *akhirRental = NULL;
NodeRental *awalRiwayat = NULL, *akhirRiwayat = NULL;

struct NodeAntrian {
    Transaksi info;
    NodeAntrian *next;
};
NodeAntrian *kepalaAntrian = NULL;

PlayStation daftarPS[3];
int counterIDRental = 101;  
int counterIDAntrian = 501; 

int main() {
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
            case 1: cout << "[Sistem]: Fitur Katalog belum dibuat.\n"; break;
            case 2: cout << "[Sistem]: Fitur Sewa belum dibuat.\n"; break;
            case 3: cout << "[Sistem]: Fitur Pantau belum dibuat.\n"; break;
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