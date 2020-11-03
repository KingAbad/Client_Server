#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[255];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     while(1)
     {
           bzero(buffer,256);
           n = read(newsockfd,buffer,255);
           if (n < 0) error("ERROR reading from socket");
           printf("Client: %s",buffer);
           printf("server: ");
          bzero(buffer,256);
          fgets(buffer,255,stdin);
          n = write(newsockfd,buffer,strlen(buffer));
           if (n < 0) error("ERROR writing to socket");
           int i=strncmp("Bye, i love you 2" , buffer, 3);
           if(i == 0)
               break;
     }
     // Log to XML File
void doLogging(char message[]){
	FILE *fp;
	time_t current_time;
	char *c_time_string;

	// Open file
	fp = fopen("/var/www/html/index.xml", "rw+");
	//printf("</inbox>"); 
	// Get Time
	current_time = time(NULL);
	c_time_string = ctime(&current_time);

	if(current_time == ((time_t) - 1)){
		fprintf(stderr, "Failure to obtain the current time.\n");
	}
	else if(c_time_string == NULL){
		fprintf(stderr, "Failure to convert the current time.\n");
	}
	
	// Delete newline
	//c_time_string[strcspn(c_time_string, "\n")] = 0;
	
	// Move cursor
	//fseek(fp, -8, SEEK_END);
	
	// Write XML data
	fprintf(fp, "\t<mail>\n");									//<mail>
	//fprintf(fp, "\t\t<from>%s</from>\n", hostname);				//<from> SENDER </from>
	fprintf(fp, "\t\t<message>%s</message>\n", message);		//<message> STRING </message>
	fprintf(fp, "\t</mail>\n");									//</mail>
	//fprintf(fp, "</inbox>");									//</inbox>

	printf("XML data logged !\n");
	
	fclose(fp);

	return;
}
     
     close(newsockfd);
     close(sockfd);
     return 0; 
}
