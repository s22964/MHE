#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

void space(int number){ //tworzy podaną ilośc "miejsca" pomiędzy znakami
    for (int i=0;i<number;i++){
        std::cout<<" ";
    }
}

void display(int w,int h, std::string txt){ //tworzy i wyświetla tekst w ramce
    using namespace std;
    int lng=txt.length();
    for (int i=0;i<w;i++){ //górna linia
        cout<<"#";
    }
    cout<<endl;
    if(lng<=w-2){ //dla jednej linii tekstu
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
    else{ //dla wielu linii tekstu
        int linie=0;
        if(lng%(w-2)==0){ //dla podzielnej ilości znaków
            linie=lng/(w-2);}
        else{linie=lng/(w-2)+1;} //dla niepodzielnej ilości znaków
            h-=linie;
            for (int i=0;i<h/2-1;i++){ //górna przestrzeń
                cout<<"#";
                space(w-2);
                cout<<"#"<<endl;
            }
            int znaki=lng/linie;
            int reszta=lng%linie;
            if(lng%(w-2)==0) {              //dla podzielnej ilości znaków
                for (int i = 0; i < linie; i++) {
                    cout << "#";
                    for (int i = 0; i < znaki; i++) {
                        cout << txt[0];
                        txt.erase(0, 1);
                    }
                    cout << "#" << endl;
                }
            }else {                             //dla niepodzielnej ilości znaków
                int p = 0;
                for (int i = 0; i < linie; i++) {
                    if (linie - i == reszta) {
                        znaki += 1;
                    }
                    p = (w - 2 - znaki) / 2;
                    cout << "#";
                    space(p);
                    for (int j = 0; j < znaki; j++) {
                        cout << txt[0];
                        txt.erase(0, 1);
                    }
                    space(p);
                    if ((w - 2 - znaki) % 2 != 0) {
                        cout << " ";
                    }
                    cout << "#" << endl;
                }
            }
    }

    for (int i=0;i<h/2-1;i++){ //dolna przestrzeń
        cout<<"#";
        space(w-2);
        cout<<"#"<<endl;
    }
    for (int i=0;i<w;i++){ //dolna krawędź
        cout<<"#";
    }


}

int main(int argc, char ** argv) {
    json data;

    if (argc==2){
        std::string path=argv[1];
        std::ifstream f("../"+path);
        data=json::parse(f);
    }else{}
    display(data["w"],data["h"],data["text"]);



    return 0;
}
