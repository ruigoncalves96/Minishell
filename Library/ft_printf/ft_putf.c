/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:06:22 by randrade          #+#    #+#             */
/*   Updated: 2024/05/30 12:09:59 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	int	i;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putaddress(unsigned long addr)
{
	size_t	nbr_len;

	if (addr == 0)
		return (ft_putstr("(nil)"));
	nbr_len = 0;
	nbr_len += ft_putstr("0x");
	nbr_len += ft_putnbr_hex(addr, 'l');
	return (nbr_len);
}

int	ft_putnbr(long nbr)
{
	size_t	nbr_len;

	nbr_len = ft_nbrlen(nbr);
	if (nbr < 0)
	{
		nbr *= -1;
		nbr_len += ft_putchar('-');
	}
	if (nbr < 10)
	{
		ft_putchar(nbr + 48);
		return (nbr_len);
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	return (nbr_len);
}

int	ft_putnbr_hex(unsigned long nbr, const char lower_upper)
{
	const char	*base_16_l = "0123456789abcdef";
	const char	*base_16_u = "0123456789ABCDEF";
	const char	*base;
	size_t		nbr_len;

	nbr_len = 0;
	if (lower_upper == 'l')
		base = base_16_l;
	else if (lower_upper == 'U')
		base = base_16_u;
	if (nbr < 16)
	{
		nbr_len += ft_putchar(nbr[base]);
		return (nbr_len);
	}
	else
	{
		nbr_len += ft_putnbr_hex(nbr / 16, lower_upper);
		nbr_len += ft_putnbr_hex(nbr % 16, lower_upper);
	}
	return (nbr_len);
}
