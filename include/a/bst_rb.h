/*!
 @file bst_rb.h
 @brief red–black self-balancing binary search tree
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef LIBA_BST_RB_H
#define LIBA_BST_RB_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_BST_RB red–black binary search tree
 @{
*/

// clang-format off
#if !defined A_BST_RB_ROOT
#define A_BST_RB_ROOT {A_NULL}
#endif /* A_BST_RB_ROOT */
// clang-format on

#define A_BST_RB_R 0 //!< red
#define A_BST_RB_B 1 //!< black

/*!
 @brief instance structure for red–black binary search tree node
*/
typedef struct a_bst_rb_s
{
    /*!< pointer to left child or NULL */
    struct a_bst_rb_s *left;
    /*!< pointer to right child or NULL */
    struct a_bst_rb_s *right;
    /*!< pointer to parent combined with the color. The mapping is: 0 => red, 1 => black.
     The rest of the bits are the pointer to the parent node. It must be 2-byte aligned,
     and it will be NULL if this is the root node and therefore has no parent.
    */
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
    a_uptr_t parent;
#else /* !A_SIZE_VPTR */
    struct a_bst_rb_s *parent;
    a_uint_t color;
#endif /* A_SIZE_VPTR */
} a_bst_rb_s;

/*!
 @brief access parent of red–black binary search tree node
 @param[in] node points to red–black binary search tree node
 @return a pointer to the parent of the specified red–black tree node,
 or NULL if it is already the root of the tree.
*/
A_INTERN a_bst_rb_s *a_bst_rb_parent(a_bst_rb_s const *const node)
{
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
    return a_cast_r(a_bst_rb_s *, node->parent & ~a_uptr_c(1));
#else /* !A_SIZE_VPTR */
    return node->parent;
#endif /* A_SIZE_VPTR */
}

/*!
 @brief initialize function for red–black binary search tree node
 @param[in] node node to be initialized
 @param[in] parent node parent
 @return initialized node
*/
A_INTERN a_bst_rb_s *a_bst_rb_init(a_bst_rb_s *const node, a_bst_rb_s *const parent)
{
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
    node->parent = a_cast_r(a_uptr_t, parent);
#else /* !A_SIZE_VPTR */
    node->color = A_BST_RB_R;
    node->parent = parent;
#endif /* A_SIZE_VPTR */
    node->right = A_NULL;
    node->left = A_NULL;
    return node;
}

/*!
 @brief instance structure for red–black binary search tree root
*/
typedef union a_bst_rb_u
{
    struct a_bst_rb_s *node; //!< root node
} a_bst_rb_u;

/*!
 @brief initialize function for red–black binary search tree root
 @param[in,out] root red–black binary search tree root
*/
A_INTERN a_void_t a_bst_rb_root(a_bst_rb_u *const root) { root->node = A_NULL; }

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief access head node of red–black binary search tree in-order
 @param[in] root red–black binary search tree root
 @return head node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_head(a_bst_rb_u const *root);

/*!
 @brief access tail node of red–black binary search tree in-order
 @param[in] root red–black binary search tree root
 @return tail node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_tail(a_bst_rb_u const *root);

/*!
 @brief access next node of red–black binary search tree node in-order
 @param[in] node red–black binary search tree node
 @return next node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_next(a_bst_rb_s *node);

/*!
 @brief access prev node of red–black binary search tree node in-order
 @param[in] node red–black binary search tree node
 @return prev node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_prev(a_bst_rb_s *node);

/*!
 @brief access next node of red–black binary search tree node preorder
 @param[in] node red–black binary search tree node
 @return next node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_pre_next(a_bst_rb_s *node);

/*!
 @brief access prev node of red–black binary search tree node preorder
 @param[in] node red–black binary search tree node
 @return prev node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_pre_prev(a_bst_rb_s *node);

/*!
 @brief access head node of red–black binary search tree postorder
 @param[in] root red–black binary search tree root
 @return head node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_post_head(a_bst_rb_u const *root);

/*!
 @brief access tail node of red–black binary search tree postorder
 @param[in] root red–black binary search tree root
 @return tail node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_post_tail(a_bst_rb_u const *root);

/*!
 @brief access next node of red–black binary search tree node postorder
 @param[in] node red–black binary search tree node
 @return next node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_post_next(a_bst_rb_s *node);

/*!
 @brief access prev node of red–black binary search tree node postorder
 @param[in] node red–black binary search tree node
 @return prev node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_post_prev(a_bst_rb_s *node);

/*!
 @brief tear a node from red–black binary search tree
 @param[in] root red–black binary search tree root
 @param[in,out] next input starting node or,
 if NULL, root node. output next node or NULL.
 @return teared node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_tear(a_bst_rb_u *root, a_bst_rb_s **next);

/*!
 @brief search specified content from red–black binary search tree
 @param[in] root red–black binary search tree root
 @param[in] ctx specified content
 @param[in] cmp a function that compares two nodes
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return specified node or NULL
*/
A_EXTERN a_bst_rb_s *a_bst_rb_search(a_bst_rb_u const *root, a_cptr_t ctx, a_int_t (*cmp)(a_cptr_t, a_cptr_t));

