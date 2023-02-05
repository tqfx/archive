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
     which is equal to height(right) - height(left).  The mapping is:
     00 => -1
     01 =>  0
     10 => +1
     11 => undefined
     The rest of the bits are the pointer to the parent node. It must be 4-byte aligned,
     and it will be NULL if this is the root node and therefore has no parent.
    */
    a_uptr_t parent;
} a_avl_s;

/*!
 @brief instance structure for AVL binary search tree root
*/
typedef union a_avl_u
{
    struct a_avl_s *node;
} a_avl_u;

/*!
 @brief access parent of AVL tree node
 @param[in] node points to AVL tree node
 @return a pointer to the parent of the specified AVL tree node,
         or NULL if it is already the root of the tree.
*/
A_INTERN a_avl_s *a_avl_parent(const a_avl_s *node)
{
    return a_cast_r(a_avl_s *, node->parent & ~a_uptr_c(3));
}

/*!
 @brief initialize function for AVL tree node
 @param[in] node node to be initialized
 @param[in] parent node parent
 @return initialized node
*/
A_INLINE a_avl_s *a_avl_init(a_avl_s *node, a_avl_s *parent)
{
    node->parent = a_cast_r(a_uptr_t, parent) | 1;
    node->right = A_NULL;
    node->left = A_NULL;
    return node;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN a_avl_s *a_avl_head(a_avl_u *root);
A_EXTERN a_avl_s *a_avl_tail(a_avl_u *root);
A_EXTERN a_avl_s *a_avl_next(a_avl_s *node);
A_EXTERN a_avl_s *a_avl_prev(a_avl_s *node);

A_EXTERN a_void_t a_avl_insert_rebalance(a_avl_u *root, a_avl_s *node);
A_EXTERN a_avl_s *a_avl_insert(a_avl_u *root, a_avl_s *node, a_int_t (*cmp)(a_cptr_t, a_cptr_t));
A_EXTERN a_avl_s *a_avl_search(const a_avl_u *root, const a_avl_s *node, a_int_t (*cmp)(a_cptr_t, a_cptr_t));
A_EXTERN a_void_t a_avl_remove(a_avl_u *root, a_avl_s *node);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_AVL */

#endif /* LIBA_AVL_H */
