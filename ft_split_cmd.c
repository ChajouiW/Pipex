/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:13:43 by mochajou          #+#    #+#             */
/*   Updated: 2025/01/31 17:14:37 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_word(char const *s, char c)
{
	int	count;
	int	flag;
	int	in;

	in = 0;
	count = 0;
	flag = 0;
	while (*s)
	{
		if (*s == '\'' && !in)
			in = 1;
		else if (*s == '\'' && in)
			in = 0;
		if (*s == c && flag)
			flag = 0;
		else if (*s != c && flag == 0 && !in)
		{
			count++;
			flag = 1;
		}
		s++;
	}
	return (count);
}

static char	*ft_t3mar(char const *s, char *word, char c, size_t len)
{
	size_t	i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	while (*s && *s == c)
		s++;
	while (i < len)
	{
		if (*s == '\'' && !in_quote)
			in_quote = 1;
		else if (*s == '\'' && in_quote)
			in_quote = 0;
		if (*s != c || in_quote)
		{
			word[i] = *s;
			i++;
		}
		s++;
	}
	word[i] = '\0';
	return (word);
}

static int	word_len(const char *s, char c, size_t *index)
{
	int	len;
	int	in_quote;
	int	i;

	i = *index;
	in_quote = 0;
	len = 0;
	while (s[i] && (s[i] != c || in_quote))
	{
		if (s[i] == '\'' && !in_quote)
			in_quote = 1;
		else if (s[i] == '\'' && in_quote)
			in_quote = 0;
		i++;
		len++;
	}
	*index = i;
	return (len);
}

/*void	ft_free(char **s, int i)
{
	if (!s)
		return ;
	if (i)
	{
		while (i >= 0)
			free(s[--i]);
		free(s);
		return ;
	}
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}*/

static char	**fill_arr(char **arr, char const *s, char c, int n_words)
{
	size_t	len;
	size_t	i;
	int		word_i;

	word_i = 0;
	while (word_i < n_words)
	{
		i = 0;
		while (s[i] == c)
			i++;
		len = word_len(s, c, &i);
		arr[word_i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!arr[word_i])
			return (ft_free(arr, word_i), NULL);
		arr[word_i] = ft_t3mar(s, arr[word_i], c, len);
		word_i++;
		s += i;
	}
	arr[word_i] = NULL;
	return (arr);
}

char	**ft_split_cmd(char const *s, char c)
{
	int		n_words;
	char	**arr;

	if (!s || !*s)
		return (NULL);
	n_words = count_word(s, c);
	arr = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!arr)
		return (NULL);
	return (fill_arr(arr, s, c, n_words));
}
/*#include <stdio.h>
int main() {
    // Write C code here
    char **s;
    s = ft_split_cmd("tr '\n'    ' '   '   a      a i '", ' ');
    for (int j = 0; s[j]; j++)
        printf("%d == %s\n",j,  s[j]);
    ft_free(s, 0);
    return 0;
}*/
