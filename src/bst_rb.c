#include "a/bst_rb.h"

/* Sets the parent and color of the specified red–black tree node. */
static A_INLINE a_void_t a_bst_rb_set_parent_color(a_bst_rb_s *const node, a_bst_rb_s *const parent, a_uint_t const color)
{
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
    node->parent = (a_uptr_t)parent | color;
#else /* !A_SIZE_VPTR */
    node->parent = parent;
    node->color = color;
#endif /* A_SIZE_VPTR */
}

/* Sets the parent of the specified red–black tree node. */
static A_INLINE a_void_t a_bst_rb_set_parent(a_bst_rb_s *const node, a_bst_rb_s *const parent)
{
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
    node->parent = (a_uptr_t)parent | (node->parent & 1);
#else /* !A_SIZE_VPTR */
    node->parent = parent;
#endif /* A_SIZE_VPTR */
}

/* Returns the color of the specified red–black tree node. */
static A_INLINE a_uint_t a_bst_rb_color(a_bst_rb_s const *const node)
{
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
    return (a_uint_t)(node->parent & 1);
#else /* !A_SIZE_VPTR */
    return node->color;
#endif /* A_SIZE_VPTR */
}

/* Sets the black color of the specified red–black tree node. */
static A_INLINE a_void_t a_bst_rb_set_black(a_bst_rb_s *const node)
{
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
    node->parent |= A_BST_RB_B;
#else /* !A_SIZE_VPTR */
    node->color = A_BST_RB_B;
#endif /* A_SIZE_VPTR */
}

static A_INLINE a_void_t a_bst_rb_mod_child(a_bst_rb_u *const root, a_bst_rb_s *const parent, a_bst_rb_s *const oldnode, a_bst_rb_s *const newnode)
{
    if (parent)
    {
        if (parent->left == oldnode)
        {
            parent->left = newnode;
        }
        else
        {
            parent->right = newnode;
        }
    }
    else
    {
        root->node = newnode;
    }
}

/*
Helper function for rotations:
 - old's parent and color get assigned to new
 - old gets assigned new as a parent and 'color' as a color.
*/
static A_INLINE a_void_t a_bst_rb_set_parents(a_bst_rb_u *const root, a_bst_rb_s *const oldnode, a_bst_rb_s *const newnode, a_uint_t const color)
{
    a_bst_rb_s *const parent = a_bst_rb_parent(oldnode);
    newnode->parent = oldnode->parent;
    a_bst_rb_set_parent_color(oldnode, newnode, color);
    a_bst_rb_mod_child(root, parent, oldnode, newnode);
}

