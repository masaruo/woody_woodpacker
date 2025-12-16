/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:57:24 by mogawa            #+#    #+#             */
/*   Updated: 2023/08/18 15:57:30 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_lstcalloc_content(void *content)
{
	ft_free_null(content);
}

/*
*param #1:	lcallocで確保されたメモリーアドレスのリスト
*return:	なし
*func:		heapに確保されたメモリー領域をフリー
*free:		なし
*/
void	ft_free_lstcalloc(t_list **head)
{
	ft_lstclear(head, ft_free_lstcalloc_content);
}

/*
*param #1:	エレメント数
*param #2:	各エレメントのサイズ
*param #3:	アドレスを格納するリストの先頭
!			初期化時には、NULLポインタであることが必要
*return:	確保された領域へのポインタ
*func:		Allocates memory and fills it with zeros
*			address is stored to the linked list
*free:		必要
*/
void	*ft_lstcalloc(size_t count, size_t size, t_list **head)
{
	void	*heap;
	t_list	*elem;

	heap = ft_calloc(count, size);
	if (!heap)
		return (NULL);
	elem = ft_lstnew(heap);
	if (!elem)
	{
		ft_free_null(heap);
		return (NULL);
	}
	ft_lstadd_back(head, elem);
	return (heap);
}

//!	test code below
// typedef struct s_inner
// {
// 	int		*in_int_arr;
// 	char	*in_char_arr;
// }	t_inner;

// typedef struct s_test
// {
// 	int		*int_arr;
// 	char	*char_arr;
// 	t_inner	*in;
// }	t_test;

// void test(t_list **head)
// {
// 	int		*arr;
// 	int		*arr2;
// 	char	*str;

// 	arr = ft_lstcalloc(5, sizeof(int), head);
// 	printf("arr=%p\n", arr);
// 	arr[0] = 0;
// 	arr[1] = 1;
// 	arr[2] = 2;
// 	arr[3] = 3;
// 	arr[4] = 4;
// 	arr2 = ft_lstcalloc(2, sizeof(int), head);
// 	printf("arr2=%p\n", arr2);
// 	arr2[0] = 99;
// 	arr2[1] = 88;
// 	str = ft_lstcalloc(3, sizeof(char), head);
// 	printf("str=%p\n", str);
// 	str[0] = 'h';
// 	str[1] = 'i';
// 	str[2] = '\0';
// 	for (int i = 0; i < 5; i++)
// 		printf("arr[i]=%d\n", arr[i]);
// 	for (int j = 0; j < 2; j++)
// 		printf("arr[j]=%d\n", arr2[j]);
// 	printf("%s\n", str);
// 	printf("size in test:%d\n", ft_lstsize(*head));
// 	return ;
// }

// void	test_struct(t_list **head)
// {
// 	t_inner	*indata;
// 	t_test	*test;

// 	indata = ft_lstcalloc(1, sizeof(t_inner), head);
// 	indata->in_char_arr = ft_lstcalloc(3, sizeof(char), head);
// 	indata->in_char_arr[0] = 'h';
// 	indata->in_char_arr[1] = 'i';
// 	indata->in_char_arr[2] = '\0';
// 	//!
// 	indata->in_int_arr = ft_lstcalloc(3, sizeof(int), head);
// 	indata->in_int_arr[0] = 1;
// 	indata->in_int_arr[1] = 2;
// 	indata->in_int_arr[2] = 3;
// 	//!
// 	test = ft_lstcalloc(1, sizeof(t_test), head);
// 	printf("test=%p\n", test);
// 	test->in = indata;
// 	test->char_arr = ft_lstcalloc(3, sizeof(char), head);
// 	printf("test-char_arr=%p\n", test->char_arr);
// 	test->char_arr[0] = 'H';
// 	test->char_arr[1] = 'i';
// 	test->char_arr[2] = '\0';
// 	//!
// 	test->int_arr = ft_lstcalloc(3, sizeof(int), head);
// 	printf("test-int_arr=%p\n", test->int_arr);
// 	test->int_arr[0] = 999;
// 	test->int_arr[1] = 888;
// 	test->int_arr[2] = 777;
// 	//!
// 	printf("indata->in_char_arr:%s\n", test->in->in_char_arr);
// 	printf("test->char_arr:%s\n", test->char_arr);
// 	for (int i = 0; i < 3; i++)
// 		printf("indata_intarr:%d\n", test->in->in_int_arr[i]);
// 	for (int i = 0; i < 3; i++)
// 		printf("test_intarr:%d\n", test->int_arr[i]);
// 	printf("size in test struct1= %d\n", ft_lstsize(*head));
// 	// ft_free_lstcalloc(head);
// 	printf("size in test struct2= %d\n", ft_lstsize(*head));
// }

// int main (void)
// {
// 	t_list *head;

// 	head = NULL;
// 	printf("head address =%p\n", head);
// 	test(&head);
// 	test_struct(&head);
// 	printf("listNum=%d\n", ft_lstsize(head));
// 	system("leaks -q a.out");
// 	return (0);
// }