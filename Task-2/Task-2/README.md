# Task 2 — Core Loop Analysis

## 1 — Core Loop

Core loop game saya adalah sebagai berikut:

1. Player menerima hand kartu
2. Player memilih kartu yang ingin dimainkan atau memutuskan untuk discard
3. System mengevaluasi kombinasi kartu yang dipilih
4. Score dihitung berdasarkan base score, combo multiplier, dan modifier aktif
5. Reward atau progress diberikan
6. Game state diperbarui (score ronde, sisa hand, sisa discard, coin)
7. Sistem mengecek apakah ronde selesai, gagal, atau lanjut
8. Repeat sampai run berakhir

## 2 — Invariants

### 1. Which steps in the loop must NEVER change order?
Beberapa langkah yang tidak boleh berubah urutannya adalah:

- Player harus memilih kartu sebelum sistem menghitung skor
- Sistem harus mengevaluasi kombinasi sebelum reward diberikan
- Reward/progress harus diberikan sebelum game state diperbarui
- Game state harus diperbarui sebelum sistem mengecek ronde selesai atau gagal

### 2. Which components must always exist for the game to function?
Komponen yang harus selalu ada adalah:

- RunSession / GameSession
- Deck
- Card
- ScoringSystem
- player action phase
- system resolve phase
- state update phase
- round / game over checking

### 3. What would break if the order changes?
Jika urutan loop berubah, maka beberapa hal akan rusak:

- Jika skor dihitung sebelum player memilih kartu, sistem tidak punya input valid
- Jika reward diberikan sebelum evaluasi, reward bisa salah
- Jika game state diperbarui sebelum hasil evaluasi selesai, progress ronde menjadi tidak akurat
- Jika pengecekan win/lose dilakukan terlalu awal, game bisa berhenti atau lanjut secara tidak valid

## 3 — Mutable Elements

Berikut adalah mutable elements dalam game saya:

### 1. Target score tiap ronde
Contoh: ronde 1 target 50, ronde 2 target 100, ronde 3 target 200.  
Ini mutable karena nilainya bisa diubah untuk menyesuaikan difficulty tanpa mengubah struktur game.

### 2. Reward coin per ronde
Jumlah coin yang didapat player setelah menyelesaikan ronde bisa diubah kapan saja.  
Ini mutable karena reward hanya parameter balancing, bukan bagian dari struktur loop.

### 3. Combo multiplier
Multiplier seperti Pair, Straight, Flush, Full House, dan lainnya bisa diubah.  
Ini mutable karena hanya memengaruhi hasil skor, bukan urutan inti proses game.

### 4. Jumlah hand dan discard
Jumlah kesempatan main dan discard per ronde dapat dinaikkan atau dikurangi.  
Ini mutable karena hanya memengaruhi tingkat kesulitan dan strategi.

### 5. Jenis modifier di shop
Isi shop seperti flat bonus atau double score bisa diganti atau ditambah.  
Ini mutable karena fitur tambahan ini bisa berkembang tanpa mengubah core loop.

## Step 4 — C++ Core Loop Skeleton

Struktur minimal C++ saya memisahkan fase-fase utama ke dalam class yang berbeda agar invariant structure terlihat jelas. main() hanya menjadi entry point, sedangkan loop utama dijalankan oleh RunSession.

## Reflection

### 1. What is the invariant structure of your game?
Invariant structure dari game saya adalah urutan proses utama yang selalu berulang selama permainan berjalan. Dalam game ini, player harus lebih dulu menerima kartu dan memilih aksi, lalu sistem mengevaluasi kombinasi kartu, menghitung skor, memberikan reward atau progress, memperbarui state permainan, dan akhirnya mengecek apakah ronde selesai atau permainan berakhir. Jika urutannya diubah, maka proses permainan menjadi tidak logis. Misalnya, skor tidak mungkin dihitung sebelum kartu dipilih, dan ronde tidak bisa dicek selesai sebelum state diperbarui.

### 2. What parts are mutable?
Bagian yang mutable adalah parameter, aturan balancing, dan konten tambahan yang tidak mengubah struktur utama loop. Contohnya adalah target score tiap ronde, jumlah reward coin, multiplier combo, jumlah hand dan discard, serta modifier yang tersedia di shop. Semua elemen ini dapat diubah untuk menyesuaikan tingkat kesulitan, membuat variasi gameplay, atau menambah fitur baru tanpa mengganti urutan dasar permainan.

### 3. If you wanted to add a new feature, which class would change?
Jika saya ingin menambahkan fitur baru, maka class yang paling mungkin berubah adalah RunSession, ScoringSystem, dan ShopSystem. RunSession akan berubah jika ada fase baru atau state baru yang harus dikelola. ScoringSystem akan berubah jika saya ingin menambah kombinasi kartu atau mengubah formula skor. ShopSystem akan berubah jika saya ingin menambah item, modifier, atau sistem upgrade lain.

### 4. If you changed the loop order, what would break?
Jika urutan loop diubah, maka yang rusak pertama adalah logika dependensi antar fase. Perhitungan skor bisa memakai data yang belum valid, reward bisa diberikan secara salah, dan state permainan bisa tidak sinkron. Karena itu, invariant pada game saya bukan angka-angkanya, tetapi struktur urutan prosesnya.