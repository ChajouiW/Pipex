/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:12:12 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/28 18:57:48 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

void	ft_printf(const char *s, ...);
//static void	handle_format(char sp, va_list ap);
//static void	print_char(const char c);
//static void	print_str(const char *s);
//static void	print_nbr(int n);

#endif
