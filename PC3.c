// Using Semaphore //

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define n 10
int buffer[n];
int full = 0;  //Semaphore to set full buffer slot to 0
int empty = n; //Semaphore to set empty buffer slot to full
int mutex = 1; //Semaphore for controlling Critical section
int count = 0;
static int p = 1;
static int in = 0;
static int out = 0;
void producer();
void consumer();
int wait(int);   //Down()
int signal(int); //Up()

int main()
{
    int ch;
    printf("1)Producer \n2)Consumer \n3)Exit \n");
    while (1)
    {
        printf("Enter your choice: \n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            if ((mutex == 1) && (empty != 0))
            {
                producer();
            }

            else
            {
                printf("[-] Buffer is full. \n");
            }

            break;
        case 2:
            if ((mutex == 1) && (full != 0))
            {
                consumer();
            }

            else
            {
                printf("[-] Buffer is empty. \n");
            }

            break;

        case 3:
            exit(0);
            break;
        }
    }
    return 0;
}
int wait(int x)
{
    if (x == 0)
    {
        printf("[-] Can not add an item to a buffer. \n");
        exit(1);
    }
    else
    {
        return --x;
    }
}
int signal(int x)
{
    return ++x;
}
void producer()
{
    empty = wait(empty);
    mutex = wait(mutex);
    printf("Producer produces an item %d. \n", p);
    buffer[in] = p;
    printf("[+] Item %d is stored in the buffer successfully. \n", p);
    in = (in + 1) % n;
    count++;
    p++;
    mutex = signal(mutex);
    full = signal(full);
}
void consumer()
{
    int q;
    printf("Number of items to be processed by the consumer: %d. \n", count);
    full = wait(full);
    mutex = wait(mutex);
    q = buffer[out];
    out = (out + 1) % n;
    count = count - 1;
    mutex = signal(mutex);
    empty = signal(empty);
    printf("[-] Item %d is processed successfully. \n", q);
}
