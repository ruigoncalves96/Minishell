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

static void disable_ctrl_backslash(void)
{
    struct termios term;

    // Get current terminal attributes
    tcgetattr(STDIN_FILENO, &term);

    // Disable the QUIT character (Ctrl + \)
    term.c_cc[VQUIT] = _POSIX_VDISABLE;
    term.c_lflag &= ~(ECHOCTL);

    // Set the modified attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void    handler(int sig)
{
    if (sig == SIGINT)
    {
        ft_printf("\n");
        rl_on_new_line();    // Tell readline we moved to a new line
        rl_replace_line("", 0);  // Clear the current input
        rl_redisplay();
    }
}

void    set_signals(void)
{
    struct sigaction sa_c;

    disable_ctrl_backslash();
    sa_c.sa_handler = handler;
    sa_c.sa_flags = SA_RESTART; // Restart system calls if interrupted
    sigemptyset(&sa_c.sa_mask); // Block no other signals during handler execution
    sigaction(SIGINT, &sa_c, NULL);

    // Ignore SIGQUIT (Ctrl+\)
    sa_c.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa_c, NULL);
    // signal(SIGINT, handler);
    // signal(SIGQUIT, SIG_IGN);
}
