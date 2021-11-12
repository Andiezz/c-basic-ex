#include "baitap7.h"

long bn_xdist(bn_tree_t t, bn_node_t n){
    long x = 0;
    bn_node_t tmp = n;
    if(n == t->root){
        return x;
    }
    while(tmp != t->root){
        if(tmp == tmp->top->left){
            x = x - 1;
        }
        else if(tmp == tmp->top->right){
            x = x + 1;
        }
        tmp = tmp->top;
    }
    return x;
}

int bn_is_bns(bn_tree_t t){
  bn_traverse_lnr(cur, t){
    if(t->root->left == NULL && t->root->right == NULL){
      return 1;
    }
    if(gtype_cmp_i(bns_node_g_key(cur), bns_node_g_key(cur->left)) < 0){
      return 0;
    }
    else if(gtype_cmp_i(bns_node_g_key(cur), bns_node_g_key(cur->right)) > 0){
      return 0;
    }
  }
  return 1;
}

bn_node_t bn_lca(bn_node_t n1, bn_node_t n2){
  if(n1->top == NULL || n2->top == NULL){
    return NULL;
  }
  if(n1->top == n2->top){
    return n1->top;
  }
  else if(bn_distance(n1) < bn_distance(n2)){
    bn_lca(n1, n2->top);
  }
  else if(bn_distance(n1) > bn_distance(n2)){
    bn_lca(n1->top, n2);
  }
  else if(bn_distance(n1) == bn_distance(n2)){
    bn_lca(n1->top, n2->top);
  }
}

bn_tree_t bns_parse_arri(int *a, size_t n){
  bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_i);
  int i = n / 2;
  int x = i, y = i;
  for(int j = 0; j < i / 2; j++){
    bns_insert_g(t, a[x++]);
    bns_insert_g(t, a[y--]);
  }
  return t;
}