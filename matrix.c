
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void printMatrix(Matrix *m1, char *msg) {
  warnmsg(msg, KIRMIZI, true);
  for (int i = 0; i < m1->row; i++) {
    for (int j = 0; j < m1->col; j++) {
      printf("%5d ", m1->data[i][j]);
    }
    printf("\n");
  }
}

Matrix *createMatrix(int row, int col) {
  Matrix *matris = (Matrix *)malloc(sizeof(Matrix));
  matris->row = row;
  matris->col = col;

  matris->data = (int **)malloc(sizeof(int *) * row);

  for (int i = 0; i < row; i++) {
    matris->data[i] = (int *)malloc(sizeof(int) * col);
  }

  return matris;
}

void freeMemoryMatrix(Matrix *m1) {
  for (int i = 0; i < m1->row; i++)
    free(m1->data[i]);

  free(m1->data);
  free(m1);
}

void setMatrix(Matrix *m1) {
  for (int i = 0; i < m1->row; i++) {
    for (int j = 0; j < m1->col; j++) {
      printf("Matrix[%d][%d] = ", i + 1, j + 1);
      scanf("%d", &m1->data[i][j]);
    }
  }
}


Matrix *sumMatrix(Matrix *m1, Matrix *m2, int ENUM_TOP_CIK) {
  if (m1->row != m2->row || m2->col != m1->col) {
    if (ENUM_TOP_CIK == TOPLAMA)
      warnmsg("2 MATRISIN BOYUTLARI UYUSMADIGINDAN TOPLAMA YAPILAMAZ ! => nxm "
              "ve nxm OLMALIDIR !",
              KIRMIZI, true);
    if (ENUM_TOP_CIK == CIKARTMA)
      warnmsg("2 MATRISIN BOYUTLARI UYUSMADIGINDAN CIKARTMA YAPILAMAZ ! => nxm "
              "ve nxm OLMALIDIR !",
              KIRMIZI, true);
    return NULL;
  }

  Matrix *sum = createMatrix(m1->row, m2->col);

  for (int i = 0; i < sum->row; i++) {
    for (int j = 0; j < sum->col; j++) {
      if (ENUM_TOP_CIK == CIKARTMA)
        sum->data[i][j] = m1->data[i][j] - m2->data[i][j];

      if (ENUM_TOP_CIK == TOPLAMA)
        sum->data[i][j] = m1->data[i][j] + m2->data[i][j];
    }
  }
  return sum;
}

// 1x3 3x1
// 1 2       7 -5      1*7 + 2*6   1*(-5) + 2*10
// 4 5       6  10     4*7 + 5*6   4*(-5) + 5*10
Matrix *mulMatrix(Matrix *m1, Matrix *m2) {
  if (m1->col != m2->row) {
    warnmsg(
        "MATRISLERDE CARPMA ICIN BOYUTLAR UYUSMUYOR => nxm ve mxn OLMALIDIR !",
        KIRMIZI, true);
    return NULL;
  }

  // birinci matrisin row'u , ikinci matrisin col'u , carpim matrisinin
  // boyutlarini olusturur
  Matrix *mul_matrix = createMatrix(m1->row, m2->col);

  for (int i = 0; i < m1->row; i++) {
    for (int j = 0; j < m2->col; j++) {
      for (int k = 0; k < m1->col; k++) {
        mul_matrix->data[i][j] += m1->data[i][k] * m2->data[k][j];
      }
    }
  }

  return mul_matrix;
}

Matrix *skalerMulMatrix(Matrix *m1, int k) {
  Matrix *skalerMul_matris = createMatrix(m1->row, m1->col);

  for (int i = 0; i < m1->row; i++)
    for (int j = 0; j < m1->col; j++) {
      skalerMul_matris->data[i][j] = m1->data[i][j] * k;
    }

  return skalerMul_matris;
}

Matrix *transposeMatrix(Matrix *m1) {}

// 1 2
// 3 4
// 1*4 - 2*3

double determinantMatrix(Matrix *m1) {
  if (m1->row != m1->col) {
    warnmsg("KARE MATRIS OLMADIGINDAN DOLAYI BU MATRISIN DETERMINANTI "
            "HESAPLANAMAZ !",
            KIRMIZI, true);
    return -1.123987;
  }

  // kofaktore girmeden direkt hesaplayalim
  if (m1->row == 2) {
    return (m1->data[0][0] * m1->data[1][1]) -
           (m1->data[0][1] * m1->data[1][0]);
  }

  return -1.123986;
}

void listMatrixArr(Matrix **addrArr, int createCount) {
  printf("\nOLUSTURDUGUN MATRISLER:\n");
  for (int i = 0; i < createCount; i++) {
    printf("%d-) %p => : %dx%d\n", i, addrArr[i], addrArr[i]->row,
           addrArr[i]->col);
  }
}

void warnmsg(char *msg, int RENK_ENUM, int nl) {
  if (RENK_ENUM == YESIL && nl == true)
    printf("\n\033[32m%s\033[0m\n", msg);
  if (RENK_ENUM == KIRMIZI && nl == true)
    printf("\n\033[31m%s\033[0m\n", msg);
  if (RENK_ENUM == MAVI && nl == true)
    printf("\n\033[34m%s\033[0m\n", msg);

  if (RENK_ENUM == YESIL && nl == false)
    printf("\033[32m%s\033[0m", msg);
  if (RENK_ENUM == KIRMIZI && nl == false)
    printf("\033[31m%s\033[0m", msg);
  if (RENK_ENUM == MAVI && nl == false)
    printf("\033[34m%s\033[0m", msg);
}

void freeAllMemoryMatrix(Matrix **addrArr, int *arr_len) {
  for (int i = 0; i < *arr_len; i++) {
    freeMemoryMatrix(addrArr[i]);
  }
  for (int j = 0; j < *arr_len; j++) {
    addrArr[j] = NULL;
    *arr_len = 0;
  }
}

void redirectingProcess(Matrix **addrArr, int *createCount, int *isRedirecting,
                        int *menuNo, Matrix *eklenecekMatris) {
  addrArr[(*createCount)++] = eklenecekMatris;
  *menuNo = 6;
  *isRedirecting = true;

  warnmsg("SONUC MATRISININ NUMARASI", YESIL, false);
  printf(" %d", (*createCount) - 1);
  warnmsg("-) \nMATRIS BASTIRMA MENUSUNE YONLENDIRILIYORSUNUZ !", KIRMIZI,
          false);
  warnmsg("MATRIS NUMARASINI GIREREK SONUC MATRISINI EKRANA BASTIRIN", MAVI,
          true);
}