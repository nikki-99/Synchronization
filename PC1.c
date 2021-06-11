#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define n 10
int buffer[n];
int count = 0;
void producer();
void consumer();

int main()
{
    printf("Buffer size is: %d \n", n);
    while (count < n)
    {
        producer();
    }
    while (count > 0)
    {
        consumer();
    }
    return 0;
}

void producer()
{
    static int p = 1;
    int in = 0;
    while (1)
    {
        while (count == n)
        {
            printf("%d items are placed in the buffer \n", count);
            // printf("Producer: Busy waiting. \n");
            printf("Buffer is full, callng Consumer\n");
            sleep(5);
            consumer();
        }
        buffer[in] = p;
        printf("[+] Item %d is produced and stored in the buffer successfully.\n", p);
        in = (in + 1) % n;
        count = count + 1;
        p++;
    }
}
void consumer()
{
    static int q = 1;
    int out = 0;
    printf("Number of Item to be processed by the consumer: %d. \n", count);
    while (1)
    {
        while (count == 0)
        {
            // printf("Consumer: Busy waiting.\n");
            printf("Buffer is empty, calling Producer.\n");
            sleep(5);
            producer();
        }
        q = buffer[out];
        out = (out + 1) % n;
        count--;
        printf("[-] Item %d is processed successfully. \n", q);
    }
}