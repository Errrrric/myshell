#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>    
#include <pwd.h>                // shell prompt. username과 hostname를 위한 헤더


#define MAX_LEN_LINE    10
#define LEN_HOSTNAME	30      //shell prompt. username과 hostname를 위한 배

열

int main(void)
{
    
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
 


    while (true) {
        char *s;
        int len;
        char *ptr;
        char *commandArr[MAX_LEN_LINE] = {NULL};
        int i = 0;
           

       char hostname[LEN_HOSTNAME + 1];
       memset(hostname, 0x00, sizeof(hostname));

       gethostname(hostname, LEN_HOSTNAME);
       printf("%s@%s $",getpwuid(getuid())->pw_name,hostname);   //printf("hostname: %s\n", hostname);  ,printf("username: %s\n", getpwuid(getuid())->pw_name); 합침


       printf("MyShell $ ");
        

        s = fgets(command, MAX_LEN_LINE, stdin);
         if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        


//프로그램 exit 구현  
        else if(strcmp(command,"exit\n") == 0 ) {
                    printf("exit\n");
                    exit(0);
            }


//

       
       ptr = strtok(s,";");
       while(ptr != NULL){
         commandArr[i] = ptr;
         i++;
         ptr = strtok(NULL,";");
       }

      

       for(int j = 0; j < i; j++)  {
           

           s = commandArr[j];
           strcpy(command,s);
           



        len = strlen(command);
        printf("%d\n", len);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        printf("[%s]\n", command);
      
        
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
            printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }
        else {  /* child */
            ret = execve(args[0], args, NULL);
            if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
        } 
       
  }

}
    return 0;
}
