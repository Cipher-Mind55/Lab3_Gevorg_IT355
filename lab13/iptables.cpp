#include <iostream>
#include <cstdlib>

using namespace std;

void block_port(int port) {
    char command[100];
    sprintf(command, "sudo iptables -A INPUT -p tcp --dport %d -j DROP", port);
    cout << "Executing: " << command << endl;
    system(command);
}

void unblock_port(int port) {
    char command[100];
    sprintf(command, "sudo iptables -D INPUT -p tcp --dport %d -j DROP", port);
    cout << "Executing: " << command << endl;
    system(command);
}

int main() {
    int port = 80;
    cout << "Blocking port " << port << "..." << endl;
    block_port(port);
    
    cout << "Unblocking port " << port << "..." << endl;
    unblock_port(port);
    
    return 0;
}
