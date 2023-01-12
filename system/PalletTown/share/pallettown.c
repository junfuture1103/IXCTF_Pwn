// gcc -o pallettown -fno-stack-protector -no-pie pallettown.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int my_type = 0;
int rival_type = 0;
int win_count = 0;

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

int fight_rival(int my_type, int rival_type)
{
    int win = 0;
    switch (rival_type)
    {
    case 0:
        if (my_type == 3)
        {
            win = 1;
        }
        break;
    case 1:
        if (my_type == 1)
        {
            win = 1;
        }
        break;
    case 2:
        if (my_type == 2)
        {
            win = 1;
        }
        break;
    default:
        printf("error");
        exit(1);
    }

    return win;
}

void print_rival()
{
    srand(time(NULL));
    rival_type = rand() % 3;

    if (rival_type == 0)
    {
        printf("Your Rival PoketMon is Pyree!!\n");
    }
    else if (rival_type == 1)
    {
        printf("Your Rival PoketMon is Bulbasaur\n");
    }
    else if (rival_type == 2)
    {
        printf("Your Rival PoketMon is Squirtle\n");
    }
    return;
}

void print_my_type()
{
    printf("1. Pyree\n");
    printf("2. Bulbasaur\n");
    printf("3. Squirtle\n");
    printf("Hi Trainier! Choose Your PoketMon! : ");
    return;
}

void regend()
{
    printf("....Welcome to PalletTown\n");
    printf("You Are Regend.");
    execve("/bin/sh", NULL, NULL);
    return;
}

int main(int argc, char *argv[])
{
    init();

    char poketname[0x30];

    if (win_count >= 1)
    {
        regend();
    }

    printf("Welcome to PalletTown!!\n");
    print_rival();
    print_my_type();
    scanf("%d", &my_type);

    if (fight_rival(my_type, rival_type))
    {
        win_count++;
        printf("OK, Let's Go to Your Advantager!\n");
        printf("What is Your PocketMon Name?");
        scanf("%s", poketname);
    }
    else
    {
        printf("Uhm.. You have to training more...");
    }

    return 0;
}
