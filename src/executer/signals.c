/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:14 by randrade          #+#    #+#             */
/*   Updated: 2025/01/17 17:39:13 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//vai se identeficar como 69 ou alguma merda quando pressionar o control + c
volatile sig_atomic_t heredoc_c_pressed = 0;


void handler_heredoc(int sig)
{
    if(sig == SIGINT)
    {
        heredoc_c_pressed = 69;
        if(heredoc_c_pressed)
        {
            write(2, "\n", 1);
            exit(0);
            //printf("Devo sair do heredoc\n");
        }
    }
}

static void handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    set_signals(void)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0; // Restart interrupted system calls if desired
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // Ignore SIGQUIT (Ctrl+\)
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
}

