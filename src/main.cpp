#include <iostream>
#include "../Incude/Session.h"
#include <json.h>
#include <fstream>
using namespace std;


void pipi(const std::string &configFilePath) {
    using json = nlohmann::json;
    std::ifstream i(configFilePath);

    std::string text = "{ \"first\": \"James\", \"last\": \"Bond\", \"nums\": [0, 0, 7] }";
    std::ofstream outFile;
}

int main(int argc, char** argv){

    cout << "here:" << endl;



    if(argc!=2)
    {
        cout << "usage splflix input_file" << endl;
        return 0;
    }
 /*   Session s(argv[1]);
    s.start();*/








    return 0;
}
