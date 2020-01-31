/***** args_parser.h *****
* Author : flekystyley
* Date   : 31.1.2019
* Brief  : parsing command line arguments for slowC
**************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "args_parser.h"

void init_args(Arguments *args)
{
    args->help = false;
    args->content_length = 1000*1000;
    args->dial_worker_count = 10;
    args->ramp_up_interval = 10;
    args->sleep_interval = 10*10;
    args->test_duration = 0;
    args->victim_url = "127.0.0.1";
    args->host_header = NULL;
}

void print_usage(const char *program)
{
    printf("Usage: %s -c contentLength [-d dialWorkerCount]\n", program);
}

void print_help(const char *program)
{
    print_usage(program);
    printf(
    "Available options:\n"
    " -c - contentLength.\n"
    " -d - dialWorkerCount.\n"
    " -r - rampUpInterval.\n"
    " -s - sleepInterval.\n"
    " -t - testDuration.\n"
    " -v - victimURL.\n"
    " -h - hostHeader.\n"
    );
}

void parse(int argc, char const **argv, Arguments *args)
{
    int opt;
    while ((opt = getopt(argc, (char *const)*argv, "h:c:d:g:r:s:t:v:h")) != -1) {
        switch (opt) {
        case 'h':
            args->help = true;
            break;
        case 'c':
            args->content_length = atoi(optarg);
            break;
        case 'd':
            args->dial_worker_count = atoi(optarg);
            break;
        case 'r':
            args->ramp_up_interval = atoi(optarg);
            break;
        case 's':
            args->sleep_interval = atoi(optarg);
        case 't':
            args->test_duration = atoi(optarg);
        case 'v':
            args->victim_url = optarg;
        case 'h':
            args->host_header = optarg;
            break;
        default:
            fprintf(stderr, "ERROR: Unknown arguments passed\n");
            print_usage(argv[0]);
            break;
        }
    }
}