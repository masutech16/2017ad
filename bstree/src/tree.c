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
tree_t *tree_create(tree_t *l, int v, tree_t *r){
  int height = 0;
  int lheight = tree_height(l);
  int rheight = tree_height(r);
  if(lheight > rheight) {
    height = lheight + 1;
  } else {
    height = rheight + 1;
  }
  tree_t *root = malloc(sizeof tree_t);
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

int tree_mem(int x, tree_t *t){
  if(t == NULL) return 0;
  if((t -> v) == d) return 1;
  //再帰処理
  if((t -> v) > x) {
    return tree_mem(x,t -> l);
  } else {
    return tree_mem(x, t -> r);
  }
}

tree_t *tree_add(int x, tree_t *t) {
  if(t == NULL) {
    tree_t *root = tree_create(NULL,x,NULL);
    return root;
  }
  if((t -> v) == d) return t;
  if((t -> v) > x) {
    t -> l = tree_add((t -> l),x);
    return t;
  } else {
    t -> r = tree_add((t -> r),x);
    return t;
  }
}

int tree_min(tree_t *t){
  while((t -> l) != NULL) {
    t = (t -> l);
  }
  return t -> v;
}

int tree_max(tree_t *t){
  while((t -> r) != NULL) {
    t = (t -> r);
  }
  return t -> v;
}

tree_t *tree_remove_min(tree_t *t){
  tree_t *tmp = t;
  while((tmp -> l) != NULL){
    tmp = tmp -> l;
  }
  free(tmp);
  return t;
}

/*
  2分探索木 t1 の要素は必ず2分探索木 t2 の要素より小さい
*/
tree_t *tree_merge(tree_t *t1, tree_t *t2){
  tree_t *tmp = t2;
  while((t2 -> l) != NULL) {
    tmp = t2 -> l;
  }
  tmp -> l = t1;
}

tree_t *tree_remove(int x, tree_t *t){
  if(!tree_mem(x,t)) return t;
  tree_t parent = t;
  //if((t -> v) == x)//rootでヒットする場合はレアケースなのでとりあえず放置
  while(t -> v != x) {
    parent = t;
    if((t -> v) > x) {
      t = t -> l;
    } else {
      t = t -> r;
    }
  }
  if((parent -> l -> v))
}

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
