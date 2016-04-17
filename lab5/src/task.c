#include "server.h"
#include "client.h"

int main(int argc, char **argv)
{
    int delay = 1000;
    if (argc > 1)
    {
        int tmp = 0;
        if (sscanf(argv[1], "%d", &tmp))
        {
            delay = tmp;
        }
    }
    int res = launch_server(delay);

    if (res == 1)
    {
        int tmp = launch_client(delay);
        if (tmp)
        {
            printf("Client failure: %d\n", tmp);
        }
    }
    else if (res)
    {
        printf("Server failure: %d\n", res);
    }

    return 0;
}