a_void_t a_bst_rb_insert_adjust(a_bst_rb_u *const root, a_bst_rb_s *node)
{
    for (a_bst_rb_s *parent = a_bst_rb_parent(node), *gparent, *tmp;;)
    {
        /* Loop invariant: node is red. */
        if (a_unlikely(!parent))
        {
            /*
            The inserted node is root. Either this is the first node,
            or we recursed at Case 1 below and are no longer violating 4).
            */
            a_bst_rb_set_parent_color(node, A_NULL, A_BST_RB_B);
            break;
        }

        /*
        If there is a black parent, we are done. Otherwise, take some corrective action as, per 4),
        we don't want a red root or two consecutive red nodes.
        */
        if (a_bst_rb_color(parent) == A_BST_RB_B)
        {
            break;
        }

        gparent = a_bst_rb_parent(parent);

        tmp = gparent->right;
        if (parent != tmp) /* parent == gparent->left */
        {
            if (tmp && a_bst_rb_color(tmp) == A_BST_RB_R)
            {
                /*
                Case 1 - node's uncle is red (color flips).

                        G            g
                       / \          / \
                      p   u  -->   P   U
                     /            /
                    n            n

                However, since g's parent might be red, and 4) does not allow this, we need to recurse at g.
                */
                a_bst_rb_set_parent_color(tmp, gparent, A_BST_RB_B);
                a_bst_rb_set_parent_color(parent, gparent, A_BST_RB_B);
                node = gparent;
                parent = a_bst_rb_parent(node);
                a_bst_rb_set_parent_color(node, parent, A_BST_RB_R);
                continue;
            }

            tmp = parent->right;
            if (node == tmp)
            {
                /*
                Case 2 - node's uncle is black and node is the parent's right child (left rotate at parent).

                      G             G
                     / \           / \
                    p   U  -->    n   U
                     \           /
                      n         p

                This still leaves us in violation of 4), the continuation into Case 3 will fix that.
                */
                tmp = node->left;
                parent->right = tmp;
                node->left = parent;
                if (tmp)
                {
                    a_bst_rb_set_parent_color(tmp, parent, A_BST_RB_B);
                }
                a_bst_rb_set_parent_color(parent, node, A_BST_RB_R);
                // a_bst_augment_rotate(parent, node);
                parent = node;
                tmp = node->right;
            }

            /*
            Case 3 - node's uncle is black and node is
            the parent's left child (right rotate at gparent).

                    G           P
                   / \         / \
                  p   U  -->  n   g
                 /                 \
                n                   U
            */
            gparent->left = tmp; /* == parent->right */
            parent->right = gparent;
            if (tmp)
            {
                a_bst_rb_set_parent_color(tmp, gparent, A_BST_RB_B);
            }
            a_bst_rb_set_parents(root, gparent, parent, A_BST_RB_R);
            break;
        }
        else
        {
            tmp = gparent->left;
            if (tmp && a_bst_rb_color(tmp) == A_BST_RB_R)
            {
                /* Case 1 - color flips */
                a_bst_rb_set_parent_color(tmp, gparent, A_BST_RB_B);
                a_bst_rb_set_parent_color(parent, gparent, A_BST_RB_B);
                node = gparent;
                parent = a_bst_rb_parent(node);
                a_bst_rb_set_parent_color(node, parent, A_BST_RB_R);
                continue;
            }

            tmp = parent->left;
            if (node == tmp)
            {
                /* Case 2 - right rotate at parent */
                tmp = node->right;
                parent->left = tmp;
                node->right = parent;
                if (tmp)
                {
                    a_bst_rb_set_parent_color(tmp, parent, A_BST_RB_B);
                }
                a_bst_rb_set_parent_color(parent, node, A_BST_RB_R);
                parent = node;
                tmp = node->left;
            }

            /* Case 3 - left rotate at gparent */
            gparent->right = tmp; /* == parent->left */
            parent->left = gparent;
            if (tmp)
            {
                a_bst_rb_set_parent_color(tmp, gparent, A_BST_RB_B);
            }
            a_bst_rb_set_parents(root, gparent, parent, A_BST_RB_R);
            break;
        }
    }
}

a_bst_rb_s *a_bst_rb_insert(a_bst_rb_u *const root, a_bst_rb_s *const node, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    a_bst_rb_s **link = &root->node;
    a_bst_rb_s *parent = root->node;
    while (*link)
    {
        parent = *link;
        a_int_t const res = cmp(node, parent);
        if (res < 0)
        {
            link = &parent->left;
        }
        else if (res > 0)
        {
            link = &parent->right;
        }
        else
        {
            return parent;
        }
    }
    *link = a_bst_rb_init(node, parent);
    a_bst_rb_insert_adjust(root, node);
    return A_NULL;
}

a_bst_rb_s *a_bst_rb_search(a_bst_rb_u const *const root, a_cptr_t const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    for (a_bst_rb_s *cur = root->node; cur;)
    {
        a_int_t const res = cmp(ctx, cur);
        if (res < 0)
        {
            cur = cur->left;
        }
        else if (res > 0)
        {
            cur = cur->right;
        }
        else
        {
            return cur;
        }
    }
    return A_NULL;
}

