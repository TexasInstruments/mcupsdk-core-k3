/*
 *  Copyright (c) Texas Instruments Incorporated 2023
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file fvid2_utils.c
 *
 *  \brief Utility functions implementation file.
 *  This file defines the helper functions like create, add and remove nodes
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <drivers/fvid2/v0/fvid2.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Fvid2Utils_Node *dutilsLinkCircularPri(Fvid2Utils_Node *headNode,
                                              Fvid2Utils_Node *node,
                                              void            *data,
                                              uint32_t         priority);
static int32_t dutilsLinkDoublePri(Fvid2UtilsLinkListObj *llobj,
                                   Fvid2Utils_Node       *node,
                                   void                  *data,
                                   uint32_t               priority,
                                   uint32_t               linkUniqePriNodes);
static Fvid2Utils_Node *dutilsUnLinkCircularPri(Fvid2Utils_Node *headNode,
                                                Fvid2Utils_Node *node);
static void dutilsUnLinkDoublePri(Fvid2UtilsLinkListObj *llobj,
                                  Fvid2Utils_Node       *node);
static Fvid2Utils_Node *dutilsUnLinkDouble(Fvid2UtilsLinkListObj *llobj,
                                           Fvid2Utils_NodDir      dir,
                                           const Fvid2Utils_Node *nodeToBeRem);
static Fvid2Utils_Node *dutilsLinkDouble(Fvid2UtilsLinkListObj *llobj,
                                         Fvid2Utils_Node       *node,
                                         void                  *data,
                                         Fvid2Utils_NodDir      dir);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  Fvid2Utils_init
 *  \brief Initializes the Util objects and create pool semaphore
 *
 *  \returns                Returns 0 on success else returns error value
 */
int32_t Fvid2Utils_init(void)
{
    return (FVID2_SOK);
}

/**
 *  Fvid2Utils_deInit
 *  \brief De-Initializes the Util objects by removing pool semaphore
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t Fvid2Utils_deInit(void *arg)
{
    return (FVID2_SOK);
}

/**
 *  Fvid2Utils_memset
 *  \brief Sets the memory with the given value. Access memory as byte.
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer
 *  \param ch               Byte value to fill with
 *  \param byteCount        Number of bytes to fill
 *
 *  \return                 The destination memory pointer
 */
void Fvid2Utils_memset(void *mem, uint8_t ch, size_t byteCount)
{
    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != mem));

    (void) memset(mem, (int32_t) ch, byteCount);
}

/**
 *  Fvid2Utils_memsetw
 *  \brief Sets the memory with the given value. Access memory as word.
 *  Hence memory pointer should be aligned to 4 byte boundary
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer
 *  \param word             Word value to fill with
 *  \param wordCount        Number of words to fill
 *
 *  \return                 The destination memory pointer
 */
void *Fvid2Utils_memsetw(void *mem, uint32_t word, uint32_t wordCount)
{
    uint32_t  count;
    uint32_t *memPtr = NULL;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != mem));

    memPtr = (uint32_t *) mem;
    for (count = 0; count < wordCount; count++)
    {
        memPtr[count] = word;
    }

    return (mem);
}

/**
 *  Fvid2Utils_memcpy
 *  \brief Copies source memory into destination memory. Access memory as byte.
 *  Returns the destination memory pointer.
 *
 *  \param dest             Destination memory pointer
 *  \param src              Source memory pointer
 *  \param byteCount        Number of bytes to copy
 *
 *  \return                 The destination memory pointer
 */
void Fvid2Utils_memcpy(void *dest, const void *src, size_t byteCount)
{
    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != dest));
    GT_assert(Fvid2Trace, (NULL_PTR != src));

    (void) memcpy(dest, src, byteCount);
}

/**
 *  Fvid2Utils_memcmp
 *  \brief Compare memory block 1 with memory block 2. Access memory as byte.
 *  Returns 0 if two memories are  identical.
 *
 *  \param mem1             memory block 1
 *  \param mem2              memory block 2
 *  \param byteCount        Number of bytes to compare
 *
 *  \return                 0 if two memory are identical other return 1
 */
