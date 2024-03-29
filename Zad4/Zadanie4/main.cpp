#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <random>
#include <functional>
#include <map>

std::vector<int> S;

int X;

typedef std::pair<std::vector<std::vector<int>>, int> (*FnPtr)(int, int, int);

int Quality(std::vector<std::vector<int>> v, int T) {
    int Q = 0, s;
    for (int i = 0; i < v.size(); i++) {
        s = reduce(v[i].begin(), v[i].end());
        Q += abs(T - s);
    }
    return Q;
}

std::pair<std::vector<std::vector<int>>, int> random_sampling(int m, int T, int it) {
    using namespace std;
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
        if (result == 0) {
            Q = result;
            break;
        }
        if (Q < 0) {
            Q = result;
        }
    }

    X = x;
    return make_pair(ans, Q);
}

std::pair<std::vector<std::vector<int>>, int> random_hill_climbing(int m, int T, int it) {
    using namespace std;
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

    X = x;
    return make_pair(ans, Q);
}

std::vector<std::vector<int>> find_best_neighbours(std::vector<std::vector<int>> Oans,int T){
    using namespace std;

    vector<int> v,va,x,l; //v-oryginalne rozwiazanie, va-sasiad, x-element sasiada
    vector<vector<int>> act,ans;
    for(int i=0;i<Oans.size();i++){
        for(int j=0;j<3;j++){
            v.push_back(Oans[i][j]); //spis wszystkich liczb oryginalnego rozwiazania
        }
    }


    int g;
    for(int k=0;k<v.size();k++){
        g=0;
        act.clear();
        va=v;
        if(k!=v.size()-1){
            iter_swap(va.begin() + k, va.begin() + k+1);} //zamienianie miejscami
        else{
            iter_swap(va.begin() + k, va.begin()); //jesli ostatnia liczba to zamienia sie z poczatkiem
        }
        for (int j = 0; j < Oans.size(); j++) { //tworzenie sasiada
            x = {va[g], va[g + 1], va[g + 2]};
            act.push_back(x);
            g += 3;
        }
        if(k==0){ //jesli to pierwszy sasiad to staje sie najlepszym
            ans=act;
            l=va;
        }else{
            if(Quality(act,T)<= Quality(ans,T)){
                ans=act;
                l=va;
            }
        }
    }

    return ans;

}
std::pair<std::vector<std::vector<int>>, int> hill_climbing_det(int m, int T, int it) {
    using namespace std;
    vector<vector<int>> ans, act;
    int Q,k=0,x=0,Qct;
    vector<int> v;
    for (int j = 0; j < m / 3; j++) {
        v = {S[k], S[k + 1], S[k + 2]};
        ans.push_back(v);
        k += 3;
    }

    Q= Quality(ans,T);
    if (Q==0){
        X=1;
        return make_pair(ans, Q);
    }
    act=ans;


    for (int i=0; i<it;i++) {
        x += 1;
        act=find_best_neighbours(act,T);
        Qct= Quality(act,T);
        if(Qct<=Q){
            Q=Qct;
            ans=act;
            if(Q==0){
                break;
            }
        }
    }
    X = x;
    return make_pair(ans, Q);
}

std::pair<std::vector<std::vector<int>>, int> przeglad(int m, int T, int it) {
    using namespace std;

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


        if ((Q >= 0 && result < Q) || (Q < 0)) {
            Q = result;
            ans = act;
        }
    }
    X = x;
    return make_pair(ans, Q);


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

int main(int argc, char **argv) {
    using namespace std;
    try {
        string Filename(argv[1]);
        readFile(Filename);

        int it = readFile(Filename).second[0];
        string fname = readFile(Filename).first;
        map<string, FnPtr> myMap;
        myMap["przeglad"] = przeglad;
        myMap["wspinaczkowyDet"] = hill_climbing_det;
        myMap["wspinaczkowyRan"] = random_hill_climbing;
        myMap["losowy"] = random_sampling;
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

            try {

                result = myMap[fname](m, T, it);
            } catch (...) {
                cout << "nieprawidłowe dane";
                exit(3);
            }
            ans = result.first;
            Q = result.second;

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
            cout << "Jakosc: " << Q << endl;
            cout << "Iteracje: " << X << endl;
        }
    }
    catch (logic_error r) {
        cout << "nie odnaleziono pliku";
        exit(3);
    }
    return 0;
}