static A_INLINE a_void_t a_bst_rb_remove_adjust(a_bst_rb_u *const root, a_bst_rb_s *node, a_bst_rb_s *parent)
{
    for (a_bst_rb_s *sibling, *tmp1, *tmp2;;)
    {
        /*
        Loop invariants:
         - node is black (or NULL on first iteration)
         - node is not the root (parent is not NULL)
         - All leaf paths going through parent and node have a
           black node count that is 1 lower than other leaf paths.
        */
        sibling = parent->right;
        if (node != sibling) /* node == parent->left */
        {
            if (a_bst_rb_color(sibling) == A_BST_RB_R)
            {
                /*
                Case 1 - left rotate at parent

                      P               S
                     / \             / \
                    N   s    -->    p   Sr
                       / \         / \
                      Sl  Sr      N   Sl
                */
                tmp1 = sibling->left;
                parent->right = tmp1;
                sibling->left = parent;
                a_bst_rb_set_parent_color(tmp1, parent, A_BST_RB_B);
                a_bst_rb_set_parents(root, parent, sibling, A_BST_RB_R);
                sibling = tmp1;
            }
            tmp1 = sibling->right;
            if (!tmp1 || a_bst_rb_color(tmp1) == A_BST_RB_B)
            {
                tmp2 = sibling->left;
                if (!tmp2 || a_bst_rb_color(tmp2) == A_BST_RB_B)
                {
                    /*
                    Case 2 - sibling color flip (p could be either color here)

                         (p)           (p)
                         / \           / \
                        N   S    -->  N   s
                           / \           / \
                          Sl  Sr        Sl  Sr

                    This leaves us violating 5) which can be fixed by flipping p to black if it was red,
                    or by recursing at p. p is red when coming from Case 1.
                    */
                    a_bst_rb_set_parent_color(sibling, parent, A_BST_RB_R);
                    if (a_bst_rb_color(parent) == A_BST_RB_R)
                    {
                        a_bst_rb_set_black(parent);
                    }
                    else
                    {
                        node = parent;
                        parent = a_bst_rb_parent(node);
                        if (parent)
                        {
                            continue;
                        }
                    }
                    break;
                }
                /*
                Case 3 - right rotate at sibling (p could be either color here)

                     (p)           (p)
                     / \           / \
                    N   S    -->  N   sl
                       / \             \
                      sl  Sr            S
                                         \
                                          Sr

                Note: p might be red, and then both p and sl are red after rotation(which breaks property 4).
                This is fixed in Case 4 (in a_bst_rb_set_parents() which set sl the color of p and set A_BST_RB_B)

                     (p)            (sl)
                     / \            /  \
                    N   sl   -->   P    S
                         \        /      \
                          S      N        Sr
                           \
                            Sr
                */
                tmp1 = tmp2->right;
                sibling->left = tmp1;
                tmp2->right = sibling;
                parent->right = tmp2;
                if (tmp1)
                {
                    a_bst_rb_set_parent_color(tmp1, sibling, A_BST_RB_B);
                }
                tmp1 = sibling;
                sibling = tmp2;
            }
            /*
            Case 4 - left rotate at parent + color flips (p and sl could be either color here.
            After rotation, p becomes black, s acquires p's color, and sl keeps its color)

                 (p)             (s)
                 / \             / \
                N   S     -->   P   Sr
                   / \         / \
                 (sl) sr      N  (sl)
            */
            tmp2 = sibling->left;
            parent->right = tmp2;
            sibling->left = parent;
            a_bst_rb_set_parent_color(tmp1, sibling, A_BST_RB_B);
            if (tmp2)
            {
                a_bst_rb_set_parent(tmp2, parent);
            }
            a_bst_rb_set_parents(root, parent, sibling, A_BST_RB_B);
            break;
        }
        else
        {
            sibling = parent->left;
            if (a_bst_rb_color(sibling) == A_BST_RB_R)
            {
                /* Case 1 - right rotate at parent */
                tmp1 = sibling->right;
                parent->left = tmp1;
                sibling->right = parent;
                a_bst_rb_set_parent_color(tmp1, parent, A_BST_RB_B);
                a_bst_rb_set_parents(root, parent, sibling, A_BST_RB_R);
                sibling = tmp1;
            }
            tmp1 = sibling->left;
            if (!tmp1 || a_bst_rb_color(tmp1) == A_BST_RB_B)
            {
                tmp2 = sibling->right;
                if (!tmp2 || a_bst_rb_color(tmp2) == A_BST_RB_B)
                {
                    /* Case 2 - sibling color flip */
                    a_bst_rb_set_parent_color(sibling, parent, A_BST_RB_R);
                    if (a_bst_rb_color(parent) == A_BST_RB_R)
                    {
                        a_bst_rb_set_black(parent);
                    }
                    else
                    {
                        node = parent;
                        parent = a_bst_rb_parent(node);
                        if (parent)
                        {
                            continue;
                        }
                    }
                    break;
                }
                /* Case 3 - left rotate at sibling */
                tmp1 = tmp2->left;
                sibling->right = tmp1;
                tmp2->left = sibling;
                parent->left = tmp2;
                if (tmp1)
                {
                    a_bst_rb_set_parent_color(tmp1, sibling, A_BST_RB_B);
                }
                tmp1 = sibling;
                sibling = tmp2;
            }
            /* Case 4 - right rotate at parent + color flips */
            tmp2 = sibling->right;
            parent->left = tmp2;
            sibling->right = parent;
            a_bst_rb_set_parent_color(tmp1, sibling, A_BST_RB_B);
            if (tmp2)
            {
                a_bst_rb_set_parent(tmp2, parent);
            }
            a_bst_rb_set_parents(root, parent, sibling, A_BST_RB_B);
            break;
        }
    }
}

