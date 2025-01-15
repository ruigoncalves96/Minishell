#include "../../includes/minishell.h"

/*
    Ideia da funcao, percorrer uma lista de comandos e printar coisas com base no tipo de dado
    
    [] Percorrer a linha e abrir todos os fds que forem precisos
    [X] Executar um comando se for tipo Comando
*/

void loop_executer(t_list *token,t_env *env)
{
    while (token)
    {
        if(token->type == COMMAND)
        {
            if(validate_command_path(*token->str,env)== 0)
            {
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
        if(!path)
        {
            ft_free_double_array(env_array);
            return -1;
        }
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
            free(path);
            ft_free_double_array(env_array);
        }
      
    return 0;
    }
    


