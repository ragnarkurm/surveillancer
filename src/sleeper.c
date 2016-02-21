#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void err(int errno, char *func);
void usage(char *msg, char *argv[]);

int main(int argc, char *argv[]) {

  int errno;
  struct  timeval now;
  useconds_t  delay;
  int interval;
  struct  tm  *tm;

  if (argc != 2) {
    usage(NULL, argv);
  }

  errno = sscanf(argv[1], "%d", &interval);
  if (errno != 1) {
    usage("Failed parsing command line argument.", argv);
  }

  if (interval < 1) {
    usage("Time divisor must be positive.", argv);
  }

  // now all checks are done
  // calculate the sleep and do it.

  errno = gettimeofday(&now, NULL);
  err(errno, "gettimeofday");

  delay = 1000000 * (interval - (now.tv_sec % interval)) - now.tv_usec;

  errno = usleep(delay);
  err(errno, "usleep");

  // output current time

  errno = gettimeofday(&now, NULL);
  err(errno, "gettimeofday");

  tm = localtime(&now.tv_sec);
  printf("%04d %02d %02d %02d %02d %02d\n",
    tm->tm_year + 1900,
    tm->tm_mon + 1,
    tm->tm_mday,
    tm->tm_hour,
    tm->tm_min,
    tm->tm_sec
  );

  return 0;

}

void usage(char *msg, char *argv[]) {
    printf("Usage: %s <time divisor pos int>\n", argv[0]);
    if (msg) {
      printf("%s\n", msg);
    }
    exit(1);
}

void err(int errno, char *func) {

  char  *errstr;

  if (errno == 0) {
    return;
  }

  errstr = strerror(errno);
  printf("Error: %s(): %s\n", func, errstr);

  exit(1);

}
