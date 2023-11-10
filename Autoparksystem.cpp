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
int m�sait_park_yeri[KAT_SAYISI][10] = {
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
    // Kullan�c� ad� ve �ifre
    string kullanici_adi, sifre;

    // Kullan�c� ad� ve �ifre giri�i
    cout << "Kullan�c� ad�: ";
    cin >> kullanici_adi;
    cout << "�ifre: ";
    cin >> sifre;

    // Kullan�c� ad� ve �ifrenin do�rulanmas�
    if (kullanici_adi == "Mall" && sifre == "Autopark") {
        // Kullan�c� giri�i ba�ar�l�
        cout << " Ho�geldiniz " << kullanici_adi << " " << sifre << endl;
    } else {
        // Kullan�c� giri�i ba�ar�s�z
        cout << "Kullan�c� ad� veya �ifre hatal�!" << endl;
        return 0;
    }

    // Vector to hold parked vehicles
    vector<ParkedVehicle> parkedVehicles;

    // Ana men�ye y�nlendirme
    ana_menu(parkedVehicles);
    return 0;
}
void ana_menu(vector<ParkedVehicle>& parkedVehicles) {
    // Men� se�enekleri
    const int ARAC_LISTELEME = 1;
    const int ARAC_GIRISI = 2;
    const int ARAC_CIKISI = 3;
    const int PROGRAM_SONLANDIRMA = 4;

    // Men� se�imi
    int secim;
    cout << "L�tfen yapmak istedi�iniz i�lemi se�iniz:" << endl;
    cout << "1 - Ara� listeleme" << endl;
    cout << "2 - Ara� giri�i" << endl;
    cout << "3 - Ara� ��k���" << endl;
    cout << "4 - Program sonland�rma" << endl;
    cin >> secim;

    // Get current time
    time_t now = time(0);
    tm* ltm = localtime(&now);

    // Print current time
    cout << "��lem zaman�: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;

    // Se�ime g�re i�lem yapma
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
        cout << "Hatal� se�im!" << endl;
        break;
    }

    // Ana men�ye y�nlendirme
    ana_menu(parkedVehicles);
}

void arac_listeleme(vector<ParkedVehicle>& parkedVehicles) {
    // List available and full parking spaces for a selected floor
    int selected_floor;
    cout << "L�tfen kat numaras�n� se�iniz (1-5): ";
    cin >> selected_floor;

    if (selected_floor < 1 || selected_floor > KAT_SAYISI) {
        cout << "Ge�ersiz kat numaras�!" << endl;
        return;
    }

    cout << "Kat " << selected_floor << " durumu:" << endl;
    for (int park_yeri = 0; park_yeri < 10; park_yeri++) {
        if (m�sait_park_yeri[selected_floor - 1][park_yeri] == 1) {
            cout << "Park Yeri " << (park_yeri + 1) << ": Bo�" << endl;
        } else {
            // Find the vehicle with the corresponding floor and place
            for (const auto& vehicle : parkedVehicles) {
                if (vehicle.floor == selected_floor && vehicle.place == (park_yeri + 1)) {
                    cout << "Park Yeri " << (park_yeri + 1) << ": Dolu - Ara� Plakas�: " << vehicle.plateNumber << endl;
                    break;
                }
            }
        }
    }
}

