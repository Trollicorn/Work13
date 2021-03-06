#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void sighandler(int signo){
  if (signo == SIGINT){
    int fd = open("errlog.txt", O_WRONLY | O_APPEND | O_CREAT, 0666 );
    char err[] = "exited because SIGINT was mean to me\n";
    int wrote = write(fd, err, strlen(err));
    if (wrote < 0){
      printf("%s\n",strerror(errno));
    }
    close(fd);
    exit(0);
  }
  else if (signo == SIGUSR1){
    printf("my %d works for nintendo\n", getppid() );
  }
}


int main(){
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while(1){
    printf("greetings friend, i am: %d\n", getpid() );
    sleep(1);
  }
  return 0;
}
