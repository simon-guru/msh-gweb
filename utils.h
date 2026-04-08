/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:17:49 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/16 13:47:48 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UTILS_H
# define UTILS_H
# include "libft.h"

/* utils */
int		ft_strcmp(const char *a, const char *b);
char	*ft_strjoin3(const char *a, const char *b, const char *c);
int		ft_isalnum_us(int c);
void	*xfree(void *p);

#endif
