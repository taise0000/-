// arrayobj.c //
// C言語でJavascriptのような配列オブジェクト機能を作成


/*************************************************************************************************************/
/* 今回のarrayobj.cでは、末尾に実体を持たないポインタ構造体変数を設定し、そのnextをNULLに設定します。                      */
/* よって先頭のアドレスを持つポインタ構造体変数"a"のnextがNULLの時、その1つ前のデータが末尾の要素を持っていることを判定できます。*/
/*************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// ここに、自分で考えた構造体の定義を記述します
struct aobj{
  long element;
  struct aobj *next;
};

// 次の4つの関数は、プロトタイプ宣言は、そのまま変更せず、
// これらに合致するように関数を作成してください
//
// 初期化の関数のプロトタイプ宣言
struct aobj *aobj_init();
//
// 配列の末尾に要素を追加する関数のプロトタイプ宣言
// 追加する要素を第2引数に入れて関数を呼び出す
struct aobj *aobj_push(struct aobj *a, long item);
//
// // 配列の末尾の要素を削除する関数のプロトタイプ宣言
// // 削除される要素を第2引数に入れ、その後でその要素を削除する
struct aobj *aobj_pop(struct aobj *a, long *item);
// //
// // 要素の個数を返す関数のプロトタイプ宣言
// // 個数を返せる場合は関数の値として1を返し、エラーの場合は0を返す
// // 個数は第2引数に入れる
// // 配列の要素の個数が0の場合には，関数の値として1が返り，個数には0が入る
int aobj_len(struct aobj *a, unsigned int *len);

/*****************************************************/
/* データinit関数  struct aobj *aobj_init()            */
/* 機能：配列の先頭を実データの無いポインタ構造体変数に設定    */
/* 引数：なし                                          */
/*****************************************************/

struct aobj *aobj_init(){

  //先頭に設定するための実体の無いポインタ構造体変数を宣言
  struct aobj *head;

  //メモリの確保
  head = (struct aobj *)malloc(sizeof(struct aobj));

  //次のデータは無いので、nextにはNULLをセット。
  head->next = NULL;

  //処理を行ったheadを返り値とする
  return head;
}

/*****************************************************************************/
/* データPush関数  struct aobj *aobj_push( struct aobj *a, long item)         */
/* 機能：引数で受け取ったitemを，新しくHeapメモリを取得し，配列の末尾に繋げる．         */
/* 引数：struct  aobj   *a            :  配列の先頭データアドレス                 */
/*              long   item          :  配列の末尾にpushするデータ               */
/*****************************************************************************/

struct aobj *aobj_push(struct aobj *a, long item){

  //データを追加するためのポインタ構造体変数を宣言
  struct aobj *newNodePos;

  //メモリの確保
  if ((newNodePos = (struct aobj *)malloc(sizeof(struct aobj))) == NULL){
    printf("malloc error\n");
    exit(EXIT_FAILURE);
  }

  //次のデータは無いので、nextにはNULLをセット。
  newNodePos->next = NULL;

  //末尾にセットするためにa->nextがNULLになるまでループ
  for (; a->next != NULL; a = a->next);

  //第2引数itemをelementに代入
  a->element = item;

  //nextに実体の無いnewNodeposを設定
  a->next = newNodePos;

  return 0;
}

/***************************************************************************/
/* データpop関数  struct aobj * aobj_pop( struct aobj *a, long *item)        */
/* 機能：配列の末尾の要素を第2引数に入れ、その後でその要素を削除する．                */
/* 引数：struct  aobj   *a            :  配列の先頭データアドレス               */
/*              long   *item         :  削除する要素を入れる変数               */
/***************************************************************************/

struct aobj *aobj_pop(struct aobj *a, long *item){

  //末尾を探すためににa->nextがNULLになるまでループ
  for (; a->next != NULL; a = a->next);

  //配列の末尾の1つ前の要素をitemに代入
  *item = (a - 1)->element;

  //配列の末尾の1つ前のnextに末尾のnextをに設定
  (a - 1)->next = a->next;

  //メモリを解放して要素を削除
  free(a - 1);

  return 0;
}

/****************************************************************************/
/* データlen関数  int aobj * aobj_len(struct aobj * a, unsigned int *len)     */
/* 機能：要素の個数を返す関数、要素は第2引数に入れる．                               */
/* 個数を返せる場合は関数の値として1を返し、エラーの場合は0を返す                      */
/*配列の要素の個数が0の場合には，関数の値として1が返り，個数には0が入る                 */
/* 引数：struct  aobj   *a            :  配列の先頭データアドレス                 */
/*      unsigned int   *len          :  要素の個数を入れる変数のアドレス          */
/****************************************************************************/

int aobj_len(struct aobj *a, unsigned int *len){

  //ループカウンターiを宣言&初期化
  unsigned int i = 0;

  //末尾までの要素数を見るためにa->nextがNULLになるまでループ
  for (; a->next != NULL; a = a->next)
    i++;

  *len = i;
  if (i != 0){
    return 1;
  }else{
    return 0;
  }
}

#define MAXINPUT 10

int main(void){
  struct aobj *myobj;
  char input[MAXINPUT];
  char *ret;
  long num, lastone;
  unsigned int len;

  myobj = aobj_init();
  // 数値の入力の繰り返し

  for (;;){
    ret = fgets(input, MAXINPUT, stdin);
    if (ret == NULL){
      break;
    }
    ret = strchr(input, '\n');
    if (ret != NULL){
      *ret = '\0';
    }else{
      while (getchar() != '\n');
    }
    num = strtol(input, NULL, 10);
    aobj_push(myobj, num);
  }
  // 長さの表示
  aobj_len(myobj, &len);
  printf("len = %u\n", len);
  // 最後の要素の削除と長さの表示
  aobj_pop(myobj, &lastone);
  aobj_len(myobj, &len);
  printf("remove %ld, len = %u\n", lastone, len);
  // もう一度、最後の要素の削除と長さの表示
  aobj_pop(myobj, &lastone);
  aobj_len(myobj, &len);
  printf("remove %ld, len = %u\n", lastone, len);
  exit(0);
}
