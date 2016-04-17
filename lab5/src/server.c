#include "server.h"

char passbuf[PASSBUFSIZE + 1];
int timeout;

void generate_password()
{
    for (int i = 0; i < PASSBUFSIZE; i++)
    {
        passbuf[i] = (char)(40 + rand()%86);
    }
    printf("generated password: %s\n", passbuf);
}

int launch_server(int password_timeout)
{
    int file_desc;

    if (password_timeout < 0)
    {
        file_desc = open(NAMEDPIPE, O_RDWR);

        if (file_desc <= 0)
        {
            perror("can't open FIFO");
            return -1;
        }

        printf("Initiating client shutdown...\n");

        memset(passbuf, 0, PASSBUFSIZE);
        passbuf[0] = EOF;
        write(file_desc, passbuf, 2);

        char buffer[1111];
        printf("Press Enter when all clients will stop...\n");
        fgets(buffer, 1111, stdin);

        printf("deleting FIFO...\n");

        close(file_desc);
        remove(NAMEDPIPE);

        printf("Done...\n");
        return 0;
    }

    int res = mkfifo(NAMEDPIPE, 0777);

    if (errno == EEXIST)
    {
        return 1;
    }
    else if (res)
    {
        printf("%d %d\n", res, EEXIST);
        perror("can't create FIFO");
        return -1;
    }

    file_desc = open(NAMEDPIPE, O_RDWR | O_NONBLOCK);

    if (file_desc <= 0)
    {
        perror("can't open FIFO");
        return -1;
    }

    printf("starting server...\n");

    srand((unsigned int)clock());
    int timeout = 0;
    int refresh = 0;

    while(true)
    {
        if (clock() > refresh)
        {
            memset(passbuf, 0, PASSBUFSIZE);
            int cnt = read(file_desc, passbuf, PASSBUFSIZE);
            if (cnt == -1 && errno == EAGAIN)
            {
                generate_password();
                timeout = clock() + password_timeout*CLOCKS_PER_SEC/1000;
            }
            else if (clock() > timeout)
            {
                printf("changing password due to timeout...\n");
                generate_password();
                timeout = clock() + password_timeout*CLOCKS_PER_SEC/1000;
            }
            write(file_desc, passbuf, PASSBUFSIZE);
            refresh = clock() + REFRESH_RATE*CLOCKS_PER_SEC/1000;
        }
    }

    return 0;
}