int32_t Fvid2Utils_memcmp(const void *mem1,
                          const void *mem2,
                          uint32_t byteCount)
{
    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != mem1));
    GT_assert(Fvid2Trace, (NULL_PTR != mem2));

    return memcmp(mem1, mem2, byteCount);
}

/**
 *  Fvid2Utils_constructLinkList
 *  \brief Constructs a link list object with the provided properties.
 *
 *  \param llobj pointer to object of type Fvid2UtilsLinkListObj
 *  \param listType         List type - circular/double link list.
 *  \param addMode          Node addition mode - Top/Bottom/Priority based.
 *
 *  \return                 Returns FVID2_SOK on success else returns error
 *                          value.
 */
int32_t Fvid2Utils_constructLinkList(Fvid2UtilsLinkListObj  *llobj,
                                     Fvid2Utils_LinkListType listType,
                                     Fvid2Utils_LinkAddMode  addMode)
{
    int32_t retVal = FVID2_SOK;
    if ((FVID2UTILS_LLT_CIRCULAR == listType) &&
        (FVID2UTILS_LAM_PRIORITY != addMode))
    {
        GT_0trace(Fvid2Trace, GT_DEBUG,
                  "Non-Priority circular link list not Supported\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        GT_assert(Fvid2Trace, (NULL_PTR != llobj));
        /* Initialize the variables */
        llobj->listType    = listType;
        llobj->addMode     = addMode;
        llobj->headNode    = NULL;
        llobj->tailNode    = NULL;
        llobj->numElements = 0U;
        llobj->priorityCnt = 0;
    }

    return retVal;
}

/**
 *  Fvid2Utils_destructLinkList
 *  \brief Destructs a link list object.
 *
 *  \param llobj pointer to object of type Fvid2UtilsLinkListObj
 *
 *  \return                None
 */
void Fvid2Utils_destructLinkList(Fvid2UtilsLinkListObj *llobj)
{
    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != llobj));
    GT_assert(Fvid2Trace, (NULL_PTR == llobj->headNode));
    GT_assert(Fvid2Trace, (NULL_PTR == llobj->tailNode));

    /* Free link list object */
    Fvid2Utils_memset(llobj, 0, sizeof (Fvid2UtilsLinkListObj));
}

/**
 *  Fvid2Utils_unLinkAllNodes
 *  \brief Releases all nodes without modifying any of the property.
 *         CAUTION - Memory is NOT de-allocated, its the responsibility of the
 *                   caller to ensure de-allocation of memory.
 *
 *  \param handle           Link list handle.
 *
 *  \return                 Returns 0 on success else returns error value.
 */
int32_t Fvid2Utils_unLinkAllNodes(Fvid2Utils_Handle handle)
{
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj              = (Fvid2UtilsLinkListObj *) handle;
    llobj->headNode    = NULL;
    llobj->tailNode    = NULL;
    llobj->numElements = 0U;
    llobj->priorityCnt = 0;

    return (0);
}

/**
 *  Fvid2Utils_linkNodePri
 *  \brief Links a node to the linked list according to the list type
 *  The memory to the node object should be allocated by the caller. This
 *  is used for link list with priority.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param priority         Priority of the node used for priority based
 *                          addition of nodes. Priority is in descending order
 *                          the value. So 0 is the highest priority and is
 *                          added to the top of the node.
 *                          Nodes with the same priority are always added to
 *                          the bottom of the existing nodes with same
 *                          priority.
 *                          For non-priority based modes, this parameter
 *                          is ignored and could be set to 0.
 */
void Fvid2Utils_linkNodePri(Fvid2Utils_Handle handle,
                            Fvid2Utils_Node  *node,
                            uint32_t          priority)
{
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));
    GT_assert(Fvid2Trace, (NULL_PTR != node));

    llobj = (Fvid2UtilsLinkListObj *) handle;

    if (FVID2UTILS_LLT_CIRCULAR == llobj->listType)
    {
        llobj->headNode = dutilsLinkCircularPri(
            llobj->headNode,
            node,
            node->data,
            priority);
    }
    else if (FVID2UTILS_LLT_DOUBLE == llobj->listType)
    {
        (void) dutilsLinkDoublePri(llobj, node, node->data, priority, (uint32_t) FALSE);
    }
    else
    {
        GT_assert(Fvid2Trace, FALSE);
    }

    return;
}

