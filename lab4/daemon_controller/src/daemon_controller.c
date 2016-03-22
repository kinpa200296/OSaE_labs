#include "daemon_controller.h"

int delay;

void save_config(const char *filename)
{
    FILE *f;

    f = fopen(filename, "w");

    if (f)
    {
        //fprintf(f, "%d %d", delay_fork, delay_finish);
        fprintf(f, "%d", delay);
        fclose(f);
    }
}

void load_config(const char *filename)
{
    FILE *f;
    char buffer[20];

    f = fopen(filename, "r");

    if (f)
    {
        fgets(buffer, 20, f);
        //sscanf(buffer, "%d %d", &delay_fork, &delay_finish);
        sscanf(buffer, "%d", &delay);
        fclose(f);
    }
}

void handle_signal(int sig_num)
{
    load_config(CONFIG_LOCATION);
    switch(sig_num)
    {
        case SIGUSR1:
            delay *= DELAY_MULTIPLIER;
            break;
        case SIGUSR2:
            delay /= DELAY_MULTIPLIER;
            break;
    }
    if (delay <= MIN_DELAY)
        delay = 0;
    save_config(CONFIG_LOCATION);
    syslog(LOG_INFO, "Delay changed to %d ms\n", delay);
}

void process_signals()
{
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while(delay > MIN_DELAY)
    {
        int i = 0;
        i++;
    }
}

void start_daemon(int generation)
{
    pid_t pid, sid;

    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {     
        exit(EXIT_SUCCESS);
    }

    umask(0);

    openlog(IDENTITY, LOG_NOWAIT | LOG_PID, LOG_USER);

    syslog(LOG_INFO, "Controller started\n");

    sid = setsid();

    if (sid < 0)
    {
        syslog(LOG_ERR, "Could not create process group\n");
        exit(EXIT_FAILURE);
    }

    if (chdir("/") < 0)
    {
        syslog(LOG_ERR, "Could not change working dorectory to /\n");
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    process_signals();

    syslog(LOG_INFO, "Controller finished\n");

    closelog();
}

int main(int argc, char **argv)
{
    load_config(CONFIG_FILE);
    save_config(CONFIG_LOCATION);

    start_daemon(0);

    return 0;
}