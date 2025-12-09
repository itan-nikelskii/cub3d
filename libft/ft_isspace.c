/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:27:20 by inikelsk          #+#    #+#             */
/*   Updated: 2025/12/09 13:27:41 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Check if c is any space character. Return 1 if so, 0 otherwise. */
int	ft_isspace(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}