/**
 *  Fvid2Utils_linkUniqePriNode
 *  \brief Very similar to Fvid2Utils_linkNodePri, except that on equal priority
 *          nodes will not be inserted. An error (FVID2_EBADARGS) would be
 *          returned.
 *          Applicable for double linked list only.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param priority         Priority of the node used for priority based
 *                          addition of nodes. Priority is in descending order
 *                          the value. So 0 is the highest priority and is
 *                          added to the top of the node.
 *                          Nodes with the same priority are always added to
 *                          the bottom of the existing nodes with same
 *                          priority.
 *                          For non-priority based modes, this parameter
 *                          is ignored and could be set to 0.
 */
int32_t Fvid2Utils_linkUniqePriNode(Fvid2Utils_Handle handle,
                                    Fvid2Utils_Node  *node,
                                    uint32_t          priority)
{
    Fvid2UtilsLinkListObj *llobj;
    int32_t rtnValue = FVID2_SOK;
    uint32_t tempPriority = priority;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));
    GT_assert(Fvid2Trace, (NULL_PTR != node));

    llobj = (Fvid2UtilsLinkListObj *) handle;

    if (FVID2UTILS_LAM_PRIORITY != llobj->addMode)
    {
        if (FVID2UTILS_LAM_TOP == llobj->addMode)
        {
            llobj->priorityCnt--;
        }
        else if (FVID2UTILS_LAM_BOTTOM == llobj->addMode)
        {
            llobj->priorityCnt++;
        }
        else
        {
            GT_assert(Fvid2Trace, FALSE);
        }
        tempPriority = llobj->priorityCnt;
    }

    if (FVID2UTILS_LLT_CIRCULAR == llobj->listType)
    {
        llobj->headNode = dutilsLinkCircularPri(
            llobj->headNode,
            node,
            node->data,
            tempPriority);
    }
    else if (FVID2UTILS_LLT_DOUBLE == llobj->listType)
    {
        rtnValue = dutilsLinkDoublePri(
            llobj,
            node,
            node->data,
            tempPriority,
            (uint32_t) TRUE);
        if (rtnValue == FVID2_SOK)
        {
            llobj->numElements++;
        }
    }
    else
    {
        GT_assert(Fvid2Trace, FALSE);
    }

    return (rtnValue);
}

/**
 *  Fvid2Utils_unLinkNodePri
 *  \brief Unlinks the node from the list. Used for the Priority linklists.
 *
 *  \param handle           Link list handle.
 *  \param node             Node pointer to be unlinked from the list.
 */
void Fvid2Utils_unLinkNodePri(Fvid2Utils_Handle handle, Fvid2Utils_Node *node)
{
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));
    GT_assert(Fvid2Trace, (NULL_PTR != node));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    if (FVID2UTILS_LLT_CIRCULAR == llobj->listType)
    {
        llobj->headNode = dutilsUnLinkCircularPri(llobj->headNode, node);
    }
    else if (FVID2UTILS_LLT_DOUBLE == llobj->listType)
    {
        dutilsUnLinkDoublePri(llobj, node);
    }
    else
    {
        GT_assert(Fvid2Trace, FALSE);
    }

    return;
}

/**
 *  Fvid2Utils_unLinkNode
 *  \brief Unlinks the node from the list. Used for Non-priority linked lists
 *
 *  \param handle           Link list handle.
 *  \param node             Node pointer to be unlinked from the list.
 */
void Fvid2Utils_unLinkNode(Fvid2Utils_Handle handle, const Fvid2Utils_Node *node)
{
    Fvid2UtilsLinkListObj *llobj;
    Fvid2Utils_NodDir      dir = FVID2UTILS_NODE_DIR_HEAD;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));
    GT_assert(Fvid2Trace, (NULL_PTR != node));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    (void) dutilsUnLinkDouble(llobj, dir, node);

    return;
}

