#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <random>
#include <functional>
#include <map>
#include <list>
#include <chrono>
#include "funkcje.h"


 std::vector<int> S;

 bool krzywa,l_celu;
 int X,lc;
std::chrono::time_point <std::chrono::system_clock, std::chrono::duration<double>> czas_start;

int main(int argc, char **argv) {
    using namespace std;
    lc=0;

    cout<<"1.Nazwa Pliku, 2.Czas Obliczen, 3.Krzywa, 4.Rozwiazanie, 5.Jakosc, 6.Liczba Iteracji, 7.Liczba Ocen"<<endl;
    try {
        string Filename(argv[1]);
        readFile(Filename);
        bool timer=((string)argv[2]=="true");
        krzywa=((string)argv[3]=="true");
        bool rozwiazanie=((string)argv[4]=="true");

        bool jakosc=((string)argv[5]=="true");
        bool l_iteracji=((string)argv[6]=="true");
        l_celu=((string)argv[7]=="true");



        int it = readFile(Filename).second[0];
        string fname = readFile(Filename).first;
        map<string, FnPtr> myMap;
        myMap["przeglad"] = przeglad;
        myMap["wspinaczkowyDet"] = hill_climbing_det;
        myMap["wspinaczkowyRan"] = random_hill_climbing;
        myMap["losowy"] = random_sampling;
        myMap["tabu"] = tabu_search;
        S = readFile(Filename).second;
        S.erase(S.begin());

        int m = S.size();
        cout << "Zbior S to: {";
        for (int i = 0; i < m; i++) {
            cout << S[i];
            if (i + 1 < m) {
                cout << ",";
            }
        }
        cout << "}" << endl;
        int Q;
        vector<vector<int>> ans;

        if (m % 3 != 0) {
            cout << "Zbior musi byc podzielny przez 3!";
        } else {
            pair<vector<vector<int>>, int> result;
            int sum = 0;
            for (auto &n: S) {
                sum += n;
            }
            int T = sum / (m / 3);
            cout << "Suma T=" << T << endl;
            czas_start = std::chrono::system_clock::now();
            try {

                result = myMap[fname](m, T, it);

            } catch (...) {
                cout << "nieprawidłowe dane";
                exit(3);
            }
            auto czas_stop = std::chrono::system_clock::now();
            ans = result.first;
            Q = result.second;
            if(rozwiazanie) {
                cout << "Wynik:" << endl;
                for (int i = 0; i < ans.size(); i++) {
                    cout << "{";
                    for (int j = 0; j < ans[i].size(); j++) {
                        cout << ans[i][j];
                        if (j + 1 < ans[i].size()) {
                            cout << ",";
                        }
                    }
                    cout << "}" << endl;
                }
            }
            if(jakosc) cout << "Jakosc: " << Q << endl;
            if(l_iteracji) cout << "Iteracje: " << X << endl;
            if (timer){
                std::chrono::duration<double> czas_obliczen = czas_stop-czas_start;
                std::cout << "Czas Obliczen: " << czas_obliczen.count() << "s\n";
            }
            if(l_celu) cout<<"Liczba Ocen: "<<lc<<endl;
        }
    }
    catch (logic_error r) {
        cout << "nie odnaleziono pliku";
        exit(3);
    }
    return 0;
}
