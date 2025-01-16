#include "../../includes/minishell.h"

/*
    Ideia da funcao, percorrer uma lista de comandos e printar coisas com base no tipo de dado
    
    [] Percorrer a linha e abrir todos os fds que forem precisos
    [X] Executar um comando se for tipo Comando
*/
//[]Funcao que vai criar uma list t_redirect

static int open_redirect(t_token *token)
{
    if (!token || !token->red || !token->red->filename[0])
        return 1;
    //[X] abrir o arquivo
    printf("Redirect filename: %s\n", token->red->filename[0]);
    if(token->red->type == OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if(token->red->type == A_OUT)
        token->red->fd = open(token->red->filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if(token->red->type == IN)
        token->red->fd = open(token->red->filename[0], O_RDONLY);
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
              if(open_redirect(token->next) == 1)
                    printf("Aconteceu alguma coisa de errado equanto processo de escrever o namefile\n");
        }
        token = token->next;
    }
    
}

static void handle_redirections(t_token *token,int *backup_fd)
{
    if (!token->next || token->next->subtype != T_REDIRECT)
        return;

    
      printf("Entrei\n");
    backup_fd[0] = dup(STDIN_FILENO);
    backup_fd[1] = dup(STDOUT_FILENO);

    while(token->next->subtype == T_REDIRECT)
    {
        if(token->next->red->type == OUT || token->next->red->type == A_OUT)
        {
            
            if(dup2(token->next->red->fd,STDOUT_FILENO) == -1)
            {
                perror("dup2");
                close(token->next->red->fd);
            }
        }
        token = token->next;
    }

}
static void close_stuff(int *backup_fd)
{
            dup2(backup_fd[0], STDIN_FILENO);   
            dup2(backup_fd[1], STDOUT_FILENO);
            close(backup_fd[0]);
            close(backup_fd[1]);
}
//[X]Primeiro loop para abrir as coisas
//[] Loop para verificar comandos
void loop_executer(t_token *token,t_env *env,t_prompt_info prompt_info)
{
    int original_fd[2];
    loop_and_open_fd(token);   
    while (token)
    {
        if(token->type == COMMAND)
        {
            if(validate_command_path(*token->token,env) == 0 || execute_builtin(token,prompt_info) == 0)//Comando valido 
            {
                    
                    handle_redirections(token,original_fd);
                    executer_manager(token->token,env); 
                    close_stuff(original_fd);
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
