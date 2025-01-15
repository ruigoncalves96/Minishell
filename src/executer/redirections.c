#include "../../includes/minishell.h"

/*
    Ideia da funcao, percorrer uma lista de comandos e printar coisas com base no tipo de dado
    
    [] Percorrer a linha e abrir todos os fds que forem precisos
    [X] Executar um comando se for tipo Comando
*/

void loop_executer(t_token *token,t_env *env)
{
    while (token)
    {
        if(token->type == COMMAND)
        {
            if(validate_command_path(*token->token,env)== 0)//Comando valido 
            {
                //executer_manager(token->token,env);
                
                //Tenho sempre de verificar a proxima node para verificar se ela e nula
                //Vejo se a mina proxima node e uma redireçao
                if(token->next && token->next->subtype == T_REDIRECT)
                { 
                    //Vou começar  a preencher as minhas variaveis
                    //[]guardar o nome do arquivo
                    //[]criar o arquivo
                    //Verifico se a terceira node existe e entro nela
                    if(token->next->next && token->next->next->token)
                    {
                        if(!token->red)
                        {
                            //[X]Dar memoria a estrutura
                            token->red = calloc(1, sizeof(t_redirect));
                            if(!token->red)
                                perror("Error alocating memory in t_redirect\n");
                        }
                        
                        //[X]Alocar memoria ao filename se necessario
                        if(!token->red->filename)
                        {
                            token->red->filename = calloc(2, sizeof(char *));
                            if(!token->red->filename)
                                perror("Error alocating memory in double array filename\n");
                        }
                        
                        //[] Vou copiar o filename
                        token->red->filename[0] = ft_strdup(token->next->next->token[0]);
                        if(!token->red->filename[0])
                            perror("Error creating filename");
                        token->red->filename[1] = NULL;
                        printf("Redirect filename: %s\n", token->red->filename[0]);
                }
            }        
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
