#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

char webpage[] = "HTTP/1.1 200 OK\r\n"
                "Server:Linux Web Server\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                "<!DOCTYPE html>\r\n"
                "<html><head><title> My Web Page </title>\r\n"
                "<style>body {background-color: #FFFF00 }</style></head>\r\n"
                "<body><center><h1>Hello world!!</h1><br>\r\n"
                "<img src=\"yosigo.jpg\"></center></body></html>\r\n";

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
    int fdimg, img_size;
    int option = TRUE;
    char buf[BUF_SIZE]
    char img_buf[70000000];

	struct sockaddr_in serv_adr, clnt_adr;
    socklen_t sin_len = sizeof(clnt_adr);

	if(argc!=2){
			printf("Usage : %s <port>\n", argv[0]);
			exit(1);
	}

	serv_sock=socket(PF_INET, SOCK_STREAM,0);
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

	if(serv_sock==-1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr= INADDR_ANY;
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	while(1){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &sin_len);
        puts("New client connection...");
        read(clnt_sock, buf, 2047);
        printf("%s\n", buf);

        if(strstr(buf, "GET /yosigo.jpg") != NULL){
            fdimg = open("yosigo.jpg", O_RDONLY);
            if((img_size = read(fdimg, img_buf, sizeof(img_buf))) == -1)
                puts("file read error!");
            close(fdimg);

            sprintf(buf, "HTTP/1.1 200 OK\r\n"
                         "Server: Linux Web Server\r\n"
                         "Content-Type: image/jpeg\r\n"
                         "Content-Legth: %ld\r\n\r\n", img_size);
            if(write(clnt_sock, buf, strlen(buf)) < 0)
                puts("file write error!!");
            if(write(clnt_sock, img_buf, img_size) < 0)
                puts("file write error!!");

            close(clnt_sock);
        }
        else{
            if(write(clnt_sock, webpage, sizeof(webpage)) == -1)
                puts("file write error!");
            puts("closing...");
            close(clnt_sock);
        }
        close(serv_sock);
        return 0;
    }
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
