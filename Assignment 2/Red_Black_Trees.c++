#include <iostream>
using namespace std;
int RED = 0, BLACK = 1;
class Node
{
public:
   double key, color;
   Node *left, *right, *p;
   Node(double key)
   {
       this->key = key;
       this->left = NULL;
       this->right = NULL;
   }
};
class Tree
{
public:
   Node *root;
   Node *nil;
   Tree()
   {
       this->root = NULL;
       this->nil = NULL;
   }
};
// /* --- Insert Operation --- */
void LEFT_ROTATE(Tree *T, Node *x)
{
   Node *y = x->right;
   x->right = y->left;
   if (y->left->key != T->nil->key)
       y->left->p = x;
   y->p = x->p;
   if (x->p->key == T->nil->key)
       T->root = y;
   else if (x == x->p->left)
       x->p->left = y;
   else
       x->p->right = y;
   y->left = x;
   x->p = y;
}
void RIGHT_ROTATE(Tree *T, Node *x)
{
   Node *y = x->left;
   x->left = y->right;
   if (y->right->key != T->nil->key)
       y->right->p = x;
   y->p = x->p;
   if (x->p->key == T->nil->key)
       T->root = y;
   else if (x == x->p->right)
       x->p->right = y;
   else
       x->p->left = y;
   y->right = x;
   x->p = y;
}
void RB_INSERT_FIXUP(Tree *T, Node *z)
{
   while (z != T->root && z->p->color == RED)
   {
       if (z->p == z->p->p->left)
       {
           Node *y = z->p->p->right;
           if (y->color == RED)
           {
               z->p->color = BLACK;
               y->color = BLACK;
               z->p->p->color = RED;
               z = z->p->p;
           }
           else
           {
               if (z == z->p->right)
               {
                   z = z->p;
                   LEFT_ROTATE(T, z);
               }
               z->p->color = BLACK;
               z->p->p->color = RED;
               RIGHT_ROTATE(T, z->p->p);
           }
       }
       else
       {
           Node *y = z->p->p->left;
           if (y->color == RED)
           {
               z->p->color = BLACK;
               y->color = BLACK;
               z->p->p->color = RED;
               z = z->p->p;
           }
           else
           {
               if (z == z->p->left)
               {
                   z = z->p;
                   RIGHT_ROTATE(T, z);
               }
               z->p->color = BLACK;
               z->p->p->color = RED;
               LEFT_ROTATE(T, z->p->p);
           }
       }
   }
   T->root->color = BLACK;
}
void RB_INSERT(Tree *T, Node *z)
{
   Node *x = T->root;
   Node *y = new Node(__DBL_MAX__);
   while (x->key != T->nil->key)
   {
       y = x;
       if (z->key < x->key)
           x = x->left;
       else
           x = x->right;
   }
   z->p = y;
   if (y->key == T->nil->key)
       T->root = z;
   else if (z->key < y->key)
       y->left = z;
   else
       y->right = z;
   z->left = new Node(__DBL_MAX__);
   z->left->p = z;
   z->right = new Node(__DBL_MAX__);
   z->right->p = z;
   z->color = RED;
   z->left->color = BLACK;
   z->right->color = BLACK;
   RB_INSERT_FIXUP(T, z);
}
// /* --- Delete Operation --- */
void RB_TRANSPLANT(Tree *T, Node *u, Node *v)
{
   if (u->p->key == T->nil->key)
       T->root = v;
   else if (u == u->p->left)
       u->p->left = v;
   else
       u->p->right = v;
   v->p = u->p;
}
Node *TREE_MINIMUM(Tree *T, Node *x)
{
   while (x->left->key != T->nil->key)
       x = x->left;
   return x;
}
void RB_DELETE_FIXUP(Tree *T, Node *x)
{
   while (x != T->root && x->color == BLACK)
   {
       if (x == x->p->left)
       {
           Node *w = x->p->right;
           if (w->color == RED)
           {
               w->color == BLACK;
               x->p->color = RED;
               LEFT_ROTATE(T, x->p);
               w = x->p->right;
           }
           if (w->left->color == BLACK && w->right->color == BLACK)
           {
               w->color = RED;
               x = x->p;
           }
           else
           {
               if (w->right->color == BLACK)
               {
                   w->left->color = BLACK;
                   w->color = RED;
                   RIGHT_ROTATE(T, w);
                   w = x->p->right;
               }
               w->color = x->p->color;
               x->p->color = BLACK;
               w->right->color = BLACK;
               LEFT_ROTATE(T, x->p);
               x = T->root;
           }
       }
       else
       {
           Node *w = x->p->left;
           if (w->color == RED)
           {
               w->color == BLACK;
               x->p->color = RED;
               RIGHT_ROTATE(T, x->p);
               w = x->p->left;
           }
           if (w->right->color == BLACK && w->left->color == BLACK)
           {
               w->color = RED;
               x = x->p;
           }
           else
           {
               if (w->left->color == BLACK)
               {
                   w->right->color = BLACK;
                   w->color = RED;
                   LEFT_ROTATE(T, w);
                   w = x->p->left;
               }
               w->color = x->p->color;
               x->p->color = BLACK;
               w->left->color = BLACK;
               RIGHT_ROTATE(T, x->p);
               x = T->root;
           }
       }
   }
   x->color = BLACK;
}
void RB_DELETE(Tree *T, Node *z)
{
   Node *x;
   Node *y = z;
   int y_original_color = y->color;
   if (z->left->key == T->nil->key)
   {
       x = z->right;
       RB_TRANSPLANT(T, z, z->right);
   }
   else if (z->right->key == T->nil->key)
   {
       x = z->left;
       RB_TRANSPLANT(T, z, z->left);
   }
   else
   {
       y = TREE_MINIMUM(T, z->right);
       y_original_color = y->color;
       x = y->right;
       if (y != z->right)
       {
           RB_TRANSPLANT(T, y, y->right);
           y->right = z->right;
           y->right->p = y;
       }
       else
           x->p = y;
       RB_TRANSPLANT(T, z, y);
       y->left = z->left;
       y->left->p = y;
       y->color = z->color;
   }
   if (y_original_color == BLACK)
       RB_DELETE_FIXUP(T, x);
   delete z;
}
/* --- Search Operation --- */
Node *RB_SEARCH(Tree *T, int k)
{
   Node *x = T->root;
   while (x->key != T->nil->key && k != x->key)
   {
       if (k < x->key)
           x = x->left;
       else
           x = x->right;
   }
   return x;
}
/* --- Traverse Operations --- */
char col(int i)
{
   return i ? 'B' : 'R';
}
void preOrder(Tree *T, Node *root)
{
   if (root->key != T->nil->key)
   {
       cout << "(" << root->key << ", " << col(root->color) << ") ";
       preOrder(T, root->left);
       preOrder(T, root->right);
   }
}
void inOrder(Tree *T, Node *root)
{
   if (root->key != T->nil->key)
   {
       inOrder(T, root->left);
       cout << "(" << root->key << ", " << col(root->color) << ") ";
       inOrder(T, root->right);
   }
}
void postOrder(Tree *T, Node *root)
{
   if (root->key != T->nil->key)
   {
       postOrder(T, root->left);
       postOrder(T, root->right);
       cout << "(" << root->key << ", " << col(root->color) << ") ";
   }
}
signed main()
{
   Tree *T = new Tree();
   T->root = new Node(__DBL_MAX__);
   T->nil = new Node(__DBL_MAX__);
   // int n;
   // cin >> n;
   // double arr[n];
   // for (int i = 0; i < n; i++)
   //     cin >> arr[i];
   int n = 12;
   double arr[n] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13, 14};
   for (int i = 0; i < n; i++)
       RB_INSERT(T, new Node(arr[i]));
   cout << "Red-Black Tree:" << endl;
   preOrder(T, T->root);
   cout << endl;
   // int m;
   // cin >> m;
   // double del[m];
   // for (int i = 0; i < m; i++)
   //     cin >> del[i];
   int m = 5;
   double del[m] = {11, 14, 13, 10, 8};
   for (int i = 0; i < m; i++)
   {
       RB_DELETE(T, RB_SEARCH(T, del[i]));
       cout << "After deleting " << del[i] << ": " << endl;
       preOrder(T, T->root);
       cout << endl;
   }
   return 0;
}
/*
12
7 3 18 10 22 8 11 26 2 6 13 14
5
11 14 13 10 8
*/