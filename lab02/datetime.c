#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[]){
    // get current time
    time_t curtime = time(0);

    // convert time_t to string in format `Www Mmm dd hh:mm:ss yyyy\n`
    printf("%s\n", ctime(&curtime));

    // convert time_t to struct tm with local calendar time
    struct tm *tm_time = localtime(&curtime);

    // write format datetime string to buffer
    // %H - hour, 24 hour clock
    // %M - minute
    // %S - second
    // %A - full weekday name
    // %d - day of month
    // %m - number of month
    // %Y - full year
    char buf[100];
    strftime(buf, sizeof(buf), "%H:%M:%S %A %d.%m.%Y", tm_time);
    printf("%s\n", buf);

    // %I - hour, 12 hour clock
    // %a - abbreviated weekday name
    // %j - day of year
    // %W - week of year (monday is the first day)
    // %B - full month name
    // %y - last two digits of year
    strftime(buf, sizeof(buf), "%I:%M %a %j/%W %B %y", tm_time);
    printf("%s\n", buf);

    return 0;
}
