#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

void space(int number){
    for (int i=0;i<number;i++){
        std::cout<<" ";
    }
}

void display(int w,int h, std::string txt){
    using namespace std;
    int lng=txt.length();

    for (int i=0;i<w;i++){
        cout<<"#";
    }
    cout<<endl;
    if(lng<=w-2){
        for (int i=0;i<h/2-1;i++){
            cout<<"#";
            space(w-2);
            cout<<"#"<<endl;
        }
        int p=(w-2-lng)/2;
        cout<<"#";
        space(p);
        cout<<txt;
        space(p);
        cout<<"#"<<endl;
    }
    else{
        int linie=0;
        if(lng%(w-2)==0){
            linie=lng/(w-2);}
        else{linie=lng/(w-2)+1;}
            h-=linie;
            for (int i=0;i<h/2-1;i++){
                cout<<"#";
                space(w-2);
                cout<<"#"<<endl;
            }
            int znaki=lng/linie;
            int reszta=lng%linie;
            if(lng%(w-2)==0) {
                for (int i = 0; i < linie; i++) {
                    cout << "#";
                    for (int i = 0; i < znaki; i++) {
                        cout << txt[0];
                        txt.erase(0, 1);
                    }
                    cout << "#" << endl;
                }
            }else{
                int p=0;
                for (int i=0;i<linie;i++){
                    if(i+1>=linie){
                        znaki+=reszta;
                    }
                    p=(w-2-znaki)/2;
                    cout<<"#";
                    space(p);
                    for (int j = 0; j < znaki; j++) {
                        cout << txt[0];
                        txt.erase(0, 1);
                    }
                    cout << "#" << endl;
                }
            }


    }

    for (int i=0;i<h/2-1;i++){
        cout<<"#";
        space(w-2);
        cout<<"#"<<endl;
    }
    for (int i=0;i<w;i++){
        cout<<"#";
    }


}

int main() {

    std::ifstream f("../config.json");
    json data = json::parse(f);
    display(data["w"],data["h"],data["text"]);


    return 0;
}
