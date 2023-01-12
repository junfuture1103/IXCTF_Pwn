// gcc -o wallet wallet.c -fno-stack-protector -no-pie
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int money = 300;
int count = 10;

void alarm_handle()
{
    puts("TIME OUT");
    exit(-1);
}

void show_money()
{
    printf("Your money : %d\n", money);
}

void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    signal(SIGALRM, alarm_handle);
    alarm(30);
}

void show_item()
{
    printf("1. I-PAD\n");
    printf("2. Laptap\n");
    printf("3. Book\n");

    return;
}

void work()
{
    srand(time(NULL));
    int Payment = 12500;
    printf("======== work ========\n");
    printf("Work hard...\n");
    printf("Your Payment : %d\n", Payment);
    money += Payment;
    count--;
    return;
}

void buy()
{
    int item_choose;
    printf("======== buy ========\n");
    show_item();
    printf("Choost Your Item :");
    scanf("%d", &item_choose);
    if (money < item_choose * 1000000)
    {
        printf("Not enough Money!\n");
    }
    else
    {
        printf("Good. Have a Good Day!\n");
        money -= item_choose * 1000000;
    }
    count--;
    return;
}

void show_menu()
{
    printf("You can Trade %d more\n", count);
    printf("1. buy\n");
    printf("2. work\n");
    printf("3. show\n");
    printf("4. lend\n");
    printf("> ");
    return;
}

void lend()
{
    int percentage;
    int count_down;

    printf("======== lend money ========\n");
    printf("Input Percentage: ");
    scanf("%d", &percentage);
    if (0 <= percentage && percentage <= 100)
    {
        money *= percentage;
    }
    else
    {
        printf("You Can't");
    }
    printf("lend finish\n");
    printf("your money : %d\n", money);

    count_down = percentage / 10;
    count -= count_down;

    return;
}

void call_func(int idx)
{
    switch (idx)
    {
    case 1:
        buy();
        break;
    case 2:
        work();
        break;
    case 3:
        show_money();
        break;
    case 4:
        lend();
        break;
    default:
        printf("Error Code");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    init();

    int idx;

    printf("Welcome to IXC Wallet!!\n");
    while (count > 0)
    {
        show_menu();
        scanf("%d", &idx);
        call_func(idx);

        if (money < 0)
        {
            char name[0x28];

            printf("Oh, You Don't Have Money\n");
            printf("Don't run!! What's Youre name?");

            read(0, name, 0x100);
            printf("%s", name);

            printf("Tell Me One More. What?");
            read(0, name, 0x100);

            printf("See You.. I will wait you.\n");
            money = 0;
        }
    }

    printf("Finish Your Trade\n");

    return 0;
}
