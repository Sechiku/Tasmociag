//Techniki programowania projekt 2, Zadanie 1. Taśmociąg 
// Aleksander Turek 203677
// Sebastian Friedrich 203361

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>

using namespace std;

class stos_samochod {
private:
    stack<float> przedmioty;
    float waga_zaladowana;
    float waga_max;
public:
    stos_samochod(float waga_max) : waga_zaladowana(0), waga_max(waga_max) {}
    bool zaladowanie(float waga_przedmiotu) {
        if (waga_zaladowana + waga_przedmiotu > waga_max) {
            return false;
        }
        przedmioty.push(waga_przedmiotu);
        waga_zaladowana += waga_przedmiotu;
        return true;
    }
    float uzysk_obecne_zaladowanie() const { return waga_zaladowana; }
    float uzysk_waga_max() const { return waga_max; }
    void wysw_zaladunek() const {  
        vector<float> temp;
        stack<float> copy = przedmioty;    
        while (!copy.empty()) {
            temp.push_back(copy.top());
            copy.pop();
        }
        for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
            cout << fixed << setprecision(1) << *it << " ";
        }
    }
};

int main() {
    srand(time(nullptr));
    random_device rd;
    mt19937 gen(rd());

    vector<float> mozliwe_wagi = {10.0f, 14.0f, 16.0f};
    uniform_int_distribution<> losuj_typ(0, mozliwe_wagi.size() - 1);

    queue<float> podajnik;
    const int il_przedm_na_podajniku = 7;
    cout << "Przedmioty na taśmociągu: ";
    for (int i = 0; i < il_przedm_na_podajniku; ++i) {
        float waga_przedmiotu = 1.0 + (rand() % 101) / 10.0;
        podajnik.push(waga_przedmiotu);
        cout << fixed << setprecision(1) << waga_przedmiotu << " ";
    }
    cout << "← kierunek podawania\n";
    cout << "\n\n";

    vector<stos_samochod*> samochody;
    
    while (!podajnik.empty()) {
        float obecny_przedmiot = podajnik.front();
        podajnik.pop();
        bool zaladowany = false;
        if (!samochody.empty()) {
            stos_samochod* ostatni = samochody.back();
            if (ostatni->zaladowanie(obecny_przedmiot)) {
                zaladowany = true;
            }
        }
        if (!zaladowany) {
            float waga_max = mozliwe_wagi[losuj_typ(gen)];
            stos_samochod* nowy_sam = new stos_samochod(waga_max);
            nowy_sam->zaladowanie(obecny_przedmiot);
            samochody.push_back(nowy_sam);
        }
    }
    cout << "Załadowane samochody:\n";
    for (size_t i = 0; i < samochody.size(); ++i) {
        cout << "Samochód " << i + 1 << " [" 
             << samochody[i]->uzysk_obecne_zaladowanie() << "/" 
             << samochody[i]->uzysk_waga_max() << "]: ";
        samochody[i]->wysw_zaladunek();
        cout << "\n";
    }
    for (auto& samochod : samochody) {
        delete samochod;
    }
    return 0;
}