#include "client.h"

int file_desc;
char passbuf[PASSBUFSIZE + 1];

void print_password()
{
    printf("password: %s\n", passbuf);
}

int read_password()
{
    memset(passbuf, 0, PASSBUFSIZE);
    int cnt = read(file_desc, passbuf, PASSBUFSIZE);
    if (cnt == -1 && errno == EAGAIN)
    {
        printf("pipe was empty...\n");
        return 1;
    }
    if (passbuf[0] == EOF)
    {
        write(file_desc, passbuf, 2);
        return 2;
    }
    return 0;
}

void launch_auto(int refresh_delay)
{
    while(true)
    {
        int res = read_password();
        if (res == 2)
            break;
        if (!res)
            print_password();
        usleep(usleep_milliseconds(refresh_delay));
    }
}

void launch_manual()
{
    char buffer[1111];
    memset(buffer, 0, 1111);
    while (strcmp(buffer, "exit\n"))
    {
        int res = read_password();
        if (res == 2)
            break;
        if (!res)
            print_password();
        fgets(buffer, 1111, stdin);
    }
}

int launch_client(int refresh_delay)
{
    file_desc = open(NAMEDPIPE, O_RDWR | O_NONBLOCK);

    if (file_desc <= 0)
    {
        perror("can't open FIFO");
        return -1;
    }

    printf("starting client...\n");

    if (refresh_delay)
    {
        launch_auto(refresh_delay);
    }
    else
    {
        launch_manual();
    }

    close(file_desc);
    
    printf("client finished...\n");
    return 0;
}