/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:51:25 by mochajou          #+#    #+#             */
/*   Updated: 2025/02/01 20:07:50 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!big || !little) && len == 0)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_error(char *cmd, t_all a, char **s, int n)
{
	if (n == -1)
	{
		ft_printf("permission denied: %s\n", cmd);
		ft_free(a.s_path, 0);
		if (a.b)
			ft_free(a.my_av, 0);
		while (wait(NULL) > 0)
			;
		exit(1);
	}
	ft_free(s, 0);
	if (n || !*cmd)
	{
		ft_printf("permission denied: %s\n", cmd);
		ft_free(a.s_path, 0);
		if (a.b)
			ft_free(a.my_av, 0);
		exit(126);
	}
	if (a.fdin > 0)
		ft_printf("command not found: %s\n", cmd);
	ft_free(a.s_path, 0);
	if (a.b)
		ft_free(a.my_av, 0);
	exit(127);
}

char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	while (s2[j] == ' ')
		j++;
	new = (char *)calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(&s2[j]) + 2));
	if (!new)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[k])
		new[i++] = s1[k++];
	new[i++] = '/';
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
