/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:17:28 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/29 00:49:25 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "ft_printf.h"
# include <sys/wait.h>
# include "ft_printf.h"

typedef struct s_all
{
	int		ac;
	int		fdin;
	int		fdout;
	char	**envp;
	char	**s_path;
}	t_all;

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*env_path(char **env);

void	ft_error(char *cmd, t_all a, char **s, int n);
void	ft_freee(char **s);
char	**cmd_path(char *cmd_arg, t_all a);

size_t	ft_strlen(const char *s);
int		check_files(char *file_name, int in_out);

#endif
