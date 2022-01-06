/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chiffre.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 21:50:36 by jcluzet           #+#    #+#             */
/*   Updated: 2022/01/06 19:45:05 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define SECONDS 20
#define MAXMOVES 5

int findanother(int min, int max, int *skip)
{
    int find;
    find = -1;
    while (find == -1 || skip[find] == 1)
    {
        find = rand() % (max - min + 1) + min;
    }
    return (find);
}

int possible(int *nb, int n, int p)
{
    time_t starttime = time(NULL);
    time_t seconds = SECONDS;
    time_t endtime = starttime + seconds;
    int nb1;
    int nb2;
    int count;
    int spino = 0;
    int lasti = 0;
    int oper;
    char *str;
    clock_t target;
    char spin[] = "\\|/-";
    char buffer[6][300];
    int res[6] = {0, 0, 0, 0, 0, 0};

    int i;
    count = 0;
    printf("\n");
    if (nb[0] == 0 && nb[1] == 0 && nb[2] == 0 && nb[3] == 0 && nb[4] == 0 && nb[5] == 0)
        return (0);
    while (1)
    {
        i = 0;
        int v;
        int c;
        char str[10000];
        res[0] = 0;
        res[1] = 0;
        res[2] = 0;
        res[3] = 0;
        res[4] = 0;
        res[5] = 0;
        v = rand() % (5 - 0 + 1) + 0;
        i = nb[v];
        res[v] = 1;
        c = 0;
        while (1)
        {
            v = findanother(0, 5, res);
            nb2 = nb[v];
            res[v] = 1;
            oper = rand() % (4 - 1 + 1) + 1;
            // printf("i = %d\nrand = %d\n", i, oper);
            if (oper == 1)
            {
                snprintf(buffer[c], sizeof(buffer[c]), "%d + %d = %d\n", i, nb2, i + nb2);
                i = i + nb2;
                c++;
            }
            else if (oper == 2)
            {
                snprintf(buffer[c], sizeof(buffer[c]), "%d - %d = %d\n", i, nb2, i - nb2);
                i = i - nb2;
                c++;
            }
            else if (oper == 3)
            {
                if (nb2 != 0)
                {
                    snprintf(buffer[c], sizeof(buffer[c]), "%d * %d = %d\n", i, nb2, i * nb2);
                    i = i * nb2;
                    c++;
                }
                else
                    res[nb2] = 0;
            }
            else if (oper == 4)
            {
                if (nb2 != 0)
                {
                    snprintf(buffer[c], sizeof(buffer[c]), "%d / %d = %d\n", i, nb2, i / nb2);
                    i = i / nb2;
                    c++;
                }
                else
                    res[nb2] = 0;
            }
            if ((i == n || (res[0] == 1 && res[1] == 1 && res[2] == 1 && res[3] == 1 && res[4] == 1 && res[5] == 1)) || c == p)
            {
                starttime = time(NULL);
                if (starttime > endtime)
                {
                    printf("\bCan't find with %d Moves.\n", p);
                    return (0);
                }
                if (count % 500 == 0)
                {
                    if (spino == 5)
                        spino = 0;
                    printf("\b%c", spin[spino]);
                    spino++;
                }
                count++;
                if (i == n && c == p)
                {
                    i = 0;
                    printf("\bFIND ! \n");
                    while (i < p)
                    {
                        printf("%s", buffer[i]);
                        i++;
                    }
                    return (1);
                }
                buffer[0][0] = '\0';
                buffer[1][0] = '\0';
                buffer[2][0] = '\0';
                buffer[3][0] = '\0';
                buffer[4][0] = '\0';
                buffer[5][0] = '\0';
                break;
            }
        }
    }
}

int *genere(int n, int argc, char **argv)
{
    int nb[6] = {0, 0, 0, 0, 0, 0};
    int tofind = MAXMOVES;
    while (1)
    {
        srand(time(NULL));
        if (argc > 1)
        {
            // argv to int in nb[0] to nb[5]
            int i;
            for (i = 0; i < 6; i++)
            {
                nb[i] = atoi(argv[i + 1]);
            }
        }
        else
        {
            nb[0] = (rand() % (30 - 1 + 1) + 1);
            nb[1] = (rand() % (30 - 1 + 1) + 1);
            nb[2] = (rand() % (30 - 1 + 1) + 1);
            nb[3] = (rand() % (60 - 1 + 1) + 1);
            nb[4] = (rand() % (100 - 1 + 1) + 1);
            nb[5] = (rand() % (100 - 1 + 1) + 1);
        }
        printf("NUMBER : %d %d %d %d %d %d \n\n", nb[0], nb[1], nb[2], nb[3], nb[4], nb[5]);
        if (argc == 1)
        {
            printf("Please touch a key to generate the result\n");
            getchar();
        }
        while (1)
        {
            if (tofind < 1)
                return (0);
            printf("\n\nNOW SEARCHING %d MOVES...\n", tofind);
            if (possible(nb, n, tofind) == -1)
                return (0);
            tofind--;
        }
        break;
    }
    // printf("%d %d %d %d %d %d\n", nb[0], nb[1], nb[2], nb[3], nb[4], nb[5]);
    return (0);
}

int main(int argc, char **argv)
{
    int numbertofind;
    int *nb;
    // generator of  a random numer
    if (argc > 1)
    {
        if (argc != 8)
        {
            printf("Please enter 6 numbers + the number to find\n");
            return (0);
        }
    }
    while (1)
    {
        srand(time(NULL));
        if (argc > 1)
            numbertofind = atoi(argv[7]);
        else
            numbertofind = (rand() % (1000 - 0 + 1) + 0);
        if (argc == 1)
        {
            printf("Please touch a key to generate the problem\n");
            getchar();
        }
        printf("\n\nNUMBER TO FIND : %d\n", numbertofind);
        nb = genere(numbertofind, argc, argv);
        break;
    }
    return (0);
}