/**
 *  Fvid2Utils_linkNodeToTail
 *  \brief                  Link the node to the tail of the double linked list.
 *                          No priority
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
void Fvid2Utils_linkNodeToTail(Fvid2Utils_Handle handle, Fvid2Utils_Node *node)
{
    Fvid2Utils_NodDir      dir = FVID2UTILS_NODE_DIR_TAIL;
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != node));
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    (void) dutilsLinkDouble(llobj, node, node->data, dir);

    return;
}

/**
 *  Fvid2Utils_linkNodeToHead
 *  \brief                  Link the node to the head of the double linked list.
 *                          No priority
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
void Fvid2Utils_linkNodeToHead(Fvid2Utils_Handle handle, Fvid2Utils_Node *node)
{
    Fvid2Utils_NodDir      dir = FVID2UTILS_NODE_DIR_HEAD;
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != node));
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    (void) dutilsLinkDouble(llobj, node, node->data, dir);

    return;
}

/**
 *  Fvid2Utils_unLinkNodeFromHead
 *  \brief                  Returns the node from head. Removes the  node from
 *                          the list.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
Fvid2Utils_Node *Fvid2Utils_unLinkNodeFromHead(Fvid2Utils_Handle handle)
{
    Fvid2Utils_NodDir      dir = FVID2UTILS_NODE_DIR_HEAD;
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    return (dutilsUnLinkDouble(llobj, dir, NULL));
}

/**
 *  Fvid2Utils_unLinkNodeFromTail
 *  \brief                  Returns the node from tail. Removes the  node from
 *                          the list.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
Fvid2Utils_Node *Fvid2Utils_unLinkNodeFromTail(Fvid2Utils_Handle handle)
{
    Fvid2Utils_NodDir      dir = FVID2UTILS_NODE_DIR_TAIL;
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    return (dutilsUnLinkDouble(llobj, dir, NULL));
}

/**
 *  Fvid2Utils_getHeadNode
 *  \brief                  Returns the reference to the headNode. Does
 *                          not remove the node from the head.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
Fvid2Utils_Node *Fvid2Utils_getHeadNode(Fvid2Utils_Handle handle)
{
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;

    return (llobj->headNode);
}

/**
 *  Fvid2Utils_getTailNode
 *  \brief                  Returns the reference to the TailNode. Does
 *                          not remove the node from the head.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
Fvid2Utils_Node *Fvid2Utils_getTailNode(Fvid2Utils_Handle handle)
{
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    return (llobj->tailNode);
}

/**
 *  Fvid2Utils_isListEmpty
 *  \brief Checks whether a list is empty or not.
 *
 *  \param handle           List handle.
 *
 *  \return                 TRUE if List is empty else returns FALSE.
 */
uint32_t Fvid2Utils_isListEmpty(Fvid2Utils_Handle handle)
{
    uint32_t isEmpty = FALSE;
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    if (NULL == llobj->headNode)
    {
        isEmpty = (uint32_t) TRUE;
    }

    return (isEmpty);
}

/**
 *  Fvid2Utils_getNumNodes
 *  \brief Returns the number of nodes present in a list.
 *
 *  \param handle           List handle.
 *
 *  \return                 Number of nodes present in a list.
 */
uint32_t Fvid2Utils_getNumNodes(Fvid2Utils_Handle handle)
{
    Fvid2Utils_Node       *node = NULL;
    Fvid2UtilsLinkListObj *llobj;
    uint32_t numNodes = 0U;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    if (FVID2UTILS_LLT_CIRCULAR == llobj->listType)
    {
        node = llobj->headNode;
        while (NULL != node)
        {
            numNodes++;
            node = node->next;
            /* Not supposed to have NULL in circular list */
            GT_assert(Fvid2Trace, (NULL_PTR != node));

            /* Check if we have come to the end of the list */
            if (node == llobj->headNode)
            {
                break;
            }
        }
    }
    else if (FVID2UTILS_LLT_DOUBLE == llobj->listType)
    {
        node = llobj->headNode;
        while (NULL != node)
        {
            numNodes++;
            node = node->next;
        }
    }
    else
    {
        GT_assert(Fvid2Trace, FALSE);
    }

    return (numNodes);
}

