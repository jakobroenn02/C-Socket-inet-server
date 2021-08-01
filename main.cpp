#include <iostream>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>

#include <string>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>
using namespace std;

#define PORT 5000

int main(){
 


    //server
    struct sockaddr_in saddr = {
        /* data */
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT)
    };
    int option = 1;
    int serveraddrSize = sizeof(saddr);
    int socketServer = socket(AF_INET, SOCK_STREAM, 0); // SOCK_DGRAM FOR UDP ISTEDET FOR TCP
    setsockopt(socketServer,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
    if (socketServer == -1){
        std::cerr << "Forbindelse kunne ikke nåes. " << std::endl;
        return 1;

    }

    //client

    struct sockaddr_in caddr;
    socklen_t caddrSize = sizeof(caddr);
    int socketClient;


    //bind socket med ip og port
    bind(socketServer, (struct sockaddr*)&saddr, sizeof(saddr));

    //lytter
    listen(socketServer, SOMAXCONN);
    //PRINT
    std::stringstream ss;
    ss << PORT 
    

    
    


    return 0;
}