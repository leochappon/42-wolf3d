/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:36:28 by lchappon          #+#    #+#             */
/*   Updated: 2017/11/18 12:40:43 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		min;
	int		max;
	int		i;

	if (!s)
		return (NULL);
	min = 0;
	while (s[min] && (s[min] == '\t' || s[min] == '\n' || s[min] == ' '))
		min++;
	max = min;
	while (s[max])
		max++;
	while (s[max - 1] == '\t' || s[max - 1] == '\n' || s[max - 1] == ' ')
		max--;
	str = (char *)malloc(sizeof(*str) * max + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (min < max)
		str[i++] = s[min++];
	str[i] = '\0';
	return (str);
}