a_void_t a_bst_rb_remove(a_bst_rb_u *const root, a_bst_rb_s *const node)
{
    a_bst_rb_s *tmp = node->left;
    a_bst_rb_s *child = node->right;
    a_bst_rb_s *parent, *adjust;
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
    a_uptr_t pc;
#else /* !A_SIZE_VPTR */
    a_uint_t c;
#endif /* A_SIZE_VPTR */

    if (!tmp)
    {
        /*
        Case 1: node to erase has no more than 1 child (easy!)
        Note that if there is one child it must be red due to 5) and node must be black due to 4).
        We adjust colors locally so as to bypass a_bst_rb_remove_adjust() later on.
        */
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
        pc = node->parent;
#else /* !A_SIZE_VPTR */
        c = node->color;
#endif /* A_SIZE_VPTR */
        parent = a_bst_rb_parent(node);
        a_bst_rb_mod_child(root, parent, node, child);
        if (child)
        {
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
            child->parent = pc;
#else /* !A_SIZE_VPTR */
            child->parent = parent;
            child->color = c;
#endif /* A_SIZE_VPTR */
            adjust = A_NULL;
        }
        else
        {
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
            adjust = (pc & 1) == A_BST_RB_B ? parent : NULL;
#else /* !A_SIZE_VPTR */
            adjust = c == A_BST_RB_B ? parent : NULL;
#endif /* A_SIZE_VPTR */
        }
        tmp = parent;
    }
    else if (!child)
    {
        /* Still case 1, but this time the child is node->left */
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
        tmp->parent = pc = node->parent;
#else /* !A_SIZE_VPTR */
        tmp->parent = node->parent;
        tmp->color = c = node->color;
#endif /* A_SIZE_VPTR */
        parent = a_bst_rb_parent(node);
        a_bst_rb_mod_child(root, parent, node, tmp);
        adjust = NULL;
        tmp = parent;
    }
    else
    {
        a_bst_rb_s *successor = child, *child2;

        tmp = child->left;
        if (!tmp)
        {
            /*
            Case 2: node's successor is its right child

                  (n)          (s)
                  / \          / \
                (x) (s)  ->  (x) (c)
                      \
                     (c)
            */
            parent = successor;
            child2 = successor->right;
        }
        else
        {
            /*
            Case 3: node's successor is leftmost under node's right child subtree

                  (n)          (s)
                  / \          / \
                (x) (y)  ->  (x) (y)
                    /            /
                  (p)          (p)
                  /            /
                (s)          (c)
                  \
                  (c)
            */
            do
            {
                parent = successor;
                successor = tmp;
                tmp = tmp->left;
            } while (tmp);
            child2 = successor->right;
            parent->left = child2;
            successor->right = child;
            a_bst_rb_set_parent(child, successor);
        }

        tmp = node->left;
        successor->left = tmp;
        a_bst_rb_set_parent(tmp, successor);

#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
        pc = node->parent;
#else /* !A_SIZE_VPTR */
        c = node->color;
#endif /* A_SIZE_VPTR */
        tmp = a_bst_rb_parent(node);
        a_bst_rb_mod_child(root, node, successor, tmp);

        if (child2)
        {
            a_bst_rb_set_parent_color(child2, parent, A_BST_RB_B);
            adjust = NULL;
        }
        else
        {
            adjust = a_bst_rb_color(successor) == A_BST_RB_B ? parent : NULL;
        }
#if defined(A_SIZE_VPTR) && (A_SIZE_VPTR + 0 > 1)
        successor->parent = pc;
#else /* !A_SIZE_VPTR */
        successor->parent = tmp;
        successor->color = c;
#endif /* A_SIZE_VPTR */
        tmp = successor;
    }

    if (adjust)
    {
        a_bst_rb_remove_adjust(root, child, adjust);
    }
}

a_bst_rb_s *a_bst_rb_head(a_bst_rb_u const *const root)
{
    a_bst_rb_s *node = root->node;
    if (node)
    {
        while (node->left)
        {
            node = node->left;
        }
    }
    return node;
}

a_bst_rb_s *a_bst_rb_tail(a_bst_rb_u const *const root)
{
    a_bst_rb_s *node = root->node;
    if (node)
    {
        while (node->right)
        {
            node = node->right;
        }
    }
    return node;
}

