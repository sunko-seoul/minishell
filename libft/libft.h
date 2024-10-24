/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:21:45 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/26 00:54:37 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <sys/types.h>

long long	ft_atoll(char *str, int *err);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isspace(int c);
char		*ft_itoa(int n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_putchar_fd(char c, int fd);
int			ft_putendl_fd(const char *s, int fd);
int			ft_putstr_fd(const char *s, int fd);
char		**ft_split(char const *s, const char *sep);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);

typedef struct s_str_bldr
{
	char	*str;
	size_t	sz;
	size_t	cap;
}	t_str_bldr;

void		init_str_bldr(t_str_bldr *str_bldr);
void		append_str(t_str_bldr *str_bldr, char *str, size_t n);
void		append_char(t_str_bldr *str_bldr, char c);

#endif
