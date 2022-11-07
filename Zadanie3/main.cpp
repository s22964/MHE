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

std::pair<std::vector<std::vector<int>>, int> Quality(std::vector<int>,int m, int T){
    int Q,Qa,i,s;
    i=0;
    std::vector<int> v;
    std::vector<std::vector<int>> act;
    for(int j=0;j<m/3;j++){
        v={S[i],S[i+1],S[i+2]};
        s=reduce(v.begin(),v.end());
        Qa+=abs(T-s);
        act.push_back(v);
        i+=3;
    }

    return std::make_pair(act,Q);
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

        vector<vector<int>> ans;
        pair<vector<vector<int>>, int> result;
//        for (int i = 0; i < m / 3; i++) {
//            result = check(T);
//            if (!result.second) {
//                cout << "nie znaleziono 3 liczb o sumie T=" + T << endl;
//                break;
//            } else {
//                ans.push_back(result.first);
//            }
//        }

        int Q,Qa,i,s;
        vector<int> v;
        Q=-1;
        int X=0;
        sort(S.begin(),S.end());
        while(next_permutation(S.begin(),S.end())){
            X+=1;
            result=Quality(S,m,T);
            if((Q>=0&&result.second<Q)||(Q<0)) {
                Q = result.second;
                ans = result.first;
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
            cout<<"Jakosc: "<<Q<<endl;
            cout<<"Iteracje: "<<X<<endl;
        }
//    }
    return 0;
}
