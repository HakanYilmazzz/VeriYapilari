#include <stdio.h>
#include <stdlib.h>

void dizi_yaz(int *dizi, int size)
{

    int i;
    for (i = 0; i < size; i++)
        printf("%4d", *(dizi + i));
    printf("\n\n");
}

void dizi_yaz1(int (*dizi)[2], int row, int column)
{

    int i, j;
    for (i = 0; i < row; i++)
    {

        for (j = 0; j < column; j++)
        {

            printf("%20d", *(*(dizi + i) + j));
            //  printf("%4d",dizi[i][j]); //aynı
        }

        printf("\n");
    }
}

void dizi_yaz2(int (*dizi)[3][5], int size)
{

    int i, j, k;
    for (i = 0; i < size; i++)
    {

        for (j = 0; j < 3; j++)
        {

            for (k = 0; k < 5; k++)
                printf("%4d", dizi[i][j][k]);
            printf("\n");
        }

        printf("\n");
    }
}

void matris_carpimi(int A[][3], int A_satir, int A_sutun,
                    int B[][2], int B_satir, int B_sutun,
                    int C[][2], int C_satir, int C_sutun)
{
    int i, j, k;

    if (A_sutun != B_satir)
    {

        printf("Carpim matrislerinin boyutlari uyusmuyor!!!");
        return;
    }

    else if (A_satir != C_satir || B_sutun != C_sutun)
    {

        printf("Sonuc matrisinin boyutlari carpan matrislere uymuyor!!!\n");
        return;
    }

    else
    {

        for (i = 0; i < A_satir; i++)
        {

            for (j = 0; j < B_sutun; j++)
            {

                C[i][j] = 0;
                for (k = 0; k < A_sutun; k++)
                {

                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                }

                printf("%4d", C[i][j]);
            }

            printf("\n");
        }
    }
}

int main(int argc, char **argv)
{
    int A[] = {0, 1, 12, 33, 4, 5, 6, 7, 8, 9};

    int B[][5] = {{0, 1, 2, 3, 4},
                  {10, 877, 12, 13, 14},
                  {20, 21, 22, 23, 24},
                  {30, 31, 32, 33, 34}};

    int C[2][3][5] = {{{0, 11, 2, 3, 4}, {10, 877, 12, 13, 14}, {20, 21, 22, 23, 24}},
                      {{0, 1, 2, 3, 4}, {10, 877, 152, 13, 14}, {20, 21, 22, 23, 274}}};

    int AA[][3] = {{1, 8, 1},
                   {2, 1, 4},
                   {5, 1, 0},
                   {1, 2, 3}};

    int BB[][2] = {{0, 1},
                   {2, 4},
                   {3, 9}};

    int CC[4][3];

    dizi_yaz(&C[0][0][0], 7);

    //    dizi_yaz1(CC,4,2);

    //    dizi_yaz2(C+1, 1);

    //    matris_carpimi(AA,4,3,BB,3,2,CC,4,2);

    return (EXIT_SUCCESS);
}