/**
 *  Fvid2Utils_constructQ
 *  \brief Constructs a Queue object.
 *
 * \param llobj pointer to object of type Fvid2UtilsLinkListObj
 *
 *  \return                 Returns FVID2_SOK on success else returns error value.
 */
int32_t Fvid2Utils_constructQ(Fvid2UtilsLinkListObj *llobj)
{
    return Fvid2Utils_constructLinkList(llobj, FVID2UTILS_LLT_DOUBLE,
                                        FVID2UTILS_LAM_BOTTOM);
}

/**
 *  Fvid2Utils_destructQ
 *  \brief Destructs a Queue object.
 *
 * \param llobj pointer to object of type Fvid2UtilsLinkListObj
 *
 *  \return                 None.
 */
void Fvid2Utils_destructQ(Fvid2UtilsLinkListObj *llobj)
{
    Fvid2Utils_destructLinkList(llobj);
}

/**
 *  Fvid2Utils_queue
 *  \brief Adds the data to the queue. Add the node to the tail of the queue.
 *
 *
 *  \param handle           Queue handle.
 *  \param qElem            Queue Element object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 */
void Fvid2Utils_queue(Fvid2Utils_QHandle handle,
                      Fvid2Utils_QElem  *qElem,
                      void              *data)
{
    Fvid2UtilsLinkListObj *llobj;
    Fvid2Utils_NodDir      dir = FVID2UTILS_NODE_DIR_TAIL;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    (void) dutilsLinkDouble(llobj, qElem, data, dir);

    return;
}

/**
 *  Fvid2Utils_dequeue
 *  \brief Removes a element from the queue. Removes the element from the head
 *   of the queue.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Returns the removed data pointer.
 */
void *Fvid2Utils_dequeue(Fvid2Utils_QHandle handle)
{
    Fvid2Utils_Node       *node;
    void                  *data = NULL;
    Fvid2UtilsLinkListObj *llobj;
    Fvid2Utils_NodDir      dir = FVID2UTILS_NODE_DIR_HEAD;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    node  = dutilsUnLinkDouble(llobj, dir, NULL);
    if (NULL != node)
    {
        data = node->data;
    }
    else
    {
        data = NULL;
    }

    return (data);
}

/**
 *  Fvid2Utils_peakHead
 *  \brief Returns the reference of the first queued element.
 *
 *  This doesn't remove the element from the queue.
 *  If the queue is empty, then this returns NULL.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Returns the reference of the first element.
 */
void *Fvid2Utils_peakHead(Fvid2Utils_QHandle handle)
{
    void *data = NULL;
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    if (llobj->headNode != NULL)
    {
        data = llobj->headNode->data;
    }

    return (data);
}

/**
 *  Fvid2Utils_peakTail
 *  \brief Returns the reference of the last queued element.
 *
 *  This doesn't remove the element from the queue.
 *  If the queue is empty, then this returns NULL.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Returns the reference of the last queued element.
 */
void *Fvid2Utils_peakTail(Fvid2Utils_QHandle handle)
{
    void *data = NULL;
    Fvid2UtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    if (llobj->tailNode != NULL)
    {
        data = llobj->tailNode->data;
    }

    return (data);
}

/**
 *  Fvid2Utils_queueBack
 *  \brief Adds the data to start of the queue. Queue the data back to the
 *  head of the queue.
 *
 *  \param handle           Queue handle.
 *  \param qElem            Queue Element object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 */
void Fvid2Utils_queueBack(Fvid2Utils_QHandle handle,
                          Fvid2Utils_QElem  *qElem,
                          void              *data)
{
    Fvid2UtilsLinkListObj *llobj;
    Fvid2Utils_NodDir      dir = FVID2UTILS_NODE_DIR_HEAD;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    llobj = (Fvid2UtilsLinkListObj *) handle;
    (void) dutilsLinkDouble(llobj, qElem, data, dir);

    return;
}

