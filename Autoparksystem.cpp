#include <iostream>
#include <string>
#include <vector>
#include <ctime>  // Added for time operations

using namespace std;

// Struct to hold information about parked vehicles
struct ParkedVehicle {
    string plateNumber;
    int floor;
    int place;
    time_t entryTime;  // Added entry time for fee calculation
};

// Function declarations
void ana_menu(vector<ParkedVehicle>& parkedVehicles);
void arac_listeleme(vector<ParkedVehicle>& parkedVehicles);
void arac_girisi(vector<ParkedVehicle>& parkedVehicles);
void arac_cikis(vector<ParkedVehicle>& parkedVehicles);

// Global variables for parking status
const int KAT_SAYISI = 5;
int müsait_park_yeri[KAT_SAYISI][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

// Function to calculate parking duration in minutes
int calculateParkingDuration(const time_t& entryTime) {
    time_t now = time(0);
    int duration = difftime(now, entryTime) / 60;  // Convert seconds to minutes
    return duration;
}

// Function to calculate parking fee based on duration
int calculateParkingFee(int duration) {
    if (duration <= 30) {
        return 0;
    } else if (duration <= 60) {
        return 20;
    } else if (duration <= 120) {
        return 40;
    } else if (duration <= 300) {
        return 80;
    } else {
        return 120;
    }
}

int main() {
    // Kullanýcý adý ve þifre
    string kullanici_adi, sifre;

    // Kullanýcý adý ve þifre giriþi
    cout << "Kullanýcý adý: ";
    cin >> kullanici_adi;
    cout << "Þifre: ";
    cin >> sifre;

    // Kullanýcý adý ve þifrenin doðrulanmasý
    if (kullanici_adi == "Mall" && sifre == "Autopark") {
        // Kullanýcý giriþi baþarýlý
        cout << " Hoþgeldiniz " << kullanici_adi << " " << sifre << endl;
    } else {
        // Kullanýcý giriþi baþarýsýz
        cout << "Kullanýcý adý veya þifre hatalý!" << endl;
        return 0;
    }

    // Vector to hold parked vehicles
    vector<ParkedVehicle> parkedVehicles;

    // Ana menüye yönlendirme
    ana_menu(parkedVehicles);
    return 0;
}
void ana_menu(vector<ParkedVehicle>& parkedVehicles) {
    // Menü seçenekleri
    const int ARAC_LISTELEME = 1;
    const int ARAC_GIRISI = 2;
    const int ARAC_CIKISI = 3;
    const int PROGRAM_SONLANDIRMA = 4;

    // Menü seçimi
    int secim;
    cout << "Lütfen yapmak istediðiniz iþlemi seçiniz:" << endl;
    cout << "1 - Araç listeleme" << endl;
    cout << "2 - Araç giriþi" << endl;
    cout << "3 - Araç çýkýþý" << endl;
    cout << "4 - Program sonlandýrma" << endl;
    cin >> secim;

    // Get current time
    time_t now = time(0);
    tm* ltm = localtime(&now);

    // Print current time
    cout << "Ýþlem zamaný: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;

    // Seçime göre iþlem yapma
    switch (secim) {
        case ARAC_LISTELEME:
        arac_listeleme(parkedVehicles);
        break;
    case ARAC_GIRISI:
        arac_girisi(parkedVehicles);
        break;
    case ARAC_CIKISI:
        arac_cikis(parkedVehicles);
        break;
    case PROGRAM_SONLANDIRMA:
        return;
    default:
        cout << "Hatalý seçim!" << endl;
        break;
    }

    // Ana menüye yönlendirme
    ana_menu(parkedVehicles);
}

void arac_listeleme(vector<ParkedVehicle>& parkedVehicles) {
    // List available and full parking spaces for a selected floor
    int selected_floor;
    cout << "Lütfen kat numarasýný seçiniz (1-5): ";
    cin >> selected_floor;

    if (selected_floor < 1 || selected_floor > KAT_SAYISI) {
        cout << "Geçersiz kat numarasý!" << endl;
        return;
    }

    cout << "Kat " << selected_floor << " durumu:" << endl;
    for (int park_yeri = 0; park_yeri < 10; park_yeri++) {
        if (müsait_park_yeri[selected_floor - 1][park_yeri] == 1) {
            cout << "Park Yeri " << (park_yeri + 1) << ": Boþ" << endl;
        } else {
            // Find the vehicle with the corresponding floor and place
            for (const auto& vehicle : parkedVehicles) {
                if (vehicle.floor == selected_floor && vehicle.place == (park_yeri + 1)) {
                    cout << "Park Yeri " << (park_yeri + 1) << ": Dolu - Araç Plakasý: " << vehicle.plateNumber << endl;
                    break;
                }
            }
        }
    }
}

void arac_girisi(vector<ParkedVehicle>& parkedVehicles) {
    int selected_floor;
    cout << "Lütfen kat numarasýný seçiniz (1-5): ";
    cin >> selected_floor;

    if (selected_floor < 1 || selected_floor > KAT_SAYISI) {
        cout << "Geçersiz kat numarasý!" << endl;
        return;
    }

    cout << "Boþ park yerleri (Kat " << selected_floor << "):" << endl;
    bool bos_yer_var = false;
    for (int park_yeri = 0; park_yeri < 10; park_yeri++) {
        if (müsait_park_yeri[selected_floor - 1][park_yeri] == 1) {
            cout << "Park Yeri " << (park_yeri + 1) << endl;
            bos_yer_var = true;
        }
    }

    if (!bos_yer_var) {
        cout << "Seçilen katta boþ park yeri bulunmamaktadýr." << endl;
        return;
    }

    int selected_park_yeri;
    cout << "Lütfen aracýnýzý park etmek istediðiniz yeri seçiniz: ";
    cin >> selected_park_yeri;

    if (selected_park_yeri < 1 || selected_park_yeri > 10 || müsait_park_yeri[selected_floor - 1][selected_park_yeri - 1] != 1) {
        cout << "Geçersiz park yeri numarasý!" << endl;
        return;
    }

    // Park yerini iþaretle
    müsait_park_yeri[selected_floor - 1][selected_park_yeri - 1] = 0;

    // Input the plate number for the parked vehicle
    string plateNumber;
    cout << "Lütfen aracýnýzýn plaka numarasýný giriniz: ";
    cin >> plateNumber;

    // Create a new ParkedVehicle object and add it to the vector
    ParkedVehicle newVehicle;
    newVehicle.plateNumber = plateNumber;
    newVehicle.floor = selected_floor;
    newVehicle.place = selected_park_yeri;
    parkedVehicles.push_back(newVehicle);

    cout << "Araç baþarýyla park edildi! Plaka Numarasý: " << plateNumber << " - Kat: " << selected_floor << " - Park Yeri: " << selected_park_yeri << endl;
}

void arac_cikis(vector<ParkedVehicle>& parkedVehicles) {
    int selected_floor;
    cout << "Lütfen kat numarasýný seçiniz (1-5): ";
    cin >> selected_floor;

    if (selected_floor < 1 || selected_floor > KAT_SAYISI) {
        cout << "Geçersiz kat numarasý!" << endl;
        return;
    }

    cout << "Dolu park yerleri (Kat " << selected_floor << "):" << endl;
    bool dolu_yer_var = false;
    for (int park_yeri = 0; park_yeri < 10; park_yeri++) {
        if (müsait_park_yeri[selected_floor - 1][park_yeri] == 0) {
            // Find the vehicle with the corresponding floor and place
            for (auto it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it) {
                if (it->floor == selected_floor && it->place == (park_yeri + 1)) {
                    cout << "Park Yeri " << (park_yeri + 1) << " - Araç Plakasý: " << it->plateNumber << endl;
                    // Ask if the user wants an invoice
                    char invoiceChoice;
                    cout << "Fatura almak ister misiniz? (E/H): ";
                    cin >> invoiceChoice;

                    if (invoiceChoice == 'E' || invoiceChoice == 'e') {
                        // Calculate parking duration
                        int duration = calculateParkingDuration(it->entryTime);

                        // Calculate parking fee
                        int fee = calculateParkingFee(duration);

                        // Print the invoice
                        cout << "Fatura Bilgileri:" << endl;
                        cout << "Araç Plakasý: " << it->plateNumber << endl;
                        cout << "Kat Numarasý: " << it->floor << endl;
                        cout << "Park Yeri Numarasý: " << it->place << endl;
                        cout << "Park Süresi: " << duration << " dakika" << endl;
                        cout << "Toplam Ücret: " << fee << " TL" << endl;

                        // Remove the vehicle from the vector
                        parkedVehicles.erase(it);
                        cout << "Araç baþarýyla çýkartýldý ve fatura yazdýrýldý." << endl;
                        return;
                    } else {
                        // Remove the vehicle from the vector without printing an invoice
                        parkedVehicles.erase(it);
                        cout << "Araç baþarýyla çýkartýldý." << endl;
                        return;
                    }
                }
            }
        }
    }

   if (!dolu_yer_var) {
        cout << "Seçilen katta dolu park yeri bulunmamaktadýr." << endl;
        return;
    }

    int selected_park_yeri;
    cout << "Lütfen aracýnýzý çýkarmak istediðiniz yeri seçiniz: ";
    cin >> selected_park_yeri;

    if (selected_park_yeri < 1 || selected_park_yeri > 10 || müsait_park_yeri[selected_floor - 1][selected_park_yeri - 1] != 0) {
        cout << "Geçersiz park yeri numarasý!" << endl;
        return;
    }

    // Park yerini boþalt
    müsait_park_yeri[selected_floor - 1][selected_park_yeri - 1] = 1;

    // Remove the vehicle from the vector
    for (auto it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it) {
        if (it->floor == selected_floor && it->place == selected_park_yeri) {
            cout << "Araç baþarýyla çýkartýldý! Plaka Numarasý: " << it->plateNumber << " - Kat: " << selected_floor << " - Park Yeri: " << selected_park_yeri << endl;
            parkedVehicles.erase(it);
            break;
        }
    }
}
