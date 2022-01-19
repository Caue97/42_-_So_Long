/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:17:18 by felcaue-          #+#    #+#             */
/*   Updated: 2022/01/13 21:19:51 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Free's the memory of the char pointer received and puts it's contents 
 * to zero
 *
 * @param str The char pointer to free
 */
static void	free_potr_char(char **str)
{
	free (*str);
	*str = NULL;
}

/**
 * @brief Removes the part of the char pointer after the '\\n' (line break)
 *
 * @param strin The string that will have it's end trimmed
 * @return The string trimmed with everything after '\\n' removed 
 */
static char	*trim_other_line(char **strin)
{
	char	*cut_line;
	char	*s_holder;
	size_t	counter;

	cut_line = NULL;
	counter = 0;
	while ((*strin)[counter] && (*strin)[counter] != '\n')
	{
		counter++;
	}
	s_holder = *strin;
	cut_line = ft_substr(s_holder, 0, counter + 1);
	*strin = ft_strdup(s_holder + counter + 1);
	free_potr_char(&s_holder);
	return (cut_line);
}

static char	*get_last_line(char **strin)
{
	char	*helping;

	if (!ft_strchr(*strin, '\n') && **strin)
	{
		helping = ft_strdup(*strin);
		free_potr_char(strin);
		return (helping);
	}
	return (NULL);
}

char	*read_until_new_line(int fd, char *buffer, char *s_str, int *size_read)
{
	char	*helper;

	while (!ft_strchr(s_str, '\n') && *size_read)
	{
		*size_read = read(fd, buffer, BUFFER_GNL);
		if (*size_read <= 0)
			break ;
		buffer[*size_read] = '\0';
		helper = s_str;
		s_str = ft_strjoin(helper, buffer);
		free_potr_char(&helper);
	}
	free_potr_char(&buffer);
	return (s_str);
}

char	*get_next_line(int fd)
{
	int			read_bytes;
	char		*buffer;
	static char	*static_var;

	buffer = NULL;
	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_GNL < 1)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_GNL + 1));
	if (buffer == NULL)
		return (NULL);
	if (!static_var)
		static_var = ft_strdup("");
	read_bytes = 1;
	static_var = read_until_new_line(fd, buffer, static_var, &read_bytes);
	if (*static_var == '\0' && read_bytes < 1)
	{
		free_potr_char(&static_var);
		return (NULL);
	}
	if (ft_strchr(static_var, '\n'))
	{
		return (trim_other_line(&static_var));
	}
	return (get_last_line(&static_var));
}
