/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:20:28 by inikelsk          #+#    #+#             */
/*   Updated: 2025/05/24 10:27:17 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Count the number of digits of n by repeatedly dividing it by 10. Note that
count = 1 account for all single-digit numbers. In case of min int, return
the hard-coded number of its digits. */
static int	count_digits(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		if (n == -2147483648)
			return (10);
		else
			n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

/* Allocate enough memory to return a string representing integer n, conserving
the sign. On allocation failure, return NULL. 
Note +1 on malloc for '\0'. Also note while (len-- > is_negative): this lets the
0th index for positive numbers to be set to the first digits, while preventing 
the loop from accessing the 0th index of negative numbers - it is reserved for
'-' right after. Also note long nbr - this is min_int guard.*/
char	*ft_itoa(int n)
{
	int		is_negative;
	int		len;
	long	nbr;
	char	*result;

	is_negative = (n < 0);
	len = count_digits(n) + is_negative;
	result = malloc(len + 1 * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	nbr = n;
	if (nbr < 0)
		nbr = -nbr;
	while (len-- > is_negative)
	{
		result[len] = '0' + (nbr % 10);
		nbr /= 10;
	}
	if (is_negative)
		result[0] = '-';
	return (result);
}

/* #include <stdio.h>
int	main(void)
{
	int	n = 2147483647;
	int	k = -2147483648;
	int	l = 0;
	printf("n: %s\nk: %s\nl: %s\n", ft_itoa(n), ft_itoa(k), ft_itoa(l));
	return (0);
} */
