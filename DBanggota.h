// DATABASE ANGGOTA
using namespace std;
void clearScreen();
struct anggota
{
    string id_anggota;
    string nama;
    string alamat;
    string no_telp;
    string tanggal_lahir;
    string status_keanggotaan;
};
// Deklarasikan vektor di luar fungsi agar dapat diakses secara global
vector<anggota> daftar_anggota;
bool cekDataDuplikat(const string &id)
{
    for (const auto &a : daftar_anggota)
    {
        if (a.id_anggota == id)
        {
            return true;
        }
    }
    return false;
}
// Deklarasikan vektor di bagain file database_anggota.txt
bool cekfile(const string &id)
{
    // baca data anggota
    if (file("database_anggota.txt"))
        ;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id_anggota;
            getline(ss, id_anggota, ',');
            if (id_anggota == id)
            {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

void inputdata_baruA(const string &file_anggota)
{
    int jumlah_anggota;
    cout << "Silahkan masukkan jumlah anggota!" << endl;
    cout << "Jumlah anggota: ";
    cin >> jumlah_anggota;
    cin.ignore();

    for (int i = 0; i < jumlah_anggota; ++i)
    {
        anggota temp; // vektor anggota
        cout << "Masukkan data anggota ke-" << i + 1 << ": " << endl;
        do
        {
            cout << "id                   : ";
            getline(cin, temp.id_anggota);
            // cek di input
            if (cekDataDuplikat(temp.id_anggota))
            {
                cout << "ID yang anda masukkan telah ada dalam database. Silahkan maukkan ID lain." << endl;
            }
            // cek data di file
            if (!cekAnggota(temp.id_anggota))
            {
                cout << "ID anggota tidak valid. Silakan masukkan ID anggota yang sesuai." << endl;
                continue; // Lanjutkan ke data peminjaman berikutnya
            }

        } while (cekDataDuplikat(temp.id_anggota));
        cout << "Nama               : ";
        getline(cin, temp.nama);
        cout << "Alamat             : ";
        getline(cin, temp.alamat);
        cout << "No telp            : ";
        getline(cin, temp.no_telp);
        cout << "Tanggal lahir      : ";
        getline(cin, temp.tanggal_lahir);
        cout << "Status keanggotaan : ";
        getline(cin, temp.status_keanggotaan);
        cout << endl;
        daftar_anggota.push_back(temp);
    }
    ofstream file(file_anggota, ios::app);
    if (file.is_open())
    {
        for (const auto &a : daftar_anggota)
        {
            file << a.id_anggota << "," << a.nama << ","
                 << a.alamat << "," << a.no_telp << ","
                 << a.tanggal_lahir << "," << a.status_keanggotaan << "\n";
        }
        file.close();
        cout << "Data berhasil diinput ke " << file_anggota << endl;
    }
    else
    {
        cout << "Gagal membuka " << file_anggota << " untuk penulisan." << endl;
    }
}
// tampilkan data anggota
void outputA(const string &file_anggota)
{
    ifstream file(file_anggota);
    if (file.is_open())
    {
        anggota temp_a;
        int indeks = 1;
        cout << "Isi Database Anggota:\n";
        string line;
        while (getline(file, line))
        {
            // cin.ignore();
            stringstream ss(line);
            getline(ss, temp_a.id_anggota, ',');
            getline(ss, temp_a.nama, ',');
            getline(ss, temp_a.alamat, ',');
            getline(ss, temp_a.no_telp, ',');
            getline(ss, temp_a.tanggal_lahir, ',');
            getline(ss, temp_a.status_keanggotaan, ',');
            cout << "Anggota ke-" << indeks << ":" << endl;
            cout << "Id                 : " << temp_a.id_anggota << endl;
            cout << "Nama               : " << temp_a.nama << endl;
            cout << "Alamat             : " << temp_a.alamat << endl;
            cout << "No telp            : " << temp_a.no_telp << endl;
            cout << "Tanggal lahir      : " << temp_a.tanggal_lahir << endl;
            cout << "Status keanggotaan : " << temp_a.status_keanggotaan << endl;
            cout << endl;
            indeks++;
        }
        file.close();
    }
    else
    {
        cout << "Gagal" << file_anggota << "untuk pembacaan." << endl;
    }
}
void hapusA(const string &file_anggota, const string &temp_anggota)
{
    ofstream file_temp(temp_anggota);
    ifstream file_sumber(file_anggota);
    if (!file_temp.is_open() || !file_sumber.is_open())
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    cin.ignore();
    string cari;
    cout << "Masukkan id atau nama yang ingin dihapus: ";
    getline(cin, cari);
    string line;
    bool anggota_ditemukan = false;
    while (getline(file_sumber, line))
    {
        stringstream ss(line);
        anggota temp;
        getline(ss, temp.id_anggota, ',');
        getline(ss, temp.nama, ',');
        getline(ss, temp.alamat, ',');
        getline(ss, temp.no_telp, ',');
        getline(ss, temp.tanggal_lahir, ',');
        getline(ss, temp.status_keanggotaan, ',');

        string cari_lower = temp.nama;
        transform(cari_lower.begin(), cari_lower.end(), cari_lower.begin(), ::tolower);
        string dicari_lower = cari;
        transform(dicari_lower.begin(), dicari_lower.end(), dicari_lower.begin(), ::tolower);

        if (dicari_lower == cari_lower || temp.id_anggota == cari)
        {
            cout << "Buku yang akan dihapus: " << endl;
            cout << "Id : " << temp.id_anggota << endl;
            cout << "Nama: " << temp.nama << endl;
            cout << "Alamat: " << temp.alamat << endl;
            cout << "No telp: " << temp.no_telp << endl;
            cout << "Tanggal lahir: " << temp.tanggal_lahir << endl;
            cout << "Status anggota: " << temp.status_keanggotaan << endl;
            cout << endl;

            char konfirmasi;
            cout << "Apakah anda yakon ingin menghapus data anggota ini? (y/n): ";
            cin >> konfirmasi;

            if (konfirmasi == 'y' || konfirmasi == 'y')
            {
                anggota_ditemukan = true;
            }
        }
        else
        {
            file_temp << line << endl;
        }
    }
    file_temp.close();
    file_sumber.close();

    if (anggota_ditemukan)
    {
        if (remove(file_anggota.c_str()) != 0)
        {
            cout << "Gagal menghapus buku dari database." << endl;
            return;
        }

        if (rename(temp_anggota.c_str(), file_anggota.c_str()) != 0)
        {
            cout << "Gagal mengubah nama file sementara." << endl;
            return;
        }
        cout << "anggota berhasil dihapus dari database" << endl;
    }
    else
    {
        cout << "Anggota dengan id atau nama " << cari << " Tidak ditemukan dalam database atau tidak dihapus." << endl;
    }
}

void updateA(const string &file_anggota)
{
    ifstream file(file_anggota);
    if (!file.is_open())
    {
        cout << "Gagal membuka file" << file_anggota << endl;
        return;
    }

    vector<anggota> daftar_anggota;
    anggota temp_a;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, temp_a.id_anggota, ',');
        getline(ss, temp_a.nama, ',');
        getline(ss, temp_a.alamat, ',');
        getline(ss, temp_a.no_telp, ',');
        getline(ss, temp_a.tanggal_lahir, ',');
        getline(ss, temp_a.status_keanggotaan, ',');
        daftar_anggota.push_back(temp_a);
    }
    file.close();

    string input;
    cout << "Masukkan id atau nama anggota yang ingin diupdate: " << endl;
    cout << "Nama atau id: ";
    cin.ignore();
    getline(cin, input);
    bool anggota_ditemukan = false;
    for (anggota &a : daftar_anggota)
    {
        if (a.id_anggota == input || a.nama == input)
        {
            cout << "Id : " << a.id_anggota << endl;
            cout << "Nama: " << a.nama << endl;
            cout << "Alamat: " << a.alamat << endl;
            cout << "No telp: " << a.no_telp << endl;
            cout << "Tanggal lahir: " << a.tanggal_lahir << endl;
            cout << "Status anggota: " << a.status_keanggotaan << endl;

            char konfirmasi;
            cout << "Ingin melakukan updata data anggota ini?(y/n): ";
            cin >> konfirmasi;
            cin.ignore();
            if (konfirmasi == 'y' || konfirmasi == 'y')
            {
                cout << "Masukkan data baru!" << endl;
                cout << "Id: ";
                getline(cin, a.id_anggota);
                cout << "Nama: ";
                getline(cin, a.nama);
                cout << "Alamat: ";
                getline(cin, a.alamat);
                cout << "No telp: ";
                getline(cin, a.no_telp);
                cout << "Tanggal lahir: ";
                getline(cin, a.tanggal_lahir);
                cout << "Status keanggotaan: ";
                getline(cin, a.status_keanggotaan);
            }
            anggota_ditemukan = true;
            break;
        }
    }
    if (!anggota_ditemukan)
    {
        cout << "Anggota tidak ditemukan." << endl;
    }

    ofstream outfile(file_anggota);
    if (outfile.is_open())
    {
        for (const auto &a : daftar_anggota)
        {
            outfile << a.id_anggota << "," << a.nama << ","
                    << a.alamat << "," << a.no_telp << ","
                    << a.tanggal_lahir << "," << a.status_keanggotaan << "\n";
        }
        outfile.close();
    }
    else
    {
        cout << "Gagal membuka file untuk tulis ulang" << endl;
    }
}
void DBanggota()
{
    bool kembali = true;
    char kembali_menu;
    do
    {
        int pilih;
        cout << "MENU PILIHAN \n"
             << "1. Kelola Data \n"
             << "2. Tampilkan \n"
             << "3. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;
        // input data anggota
        if (pilih == 1)
        {
            int pilih_menu;
            cout << "Apa yang ingin anda lakukan: \n"
                 << "1. Buat\n"
                 << "2. Ubah data\n"
                 << "3. Hapus\n";
            cout << "Pilih: ";
            cin >> pilih_menu;
            switch (pilih_menu)
            {
            case 1:
                inputdata_baruA("database_anggota.txt");
                break;
            case 2:
                updateA("database_anggota.txt");
                break;
            case 3:
                hapusA("database_anggota.txt", "anggota_temp.txt");
                break;
            default:
                break;
            }
        }
        // tampilkan data
        if (pilih == 2)
        {
            outputA("database_anggota.txt");
        }
        if (kembali_menu == 'y')
        {
            kembali = true;
        }
        if (kembali_menu == 'n')
        {
            kembali = false;
        }
        cout << "Apakah anda ingin kembali ke menu?" << endl;
        cout << "Pilih(y/n):";
        cin >> kembali_menu;
        clearScreen();
    } while (kembali);
}