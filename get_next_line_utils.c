/* header */

#include "get_next_line.h"

char    *ft_strchr(const char *s, char c)
{
    while(*s)
    {

        if(*(unsigned char*)s == (unsigned char)c)
            return ((char *)s);
        s++;
    }
    if (*(unsigned char*)s == (unsigned char)c)
        return ((char*)s);
    return (NULL); 
}

size_t  ft_strlen(const char *s)
{
    size_t  len;

    len = 0;
    while (s[len] != '\0')
        len++;
    return (len);
}

size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t  i;
    size_t  src_len;

    src_len = ft_strlen(src);
    if (dstsize == 0)
        return (src_len);
    i = 0;
    while (i < dstsize - 1 && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (src_len);
}

char    *ft_strdup(const char *s1)
{
    char    *dup;
    size_t  len;
    size_t  i;

    len = ft_strlen(s1);
    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dup[i] = s1[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

void    *ft_calloc(size_t count, size_t size)
{
    void    *ptr;
    size_t  total_size;
    size_t  i;
    char    *cptr;

    total_size = count * size;
    ptr = malloc(total_size);
    if (!ptr)
        return (NULL);
    cptr = (char *)ptr;
    i = 0;
    while (i < total_size)
    {
        cptr[i] = 0;
        i++;
    }
    return (ptr);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t  len1;
    size_t  len2;
    char    *joined;
    size_t  i;
    size_t  j;

    if (!s1 || !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    joined = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!joined)
        return (NULL);
    i = 0;
    while (i < len1)
    {
        joined[i] = s1[i];
        i++;
    }
    j = 0;
    while (j < len2)
    {
        joined[i + j] = s2[j];
        j++;
    }
    joined[i + j] = '\0';
    return (joined);
}

void *ft_memcpy(void *s, const void *c, size_t len)
{
    unsigned char *ptr;
    const unsigned char *ptr2;
    size_t i;

    ptr = s;
    ptr2 = c;
    i = 0;
    while (i < len)
    {
        *ptr++ = *ptr2++;
        i++;
    }
    return(s);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *sub;
    size_t length;

    if (s == NULL)
        return NULL;
    length = ft_strlen(s);
    sub = (char *)malloc(sizeof(char) * (len + 1));
    if (!sub)
        return (NULL);
    if (start >= length)
    {
        *sub = '\0';
        return sub;
    }
    if (len > length - start)
        len = length - start;

    ft_memcpy(sub, &s[start], len);
    sub[len] = '\0';
    return sub;
}