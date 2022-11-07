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


std::pair<std::vector<std::vector<int>>, int> generate_random_solution(int m, int T, int it) {
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
        if ((Q >= 0 && result < Q) || (Q < 0)) {
            Q = result;
            ans = act;
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
std::pair<std::string,std::vector<int>>readFile(std::string Filename){
    using namespace std;
    ifstream source;
    source.open(Filename);
    vector<std::string> lines;
    string line;
    while (std::getline(source, line))
    {
        lines.push_back(line);
    }
    if(!lines.size()==3) {
        cout << "zla ilosc zmiennych";
        exit(3);
    }
        string fname=lines[0];
        stringstream iss( lines[2] );
        int number;
        std::vector<int> myNumbers;
        myNumbers.push_back(std::stoi( lines[1] ));
        while ( iss >> number ) {
            myNumbers.push_back(number);
        }
    return make_pair(fname,myNumbers);
}

int main(int argc, char **argv) {
    using namespace std;
    string Filename(argv[1]);
    readFile(Filename);

    int it = readFile(Filename).second[0];
    string fname= readFile(Filename).first;
    map<string, FnPtr> myMap;
    myMap["przeglad"] = przeglad;
    myMap["losowe"] = generate_random_solution;
    S= readFile(Filename).second;
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
    return 0;
}
