/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:29:41 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/29 00:44:08 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_char(const char c)
{
	(write(1, &c, 1));
}

static void	print_str(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		(print_str("(null)"));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

static void	print_nbr(int n)
{
	unsigned int	num;

	if (n < 0)
	{
		num = -n;
		print_char('-');
	}
	else
		num = n;
	if (num > 9)
		print_nbr(num / 10);
	print_char(num % 10 + '0');
}

static void	handle_format(char sp, va_list ap)
{
	if (sp == 'c')
		print_char(va_arg(ap, int));
	else if (sp == 's')
		print_str(va_arg(ap, char *));
	else if (sp == 'd')
		print_nbr(va_arg(ap, int));
}

void	ft_printf(const char *s, ...)
{
	int		i;
	va_list	ap;

	if (!s)
		return ;
	va_start(ap, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
			handle_format(s[++i], ap);
		else
			print_char(s[i]);
		i++;
	}
	va_end(ap);
}
