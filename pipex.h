/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:17:28 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/31 23:35:57 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include "ft_printf.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"

typedef struct s_all
{
	int		ac;
	int		fdin;
	int		fdout;
	int		b;
	char	**envp;
	char	**s_path;
	char	**my_av;
}	t_all;

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char c);
char	**ft_split_cmd(char const *s, char c);
char	*ft_pathjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*env_path(char **env);

void	here_doc(t_all a, char **av, int *status);

void	execute(t_all a, char *arg, int fd, pid_t *pid);
void	pipex(t_all a, char **av, int *status);
void	ft_error(char *cmd, t_all a, char **s, int n);
void	ft_free(char **s, int i);
void	usage(int part);

char	**cmd_path(char *cmd_arg, t_all a);

size_t	ft_strlen(const char *s);
int		check_files(char *file_name, int in_out, int bonus);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
