#include <stdio.h>
#include <stdlib.h>


struct tree {
  struct tree *l;
  int v;
  struct tree *r;
  int h;
};

typedef struct tree tree_t;

int count;

/**
 * @param t: 木
 * @description: tが根の木の高さを返す関数
 */
int tree_height(tree_t *t){
  if(t == NULL) return 0;
  int leftHeight = tree_height(t -> l);
  int rightHeight = tree_height(t -> r);
  if(leftHeight > rightHeight) {
    return leftHeight + 1;
  } else {
    return rightHeight +1;
  }
}

/*
  2分探索木 l の要素は必ず v より小さい
  2分探索木 r の要素は必ず v より大きい
*/
/**
 * @param l: rootの左側につく木
 * @param v: 新しい数字
 * @param r: rootの右側につく木
 * @description: 新しいnodeを生成し、その左にlを、右にrを入れた木を作る。返り値は根のポインタ
 */
tree_t *tree_create(tree_t *l, int v, tree_t *r){
  int height = 0;
  int lheight = tree_height(l);
  int rheight = tree_height(r);
  if(lheight > rheight) {
    height = lheight + 1;
  } else {
    height = rheight + 1;
  }
  tree_t *root = malloc(sizeof(tree_t));
  root -> l = l;
  root -> v = v;
  root -> r = r;
  root -> h = height;
  return root;
}

void tree_free(tree_t *t){
  if(t != NULL){
    free(t);
    count--;
  }
}

/**
 * @param t: 木
 * @description: 木に含まれている数字の個数を出力する関数
 */
int tree_size(tree_t *t) {
  if(t == NULL) return 0;
  if(t -> h == 1) return 1;
  return tree_size(t -> r) + tree_size(t ->l) + 1;
}

/**
 * @param t: 木
 * @description: 木に含まれている数字を小さい順に出力する関数
 */
void tree_print_elements(tree_t *t){
  if(t == NULL) return;
  tree_print_elements(t -> l);
  printf("%d\n",t -> v);
  tree_print_elements(t -> r);
}

/*
  tree_height(l) <= tree_height(r) + 2 &&
  tree_height(r) <= tree_height(l) + 2
  が true であると仮定してよい
*/
/*
発展的課題
tree_t *tree_bal(tree_t *l, int v, tree_t *r) {
}
*/

/**
 * @param x: 調
 * @param t: 木
 * @description: tの中にxが関数含まれていれば1、なければ0を返す
 */
int tree_mem(int x, tree_t *t){
  if(t == NULL) return 0;
  if((t -> v) == x) return 1;
  //再帰処理
  if((t -> v) > x) {
    return tree_mem(x,t -> l);
  } else {
    return tree_mem(x, t -> r);
  }
}

/**
 * @param x: 付け加える数字
 * @param t: 木
 * @description: tにxを付け加え、その根を返す。元から含まれていれば引数tと等しいものを返す。
 *  全て再生成しているのでメモリに注意
 */
tree_t *tree_add(int x, tree_t *t) {
  if(t == NULL) return tree_create(NULL,x,NULL);
  if(t -> v == x) return t;
  if(t -> v > x) {
    return tree_create(tree_add(x, t -> l), t -> v, t -> r);
  } else {
    return tree_create(t -> l, t -> v, tree_add(x, t -> r));
  }
}

/**
 * @param t: 木
 * @description: tに含まれる最小値を返す
 */
int tree_min(tree_t *t){
  while((t -> l) != NULL) {
    t = (t -> l);
  }
  return t -> v;
}

/**
 * @param t: 木
 * @description: tに含まれる最大値を返す。
 */
int tree_max(tree_t *t){
  while((t -> r) != NULL) {
    t = (t -> r);
  }
  return t -> v;
}

/**
 * @param t: 木
 * @description: tに含まれる最小値を除去する関数。返り値は最小の数字を除去した後の木の根
 */
tree_t *tree_remove_min(tree_t *t){
  if(t -> l != NULL) return tree_create(tree_remove_min(t -> l), t-> v, t -> r);
  if(t -> r != NULL) return tree_create(t -> r -> l, t -> r -> v, t ->r -> r);
  return NULL;
}

/**
 * @param t1,t2: 木。t1の要素は必ずt2の要素より小さい
 * @description: t1,t2の要素をすべて持つ木を返す。
 */
tree_t *tree_merge(tree_t *t1, tree_t *t2){
  if(t2 == NULL) return t1;
  return tree_create(t1, tree_min(t2),tree_remove_min(t2));
}

/**
 * @param x: 除去する値
 * @param t: 木
 * @description: 指定された値を消す関数。除去した後の木を返す。
 */
tree_t *tree_remove(int x, tree_t *t){
  if(t == NULL) return t;
  if(t -> v == x) {
    return tree_merge(t -> l, t -> r);
  } else if(t -> v > x) {
    return tree_create(tree_remove(x, t->l),t -> v, t -> r);
  } else {
    return tree_create(t -> r, t -> v, tree_remove(x, t -> r));
  }

}

//自作関数

/*
平衡性のチェック(発展的課題)
int tree_check(tree_t *t){
  if(t == NULL) return 1;
  return tree_height(t->l) <= tree_height(t->r)+1 &&
  tree_height(t->r) <= tree_height(t->l)+1 && tree_check(t->l) && tree_check(t->r);
}
*/

int main(){
  int i;
  tree_t *t = NULL;

  for(i = 0; i < 7919; i++){
    t = tree_add(i*4000 % 7919, t);
  }

  tree_print_elements(t);

// サイズが7919かチェック
  printf("size = %d\n", tree_size(t));

  for(i = 0; i < 7919; i++){
    t = tree_remove(i*5000 % 7919, t);
  }

  tree_print_elements(t);
// サイズが0かチェック
  printf("size = %d\n", tree_size(t));

/*
//  平衡性のチェック
  for(i = 0; i < 100000; i++) {
    int rnd = rand()%1000;
    if(rand() % 2)
      t = tree_remove(rnd, t);
    else
      t = tree_add(rnd, t);
    if(!tree_check(t)) puts("ERROR");
  }

//  確保しているノードの領域の数と木のサイズが一致するかチェック
  printf("count = %d\n", count);
  printf("size = %d\n", tree_size(t));
*/
 

  return 0;
}