/*!
 @brief insert specified node into red–black binary search tree
 @param[in] root red–black binary search tree root
 @param[in] node specified tree node
 @param[in] cmp a function that compares two nodes
  @arg cmp(lhs,rhs)==0 *lhs is equivalent to *rhs
  @arg cmp(lhs,rhs)<0 *lhs goes before *rhs
  @arg cmp(lhs,rhs)>0 *lhs goes after *rhs
 @return NULL or duplicate node
*/
A_EXTERN a_bst_rb_s *a_bst_rb_insert(a_bst_rb_u *root, a_bst_rb_s *node, a_int_t (*cmp)(a_cptr_t, a_cptr_t));

/*!
 @brief rebalance the tree after insertion of the specified node
 @param[in] root red–black binary search tree root
 @param[in] node insert tree node
*/
A_EXTERN a_void_t a_bst_rb_insert_adjust(a_bst_rb_u *root, a_bst_rb_s *node);

/*!
 @brief remove specified node from red–black binary search tree
 @param[in] root red–black binary search tree root
 @param[in] node specified tree node
*/
A_EXTERN a_void_t a_bst_rb_remove(a_bst_rb_u *root, a_bst_rb_s *node);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief access the struct for this entry
 @param ptr the &a_bst_rb_s pointer
 @param type the type of the struct this is embedded in
 @param member the name of the a_bst_rb_s within the struct
*/
#define a_bst_rb_entry(ptr, type, member) a_container_of(ptr, type, member)

/*!
 @brief iterate over a red–black binary search tree in-order
 @code{.c}
 typedef struct { a_bst_rb_u node; } T;
 a_bst_rb_u root = A_BST_RB_ROOT;
 a_bst_rb_foreach(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_bst_rb_s to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_bst_rb_foreach(cur, root) \
    for (a_bst_rb_s *cur = a_bst_rb_head(root); cur; cur = a_bst_rb_next(cur))

/*!
 @brief iterate over a red–black binary search tree in-order reverse
 @code{.c}
 typedef struct { a_bst_rb_u node; } T;
 a_bst_rb_u root = A_BST_RB_ROOT;
 a_bst_rb_foreach_reverse(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_bst_rb_s to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_bst_rb_foreach_reverse(cur, root) \
    for (a_bst_rb_s *cur = a_bst_rb_tail(root); cur; cur = a_bst_rb_prev(cur))

/*!
 @brief iterate over a red–black binary search tree preorder
 @code{.c}
 typedef struct { a_bst_rb_u node; } T;
 a_bst_rb_u root = A_BST_RB_ROOT;
 a_bst_rb_pre_foreach(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_bst_rb_s to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_bst_rb_pre_foreach(cur, root) \
    for (a_bst_rb_s *cur = (root)->node; cur; cur = a_bst_rb_pre_next(cur))

/*!
 @brief iterate over a red–black binary search tree preorder reverse
 @code{.c}
 typedef struct { a_bst_rb_u node; } T;
 a_bst_rb_u root = A_BST_RB_ROOT;
 a_bst_rb_pre_foreach_reverse(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_bst_rb_s to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_bst_rb_pre_foreach_reverse(cur, root) \
    for (a_bst_rb_s *cur = (root)->node; cur; cur = a_bst_rb_pre_prev(cur))

/*!
 @brief iterate over a red–black binary search tree postorder
 @code{.c}
 typedef struct { a_bst_rb_u node; } T;
 a_bst_rb_u root = A_BST_RB_ROOT;
 a_bst_rb_post_foreach(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_bst_rb_s to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_bst_rb_post_foreach(cur, root) \
    for (a_bst_rb_s *cur = a_bst_rb_post_head(root); cur; cur = a_bst_rb_post_next(cur))

/*!
 @brief iterate over a red–black binary search tree postorder reverse
 @code{.c}
 typedef struct { a_bst_rb_u node; } T;
 a_bst_rb_u root = A_BST_RB_ROOT;
 a_bst_rb_post_foreach_reverse(cur, &root)
 {
     T *it = a_container_of(cur, T, node);
 }
 @endcode
 @param cur the &a_bst_rb_s to use as a loop counter
 @param root red–black binary search tree root
*/
#define a_bst_rb_post_foreach_reverse(cur, root) \
    for (a_bst_rb_s *cur = a_bst_rb_post_tail(root); cur; cur = a_bst_rb_post_prev(cur))

/*! @} A_BST_RB */

#endif /* LIBA_BST_RB_H */
