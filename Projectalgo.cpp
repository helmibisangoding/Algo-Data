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
    daftarPS[0].kodePS = 1; strcpy(daftarPS[0].jenisPS, "PS3"); daftarPS[0].stokTotal = 2; daftarPS[0].stokTersedia = 2; daftarPS[0].hargaPerJam = 5000;
    daftarPS[1].kodePS = 2; strcpy(daftarPS[1].jenisPS, "PS4"); daftarPS[1].stokTotal = 3; daftarPS[1].stokTersedia = 3; daftarPS[1].hargaPerJam = 8000;
    daftarPS[2].kodePS = 3; strcpy(daftarPS[2].jenisPS, "PS5"); daftarPS[2].stokTotal = 2; daftarPS[2].stokTersedia = 2; daftarPS[2].hargaPerJam = 12000;
    
    kepalaAntrian = new NodeAntrian;
    kepalaAntrian->info.idRental = -1; strcpy(kepalaAntrian->info.namaPenyewa, "DUMMY_HEAD");
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

int cariIndeksPS(int kode) {
    for (int i = 0; i < jumlahPS; i++) if (daftarPS[i].kodePS == kode) return i;
    return -1;
}

void sisipAkhirRental(NodeRental **awal, NodeRental **akhir, Transaksi data) {
    NodeRental *NB = new NodeRental;
    NB->info = data; NB->kiri = NULL; NB->kanan = NULL;
    if (*awal == NULL) { *awal = *akhir = NB; } 
    else { (*akhir)->kanan = NB; NB->kiri = *akhir; *akhir = NB; }
}

NodeRental* cariSewa(int id) {
    NodeRental *bantu = awalRental;
    while (bantu != NULL) {
        if (bantu->info.idRental == id) return bantu;
        bantu = bantu->kanan;
    }
    return NULL; 
}

void lepasNodeRental(NodeRental* hapus) {
    if (hapus == awalRental && hapus == akhirRental) { awalRental = akhirRental = NULL; } 
    else if (hapus == awalRental) { awalRental = hapus->kanan; awalRental->kiri = NULL; } 
    else if (hapus == akhirRental) { akhirRental = hapus->kiri; akhirRental->kanan = NULL; } 
    else { hapus->kiri->kanan = hapus->kanan; hapus->kanan->kiri = hapus->kiri; }
}

void cekAntrianOtomatis(int kodePS, int indeksPS) {
    if (kepalaAntrian->next == kepalaAntrian) return; 
    
    NodeAntrian *sebelum = kepalaAntrian;
    NodeAntrian *bantu = kepalaAntrian->next;
    
    while (bantu != kepalaAntrian) {
        if (bantu->info.kodePS == kodePS) {
            Transaksi dataBaru = bantu->info;
            dataBaru.idRental = counterIDRental++; 
            strcpy(dataBaru.status, "Aktif");

            sisipAkhirRental(&awalRental, &akhirRental, dataBaru);
            daftarPS[indeksPS].stokTersedia--;

            sebelum->next = bantu->next; 
            delete bantu;
            
            cout << "[Sistem]: Notifikasi otomatis! Antrian " << dataBaru.namaPenyewa 
                 << " diproses ke room " << dataBaru.jenisPS << " (ID: " << dataBaru.idRental << ")\n";
            return;
        }
        sebelum = bantu;
        bantu = bantu->next;
    }
}

void checkInSewa() {
    tampilkanKatalogPS();
    int kode; cout << "Pilih Kode PS (1-3): "; cin >> kode;
    int idx = cariIndeksPS(kode);
    
    if (idx == -1) { cout << "[Sistem]: Kode tidak valid.\n"; return; }

    Transaksi t;
    cout << "Nama Anda: "; cin >> ws; cin.getline(t.namaPenyewa, 50);
    cout << "Durasi Sewa (Jam): "; cin >> t.lamaSewa;

    if (t.lamaSewa <= 0) { cout << "[Sistem]: Durasi tidak valid.\n"; return; }

    t.kodePS = daftarPS[idx].kodePS;
    strcpy(t.jenisPS, daftarPS[idx].jenisPS);
    t.hargaPerJam = daftarPS[idx].hargaPerJam;
    t.totalBayar = t.lamaSewa * t.hargaPerJam;

    if (daftarPS[idx].stokTersedia > 0) {
        t.idRental = counterIDRental++;
        strcpy(t.status, "Aktif");
        sisipAkhirRental(&awalRental, &akhirRental, t);
        daftarPS[idx].stokTersedia--;
        cout << "\n[Check In Berhasil] ID: " << t.idRental << " | Tagihan: Rp " << t.totalBayar << "\n";
    } else {
        t.idRental = counterIDAntrian++;
        strcpy(t.status, "Antrian");
        
        NodeAntrian *NB = new NodeAntrian; NB->info = t;
        NodeAntrian *bantu = kepalaAntrian;
        while (bantu->next != kepalaAntrian) bantu = bantu->next; 
        NB->next = kepalaAntrian; bantu->next = NB; 
        cout << "\n[Sistem]: Room penuh. Anda masuk antrian dengan ID: " << t.idRental << "\n";
    }
}