a_bst_rb_s *a_bst_rb_next(a_bst_rb_s *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    if (!node)
    {
        return node;
    }
    if (node->right) /* D -> F -> E */
    {
        for (node = node->right; node->left; node = node->left)
        {
        }
    }
    else /* C -> B -> D */
    {
        a_bst_rb_s *last = node;
        for (node = a_bst_rb_parent(node); node && node->left != last;)
        {
            last = node;
            node = a_bst_rb_parent(node);
        }
    }
    return node;
}

a_bst_rb_s *a_bst_rb_prev(a_bst_rb_s *node)
{
    if (!node)
    {
        return node;
    }
    if (node->left)
    {
        for (node = node->left; node->right; node = node->right)
        {
        }
    }
    else
    {
        a_bst_rb_s *last = node;
        for (node = a_bst_rb_parent(node); node && node->right != last;)
        {
            last = node;
            node = a_bst_rb_parent(node);
        }
    }
    return node;
}

a_bst_rb_s *a_bst_rb_pre_next(a_bst_rb_s *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    if (!node)
    {
        return node;
    }
    if (node->left)
    {
        return node->left;
    }
    if (node->right)
    {
        return node->right;
    }
    a_bst_rb_s *last = node;
    for (node = a_bst_rb_parent(node); node; node = a_bst_rb_parent(node))
    {
        if (node->right && node->right != last)
        {
            node = node->right; /* A -> B -> C */
            break;
        }
        last = node; /* C -> B -> D -> F */
    }
    return node;
}

a_bst_rb_s *a_bst_rb_pre_prev(a_bst_rb_s *node)
{
    if (!node)
    {
        return node;
    }
    if (node->right)
    {
        return node->right;
    }
    if (node->left)
    {
        return node->left;
    }
    a_bst_rb_s *last = node;
    for (node = a_bst_rb_parent(node); node; node = a_bst_rb_parent(node))
    {
        if (node->left && node->left != last)
        {
            node = node->left;
            break;
        }
        last = node;
    }
    return node;
}

#define A_BST_RB_POST_NEXT(node) \
    do                           \
    {                            \
        if (node->left)          \
        {                        \
            node = node->left;   \
        }                        \
        else if (node->right)    \
        {                        \
            node = node->right;  \
        }                        \
        else                     \
        {                        \
            break;               \
        }                        \
    } while (A_TRUE)

a_bst_rb_s *a_bst_rb_post_head(a_bst_rb_u const *const root)
{
    a_bst_rb_s *node = root->node;
    if (node)
    {
        A_BST_RB_POST_NEXT(node);
    }
    return node;
}

#define A_BST_RB_POST_PREV(node) \
    do                           \
    {                            \
        if (node->right)         \
        {                        \
            node = node->right;  \
        }                        \
        else if (node->left)     \
        {                        \
            node = node->left;   \
        }                        \
        else                     \
        {                        \
            break;               \
        }                        \
    } while (A_TRUE)

a_bst_rb_s *a_bst_rb_post_tail(a_bst_rb_u const *const root)
{
    a_bst_rb_s *node = root->node;
    if (node)
    {
        A_BST_RB_POST_PREV(node);
    }
    return node;
}

a_bst_rb_s *a_bst_rb_post_next(a_bst_rb_s *node)
{
    /*
         D
       /   \
      B     F
     / \   / \
    A   C E   G
    */
    if (!node)
    {
        return node;
    }
    a_bst_rb_s *last = node;
    node = a_bst_rb_parent(node);
    if (node && node->right && node->right != last)
    {
        node = node->right; /* B -> D -> F -> E */
        A_BST_RB_POST_NEXT(node); /* A -> B -> C */
    } /* C -> B */
    return node;
}

a_bst_rb_s *a_bst_rb_post_prev(a_bst_rb_s *node)
{
    if (!node)
    {
        return node;
    }
    a_bst_rb_s *last = node;
    node = a_bst_rb_parent(node);
    if (node && node->left && node->left != last)
    {
        node = node->left;
        A_BST_RB_POST_PREV(node);
    }
    return node;
}

a_bst_rb_s *a_bst_rb_tear(a_bst_rb_u *const root, a_bst_rb_s **const next)
{
    a_bst_rb_s *node = *next;
    if (!node)
    {
        node = root->node;
        if (!node)
        {
            return node;
        }
    }
    A_BST_RB_POST_NEXT(node);
    a_bst_rb_s *const parent = a_bst_rb_parent(node);
    if (parent)
    {
        if (parent->left == node)
        {
            parent->left = A_NULL;
        }
        else
        {
            parent->right = A_NULL;
        }
    }
    else
    {
        root->node = A_NULL;
    }
    *next = parent;
    return node;
}
