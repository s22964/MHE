#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

std::vector<int> S;

//std::pair<std::vector<int>, bool> check(int T) {
//    std::vector<int> v;
//    int m = S.size();
//    bool t = false;
//    for (int i = 0; i < m; i++) {
//        for (int j = i + 1; j < m; j++) {
//            for (int k = j + 1; k < m; k++) {
//                if (S[i] + S[j] + S[k] == T) {
//                    t = true;
//                    v = {S[i], S[j], S[k]};
//                    S.erase(S.begin() + k);
//                    S.erase(S.begin() + j);
//                    S.erase(S.begin() + i);
//                    return std::make_pair(v, t);
//                }
//            }
//        }
//    }
//
//    return std::make_pair(v, t);
//
//}

int Quality(std::vector<std::vector<int>> v, int T) {
    int Q=0, s;
    for (int i = 0; i < v.size(); i++) {
        s = reduce(v[i].begin(), v[i].end());
        Q += abs(T - s);
    }
    return Q;
}


int main(int argc, char **argv) {
    using namespace std;

    for (int i = 1; i < argc; i++) {
        S.push_back(strtol(argv[i], NULL, 10));
    }

    int m = S.size();
    cout << "Zbior S to: {";
    for (int i = 0; i < m; i++) {
        cout << S[i];
        if (i + 1 < m) {
            cout << ",";
        }
    }
    cout << "}" << endl;


    if (m % 3 != 0) {
        cout << "Zbior musi byc podzielny przez 3!";
    } else {
        int sum = 0;
        for (auto &n: S) {
            sum += n;
        }
        int T = sum / (m / 3);
        cout << "Suma T=" << T << endl;

        vector<vector<int>> ans, act;
//        pair<vector<vector<int>>, bool> result;
//        for (int i = 0; i < m / 3; i++) {
//            result = check(T);
//            if (!result.second) {
//                cout << "nie znaleziono 3 liczb o sumie T=" + T << endl;
//                break;
//            } else {
//                ans.push_back(result.first);
//            }
//        }

        int Q=-1, i,result;
        vector<int> v;
        int X = 0;
        sort(S.begin(), S.end());
        while (next_permutation(S.begin(), S.end())) {
            act.clear();
            i = 0;
            X += 1;
            for (int j = 0; j < m / 3; j++) {
                v = {S[i], S[i + 1], S[i + 2]};
                act.push_back(v);
                i += 3;
            }
            result = Quality(act,T);


            if ((Q >= 0 && result < Q) || (Q < 0)) {
                Q = result;
                ans = act;
            }
        }




//        if (result.second) {
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
//    }
    return 0;
}
