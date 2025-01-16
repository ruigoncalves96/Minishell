#include "../../includes/minishell.h"

/*
    Ideia da funcao, percorrer uma lista de comandos e printar coisas com base no tipo de dado
    
    [] Percorrer a linha e abrir todos os fds que forem precisos
    [X] Executar um comando se for tipo Comando
*/
//[]Funcao que vai criar uma list t_redirect

static int handle_redirect(t_token *token)
{
    //[X]Vou criar a lista se nao existir

    //[X] abrir o arquivo
    printf("Redirect filename: %s\n", token->red->filename[0]);
    if(token->red->type == OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if(token->red->type == A_OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if(token->red->type == IN)
        token->red->fd = open(token->red->filename[0], O_WRONLY);
    if(token->red->fd == -1)
    {
        //Talvez tenha de dar free no red e na str
        return 1;
    }
    return 0;
} 
//

static void loop_and_open_fd(t_token *token)
{
    while (token)
    {
        if(token->next && token->next->subtype == T_REDIRECT)
        {
              if(handle_redirect(token->next) == 1)
                    printf("Aconteceu alguma coisa de errado equanto processo de escrever o namefile\n");
        }
        token = token->next;
    }
    
}
//[X]Primeiro loop para abrir as coisas
//[] Loop para verificar comandos
void loop_executer(t_token *token,t_env *env)
{
    loop_and_open_fd(token);
    while (token)
    {
        if(token->type == COMMAND)
        {
            if(validate_command_path(*token->token,env) == 0)//Comando valido 
            {
                //printf("Comando valido\n");
                executer_manager(token->token,env);          
            }                  
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
        }
            ft_free_double_array(env_array);
      
    return 0;
    }