void cetakRentalAktif() {
    if (awalRental == NULL) { cout << "[Sistem]: Tidak ada sesi aktif.\n"; return; }
    cout << "\n--- DAFTAR SESI RENTAL PS AKTIF ---\n";
    NodeRental *bantu = awalRental;
    while (bantu != NULL) {
        cout << "ID: " << bantu->info.idRental << " | " << bantu->info.namaPenyewa 
             << " | " << bantu->info.jenisPS << " | " << bantu->info.lamaSewa << " Jam | Rp " << bantu->info.totalBayar << "\n";
        bantu = bantu->kanan;
    }
}

void perpanjangDurasiSewa() {
    int id, jam;
    cout << "ID Transaksi Anda: "; cin >> id;
    
    NodeRental *target = cariSewa(id);
    if (target == NULL) { cout << "[Sistem]: ID tidak ditemukan.\n"; return; }

    cout << "Tambah Durasi (Jam): "; cin >> jam;
    if (jam <= 0) { cout << "[Sistem]: Durasi tidak valid.\n"; return; }

    target->info.lamaSewa += jam;
    target->info.totalBayar = target->info.lamaSewa * target->info.hargaPerJam;
    cout << "[Sistem]: Diperpanjang. Total bayar baru: Rp " << target->info.totalBayar << "\n";
}

void checkOutSewa() {
    int id; cout << "ID Transaksi yang Selesai: "; cin >> id;
    
    NodeRental *hapus = cariSewa(id);
    if (hapus == NULL) { cout << "[Sistem]: ID tidak ditemukan.\n"; return; }

    Transaksi dataSelesai = hapus->info;
    strcpy(dataSelesai.status, "Selesai");
    sisipAkhirRental(&awalRiwayat, &akhirRiwayat, dataSelesai);

    int idx = cariIndeksPS(hapus->info.kodePS);
    if (idx != -1) daftarPS[idx].stokTersedia++;

    lepasNodeRental(hapus); 
    delete hapus; 
    
    cout << "\n[Sistem]: Rental atas nama " << dataSelesai.namaPenyewa << " Selesai. Total Tagihan: Rp " << dataSelesai.totalBayar << "\n";
    
    cekAntrianOtomatis(dataSelesai.kodePS, idx); 
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
        cout << "[4] Tambah Durasi Room Sewa\n";
        cout << "[5] Selesai Main & Bayar Kasir\n";
        cout << "[6] Lihat Antrian Waiting List\n";
        cout << "[7] Analisis Billing Tertinggi (Sorting Bubble)\n";
        cout << "[8] Backup Seluruh Status Transaksi ke Disk\n";
        cout << "[9] Muat Pembukuan Total Kas dari Disk\n";
        cout << "[0] Matikan Sistem\n";
        cout << "--------------------------------------------------\n";
        cout << "Pilih Menu Navigasi: "; cin >> pilihan;
        
        cout << "\n"; 
        switch (pilihan) {
            case 1: tampilkanKatalogPS(); break; 
            case 2: checkInSewa(); break;
            case 3: cetakRentalAktif(); break;
            case 4: perpanjangDurasiSewa(); break;
            case 5: checkOutSewa(); break;
            case 6: cout << "[Sistem]: Fitur Antrian masih dikembangkan.\n"; break;
            case 7: cout << "[Sistem]: Fitur Sorting masih dikembangkan.\n"; break;
            case 8: cout << "[Sistem]: Fitur Backup masih dikembangkan.\n"; break;
            case 9: cout << "[Sistem]: Fitur Laporan masih dikembangkan.\n"; break;
            case 0: cout << "[Sistem]: Menutup aplikasi. Terimakasih.\n"; break;
            default: cout << "[Sistem]: Kode tidak terdaftar.\n";
        }
        if (pilihan != 0) { cout << "\n"; system("pause"); }
    } while (pilihan != 0);
    return 0;
}
