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
    ss << PORT;
    std::cout <<  "[SERVER] Lytter på PORT" << ss.str() << std::endl;


    char buff[4096];
    int sizeBytesOfRecivedData;

    //whileloop
    while (true)
    {
        /* code */
        socketClient = accept(socketServer,(struct sockaddr*)&caddr, (socklen_t*)&caddrSize);
        std::cout << "[SERVER] Forbindelse oprettet" << std::endl;


        char hostClient[NI_MAXHOST];
        char portClient[NI_MAXSERV];
        memset(hostClient, 0, NI_MAXHOST);
        memset(portClient,0,NI_MAXSERV);
        if (getnameinfo((sockaddr*)&caddr,sizeof(caddr), hostClient, NI_MAXHOST,portClient,NI_MAXSERV,0) == 0){

            std::cout << "--> IP:  " << hostClient << "--> PORT: " << portClient << std::endl;
        }
        else{
            inet_ntop(AF_INET, &caddr.sin_addr,hostClient, NI_MAXHOST);
            std::cout << "--> IP: " << hostClient << "--> " << ntohs(caddr.sin_port) << std::endl;
        
        }
        //modtag data
        sizeBytesOfRecivedData = recv(socketClient,buff, 4096,0 );
        if(sizeBytesOfRecivedData == -1){
            std::cerr << "Error" << endl;
            break;
        }
        else if(sizeBytesOfRecivedData == 0) {
            std::cout << "Client disconnected" << std::endl;
            break;

        }

        send(socketClient, buff, sizeBytesOfRecivedData + 1, 0);
        std::cout << std::string(buff,0, sizeBytesOfRecivedData) << std::endl;
        close(socketClient);
    }

    return 0;
}