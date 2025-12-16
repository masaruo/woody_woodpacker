/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:56:22 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/27 21:03:41 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lfree_content(void *content)
{
	t_mem	*heap;

	heap = (t_mem *) content;
	ft_free_null(heap->adr);
	ft_free_null(heap);
}

/*
*param #1:	lcallocで確保されたメモリーアドレスのリスト
*param #2:	削除するメモリーグループを指定
			「 ALL 」で全部のリストを削除
*return:	なし
*func:		heapに確保されたメモリー領域をフリー
!			lallocの全プロセスの終了には、ft_lalloc_destry(t_list *head)
!			を使用すること
*free:		なし
*/
void	ft_lfree(t_list **head, int grp)
{
	t_list	*crnt;
	t_list	*prev;
	t_list	*tmp;
	t_mem	*heap;

	prev = *head;
	crnt = prev->next;
	while (crnt != NULL)
	{
		tmp = crnt->next;
		heap = (t_mem *) crnt->content;
		if (heap->grp == grp || grp == ALL)
		{
			prev->next = tmp;
			ft_lstdelone(crnt, ft_lfree_content);
		}
		else
		{
			prev = crnt;
		}
		crnt = tmp;
	}
}

static t_mem	*ft_get_tmem_struct(size_t count, size_t size, int grp)
{
	t_mem	*mem;

	mem = ft_calloc(1, sizeof(t_mem));
	if (!mem)
	{
		return (NULL);
	}
	mem->adr = ft_calloc(count, size);
	if (!mem->adr)
	{
		free(mem);
		return (NULL);
	}
	mem->grp = grp;
	return (mem);
}

/*
*param #1:	エレメント数
*param #2:	各エレメントのサイズ
*param #3:	ft_lalloc_init()で初期化されたリストの先頭
!			ft_lalloc_init()で初期化し、ft_lalloc_destroy()で終了処理が必要
*return:	確保された領域へのポインタ
*func:		Allocates memory and fills it with zeros
*			address is stored to adrs linked list
*free:		必要
*/
void	*ft_lalloc(size_t count, size_t size, t_list **head, int grp)
{
	t_list	*elem;
	t_mem	*mem;

	mem = ft_get_tmem_struct(count, size, grp);
	if (!mem)
		return (NULL);
	elem = ft_lstnew(mem);
	if (!elem)
	{
		ft_free_null(mem->adr);
		ft_free_null(mem);
		return (NULL);
	}
	ft_lstadd_back(head, elem);
	return (mem->adr);
}

//! test code:
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

// 	arr = ft_lalloc(5, sizeof(int), head, 0);
// 	printf("arr=%p\n", arr);
// 	arr[0] = 0;
// 	arr[1] = 1;
// 	arr[2] = 2;
// 	arr[3] = 3;
// 	arr[4] = 4;
// 	arr2 = ft_lalloc(2, sizeof(int), head, 1);
// 	printf("arr2=%p\n", arr2);
// 	arr2[0] = 99;
// 	arr2[1] = 88;
// 	str = ft_lalloc(3, sizeof(char), head, 2);
// 	printf("str=%p\n", str);
// 	str[0] = 'h';
// 	str[1] = 'i';
// 	str[2] = '\0';
// 	for (int i = 0; i < 5; i++)
// 		printf("arr[i]=%d\n", arr[i]);
// 	ft_lfree(head, 0);
// 	for (int j = 0; j < 2; j++)
// 		printf("arr[j]=%d\n", arr2[j]);
// 	ft_lfree(head, 1);
// 	printf("%s\n", str);
// 	ft_lfree(head, 2);
// 	ft_lfree(head, ALL);
// 	printf("size in test:%d\n", ft_lstsize(*head));
// 	return ;
// }

// void	test_struct(t_list **head)
// {
// 	t_inner	*indata;
// 	t_test	*test;

// 	indata = ft_lalloc(1, sizeof(t_inner), head, 0);
// 	indata->in_char_arr = ft_lalloc(3, sizeof(char), head, 1);
// 	indata->in_char_arr[0] = 'h';
// 	indata->in_char_arr[1] = 'i';
// 	indata->in_char_arr[2] = '\0';
// 	//!
// 	indata->in_int_arr = ft_lalloc(3, sizeof(int), head, 2);
// 	indata->in_int_arr[0] = 1;
// 	indata->in_int_arr[1] = 2;
// 	indata->in_int_arr[2] = 3;
// 	//!
// 	test = ft_lalloc(1, sizeof(t_test), head, 3);
// 	printf("test=%p\n", test);
// 	test->in = indata;
// 	test->char_arr = ft_lalloc(3, sizeof(char), head, 4);
// 	printf("test-char_arr=%p\n", test->char_arr);
// 	test->char_arr[0] = 'H';
// 	test->char_arr[1] = 'i';
// 	test->char_arr[2] = '\0';
// 	//!
// 	test->int_arr = ft_lalloc(3, sizeof(int), head, 5);
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
// 	printf("size in test struct beg= %d\n", ft_lstsize(*head));
// 	ft_lfree(head, 4);
// 	ft_lfree(head, 0);
// 	ft_lfree(head, 5);
// 	ft_lfree(head, 3);
// 	printf("size in test struct mid= %d\n", ft_lstsize(*head));
// 	ft_lfree(head, 2);
// 	ft_lfree(head, 1);
// 	ft_lfree(head, ALL);
// 	printf("size in test struct end= %d\n", ft_lstsize(*head));
// 	ft_lalloc_destroy(*head);
// }

// int main (void)
// {
// 	t_list *head;

// 	head = ft_lalloc_init();
// 	printf("head address =%p\n", head);
// 	test(&head);
// 	test_struct(&head);
// 	printf("listNum=%d\n", ft_lstsize(head));
// 	// ft_lalloc_destroy(head);
// 	printf("listNum=%d\n", ft_lstsize(head));
// 	system("leaks -q a.out");
// 	return (0);
// }