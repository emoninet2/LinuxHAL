/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>

void GPIO_export (int pin){
    int fd;
    char buf[255];
    fd = open("/sys/class/gpio/export", O_WRONLY);
    sprintf(buf, "%d", pin); 
    write(fd, buf, strlen(buf));
    close(fd);
}
void GPIO_unexport (int pin){
    int fd;
    char buf[255];
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    sprintf(buf, "%d", pin); 
    write(fd, buf, strlen(buf));
    close(fd);
}
void GPIO_direction(int pin, int dir){
    int fd;
    char buf[255];
    sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(buf, O_WRONLY);

    if (dir)
    {
        write(fd, "out", 3);
    }
    else
    {
        write(fd, "in", 2);
    }
    close(fd);
}
void GPIO_write(int pin, int val){
    int fd;
    char buf[255];
    sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(buf, O_WRONLY);
    sprintf(buf, "%d", val);
    write(fd, buf, 1);
    
    close(fd);
}
int GPIO_read(int pin){
    int fd;
    char buf[255];
    sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(buf, O_RDONLY);
    int n = read (fd,buf,1);
    return strtol(buf, NULL, 16);
}