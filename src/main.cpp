#include <iostream>
#include "../Include/Session.h"

using namespace std;

int main(int argc, char** argv){
    if(argc!=2)
    {
        cout << "usage splflix input_file" << endl;
        return 0;
    }
    Session s(argv[1]);
    s.start();

//    while (true) {
//        cout<<"Enter an action : ";
//        cin>>actionff;
//
//        break;
//    }

    return 0;
}