/**
 *  Fvid2Utils_isQEmpty
 *  \brief Checks whether a queue is empty or not.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 TRUE if queue is empty else returns FALSE.
 */
uint32_t Fvid2Utils_isQEmpty(Fvid2Utils_QHandle handle)
{
    return Fvid2Utils_isListEmpty(handle);
}

/**
 *  Fvid2Utils_getNumQElem
 *  \brief Returns the number of Queue Elements present in a Queue.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Number of Queue Elements present in a Queue.
 */
uint32_t Fvid2Utils_getNumQElem(Fvid2Utils_QHandle handle)
{
    return Fvid2Utils_getNumNodes(handle);
}

/**
 *  dutilsLinkCircularPri
 *  \brief Links a node to a circular link list based on priority.
 *  For nodes with same priority, the new node will be added to the last.
 */
static Fvid2Utils_Node *dutilsLinkCircularPri(Fvid2Utils_Node *headNode,
                                              Fvid2Utils_Node *node,
                                              void            *data,
                                              uint32_t         priority)
{
    Fvid2Utils_Node *curNode;
    Fvid2Utils_Node *tempHeadNode = headNode;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != node));

    node->data     = data;
    node->priority = priority;

    /* Check if this is the first node. */
    if (NULL != tempHeadNode)
    {
        /* Add to the list based on priority */
        curNode = tempHeadNode;
        do
        {
            /* Nodes with the same priority are always added to the bottom
             * of the existing nodes with same priority. */
            if (priority < curNode->priority)
            {
                if (curNode == tempHeadNode)
                {
                    /* Adding to the top of the list */
                    tempHeadNode = node;
                }
                break;
            }

            /* Move to next node */
            curNode = curNode->next;
            /* Not supposed to have NULL in circular list */
            GT_assert(Fvid2Trace, (NULL_PTR != curNode));
        } while (curNode != tempHeadNode);
        /* Check if we have come to the end of the list */

        /* Add the node before the current node as we have traversed one
         * extra node. */
        node->next = curNode;
        node->prev = curNode->prev;

        /* Not supposed to have NULL in circular list */
        GT_assert(Fvid2Trace, (NULL_PTR != curNode->prev));
        GT_assert(Fvid2Trace, (NULL_PTR != curNode->prev->next));
        curNode->prev->next = node;
        curNode->prev       = node;
    }
    else
    {
        /* First node. Add to as head node */
        tempHeadNode   = node;
        node->next = node;
        node->prev = node;
    }

    return (tempHeadNode);
}

/**
 *  dutilsLinkDoublePri
 *  \brief Links a node to a double link list based on priority.
 *  For nodes with same priority, the new node will be added to the last.
 *
 *  ToDo - Remove multiple return statements - Have one exit point for the
 *         Function.
 */
