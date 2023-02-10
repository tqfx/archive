/*!
 @file avl.h
 @brief Adelson-Velsky and Landis binary search tree
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef LIBA_AVL_H
#define LIBA_AVL_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_AVL AVL binary search tree
 @{
*/

/*!
 @brief instance structure for AVL binary search tree node
*/
typedef struct a_avl_s
{
    /*!< pointer to left child or NULL */
    struct a_avl_s *left;
    /*!< pointer to right child or NULL */
    struct a_avl_s *right;
    /*!< pointer to parent combined with the balance factor
     Low 2 bits: One greater than the balance factor of this subtree,
     which is equal to height(right) - height(left). The mapping is:
     00 => -1
     01 =>  0
     10 => +1
     11 => undefined
     The rest of the bits are the pointer to the parent node. It must be 4-byte aligned,
     and it will be NULL if this is the root node and therefore has no parent.
    */
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 3)
    a_uptr_t parent;
#else /* !A_SIZE_VPTR */
    struct a_avl_s *parent;
    a_int_t factor;
#endif /* A_SIZE_VPTR */
} a_avl_s;

/*!
 @brief access parent of AVL binary search tree node
 @param[in] node points to AVL binary search tree node
 @return a pointer to the parent of the specified AVL tree node,
         or NULL if it is already the root of the tree.
*/
A_INTERN a_avl_s *a_avl_parent(const a_avl_s *node)
{
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 3)
    return a_cast_r(a_avl_s *, node->parent & ~a_uptr_c(3));
#else /* !A_SIZE_VPTR */
    return node->parent;
#endif /* A_SIZE_VPTR */
}

/*!
 @brief initialize function for AVL binary search tree node
 @param[in] node node to be initialized
 @param[in] parent node parent
 @return initialized node
*/
A_INTERN a_avl_s *a_avl_init(a_avl_s *node, a_avl_s *parent)
{
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 3)
    node->parent = a_cast_r(a_uptr_t, parent) | 1;
#else /* !A_SIZE_VPTR */
    node->parent = parent;
    node->factor = 0;
#endif /* A_SIZE_VPTR */
    node->right = A_NULL;
    node->left = A_NULL;
    return node;
}

#if !defined A_AVL_NIL
// clang-format off
#define A_AVL_NIL {A_NULL}
// clang-format on
#endif /* A_AVL_NIL */

/*!
 @brief instance structure for AVL binary search tree root
*/
typedef union a_avl_u
{
    struct a_avl_s *node; //!< root node
} a_avl_u;

