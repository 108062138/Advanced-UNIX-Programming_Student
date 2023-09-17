#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
    int fd = open("sample.txt", O_RDWR);
    if(fd == -1){
        printf("Error opening file\n");
        exit(1);
    }
    //utilize lseek to change the file offset
    off_t offset = lseek(fd, 14, SEEK_SET);
    if(offset == -1){
        printf("Error changing file offset to 14\n");
        exit(1);
    }
    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, strlen("student.")*sizeof(char));
    if(bytes_read == -1){
        printf("Error reading file\n");
        exit(1);
    }else{
        printf("%s\n", buffer);
    }
    offset = lseek(fd, 14, SEEK_SET);
    ssize_t bytes_written = write(fd, "NTHU student.", strlen("NTHU student.")*sizeof(char));
    if(bytes_written == -1){
        printf("Error writing file\n");
        exit(1);
    }
    offset = lseek(fd, 0, SEEK_SET);
    if(offset == -1){
        printf("Error changing file offset to 0\n");
        exit(1);
    }
    char read_line[100], ch;
    while((bytes_read = read(fd, &ch, sizeof(char))) > 0){
        if(ch == '\n'){
            break;
        }
        strncat(read_line, &ch, 1);
    }
    printf("%s\n", read_line);
    return 0;
}