#include "headers.h"

void fetchManPage(const char *command_name) {
    // Step 1: DNS resolution
    struct hostent *he;
    if ((he = gethostbyname("man.he.net")) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    // Step 2: Create a socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Define server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(server_addr.sin_zero), 0, 8);

    // Step 3: Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }

    // Step 4: Send HTTP GET request
    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);
    // snprintf(request, sizeof(request), "GET /%s.1.html HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);
    if (send(sockfd, request, strlen(request), 0) == -1) {
        perror("send");
        exit(1);
    }

    // Step 5: Receive and parse the response
    char response[1000000];
    int bytes_received;
    int flag_to_print=0;
    int inside_body=0;
    if((bytes_received = recv(sockfd, response, sizeof(response), 0)) > 0) {
        response[bytes_received] = '\0';  // Null-terminate the response

        char* dup1 = strdup(response);

        char * part1 = strstr(dup1,"NAME");
        part1 +=4;
        part1 = strstr(part1,"NAME");

        *(strstr(part1,"AUTHOR"))=0;

        printf("%s",part1);






        // printf("%s",response);





        

        
        


        // if (part_name && part_end) {
        //     size_t part_name_length = part_end - part_name;
        //     char* part_name_copy = strndup(part_name, part_name_length);
        //     if (part_name_copy) {
        //         printf("%s", part_name_copy);
        //         free(part_name_copy);
        //     }  // Don't forget to free the allocated memory
         
   



        

        // if (strstr(response, "NAME") != NULL) {
        //     inside_body = 1;
        // }


        // if (strstr(response, "SYNOPSIS") != NULL) {
        //     inside_body = 1;
        // }

        // if(strstr(response,"DESCRIPTION")!=NULL){
        //     inside_body=1;
        // }

        // if(inside_body>0 && response[0]=='\n'){
        //     inside_body=0;
        // }
    
        // if (inside_body>0) {
        //     // Concatenate the line to the body content
        //     printf("%s\n",response);
        // }

        // Check if the line contains the </body> tag
        // printf("%s\n",response);
        
    }
    // Step 6: Close the socket
    close(sockfd);
}

void iman_main(char* command_to_fetch){
    fetchManPage(command_to_fetch);
}