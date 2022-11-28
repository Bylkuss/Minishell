/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainTest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 07:57:45 by gehebert          #+#    #+#             */
/*   Updated: 2021/10/06 07:30:01 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int main(void)
{
	// var.
	char **xab;
	//char sep;
	int test;
	char *answer;
    int i,a;
    int j,b;
    int num;
    char *str;
    char *newb;
    //size_t *news;
    char sts[20];
    char star[20];
    char newstr[20];
    char *s;
    char s1[30];
    char s2[30];
    char ss[30];
    int rep;  // retour-reponse
    char *rp;  // retour-reponse pointeur
    i = 2;
    j = 3;
    char arr[i][j];
    
	test = ft_isalpha('i');  // test isalpha
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is alpha %s\n", test, answer);
	test = ft_isalpha('A');  // test isalpha
	if (test == 0)
	answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is alpha %s\n", test, answer); 	
	test = ft_isalpha('3');  // test isalpha
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is alpha %s\n", test, answer);
	test = ft_isdigit('3');         //  test isdigit
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is digit  %s\n", test, answer);
	test = ft_isdigit('b');         //  test isdigit
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is digit  %s\n", test, answer);
	test = ft_isalnum('3');         // test isalnum
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is  alnum %s\n", test, answer); 
 	test = ft_isalnum('b');             // test isalnum
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is alnum  %s\n", test, answer);
	test = ft_isalnum(' ');             // test isalnum
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is alnum  %s\n", test, answer);
	test = ft_isascii(129);                 //  test isascii
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is ascii  %s\n", test, answer);
	test = ft_isascii(87);              //  test isascii
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is ascii  %s\n", test, answer);
	test = ft_isascii(40);              //  test isascii
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is ascii  %s\n", test, answer);
	test = ft_isprint(129);                 // test isprint
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is print  %s\n", test, answer);
	test = ft_isprint(87);              // test isprint
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is print  %s\n", test, answer);
	test = ft_isprint(25);              // test isprint
	if (test == 0)
		answer = "NO";
	else 
		answer = "YES";
	printf(" %d Is print %s\n", test, answer);
                                        // test ft_strlen
        str = "alloblublu000";
        num = ft_strlen(str);
        printf("_%s_  long string: %d\n", str, num);
        strcpy(newstr,"alloblublu");
        printf(" %s\n", newstr);
                                        // test ft_memset
        ft_memset(newstr+6, 'x', 4);
        printf(" memset depass %s\n", newstr);
        memset(newstr+6, 'x', 4);
        printf("Off memset depass %s\n\n", newstr);
        	                             //  test b zero
        ft_bzero(newstr, 12);
        ft_bzero(star, 12);
                                        //    test ft_memcpy
        strcpy(star,"123456789");
        strcpy(newstr,"abcdef");
        printf("\norigine STR: %s\n", star);
        printf("origine NEWSTR: %s\n", newstr);
        ft_memcpy(newstr+2, star,4);
        printf("ft_memcpy__ %s__\n", newstr);
                                        // compare to memcpy
        strcpy(star,"123456789");
        strcpy(newstr,"abcdef");
        printf("origine STR: %s\n", star);
        printf("origine NEWSTR: %s\n", newstr);
        memcpy(newstr+2, star, 4);
        printf("memcpy__ %s__\n\n ", newstr);
                                        //   initialize str...
        ft_bzero(newstr, 12);
        ft_bzero(star, 12);
                                        // test ft_memmove
        strcpy(star,"123456789");
        strcpy(newstr,"abcdef");
        printf("origine STR: %s\n", star);
        printf("origine NEWSTR: %s\n", newstr);
        ft_memmove(newstr+2, star, 9);
        printf("ft_memmove__ %s__\n\n", newstr);
                                    //   compare  to memmove
        strcpy(star,"123456789");
        strcpy(newstr,"abcdef");
        printf("origine STR: %s\n", star);
        printf("origine NEWSTR: %s\n", newstr);
        memmove(newstr+2, star, 9);
        printf("memmove__ %s__\n\n", newstr);
                                        //  insert ft_calloc...
        strcpy(star,"111111");
        strcpy(newstr,"");
        printf("star fill with 1...%s\n", star);
        printf("newstr nonefill __%s__\n",newstr);
        ft_calloc(i, j);
        for (a = 1; a <= i; a++)  {
            for (b = 1; b <= j; b++) {
                printf("test calloc_%d_", arr[i][j]);
            }
            printf("\n");
        }
                                      		  // test ft_substr
        printf("fill with ...%s\n", star);
        newb = ft_substr(str, 5, 7);
        printf("newstr newValue Set __%s__\n", newb);
  										  //    test_ ft_strlcat ...
        strcpy(sts,"123456789");
        strcpy(newstr,"abcdef");
        ft_strlcat(newstr, sts, 3);
        printf("\n ft_strlcat:::sts %s, newstr %s\n", sts, newstr);
//
        strcpy(sts,"123456789");
        strcpy(newstr,"abcdef");
        printf("\n OFF sts %s, newstr %s\n", sts, newstr);
		
 		strlcat(newstr, sts, 3);
	    printf("\n strlcat  %s, newstr %s\n", sts, newstr);
  		
  		 								 //    test_ ft_strlcpy ...
        strcpy(sts,"123456789");
        strcpy(newstr,"abcdef");
        ft_strlcpy(newstr, sts, 2);
        printf("\n ---strlcpysts %s, newstr %s\n", sts, newstr);
//
        strcpy(sts,"123456789");
        strcpy(newstr,"abcdef");
       // strlcpy(newstr, sts, 11);
        printf("\n OFF str %s, newstr %s\n", sts, newstr);
								   			 // test___ toupper - tolower
         num = ft_toupper('a');
        printf("  %c\n", num);
        num = ft_tolower('A');
        printf("  %c\n", num);
   										 // test ---  strchr - strrchr
        strcpy(sts,"Allo, Champion");
        s = ft_strrchr(sts, 'o');
        printf("test _last_ strrchr next pos is:%s\n", (s+1));
		s = strchr(sts, 'o');
		printf("test NEW_ strchr : %s\n", (s));
		
        strcpy(sts,"Allo, Champion");
        s = ft_strchr(sts, 'o');
        printf("next pos _first_test strchr is:%s\n", (s));
   										 // string to compare
        strcpy(s1,"allo, champion");
        strcpy(s2,"allo, Champion");
        strcpy(ss,"pi");
        strcpy(ss,"-a22");
										    // test ft_strncmp
        rep = ft_strncmp(s1, s2, 5);
        printf("Rep = %d\n",rep);
									        // test strncmp
        rep = strncmp(s1, s2, 5);
        printf("Off.Rep = %d\n",rep);
   										 // test ft_memcmp
	    rep = ft_memcmp(s1, s2, 9);
        printf("memcmp Rep = %d\n",rep);
								        // test memcmp
        rep = memcmp(s1, s2, 9);
        printf("Off.memcmp Rep = %d\n",rep);
   										 // test ft_memchr
		rp = ft_memchr(s1, 'p', 12);
        printf("memchr Rep = %s\n",rp);
								        // test strncmp
        rp = memchr(s1, 'p', 12);
        printf("Off. memchr Rep = %s\n",rp);
   									 // test ft_strnstr
        rp = ft_strnstr(s1, ss, 12);
        printf("Rep = %s\n",rp);
								        // test strnstr
     //   rp = strnstr(s1, ss, 12);
        printf("Off. strnstr Rep = %s\n",rp);
   									 //test atoi  --- ft_atoi
		strcpy(ss,"99999999999999999999999999");
											 
        rep = atoi(ss);
        printf("string = %s  , Int = %d\n",ss , rep);
        rep = ft_atoi(ss);
        printf("ft_atoi %d\n", rep);
                                            //   test ft_strjoin
        strcpy(s1,"xoxxAllo, champion, ");
        strcpy(s2,"...Bien, bravoxo");
        newb = ft_strjoin(s1, s2);
        printf("RESULTAT: %s\n", newb);
          									  // test ft_strtrim
        answer = ft_strtrim(newb, "xo");
        printf("TRIMD RESULTAT: %s\n", answer);
    										 //   test ft_split
		printf("\n ft_split new testi\n");
		strcpy(answer, "        ");		
        xab = ft_split(answer, ' ');
        i = 0;
		printf("test split , , , __\n");
        while (xab[i] != NULL)
        {
            printf(":: _ %s __%d\n", xab[i], i);
            i ++;        
		}
        while (xab[i])
        {
            free(xab[i]);
            i++;        
		}
        free(xab);
											//  ft_itoa
		printf("\nft_itoa -> %s\n", ft_itoa(-19));

							// ft_strmapi.c    link my_func remove from libft-makefile
		strcpy(sts, "germainh");
 		printf("The result is %s\n", sts);
 		printf("The result is %s\n", ft_strmapi(sts, mapi_f)); 		
		//		test ft_striteri
		strcpy(sts, "gErmAin");
		ft_striteri(sts, it_t); 	
		printf("\n  test Iteri >> \n%s__ \n", sts); 

	//   test ft_put_fd ......ish
		strcpy(ss, "ALLOCATION:");
		printf("_putchar_ ");
	   	ft_putchar_fd('+', 1);
		printf("_putstr_");
		ft_putstr_fd(ss, 1);
		ft_putendl_fd(ss, 1);
		printf("[ft_putnbr_fd]\n");
		ft_putnbr_fd(-31416, 1);//FT_PUTNBR_FD	
		printf("\n");
		printf("\n");
		printf("[expected]\n");
		printf("-31416\n");	

		printf("\n-----------end of Mandatory part -----\n");
}
