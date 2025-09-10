# microteaching_strukturdata
Kasir Mini Market – Implementasi Struktur Data C++

Deskripsi
Repositori ini berisi implementasi struktur data menggunakan C++ dengan studi kasus program kasir mini market.
Program ini menerapkan struct, array, stack (linked stack), sorting, dan searching untuk mengelola transaksi pelanggan, menampilkan struk belanja, serta menyimpan histori pembelian.

Fitur Program 
1. Melayani Pelanggan : Input nama pelanggan dan daftar barang yang dibeli. Barang otomatis dihitung subtotalnya (jumlah × harga). Daftar barang diurutkan berdasarkan subtotal (bubble sort). Sistem menghitung total belanja, diskon, dan total bayar. Data transaksi disimpan ke histori menggunakan stack.
2. Menampilkan Histori Pelanggan : Menampilkan semua transaksi pelanggan sebelumnya lengkap dengan struk belanja.
3. Mencari Pelanggan : Pencarian berdasarkan nama pelanggan. Jika ditemukan, struk belanja pelanggan tersebut akan ditampilkan.
4. Menghapus Histori Pelanggan Terakhir : Menghapus transaksi terakhir dari histori stack.
5. Menghitung Total Penjualan : Menjumlahkan seluruh transaksi pelanggan dari histori.
6. Keluar dari Program : Mengakhiri aplikasi dan membersihkan memori stack.

Struktur Data yang Digunakan
1. Struct Barang → menyimpan informasi nama, jumlah, harga, dan subtotal.
2. Struct Stack → menyimpan daftar barang pelanggan, nama pelanggan, dan pointer ke stack berikutnya.
3. Array → menyimpan barang dalam satu transaksi (maksimal 100).
4. Stack (Linked Stack) → menyimpan histori transaksi pelanggan.
5. Sorting → bubble sort berdasarkan subtotal barang.
6. Searching → pencarian pelanggan berdasarkan nama.
