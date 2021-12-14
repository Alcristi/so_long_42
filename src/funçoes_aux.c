/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funçoes_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:16:02 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/13 22:56:46 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static size_t	count_letters(char const *s, char c)
{
	int	amount_of_letters;

	amount_of_letters = 0;
	while (s[amount_of_letters] != c && s[amount_of_letters])
		amount_of_letters++;
	return (amount_of_letters);
}

static size_t	count_words(char const *s, char c)
{
	int		total;
	int		i;

	i = 0;
	total = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		total++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (total);
}

static int	ft_abs(int p1, int p2)
{
	if ((p1 - p2) < 0)
		return (p2 - p1);
	return (p1 - p2);
}

static char	*ft_substrsplit(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*sub;

	i = 0;
	size = ft_strlen(s);
	if ((ft_strlen(s + 1) < start))
		len = 0;
	if ((ft_strlen(s) + 1) < len + 1)
		sub = (char *)malloc(ft_strlen(s) + 1);
	else if (len == ft_strlen(s))
		sub = (char *)malloc(ft_abs((int)len, (int)start) + 1);
	else
		sub = (char *)malloc(len + 1);
	if ((!s || !sub))
		return (0);
	while ((i < len) && (start + i) < size)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	**ft_split_long(char const *s, char c)
{
	char	**list;
	size_t	c_words;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	c_words = count_words(s, c);
	list = malloc(sizeof(char *) * (c_words + 1));
	if (!list)
		return (0);
	while (i < c_words && *s)
	{
		if (*s != c)
		{
			list[i] = ft_substrsplit(s, 0, count_letters(s, c));
			if (!list[i++])
				return (0);
			s += count_letters(s, c);
		}
		else
			s++;
	}
	list[c_words] = NULL;
	return (list);
}
