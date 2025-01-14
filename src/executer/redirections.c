#include "../../includes/minishell.h"

/*
    Ideia da funcao, percorrer uma lista de comandos e printar coisas com base no tipo de dado
    
    [] Executar um comando se for tipo Comando
*/

void loop_executer(t_list *token,t_env *env)
{
    //token vai entrar aqui, vou percorrer o que tenho armazenado nos tokens
    while (token)
    {
        if(token->type == COMMAND)
        {
            //EPA CONSEGUI ENTRAR, DEIXA LA VER SE ES MESMO UM COMANDO SEU MAROTO
            if(validate_command_path(*token->str,env)== 0)
            {
                printf("WOW estou proximo de ser amado\n");
                executer_manager(token->str,env);
            }
        }else if(token->subtype == T_REDIRECT)
        {
            printf("Sou um sinal redirect\n");
        }
        token = token->next;
    }
}


int executer_manager( char **str,t_env *env)
{
		char *path;
		char **env_array;
		int child;

        child = fork();
        env_array = convert_env_to_array(env);
		path = get_command_path(*str,env);

        if(child == 0)
        {
            if(execve(path,str,env_array) == -1)
            {
             perror("exeve");
             free(path);
            ft_free_double_array(env_array);
            }
        }else
        {
            wait(NULL);
        }
      
    return 0;
    }
    


