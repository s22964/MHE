#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <functional>
#include <map>
#include <list>
#include <chrono>
#include "funkcje.h"




typedef std::tuple<std::vector<std::vector<int>>, int,int,int> (*FnPtr)(std::vector<int>,int, int, int,Time,bool);
bool krzywa;
int lc=0;

int Quality(std::vector<std::vector<int>> v, int T) {
    int Q = 0, s;
    for (int i = 0; i < v.size(); i++) {
        s = reduce(v[i].begin(), v[i].end());
        Q += abs(T - s);
    }
    lc += 1;
    return Q;
}

std::tuple<std::vector<std::vector<int>>, int,int,int> random_sampling(std::vector<int> S,int m, int T, int it,Time czas_start,bool K) {
    using namespace std;//settings part
    std::ofstream outfile;
    krzywa=K;
    outfile.open("rndsam.txt", std::ios_base::app); // append instead of overwri
    int x = 0;
    int Q = -1, result;
    std::vector<int> in, v;
    vector<vector<int>> ans;




    for (int k = 0; k < it; k++) {
        ans.clear();
        x += 1;
        in = S;
        for (int j = 0; j < m / 3; j++) {
            v.clear();
            size_t nelems = 3;
            sample(
                    in.begin(),
                    in.end(),
                    back_inserter(v),
                    nelems,
                    mt19937{random_device{}()}
            );
            for (int a = 0; a < 3; a++) {
                in.erase(remove(in.begin(), in.end(), v[a]), in.end());
            }
            ans.push_back(v);
        }
        result = Quality(ans, T);
        if(krzywa){
            auto stop = std::chrono::system_clock::now();
            std::chrono::duration<double> czas = stop-czas_start;
            outfile<<x<<" "<<czas.count()<<" "<<lc<<" "<<result<<endl;
        }
        if (result == 0) {
            Q = result;
            break;
        }
        if (Q < 0) {
            Q = result;
        }
    }


    return {ans, Q,x,lc};
}

std::tuple<std::vector<std::vector<int>>, int,int,int>random_hill_climbing(std::vector<int> S,int m, int T, int it,Time czas_start,bool K) {
    using namespace std;  //settings part
    std::ofstream outfile;
    krzywa=K;
    outfile.open("hillclmb.txt", std::ios_base::app); // append instead of overwri
    int x = 0;
    int Q = -1, result;
    std::vector<int> in, v;
    vector<vector<int>> ans, act;




    for (int k = 0; k < it; k++) {
        act.clear();
        x += 1;
        in = S;
        for (int j = 0; j < m / 3; j++) {
            v.clear();
            size_t nelems = 3;
            sample(
                    in.begin(),
                    in.end(),
                    back_inserter(v),
                    nelems,
                    mt19937{random_device{}()}
            );
            for (int a = 0; a < 3; a++) {
                in.erase(remove(in.begin(), in.end(), v[a]), in.end());
            }
            act.push_back(v);
        }
        result = Quality(act, T);
        if(krzywa){
            auto stop = std::chrono::system_clock::now();
            std::chrono::duration<double> czas = stop-czas_start;
            outfile<<x<<" "<<czas.count()<<" "<<lc<<" "<<result<<endl;
        }
        if (result == 0) {
            Q = result;
            ans = act;
            break;
        }
        if ((Q >= 0 && result < Q) || (Q < 0)) {
            Q = result;
            ans = act;
        }

    }


    return {ans, Q,x,lc};
}


std::tuple<std::vector<std::vector<int>>, int,int,int>hill_climbing_det(std::vector<int> S,int m, int T, int it,Time czas_start,bool K) {
    using namespace std; //settings part
    std::ofstream outfile;
    krzywa=K;
    outfile.open("hillclimbdet.txt", std::ios_base::app); // append instead of overwri
    vector<vector<int>> ans, act;
    int Q,k=0,x=0,Qct;
    vector<int> v;




    for (int j = 0; j < m / 3; j++) { //first answer
        v = {S[k], S[k + 1], S[k + 2]};
        ans.push_back(v);
        k += 3;
    }

    Q= Quality(ans,T);
    if (Q==0){
        x=1;
        return {ans, Q,x,lc};
    }
    act=ans;


    for (int i=0; i<it;i++) {
        x += 1;
        act=find_best_neighbours(act,T);
        Qct= Quality(act,T);
        if(krzywa){
            auto stop = std::chrono::system_clock::now();
            std::chrono::duration<double> czas = stop-czas_start;
            outfile<<x<<" "<<czas.count()<<" "<<lc<<" "<<Q<<endl;
        }
        if(Qct<=Q){
            Q=Qct;
            ans=act;
            if(Q==0){
                break;
            }
        }
    }

    return {ans, Q,x,lc};
}

