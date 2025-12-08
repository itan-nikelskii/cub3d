/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:43:33 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/26 13:18:33 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Applies the function f to each character of the string s; f takes the index
of a character as the first argument and the character itself as the second.
The original string is modified as a result. */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* // Put this on top for testing
void	ft_toupper_map(unsigned int i, char* c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c = *c - ('a' - 'A');
}
#include <stdio.h>
int	main(void)
{
	char	s[] = "123 abcdE";
    printf("Original: %s\n", s);
	ft_striteri(s, ft_toupper_map);
    printf("Modified: %s\n", s);
    return (0);
} */
