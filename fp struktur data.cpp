#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Struct untuk barang
struct Barang {
    string nama;
    int jumlah;
    int harga;
    int subTotal;
};

// Stack untuk histori belanja pelanggan
struct Stack {
    Barang belanjaan[100]; // Array untuk barang, maksimal 100 barang per transaksi
    int jumlahBarang; // Jumlah barang yang dibeli pelanggan
    string namaPelanggan;
    Stack* next;  // Pointer ke elemen stack berikutnya
};

Stack* top = NULL;

// Fungsi menambah barang ke array
void tambahBarang(Stack& stack, string nama, int jumlah, int harga) {
    int i = stack.jumlahBarang;
    stack.belanjaan[i].nama = nama;
    stack.belanjaan[i].jumlah = jumlah;
    stack.belanjaan[i].harga = harga;
    stack.belanjaan[i].subTotal = jumlah * harga;
    stack.jumlahBarang++;
}

// Fungsi menampilkan daftar barang di array
void tampilkanBarang(const Stack& stack) {
    cout << endl;
    cout << "STRUK BELANJA" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "No   Nama Barang       Jumlah     Harga Satuan     Sub Total" << endl;
    for (int i = 0; i < stack.jumlahBarang; ++i) {
        cout << setw(2) << right << i + 1
             << "   " << left << setw(15) << stack.belanjaan[i].nama
             << setw(7) << right << stack.belanjaan[i].jumlah
             << setw(17) << stack.belanjaan[i].harga
             << setw(15) << stack.belanjaan[i].subTotal << endl;
    }
}

// Fungsi menghitung total belanja dari array
int hitungTotal(const Stack& stack) {
    int total = 0;
    for (int i = 0; i < stack.jumlahBarang; ++i) {
        total += stack.belanjaan[i].subTotal;
    }
    return total;
}

// Fungsi menghitung diskon
int hitungDiskon(int total) {
    if (total >= 500000) return total * 0.1;
    else if (total >= 250000) return total * 0.05;
    else if (total >= 100000) return total * 0.02;
    return 0;
}

// Fungsi sorting barang (bubble sort berdasarkan subtotal)
void sortingBarang(Stack& stack) {
    for (int i = 0; i < stack.jumlahBarang - 1; ++i) {
        for (int j = 0; j < stack.jumlahBarang - i - 1; ++j) {
            if (stack.belanjaan[j].subTotal < stack.belanjaan[j + 1].subTotal) {
                swap(stack.belanjaan[j], stack.belanjaan[j + 1]);
            }
        }
    }
}

// Fungsi untuk menghitung total penjualan seluruh pelanggan
int hitungTotalPenjualan() {
    int totalPenjualan = 0;
    Stack* temp = top;
    while (temp != NULL) {
        totalPenjualan += hitungTotal(*temp);
        temp = temp->next;
    }
    return totalPenjualan;
}

// Push histori belanja ke stack (menambahkan di bagian bawah stack)
void push(Stack& stack) {
    Stack* baru = new Stack;
    *baru = stack; // Menyalin data transaksi ke elemen stack baru
    baru->next = NULL;

    if (top == NULL) {
        top = baru; // Jika stack kosong, elemen baru menjadi top
    } else {
        Stack* temp = top;
        while (temp->next != NULL) {
            temp = temp->next; // Iterasi hingga elemen terakhir
        }
        temp->next = baru; // Tambahkan elemen baru di bagian bawah stack
    }
}


// Pop histori belanja dari stack
Stack* pop() {
    if (!top) return NULL;
    Stack* temp = top;
    top = top->next;
    return temp;
}

// Menampilkan histori belanja
void tampilkanHistori() {
    Stack* temp = top;
    int no = 1;
    while (temp != NULL) {
        cout << "Histori Ke-" << no++ << " - Pelanggan: " << temp->namaPelanggan << endl;
        tampilkanBarang(*temp);
        cout << "---------------------------------------------------------" << endl;
        temp = temp->next;
    }
}

// Fungsi membersihkan stack dan array barang
void hapusStack() {
    while (top != NULL) {
        Stack* temp = top;
        top = top->next;
        delete temp;
    }
}

// Fungsi utama
int main() {
    int pilihan;
    do {
        cout << endl;
        cout << "PROGRAM KASIR MINI MARKET" << endl;
        cout << "1. Melayani Pelanggan" << endl;
        cout << "2. Menampilkan Histori Pelanggan" << endl;
        cout << "3. Mencari Pelanggan" << endl;
        cout << "4. Menghapus Histori Pelanggan Terakhir" << endl;
        cout << "5. Menghitung Total Penjualan" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            string namaPelanggan;
            int jumlahBarang;

            cin.ignore();
            cout << "Nama Pelanggan: ";
            getline(cin, namaPelanggan);
            cout << "Jumlah Barang: ";
            cin >> jumlahBarang;

            Stack belanjaan = { {}, 0, namaPelanggan, NULL };

            for (int i = 0; i < jumlahBarang; i++) {
                string nama;
                int jumlah, harga;

                cin.ignore();
                cout << "Nama Barang: ";
                getline(cin, nama);
                cout << "Jumlah: ";
                cin >> jumlah;
                cout << "Harga: ";
                cin >> harga;

                tambahBarang(belanjaan, nama, jumlah, harga);
            }

            sortingBarang(belanjaan);
            int total = hitungTotal(belanjaan);
            int diskon = hitungDiskon(total);

            tampilkanBarang(belanjaan);
            cout << "---------------------------------------------------------" << endl;
            cout << "Total Belanja : Rp." << total << endl;
            cout << "Diskon        : Rp." << diskon << endl;
            cout << "Total Bayar   : Rp." << total - diskon << endl;

            push(belanjaan);
            break;
        }
        case 2:
            cout << endl << "Histori Pelanggan:" << endl;
            tampilkanHistori();
            break;

        case 3: {
            string namaPelanggan;
            cin.ignore();
            cout << "Masukkan nama pelanggan yang dicari: ";
            getline(cin, namaPelanggan);

            Stack* temp = top;
            bool ditemukan = false;

            while (temp != NULL) {
                if (temp->namaPelanggan == namaPelanggan) {
                    cout << "Pelanggan ditemukan!" << endl;
                    tampilkanBarang(*temp);
                    ditemukan = true;
                    break;
                }
                temp = temp->next;
            }

            if (!ditemukan) {
                cout << "Pelanggan tidak ditemukan." << endl;
            }
            break;
        }
        case 4:
            if (top) {
                Stack* dihapus = pop();
                cout << "Histori pelanggan " << dihapus->namaPelanggan << " telah dihapus." << endl;
                delete dihapus;
            } else {
                cout << "Tidak ada histori yang bisa dihapus." << endl;
            }
            break;

        case 5:
            cout << "Total Penjualan: Rp." << hitungTotalPenjualan() << endl;
            break;

        case 6:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 6);

    hapusStack(); // Membersihkan stack yang tersisa
    return 0;
}

