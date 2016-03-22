#include "daemon_process.h"

#define MAX_GENERATION 10

//int delay_fork, delay_finish;
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

void start_daemon(int generation)
{
    pid_t pid, sid;

    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    openlog(IDENTITY, LOG_NOWAIT | LOG_PID, LOG_USER);

    if (pid > 0)
    {
        //usleep(usleep_milliseconds(delay_finish));

        syslog(LOG_INFO, "pid = %u, generation =  %d", getpid(), generation);
        //syslog(LOG_INFO, "Daemon %u finished\n", getpid());
        closelog();

        exit(EXIT_SUCCESS);
    }

    umask(0);

    //syslog(LOG_INFO, "Daemon %u started\n", getpid());

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

    //usleep(usleep_milliseconds(delay_fork));
    load_config(CONFIG_LOCATION);
    if (delay > 0)
    {
        usleep(usleep_milliseconds(delay));
    }
    else
    {
        return;
    }
    start_daemon(generation + 1);
}

int main(int argc, char **argv)
{
    load_config(CONFIG_FILE);
    save_config(CONFIG_LOCATION);

    start_daemon(0);

    return 0;
}