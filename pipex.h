/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:17:28 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/25 21:04:25 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "ft_printf.h"
# include <sys/wait.h>
typedef struct s_io
{
	int	in;
	int	out;
}	t_io;

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char    *env_path(char **env);

void	ft_freee(char **s);
char    **cmd_path(char *cmd_arg, char **path);
size_t	ft_strlen(const char *s);
int	check_files(char *file_name, int in_out);

#endif
