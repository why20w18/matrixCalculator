#ifndef __MATRIX_H__
#define __MATRIX_H__

#define true 1
#define false 0

enum MENU_SECENEK {
  MATRIS_CREATE = 1,
  MATRIS_DELETE,
  MATRIS_SUM,
  MATRIS_MUL,
  MATRIS_DETERMINANT,
  MATRIS_PRINT,
  MATRIS_SET,
  MATRIS_SUB,
  MATRIS_SKALER_MUL,
  MATRIS_TRANSPOZE,
  EXIT,
  YESIL,
  KIRMIZI,
  MAVI
};

enum SUM_SUB_DURUM{ 
    TOPLAMA = 1, 
    CIKARTMA 
};

typedef struct {
  int **data;
  int row;
  int col;
} Matrix;


void warnmsg(char *msg, int RENK_ENUM, int nl);
void printMatrix(Matrix *m1, char *msg);
Matrix *createMatrix(int row, int col);
void freeMemoryMatrix(Matrix *m1);
void setMatrix(Matrix *m1);
Matrix *sumMatrix(Matrix *m1, Matrix *m2, int ENUM_TOP_CIK);
Matrix *mulMatrix(Matrix *m1, Matrix *m2);
Matrix *skalerMulMatrix(Matrix *m1, int k);
Matrix *transposeMatrix(Matrix *m1);
double determinantMatrix(Matrix *m1);
void listMatrixArr(Matrix **addrArr, int createCount);
void freeAllMemoryMatrix(Matrix **addrArr, int *arr_len);
void redirectingProcess(Matrix **addrArr, int *createCount, int *isRedirecting,int *menuNo, Matrix *eklenecekMatris);


#endif