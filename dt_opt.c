#include <stdio.h>
#include <time.h>
#include <getopt.h>
#include <string.h>


/* **** HELP ****
 *
 * -h, --help
 *      Display help
 *
 * -H, --hour s|l
 *      Hour
 *          s - 12 hour clock
 *          l - 24 hour clock
 *
 * -m, --minute
 *      Minute
 *
 * -s, --second
 *      Second
 *
 * -d, --day
 *      Day in month
 *
 * -w, --wday s|l|n
 *      Weekday
 *          s - abbrevaited name
 *          l - full name
 *          n - as number ([1, 7], monday is 1)
 *
 * -M, --month s|l|n
 *      Month
 *          s - abbreviated name
 *          l - full name
 *          n - as number
 *
 * -y, --year s|l
 *      Year
 *          s - two last digits of year
 *          l - full number
**/


void showHelp();


int main(int argc, char *argv[]){
    int opt = 0;
    const char *shortopt = "hH:msdw:M:y:";
    const struct option longopt[] = {
        {"help", no_argument, 0, 'h'},
        {"hour", required_argument, 0, 'H'},
        {"minute", no_argument, 0, 'm'},
        {"second", no_argument, 0, 's'},
        {"day", no_argument, 0, 'd'},
        {"wday", required_argument, 0, 'w'},
        {"month", required_argument, 0, 'M'},
        {"year", required_argument, 0, 'y'},
        {0, 0, 0, 0}
    };

    char fbuf[30];
    while ((opt = getopt_long(argc, argv, shortopt, longopt, 0)) != -1){
        switch (opt){
        case 'H':
            if (*optarg == 's')
                strcat(fbuf, "%I");
            else if (*optarg == 'l')
                strcat(fbuf, "%H");
            break;

        case 'm':
            strcat(fbuf, ":%M");
            break;

        case 's':
            strcat(fbuf, ":%S ");
            break;

        case 'd':
            strcat(fbuf, " %d");
            break;

        case 'w':
            if (*optarg == 's')
                strcat(fbuf, " %a ");
            else if (*optarg == 'l')
                strcat(fbuf, " %A ");
            else if (*optarg == 'n')
                strcat(fbuf, " %u ");
            break;

        case 'M':
            if (*optarg == 's')
                strcat(fbuf, " %b ");
            else if (*optarg == 'l')
                strcat(fbuf, " %B ");
            else if (*optarg == 'n')
                strcat(fbuf, "/%m/");
            break;

        case 'y':
            if (*optarg == 's')
                strcat(fbuf, "%y");
            else if (*optarg == 'l')
                strcat(fbuf, "%Y");
            break;

        case 'h':
        case '?':
        default:
            showHelp();
        }
    }

    time_t timer = time(0);
    struct tm *dt = localtime(&timer);
    char timebuf[100];
    strftime(timebuf, sizeof(timebuf), fbuf, dt);
    printf("%s\n", timebuf);

    return 0;
}


void showHelp(){
    fprintf(stderr, "**** HELP ****\n\n"
            "-h, --help\n"
            "\tDisplay help\n\n"
            "-H, --hour s|l\n"
            "\tHour\n"
            "\t\ts - 12 hour clock\n"
            "\t\tl - 24 hour clock\n\n"
            "-m, --minute\n"
            "\tMinute\n\n"
            "-s, --second\n"
            "\tSecond\n\n"
            "-d, --day\n"
            "\tDay in month\n\n"
            "-w, --wday s|l|n\n"
            "\tWeekday\n"
            "\t\ts - abbrevaited name\n"
            "\t\tl - full name\n"
            "\t\tn - as number ([1, 7], monday is 1)\n\n"
            "-M, --month s|l|n\n"
            "\tMonth\n"
            "\t\ts - abbreviated name\n"
            "\t\tl - full name\n"
            "\t\tn - as number\n\n"
            "-y, --year s|l\n"
            "\tYear\n"
            "\t\ts - two last digits of year\n"
            "\t\tl - full number\n"
    );
}
