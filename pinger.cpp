//запуститься тільки на MacOS

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <thread>
#include <chrono>
using namespace std;

class ping{
    int count = 0;
    char command[100];
public:

    ping(const char *ins){
        snprintf(command, sizeof(command),"ping -c16 -s1 %s", ins);
    }
    
void pinger(){
        while(true){
            FILE * pingFile;
            pingFile = popen(command, "r");
            if(!pingFile){
                cerr<<"Error opening file"<<endl;
                return;
            }
            char buffer[256];
            bool succ=false;
            while(fgets(buffer, sizeof(buffer), pingFile) != nullptr){
                cout<<buffer;
                if(strstr (buffer, "bytes from") != nullptr){
                    succ=true;
                }
                
            }
            pclose(pingFile);
            
            if(succ){
                cout<<"Success";
                count=0;
            }
            else{
                cout<<"Failed";
                count++;
            }
            
            this_thread::sleep_for(chrono::seconds(1));
            
            if (count >= 5) {
                cout << "Bad connection. 5 failed attempts." << endl;}
        }
    }
    
};
int main() {
    cout<<"url/ip: "<<endl;
    char ins[100];
    cin.getline(ins, 100);
    
    ping data(ins);
    data.pinger();
    return 0;
}