static int32_t dutilsLinkDoublePri(Fvid2UtilsLinkListObj *llobj,
                                   Fvid2Utils_Node       *node,
                                   void                  *data,
                                   uint32_t               priority,
                                   uint32_t               linkUniqePriNodes)
{
    int32_t          retVal = FVID2_SOK;
    Fvid2Utils_Node *curNode, *prevNode = NULL;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != node));

    node->data     = data;
    node->priority = priority;

    /* Add to the list based on priority */
    curNode = llobj->headNode;
    while (NULL != curNode)
    {
        /* Nodes with the same priority are always added to the bottom
         * of the existing nodes with same priority. */
        if (priority < curNode->priority)
        {
            break;
        }

        /* Move to next node */
        prevNode = curNode;
        curNode  = curNode->next;
    }

    /* If unique priority check is enabled - check for uniqueness */
    if (linkUniqePriNodes == (uint32_t) TRUE)
    {
        if (prevNode != NULL)
        {
            if (priority == prevNode->priority)
            {
                retVal = FVID2_EBADARGS;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Add the node between current and previous nodes */
        node->next = curNode;
        node->prev = prevNode;
        if (NULL != prevNode)
        {
            prevNode->next = node;
        }
        else
        {
            /* Adding to the top of the list */
            llobj->headNode = node;
        }

        if (NULL != curNode)
        {
            curNode->prev = node;
        }
        else
        {
            llobj->tailNode = node;
        }
        retVal = FVID2_SOK;
    }

    return (retVal);
}

/**
 *  dutilsUnLinkCircularPri
 *  \brief Unlinks a node from a circular link list.
 */
static Fvid2Utils_Node *dutilsUnLinkCircularPri(Fvid2Utils_Node *headNode,
                                                Fvid2Utils_Node *node)
{
    Fvid2Utils_Node *tempHeadNode = headNode;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != tempHeadNode));
    GT_assert(Fvid2Trace, (NULL_PTR != node));

    /* Not supposed to have NULL in circular list */
    GT_assert(Fvid2Trace, (NULL_PTR != node->next));
    GT_assert(Fvid2Trace, (NULL_PTR != node->prev));

    /* Link the node's previous node to node's next node */
    node->prev->next = node->next;
    node->next->prev = node->prev;

    if (node == tempHeadNode)
    {
        /* Unlinking head node */
        if ((tempHeadNode == tempHeadNode->next) || (tempHeadNode == tempHeadNode->prev))
        {
            /* Unlinking last node */
            GT_assert(Fvid2Trace,
                      ((tempHeadNode == tempHeadNode->next) &&
                       (tempHeadNode == tempHeadNode->prev)));
            tempHeadNode = NULL;
        }
        else
        {
            /* Make next node as head node */
            tempHeadNode = node->next;
        }
    }

    /* Reset node memory */
    node->next = NULL;
    node->prev = NULL;

    return (tempHeadNode);
}

/**
 *  dutilsUnLinkDoublePri
 *  \brief Unlinks a node from a double link list.
 */
static void dutilsUnLinkDoublePri(Fvid2UtilsLinkListObj *llobj,
                                  Fvid2Utils_Node       *node)
{
    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != llobj));
    GT_assert(Fvid2Trace, (NULL_PTR != node));

    if (NULL == node->prev)
    {
        /* Removing head node */
        llobj->headNode = node->next;
    }
    else
    {
        /* Removing non-head node */
        node->prev->next = node->next;
    }

    if (NULL != node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        llobj->tailNode = NULL;
    }

    /* Reset node memory */
    node->next = NULL;
    node->prev = NULL;

    return;
}

/**
 *  dutilsUnLinkDouble
 *  \brief Unlinks a node from a double link list.
 */
static Fvid2Utils_Node *dutilsUnLinkDouble(Fvid2UtilsLinkListObj *llobj,
                                           Fvid2Utils_NodDir      dir,
                                           const Fvid2Utils_Node *nodeToBeRem)
{
    Fvid2Utils_Node *node = NULL, *headNode, *tailNode, *listNode;
    uint32_t         nodeCnt;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != llobj));

    if (NULL == nodeToBeRem)
    {
        if ((NULL == llobj->headNode) && (NULL == llobj->tailNode))
        {
            node = NULL;
        }
        /* Check for the last node in the list */
        else if ((NULL != llobj->headNode) &&
                 (NULL == llobj->headNode->next) &&
                 (NULL == llobj->headNode->prev))
        {
            node = llobj->headNode;
            llobj->tailNode = NULL;
            llobj->headNode = NULL;
        }
        else if ((NULL != llobj->headNode) &&
                 (NULL != llobj->tailNode) &&
                 (FVID2UTILS_NODE_DIR_HEAD == dir))
        {
            /* Point headnode to the head of the list */
            headNode = llobj->headNode;
            /* headnode points to now next in the list */
            llobj->headNode = headNode->next;
            /* prev of the new headnode point to headNode of the list */
            if (NULL != llobj->headNode)
            {
                llobj->headNode->prev = NULL;
            }
            else
            {
                llobj->tailNode = NULL;
            }
            /* return the detached node */
            node = headNode;
        }
        else if ((NULL != llobj->headNode) &&
                 (NULL != llobj->tailNode) &&
                 (FVID2UTILS_NODE_DIR_TAIL == dir))
        {
            /* point to the tail node. */
            tailNode = llobj->tailNode;
            /* tailnode of the list points to the previous node */
            llobj->tailNode = tailNode->prev;
            /* next node of the previous node points to the tail node of list */
            if (NULL != llobj->tailNode)
            {
                llobj->tailNode->next = NULL;
            }
            else
            {
                llobj->headNode = NULL;
            }
            /*  return the tail node */
            node = tailNode;
        }
        else
        {
            GT_assert(Fvid2Trace, FALSE);
        }
    }
    else
    {
        listNode = llobj->headNode;
        for (nodeCnt = 0; nodeCnt < llobj->numElements; nodeCnt++)
        {
            if (listNode == nodeToBeRem)
            {
                /* Last node in the list */
                if ((llobj->headNode == listNode) &&
                    (llobj->tailNode == listNode))
                {
                    llobj->headNode = NULL;
                    llobj->tailNode = NULL;
                }
                else if (llobj->headNode == listNode)
                {
                    llobj->headNode       = listNode->next;
                    llobj->headNode->prev = NULL;
                }
                else if (llobj->tailNode == listNode)
                {
                    llobj->tailNode       = listNode->prev;
                    llobj->tailNode->next = NULL;
                }
                else
                {
                    listNode->prev->next = listNode->next;
                    listNode->next->prev = listNode->prev;
                }
                node = listNode;
                break;
            }
            listNode = listNode->next;
        }
    }
    if (NULL != node)
    {
        /* Reset node memory */
        node->next = NULL;
        node->prev = NULL;
        llobj->numElements--;
    }

    return (node);
}

