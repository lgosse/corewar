/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaragoz <akaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 15:05:41 by akaragoz          #+#    #+#             */
/*   Updated: 2016/09/17 17:25:43 by gbuclin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_get_file_content(char *file_name)
{
	char	*file_content;
	char	*buffer;
	int		fd;

	file_content = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while (get_next_line(fd, &buffer) > 0)
	{
		file_content = ft_strjoin_n_free(file_content, buffer);
		file_content = ft_strjoin_n_free(file_content, "\n");
		free(buffer);
	}
	close(fd);
	return (file_content);
}
