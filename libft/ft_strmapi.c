/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:36:09 by lchappon          #+#    #+#             */
/*   Updated: 2017/11/18 12:29:01 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	length;
	char	*str;
	size_t	i;

	if (s && f)
	{
		length = 0;
		while (s[length])
			length++;
		str = (char *)malloc(sizeof(*str) * (length + 1));
		if (str == NULL)
			return (NULL);
		i = 0;
		while (i < length)
		{
			str[i] = f(i, s[i]);
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