/**
 *  Fvid2Utils_getNumNodes
 *  \brief Returns the number of nodes present in a list.
 *
 *  \param handle           List handle.
 *
 *  \return                 Number of nodes present in a list.
 */
uint32_t Fvid2Utils_getNodeCnt(Fvid2Utils_Handle handle)
{
    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != handle));

    return (((Fvid2UtilsLinkListObj *) handle)->numElements);
}

/**
 *  dutilsLinkDouble
 *  \brief Links a node to a double link list either at head of the list or
 *  at tail of the list.
 *
 *
 */
static Fvid2Utils_Node *dutilsLinkDouble(Fvid2UtilsLinkListObj *llobj,
                                         Fvid2Utils_Node       *node,
                                         void                  *data,
                                         Fvid2Utils_NodDir      dir)
{
    Fvid2Utils_Node *headNode, *tailNode = NULL;

    /* NULL pointer check */
    GT_assert(Fvid2Trace, (NULL_PTR != node));
    GT_assert(Fvid2Trace, (NULL_PTR != llobj));

    node->data = data;
    /* check for the first element in the list */
    if ((NULL == llobj->headNode) && (NULL == llobj->tailNode))
    {
        /* Add the first element in the list */
        /* head node points to new element */
        llobj->headNode = node;
        /* tail node also points to new element */
        llobj->tailNode = node;
        /* next of node points to tail */
        node->next = NULL;
        /* prev of node points to head */
        node->prev = NULL;
    }
    else if ((NULL != llobj->headNode) &&
             (NULL != llobj->tailNode) &&
             (FVID2UTILS_NODE_DIR_HEAD == dir))
    {
        headNode = llobj->headNode;
        /* headNode now points to new node */
        llobj->headNode = node;
        /* previous of new node points to headNode */
        node->prev = NULL;
        /* next of new points to prev head node */
        node->next = headNode;
        /* prev of previous head node head points to new node */
        headNode->prev = node;
    }
    else if ((NULL != llobj->headNode) &&
             (NULL != llobj->tailNode) &&
             (FVID2UTILS_NODE_DIR_TAIL == dir))
    {
        tailNode = llobj->tailNode;
        /* next of new node points to tail of list */
        node->next = NULL;
        /* tail of list points to new node */
        llobj->tailNode = node;
        /* next of previous tial node points to new tail node */
        tailNode->next = node;
        /* previous of new tail node points to previous tail node */
        node->prev = tailNode;
    }
    else
    {
        GT_assert(Fvid2Trace, FALSE);
    }
    llobj->numElements++;
    return (node);
}
