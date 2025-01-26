/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:12:12 by mochajou          #+#    #+#             */
/*   Updated: 2024/11/23 20:40:13 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

typedef struct s_flags
{
	char	sp;
	int		plus;
	int		hash;
	int		space;
}	t_f;

int	flag_handle(va_list ap, t_f flag);
int	flaged(const char sp, t_f flag);

int	ft_printf(const char *s, ...);
int	handle_format(char sp, va_list ap);
int	print_char(const char c);
int	print_str(const char *s);
int	print_nbr(int n);
int	print_unsigned(unsigned int n);
int	print_hex(unsigned long n, char x);
int	print_ptr(unsigned long n);

#endif
