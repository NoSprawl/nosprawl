// EXAMPLE: nosprawl-tcp --start -l 64.192.56.401/80 -r 192.168.1.98/80

#include <unistd.h>
#include <getopt.h>
#include <stdio.h>

static const char    option_str[]   = "l:r:udh";
static struct option long_options[] = {
    {"local", 1, 0, 'l'},
    {"remote", 1, 0, 'r'},
    {"start", 0, 0, 'u'},
    {"stop", 0, 0, 'd'},
    {"help", 0, 0, 'h'},
    {0, 0, 0, 0}
};

typedef enum {
    cmd_unknown = -1,
    cmd_activate,
    cmd_deactivate
} cmd_e;

static void usage(const char *pr)
{
    printf("usage: %s [options]\n", pr);
    printf("\tthis tool activates and deactivates the NoS kernel modules so that we can turn on and off the flow of data to userspace applications.\n");
    printf("-h|--help shows this help message\n");
    printf("-u|--start activates the kernel module\n");
    printf("-d|--stop deactivates the kernel module\n");
    printf("-l|--local the local ip/port to listen for incoming traffic on, for example 64.192.56.401/80\n");
    printf("-r|--remote the ip/port that the cloned service is listening on, for example 64.192.56.401/80\n");
    printf("\n");
}

int main(int argc, char *argv[])
{
    int option_index = 0, c = 0;
    cmd_e cmd = cmd_unknown;
    char local_ip_port[64];
    char remote_ip_port[64];
    local_ip_port[0] = 0;
    remote_ip_port[0] = 0;

    if(1 == argc) {
        usage(argv[0]);
        return 1;
    }

    while ((c = getopt_long(argc, argv, option_str, long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                usage(argv[0]);
                return 0;
                break;
            case 'u':
                cmd = cmd_activate;
                break;
            case 'd':
                cmd = cmd_deactivate;
                break;
            case 'l':
                snprintf(local_ip_port, sizeof(local_ip_port), "%s", optarg);
                break;
            case 'r':
                snprintf(remote_ip_port, sizeof(remote_ip_port), "%s", optarg);

                break;
            default:
                printf("Unknown argument '%c'\n", c);
                usage(argv[0]);
                return 1;
        }
    }

    if(cmd_activate == cmd) {
        // load the module and redirect the net flow
    }
    else if(cmd_deactivate == cmd) {
        // deactivate redirection
    }
    else {
        printf("either --start or --stop option has to be specified\n");
        return 1;
    }

    return 0;
}

