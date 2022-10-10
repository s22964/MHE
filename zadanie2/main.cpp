#include <iostream>
#include <vector>

std::pair<std::vector<int>,bool>  check (std::vector<int> S,int T){
    std::vector<int> v;
    bool c;
    return std::make_pair(v,c);

}

int main() {
    using namespace std;
    vector<int> S={20,23,25,30,49,45,27,30,30,40,22,19};
    int m=S.size();
    if (m%3!=0){
        cout<<"Zbior musi byc podzielny przez 3!";
    }else{
        int sum=0;
        for (auto& n: S){
            sum+=n;
        }
        int T=sum/(m/3);
        cout<<T;
        vector<vector<int>> ans;
        pair<vector<int>,bool> result;
        for (int i=0;i<m;i++){
            result=check(S,T);
            if(!result.second){
                cout<<"nie mozna.";
                break;
            }else{
                ans.push_back(result.first);
            }
        }



    }
    return 0;
}
