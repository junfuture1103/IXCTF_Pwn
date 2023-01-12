#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler()
{
    puts("TIME OUT");
    exit(-1);
}

void initialize()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    signal(SIGALRM, alarm_handler);
    alarm(60);
}

int main()
{
    int num = 0;

    printf("If you enter 1, you can get flag : ");
    scanf("%d", &num);

    if (num == 1)
    {
        printf("\nHello! Flag is IxCTF{Hello_ISANG_CAUTION!@!}\n");
    }
    else
    {
        printf("\nHhm.. That's Wrong...\n");
    }
    return 0;
}