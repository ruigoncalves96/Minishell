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

// static void disable_ctrl_backslash(void)
// {
//     struct termios term;

//     memset(&term, 0, sizeof(struct termios));
//     // Get current terminal attributes
//     tcgetattr(STDIN_FILENO, &term);

//     // Disable the QUIT character (Ctrl + \)
//     term.c_cc[VQUIT] = _POSIX_VDISABLE;
//     term.c_lflag &= ~(ECHOCTL);

//     // Set the modified attributes
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

volatile sig_atomic_t g_signal = 0;
volatile sig_atomic_t g_in_heredoc = 0;
static void handler(int sig)
{
    if (sig == SIGINT)
    {
        g_signal = 130;
        write(1, "\n", 1);
        if (!g_in_heredoc)
        {
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
        }
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

