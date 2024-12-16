#include "../../includes/minishell.h"


void pwd_builtin(void)
{
    char *pwd;
    
    //NULL signifaca que queremos que aloque memoria
    //0 e uma flag que faz com que nao haja cap na alocacao
    pwd = getcwd(NULL, 0); 
    if (pwd != NULL) {
        printf("%s\n", pwd);
        free(pwd);
    } else {
        perror("getcwd failed");
    }
}
