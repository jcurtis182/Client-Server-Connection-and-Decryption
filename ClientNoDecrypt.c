
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>




int main(int argc, char** argv){

    if(argc != 3){
        printf("[*]USAGE: %s <ipaddr> <port> \n",argv[0]);
        return 0;
    }


    printf("[*]Starting...\n");
    int port = atoi(argv[2]); //We get the port as text, so convert it to an integer with atoi (ascii to integer)
    int sock, addrlen, opt;

    struct sockaddr_in server; //make our scokaddr struct
    sock = socket(AF_INET,SOCK_STREAM,0);//AF_Inet - addresses are in ipv4 format | SOCK_STREAM -> connected, Stream based (TCP) | 0 corresponds to the IP protocol (see man socket)
    server.sin_family = AF_INET; //server's address will be in ipv4
    server.sin_port = htons(port); // convert local machine port representation (little endian most likely) to network representation (Big endian)

    //Next we convert our text based ipv4 address into one that the struct needs (binary)
    if(inet_pton(AF_INET,argv[1],&server.sin_addr) <=0){
        printf("[!]Error processing IP address\n");
        return 1;
    }
    //Connect to server
    if(connect(sock,(struct sockaddr *) &server, sizeof(server))){
        printf("[!]Connection to file server failed\n");
        return 1;
    }

  

    
    char buf[1024];
    printf("[*]Waiting for server response...\n");
    int readCount;
    printf("[*]Begin Message!\n");                  //Opening Msg
    do{
        readCount = recv(sock,buf, 32, 0);
        buf[readCount +1] = '\0';
        
        printf("%s",buf);
    } while(readCount == 32);
    printf("<---------END--------->\n");

    
    printf("[*]Enter a message to send to the server:\n");      //1st Response
    fgets(buf,1024,stdin);
    int len = strlen(buf);
    int sentC;
 
    //send data to server
    //return value from send is how many bytes actually sent
    if((sentC = send(sock,buf,len,0)) < len){
        printf("[!]Message not fully sent!\n");
    }
    printf("[*]Message sent! Sent %d bytes!\n",sentC);
    
    printf("[*]Waiting for server response...\n");  
    printf("[*]Begin Message!\n");                  //1st Reply
    do{
        readCount = recv(sock,buf, 32, 0);
        buf[readCount +1] = '\0';
        
        printf("%s",buf);
    } while(readCount == 32);
    printf("<---------END--------->\n");

    printf("[*]Enter a message to send to the server:\n");      //2nd Response
    fgets(buf,1024,stdin);
    len = strlen(buf);
    
    
    //send data to server
    //return value from send is how many bytes actually sent
    if((sentC = send(sock,buf,len,0)) < len){
        printf("[!]Message not fully sent!\n");
    }
    printf("[*]Message sent! Sent %d bytes!\n",sentC);
    
    printf("[*]Waiting for server response...\n");
    printf("[*]Begin Message!\n");                      //2nd Reply
    do{
        readCount = recv(sock,buf, 32, 0);
        buf[readCount +1] = '\0';
        
        printf("%s",buf);
    } while(readCount == 32);
    printf("<---------END--------->\n");



    printf("[*]Enter a message to send to the server:\n");      //3nd Response
    fgets(buf,1024,stdin);
    len = strlen(buf);
    
    
    //send data to server
    //return value from send is how many bytes actually sent
    if((sentC = send(sock,buf,len,0)) < len){
        printf("[!]Message not fully sent!\n");
    }
    printf("[*]Message sent! Sent %d bytes!\n",sentC);
    
    printf("[*]Waiting for server response...\n");
    printf("[*]Begin Message!\n");                      //3nd Reply
    do{
        readCount = recv(sock,buf, 32, 0);
        buf[readCount +1] = '\0';
        
        printf("%s",buf);
    } while(readCount == 32);
    printf("<---------END--------->\n");
    close(sock);
    }
    

    
    



void XORBuf(char* buf, int readCount){
    char key[] = "roux";
    for(int i=0; i < readCount; i++){
        buf[i] = buf[i] ^ key[i%4];
    }
}