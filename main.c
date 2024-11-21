#include <stdio.h>
#include "matrix.h"

int main() {
  int menuNo = 0;

  char *menuMsg =
      "\n<--->MENU<--->\n1-MATRIS OLUSTUR\n2-MATRIS SIL\n3-MATRIS TOPLAMA\n4-MATRIS CARP\n\
5-MATRIS DETERMINANTI BUL\n6-MATRIS BASTIR\n7-MATRIS AYARLA\n8-MATRIS CIKARTMA\n9-SKALER CARPIM\n\
10-MATRIS TRANSPOZE\n11-EXIT\n";

  int isDelete = true;
  int isRedirecting = false;

  int row = 0, col = 0;
  int createCount = 0;
  Matrix *addrArr[10];

  while (true) {

    if (isRedirecting == false) {
      warnmsg(menuMsg, MAVI, true);
      printf(">>>");
      scanf("%d", &menuNo);
    }

    switch (menuNo) {

    case MATRIS_CREATE: {
      printf("ROW AND COL >>");
      scanf("%d %d", &row, &col);

      Matrix *m1 = createMatrix(row, col);

      addrArr[createCount++] = m1;
      // olusturulan her matrisin adresini tutan array

      warnmsg("MATRIS OLUSTURULDU !", YESIL, true);
      isDelete = false;
      break;
    }

    case MATRIS_DELETE: {
      if (isDelete == true) {
        warnmsg("MATRIS OLUSTURMADAN SILEMEZSIN !", KIRMIZI, true);
        continue;
      }
      freeAllMemoryMatrix(addrArr, &createCount);

      warnmsg("TUM MATRISLER SILINDI !", YESIL, true);
      isDelete = true;
      break;
    }

    case MATRIS_SUM: {
      listMatrixArr(addrArr, createCount);
      printf("HANGI MATRISLERI TOPLAMAK ISTIYORSUN >>>");
      int m1_index = 0, m2_index = 0;
      scanf("%d %d", &m1_index, &m2_index);
      Matrix *m1 = addrArr[m1_index], *m2 = addrArr[m2_index];
      Matrix *sum_matris = sumMatrix(m1, m2, TOPLAMA);

      if (sum_matris != NULL) {
        redirectingProcess(addrArr, &createCount, &isRedirecting, &menuNo,
                           sum_matris);
        break;
      }
      warnmsg("MATRIS TOPLAMADA HATA !", KIRMIZI, true);
      break;
    }

    case MATRIS_MUL: {
      listMatrixArr(addrArr, createCount);
      printf("HANGI MATRISLERI CARPMAK ISTIYORSUN >>>");
      int m1_index = 0, m2_index = 0;
      scanf("%d %d", &m1_index, &m2_index);
      Matrix *m1 = addrArr[m1_index], *m2 = addrArr[m2_index];

      Matrix *mul_matris = mulMatrix(m1, m2);
      if (mul_matris == NULL) {
        warnmsg("MATRIS CARPIMINDA HATA !", KIRMIZI, true);
        continue;
      }
      redirectingProcess(addrArr, &createCount, &isRedirecting, &menuNo,
                         mul_matris);
      break;
    }

    case MATRIS_DETERMINANT: {
      listMatrixArr(addrArr, createCount);
      printf("HANGI MATRISIN DETERMINANTINI HESAPLAMAK ISTIYORSUN >>>");
      int m1_index = 0;
      scanf("%d", &m1_index);
      Matrix *m1 = addrArr[m1_index];
      double det_m1 = determinantMatrix(m1);

      if (det_m1 == -1.123986) {
        warnmsg("SIMDILIK SADECE 2x2 MATRISLERDE CALISIYOR !", KIRMIZI, true);
        continue;
      }

      warnmsg("\nDETERMINANT :", YESIL, false);
      printf(" %lf\n", det_m1);
      break;
    }

    case MATRIS_PRINT: {
      if (createCount == 0) {
        warnmsg("DAHA MATRIS OLUSTURMADINIZ !", KIRMIZI, true);
        continue;
      }

      if (isRedirecting == true)
        isRedirecting = false;

      listMatrixArr(addrArr, createCount);
      int matrixSelect = 0;
      printf("BASTIRILACAK MATRISI SEC >> ");
      scanf("%d", &matrixSelect);
      printMatrix(addrArr[matrixSelect], "\nSECILEN MATRIS\n");

      break;
    }

    case MATRIS_SET: {
      if (createCount == 0) {
        warnmsg("DAHA MATRIS OLUSTURMADINIZ !", YESIL, true);
        continue;
      }

      listMatrixArr(addrArr, createCount);
      int matrixSelect = 0;

      printf("AYARLAMAK ISTEDIGINIZ MATRISI SEC >> ");
      scanf("%d", &matrixSelect);
      setMatrix(addrArr[matrixSelect]);

      break;
    }

    case MATRIS_SUB: {
      listMatrixArr(addrArr, createCount);
      printf("HANGI MATRISLERI CIKARTMAK ISTIYORSUN >>>");
      int m1_index = 0, m2_index = 0;
      scanf("%d %d", &m1_index, &m2_index);
      Matrix *m1 = addrArr[m1_index], *m2 = addrArr[m2_index];
      Matrix *sub_matris = sumMatrix(m1, m2, CIKARTMA);

      if (sub_matris != NULL) {
        redirectingProcess(addrArr, &createCount, &isRedirecting, &menuNo,
                           sub_matris);
      }
      warnmsg("MATRIS CIKARTMADA HATA !", KIRMIZI, true);
      break;
    }

    case MATRIS_SKALER_MUL: {
      listMatrixArr(addrArr, createCount);
      printf("HANGI MATRISI HANGI SKALERLE CARPMAK ISTIYORSUN >>>");
      int m1_index = 0, k = 0;
      scanf("%d %d", &m1_index, &k);
      Matrix *m1 = addrArr[m1_index];
      Matrix *skaler_mul = skalerMulMatrix(m1, k);
      redirectingProcess(addrArr, &createCount, &isRedirecting, &menuNo,
                         skaler_mul);
      break;
    }

    case MATRIS_TRANSPOZE: {

      break;
    }

    case EXIT: {
      if (isDelete == false) {
        freeAllMemoryMatrix(addrArr, &createCount);
        warnmsg("SILMEYI UNUTTUGUN BELLEK BOLGESI OTOMATIK SILINDI !", KIRMIZI,
                true);
      }
      warnmsg("CIKIS YAPILDI !", YESIL, true);
      return 0x0;
    }
    }
  }

  return 0x1;
}