// gcc -o basic_rop -fno-stack-protector -no-pie basic_rop.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handle()
{
    puts("TIME OUT");
    exit(-1);
}

void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    signal(SIGALRM, alarm_handle);
    alarm(30);
}

int main(int argc, char *argv[])
{
    init();
    
    printf("Attack Me :");
    char buf[0x30];

    read(0, buf, 0x100);
    write(1, buf, 0x100);

    printf("Again :");
    read(0, buf, 0x100);
    return 0;
}