std::vector<std::vector<int>> find_best_neighbours(std::vector<std::vector<int>> Oans, int T) {
    using namespace std;
    vector<int> v, va, x, l; //v-oryginalne rozwiazanie, va-sasiad, x-element sasiada
    vector<vector<int>> act, ans;
    for (int i = 0; i < Oans.size(); i++) {
        for (int j = 0; j < 3; j++) {
            v.push_back(Oans[i][j]); //spis wszystkich liczb oryginalnego rozwiazania
        }
    }

    int g;
    for (int k = 0; k < v.size(); k++) {
        g = 0;
        act.clear();
        va = v;
        if (k != v.size() - 1) {
            iter_swap(va.begin() + k, va.begin() + k + 1);
        } //zamienianie miejscami
        else {
            iter_swap(va.begin() + k, va.begin()); //jesli ostatnia liczba to zamienia sie z poczatkiem
        }
        for (int j = 0; j < Oans.size(); j++) { //tworzenie sasiada
            x = {va[g], va[g + 1], va[g + 2]};
            act.push_back(x);
            g += 3;
        }
        if (k == 0) { //jesli to pierwszy sasiad to staje sie najlepszym
            ans = act;
            l = va;
        } else {
            if (Quality(act, T) <= Quality(ans, T)) {
                ans = act;
                l = va;
            }
        }
    }

    return ans;

}

std::tuple<std::vector<std::vector<int>>, int,int,int> tabu_search(std::vector<int> S,int m, int T, int it,Time czas_start,bool K) {
    using namespace std; //settings part
    std::ofstream outfile;
    krzywa=K;
    outfile.open("test.txt", std::ios_base::app); // append instead of overwrite
    const int tabu_size = 1000;
    list<vector<vector<int>>> tabu_list;
    int i, a, x = 0;
    vector<vector<int>> ans, act;
    vector<int> v;
    i = 0;




    for (int j = 0; j < m / 3; j++) { //pierwsze rozwiazanie
        v = {S[i], S[i + 1], S[i + 2]};
        act.push_back(v);
        i += 3;
    }
    tabu_list.push_back(act);
    ans = tabu_list.back();

    for (int k = 0; k < it; k++) {
        x += 1;
        vector<vector<int>> best_neighbour = find_best_neighbours(tabu_list.back(),
                                                                  T); //znalezienie sasiada i wybranie najlepszego z nich
        if (best_neighbour == ans) {
            cerr << "we ate our tail :/" << endl;
            break;
        }
        tabu_list.push_back(best_neighbour);

        a=Quality(tabu_list.back(), T);
        if(krzywa){
            auto stop = std::chrono::system_clock::now();
            std::chrono::duration<double> czas = stop-czas_start;
            outfile <<x<<" "<<czas.count()<<" "<<lc<<" "<<a<<endl;
        }
        if (a <= Quality(ans, T)) {
            ans = tabu_list.back();
        }
        if (tabu_list.size() == tabu_size) {
            tabu_list.pop_front();
        }

    }
    return {ans, Quality(ans, T),x,lc};
}



std::tuple<std::vector<std::vector<int>>, int,int,int> przeglad(std::vector<int> S,int m, int T, int it,Time czas_start,bool K) {
    using namespace std; //setting part
    std::ofstream outfile;
    krzywa=K;
    outfile.open("przeglad.txt", std::ios_base::app); // append instead of overwrite
    vector<vector<int>> ans, act;
    int Q = -1, i, result;
    vector<int> v;
    int x = 0;




    sort(S.begin(), S.end());
    while (next_permutation(S.begin(), S.end())) {
        act.clear();
        i = 0;
        x += 1;
        for (int j = 0; j < m / 3; j++) {
            v = {S[i], S[i + 1], S[i + 2]};
            act.push_back(v);
            i += 3;
        }
        result = Quality(act, T);
        if(krzywa&&x<10001){
            auto stop = std::chrono::system_clock::now();
            std::chrono::duration<double> czas = stop-czas_start;
            outfile<<x<<" "<<czas.count()<<" "<<lc<<" "<<result<<endl;
        }

        if ((Q >= 0 && result < Q) || (Q < 0)) {
            Q = result;
            ans = act;
        }
    }

    return {ans, Q,x,lc};
}

std::pair<std::string, std::vector<int>> readFile(std::string Filename) {
    using namespace std;
    ifstream source;
    source.open(Filename);
    vector<std::string> lines;
    string line;
    while (std::getline(source, line)) {
        lines.push_back(line);
    }
    if (!lines.size() == 3) {
        cout << "zla ilosc zmiennych";
        exit(3);
    }
    string fname = lines[0];
    stringstream iss(lines[2]);
    int number;
    std::vector<int> myNumbers;

    if (lines[1] == ("")) {
        myNumbers.push_back(0);
    } else {
        myNumbers.push_back(std::stoi(lines[1]));
    }
    while (iss >> number) {
        myNumbers.push_back(number);
    }
    return make_pair(fname, myNumbers);
}