void arac_girisi(vector<ParkedVehicle>& parkedVehicles) {
    int selected_floor;
    cout << "L�tfen kat numaras�n� se�iniz (1-5): ";
    cin >> selected_floor;

    if (selected_floor < 1 || selected_floor > KAT_SAYISI) {
        cout << "Ge�ersiz kat numaras�!" << endl;
        return;
    }

    cout << "Bo� park yerleri (Kat " << selected_floor << "):" << endl;
    bool bos_yer_var = false;
    for (int park_yeri = 0; park_yeri < 10; park_yeri++) {
        if (m�sait_park_yeri[selected_floor - 1][park_yeri] == 1) {
            cout << "Park Yeri " << (park_yeri + 1) << endl;
            bos_yer_var = true;
        }
    }

    if (!bos_yer_var) {
        cout << "Se�ilen katta bo� park yeri bulunmamaktad�r." << endl;
        return;
    }

    int selected_park_yeri;
    cout << "L�tfen arac�n�z� park etmek istedi�iniz yeri se�iniz: ";
    cin >> selected_park_yeri;

    if (selected_park_yeri < 1 || selected_park_yeri > 10 || m�sait_park_yeri[selected_floor - 1][selected_park_yeri - 1] != 1) {
        cout << "Ge�ersiz park yeri numaras�!" << endl;
        return;
    }

    // Park yerini i�aretle
    m�sait_park_yeri[selected_floor - 1][selected_park_yeri - 1] = 0;

    // Input the plate number for the parked vehicle
    string plateNumber;
    cout << "L�tfen arac�n�z�n plaka numaras�n� giriniz: ";
    cin >> plateNumber;

    // Create a new ParkedVehicle object and add it to the vector
    ParkedVehicle newVehicle;
    newVehicle.plateNumber = plateNumber;
    newVehicle.floor = selected_floor;
    newVehicle.place = selected_park_yeri;
    parkedVehicles.push_back(newVehicle);

    cout << "Ara� ba�ar�yla park edildi! Plaka Numaras�: " << plateNumber << " - Kat: " << selected_floor << " - Park Yeri: " << selected_park_yeri << endl;
}

void arac_cikis(vector<ParkedVehicle>& parkedVehicles) {
    int selected_floor;
    cout << "L�tfen kat numaras�n� se�iniz (1-5): ";
    cin >> selected_floor;

    if (selected_floor < 1 || selected_floor > KAT_SAYISI) {
        cout << "Ge�ersiz kat numaras�!" << endl;
        return;
    }

    cout << "Dolu park yerleri (Kat " << selected_floor << "):" << endl;
    bool dolu_yer_var = false;
    for (int park_yeri = 0; park_yeri < 10; park_yeri++) {
        if (m�sait_park_yeri[selected_floor - 1][park_yeri] == 0) {
            // Find the vehicle with the corresponding floor and place
            for (auto it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it) {
                if (it->floor == selected_floor && it->place == (park_yeri + 1)) {
                    cout << "Park Yeri " << (park_yeri + 1) << " - Ara� Plakas�: " << it->plateNumber << endl;
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
                        cout << "Ara� Plakas�: " << it->plateNumber << endl;
                        cout << "Kat Numaras�: " << it->floor << endl;
                        cout << "Park Yeri Numaras�: " << it->place << endl;
                        cout << "Park S�resi: " << duration << " dakika" << endl;
                        cout << "Toplam �cret: " << fee << " TL" << endl;

                        // Remove the vehicle from the vector
                        parkedVehicles.erase(it);
                        cout << "Ara� ba�ar�yla ��kart�ld� ve fatura yazd�r�ld�." << endl;
                        return;
                    } else {
                        // Remove the vehicle from the vector without printing an invoice
                        parkedVehicles.erase(it);
                        cout << "Ara� ba�ar�yla ��kart�ld�." << endl;
                        return;
                    }
                }
            }
        }
    }

   if (!dolu_yer_var) {
        cout << "Se�ilen katta dolu park yeri bulunmamaktad�r." << endl;
        return;
    }

    int selected_park_yeri;
    cout << "L�tfen arac�n�z� ��karmak istedi�iniz yeri se�iniz: ";
    cin >> selected_park_yeri;

    if (selected_park_yeri < 1 || selected_park_yeri > 10 || m�sait_park_yeri[selected_floor - 1][selected_park_yeri - 1] != 0) {
        cout << "Ge�ersiz park yeri numaras�!" << endl;
        return;
    }

    // Park yerini bo�alt
    m�sait_park_yeri[selected_floor - 1][selected_park_yeri - 1] = 1;

    // Remove the vehicle from the vector
    for (auto it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it) {
        if (it->floor == selected_floor && it->place == selected_park_yeri) {
            cout << "Ara� ba�ar�yla ��kart�ld�! Plaka Numaras�: " << it->plateNumber << " - Kat: " << selected_floor << " - Park Yeri: " << selected_park_yeri << endl;
            parkedVehicles.erase(it);
            break;
        }
    }
}
