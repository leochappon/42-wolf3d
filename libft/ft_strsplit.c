/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:33:10 by lchappon          #+#    #+#             */
/*   Updated: 2018/04/23 17:31:10 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_prtcount(char const *s, char c)
{
	int		count;
	int		part;

	part = 0;
	count = 0;
	while (*s)
	{
		if (part == 1 && *s == c)
			part = 0;
		if (part == 0 && *s != c)
		{
			part = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int		ft_prtlength(char const *s, char c)
{
	int		length;

	length = 0;
	while (*s && *s != c)
	{
		length++;
		s++;
	}
	return (length);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	count = ft_prtcount(s, c);
	tab = (char **)malloc(sizeof(*tab) * (count + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (count--)
	{
		while (*s && *s == c)
			s++;
		tab[i] = ft_strsub(s, 0, ft_prtlength(s, c));
		if (tab[i] == NULL)
			return (NULL);
		s = s + ft_prtlength(s, c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
