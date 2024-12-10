/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:55:54 by randrade          #+#    #+#             */
/*   Updated: 2024/05/25 17:06:34 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdarg.h>

// ---------- ft_printf.c ----------

int	ft_printf(const char *str, ...);

// ---------- ft_putf.c ----------

int	ft_putchar(char c);
int	ft_putstr(const char *str);
int	ft_putaddress(unsigned long addr);
int	ft_putnbr(long nbr);
int	ft_putnbr_hex(unsigned long nbr, const char lower_upper);

#endif