/*!
 @brief initialize function for AVL binary search tree root
 @param[in,out] root AVL binary search tree root
*/
A_INTERN a_void_t a_avl_nil(a_avl_u *root) { root->node = A_NULL; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief access head node of AVL binary search tree in-order
 @param[in] root AVL binary search tree root
 @return head node or NULL
*/
A_EXTERN a_avl_s *a_avl_head(const a_avl_u *root);

/*!
 @brief access tail node of AVL binary search tree in-order
 @param[in] root AVL binary search tree root
 @return tail node or NULL
*/
A_EXTERN a_avl_s *a_avl_tail(const a_avl_u *root);

/*!
 @brief access next node of AVL binary search tree node in-order
 @param[in] node AVL binary search tree node
 @return next node or NULL
*/
A_EXTERN a_avl_s *a_avl_next(a_avl_s *node);

/*!
 @brief access prev node of AVL binary search tree node in-order
 @param[in] node AVL binary search tree node
 @return prev node or NULL
*/
A_EXTERN a_avl_s *a_avl_prev(a_avl_s *node);

/*!
 @brief access next node of AVL binary search tree node preorder
 @param[in] node AVL binary search tree node
 @return next node or NULL
*/
A_EXTERN a_avl_s *a_avl_pre_next(a_avl_s *node);

/*!
 @brief access prev node of AVL binary search tree node preorder
 @param[in] node AVL binary search tree node
 @return prev node or NULL
*/
A_EXTERN a_avl_s *a_avl_pre_prev(a_avl_s *node);

/*!
 @brief access head node of AVL binary search tree postorder
 @param[in] root AVL binary search tree root
 @return head node or NULL
*/
A_EXTERN a_avl_s *a_avl_post_head(const a_avl_u *root);

/*!
 @brief access tail node of AVL binary search tree postorder
 @param[in] root AVL binary search tree root
 @return tail node or NULL
*/
A_EXTERN a_avl_s *a_avl_post_tail(const a_avl_u *root);

/*!
 @brief access next node of AVL binary search tree node postorder
 @param[in] node AVL binary search tree node
 @return next node or NULL
*/
A_EXTERN a_avl_s *a_avl_post_next(a_avl_s *node);

/*!
 @brief access prev node of AVL binary search tree node postorder
 @param[in] node AVL binary search tree node
 @return prev node or NULL
*/
A_EXTERN a_avl_s *a_avl_post_prev(a_avl_s *node);

/*!
 @brief tear a node from AVL binary search tree
 @param[in] root AVL binary search tree root
 @param[in,out] next input starting node or,
 if NULL, root node. output next node or NULL.
 @return teared node or NULL
*/
A_EXTERN a_avl_s *a_avl_tear(a_avl_u *root, a_avl_s **next);

/*!
 @brief search specified content from AVL binary search tree
 @param[in] root AVL binary search tree root
 @param[in] ctx specified content
 @param[in] cmp a function that compares two nodes
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return specified node or NULL
*/
A_EXTERN a_avl_s *a_avl_search(const a_avl_u *root, a_cptr_t ctx, a_int_t (*cmp)(a_cptr_t, a_cptr_t));

/*!
 @brief insert specified node into AVL binary search tree
 @param[in] root AVL binary search tree root
 @param[in] node specified tree node
 @param[in] cmp a function that compares two nodes
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return NULL or duplicate node
*/
A_EXTERN a_avl_s *a_avl_insert(a_avl_u *root, a_avl_s *node, a_int_t (*cmp)(a_cptr_t, a_cptr_t));

/*!
 @brief rebalance the tree after insertion of the specified node
 @param[in] root AVL binary search tree root
 @param[in] node insert tree node
*/
A_EXTERN a_void_t a_avl_insert_adjust(a_avl_u *root, a_avl_s *node);

/*!
 @brief remove specified node from AVL binary search tree
 @param[in] root AVL binary search tree root
 @param[in] node specified tree node
*/
A_EXTERN a_void_t a_avl_remove(a_avl_u *root, a_avl_s *node);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief iterate over a AVL binary search tree in-order
 @code{.c}
 typedef struct { a_avl_u node; } T;
 a_avl_u root = A_AVL_NIL;
 a_avl_foreach(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_avl_s to use as a loop counter
 @param root AVL binary search tree root
*/
#define a_avl_foreach(cur, root) \
    for (a_avl_s *cur = a_avl_head(root); cur; cur = a_avl_next(cur))

/*!
 @brief iterate over a AVL binary search tree in-order reverse
 @code{.c}
 typedef struct { a_avl_u node; } T;
 a_avl_u root = A_AVL_NIL;
 a_avl_foreach_reverse(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_avl_s to use as a loop counter
 @param root AVL binary search tree root
*/
#define a_avl_foreach_reverse(cur, root) \
    for (a_avl_s *cur = a_avl_tail(root); cur; cur = a_avl_prev(cur))

/*!
 @brief iterate over a AVL binary search tree preorder
 @code{.c}
 typedef struct { a_avl_u node; } T;
 a_avl_u root = A_AVL_NIL;
 a_avl_pre_foreach(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_avl_s to use as a loop counter
 @param root AVL binary search tree root
*/
#define a_avl_pre_foreach(cur, root) \
    for (a_avl_s *cur = (root)->node; cur; cur = a_avl_pre_next(cur))

/*!
 @brief iterate over a AVL binary search tree preorder reverse
 @code{.c}
 typedef struct { a_avl_u node; } T;
 a_avl_u root = A_AVL_NIL;
 a_avl_pre_foreach_reverse(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_avl_s to use as a loop counter
 @param root AVL binary search tree root
*/
#define a_avl_pre_foreach_reverse(cur, root) \
    for (a_avl_s *cur = (root)->node; cur; cur = a_avl_pre_prev(cur))

/*!
 @brief iterate over a AVL binary search tree postorder
 @code{.c}
 typedef struct { a_avl_u node; } T;
 a_avl_u root = A_AVL_NIL;
 a_avl_post_foreach(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_avl_s to use as a loop counter
 @param root AVL binary search tree root
*/
#define a_avl_post_foreach(cur, root) \
    for (a_avl_s *cur = a_avl_post_head(root); cur; cur = a_avl_post_next(cur))

/*!
 @brief iterate over a AVL binary search tree postorder reverse
 @code{.c}
 typedef struct { a_avl_u node; } T;
 a_avl_u root = A_AVL_NIL;
 a_avl_post_foreach_reverse(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_avl_s to use as a loop counter
 @param root AVL binary search tree root
*/
#define a_avl_post_foreach_reverse(cur, root) \
    for (a_avl_s *cur = a_avl_post_tail(root); cur; cur = a_avl_post_prev(cur))

/*! @} A_AVL */

#endif /* LIBA_AVL_H */
