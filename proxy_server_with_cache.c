#include "proxy_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


// struct (or structure) --> is a collection of variables (can be of different types) under a single name

#define MAX_CLIENT 10

typedef struct cache_element cache_element;

struct cache_element
{
    char* data;
    int element;
    char* url;
    time_t lru_time_track;
    cache_element* next;
};

// In LRU we'll use linked list and create a algo to find the element from that list
cache_element* find(char* url);
int add_cache_element(char* data, int element, char* url);
void remove_from_cache_element()

int port_number = 8080;
int proxy_socketId;
pthread_t tid[MAX_CLIENT];
sem_t semaphore;
pthread_mutex_t lock;

cache_element* HEAD;
int cache_size;

int main(int argc, char* argv[]){
    int client_SocketID , client_len;
    stuct sockaddr_in server_addr, clinet_addr;
    sem_init(&semaphore,0, MAX_CLIENT);
    pthread_mutex_init(&lock, NULL)

    if(argv == 2){
        port_number = atoi(argv[1]);
    }else{
        printf("Too few arguments.");
        exit(1);   //system call to exit program
    }
    printf("Strating proxy server at port: %d\n",port_number);

    proxy_socketId = socket(AF_INET, SOCK_STREAM, 0);
    if(proxy_socketId < 0){
        printf("Failed to create a socket\n");
        exit(1);
    }
    int reuse = 1;
    if(setsockopt(proxy_socketId, SOL_SOCKET, SO_REUSEADDR, (const char*) &reuse, sizeof(reuse))<0){
        perror("setSockOpt failed\n");
    }

    bzero((char*)&server_addr, sizeof(server_addr));  //clean the previous values
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;   //jis server se communicate krne wale ho uska address
    if(bind(proxy_socketId, (struct sockaddr*)&server_addr,sizeof(server_addr)<0)){
        perror("Port is not avaliable\n");
        exit(1);
    }
    printf("Binding on port %d\n",port_number);

    int listen_status = listen(proxy_socketId, MAX_CLIENT);  //apna server listen krega
    if(listen_status<0){
        perror('Error in listening')
        exit(1);
    }
}
 