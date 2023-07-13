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
 *  \file fvid2_utils.h
 *
 *  \brief FVID2 Utility functions header file
 *  This file declares the functions required to create, add and remove nodes.
 *  Also provides various memset functions.
 *
 */

#ifndef FVID2_UTILS_H_
#define FVID2_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

//#include <ti/csl/csl_types.h> //TODO: Possible cause of error
//#include <ti/osal/osal.h>   //TODO
#include <kernel/dpl/HwiP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Number of timestamps. */
#define FVID2UTILS_NUM_TIMESTAMP_LOG    (100U)

/**
 *  \anchor Fvid2Utils_LinkListType
 *  \name Link List Type
 *  @{
 */
/**
 *  \brief Enums for the type of link list to be created.
 */
typedef uint32_t Fvid2Utils_LinkListType;
#define FVID2UTILS_LLT_DOUBLE           (0U)
/**< Double link list. */
#define FVID2UTILS_LLT_CIRCULAR         (1U)
/**< Circular link list using double link list. */
/* @} */

/**
 *  \anchor Fvid2Utils_LinkAddMode
 *  \name Link Add Mode
 *  @{
 */
/**
 *  \brief Enums for the different modes of adding a node to a link list.
 */
typedef uint32_t Fvid2Utils_LinkAddMode;
#define FVID2UTILS_LAM_TOP              (0U)
/**< Add nodes to the top of the list. */
#define FVID2UTILS_LAM_BOTTOM           (1U)
/**< Add nodes to the bottom of the list. */
#define FVID2UTILS_LAM_PRIORITY         (2U)
/**< Add nodes to the list based on ascending order of priority.
 *   Nodes with the same priority are always added to the bottom of the
 *   existing nodes with same priority. */
/* @} */

/**
 *  \anchor Fvid2Utils_NodDir
 *  \name Node Direction
 *  @{
 */
/**
 *  \brief Enums for the different modes of adding a node to a link list.
 */
typedef uint32_t Fvid2Utils_NodDir;
#define FVID2UTILS_NODE_DIR_HEAD        (0U)
/**< Add nodes to the top of the list. */
#define FVID2UTILS_NODE_DIR_TAIL        (1U)
/**< Add nodes to the bottom of the list. */
/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**< \brief Typedef for Node structure. */
typedef struct Fvid2Utils_Node_t Fvid2Utils_Node;

/**
 *  struct Fvid2Utils_Node_t
 *  \brief Self referential structure for double link list.
 */
struct Fvid2Utils_Node_t
{
    Fvid2Utils_Node *next;
    /**< Pointer to the next node. */
    Fvid2Utils_Node *prev;
    /**< Pointer to the previous node. */
    void            *data;
    /**< Node data pointer. */
    uint32_t         priority;
    /**< Priority of the node. Used for priority based linked list. */
};

/**
 *  struct Fvid2Utils_QElem
 *  \brief Typedef for Queue Node element.
 */
typedef Fvid2Utils_Node Fvid2Utils_QElem;

/**
 *  struct Fvid2Utils_PoolParams
 *  \brief Create parameters for the fixed size pool.
 */
typedef struct
{
    void       *mem;
    /**< Pointer to the pool memory. */
    uint32_t    numElem;
    /**< Number of elements in the pool. */
    uint32_t    elemSize;
    /**< Size of each element in bytes. */
    uint32_t   *flag;
    /**< Array of flag variable used by pool manager to indicate whether a pool
     *   element is allocated or not. The size of this array should be
     *   equal to the number of elements in this pool. */
    uint32_t    numFreeElem;
    /**< Count to keep track of the number of free elements in the pool. */
} Fvid2Utils_PoolParams;

/**
 *  struct Fvid2Utils_TsPrfLog
 *  \brief Timestamp Performance log structure in OSAL timestamp ticks.
 */
typedef struct
{
    uint64_t startTime;
    /**< Start time - updated in start function. */
    uint64_t total;
    /**< Total duration of all log entires.
     *   To get average divide by totalCnt. */
    uint32_t totalCnt;
    /**< Total number of log entires. */
    uint64_t min;
    /**< Minimum duration. */
    uint64_t max;
    /**< Maximum duration. */
    uint32_t prfLogIndex;
    /**< Current index. This will wrap around every FVID2UTILS_NUM_TIMESTAMP_LOG
     *   count. */
    uint64_t prfLog[FVID2UTILS_NUM_TIMESTAMP_LOG];
    /**< History of the past FVID2UTILS_NUM_TIMESTAMP_LOG entires. */
} Fvid2Utils_TsPrfLog;

/**
 *  struct Fvid2UtilsLinkListObj
 *  \brief Structure to the link list object information.
 */
typedef struct
{
    Fvid2Utils_LinkListType listType;
    /**< Type of linked list. */
    Fvid2Utils_LinkAddMode  addMode;
    /**< Mode of adding a node to a link list. */
    Fvid2Utils_Node        *headNode;
    /**< Head Node. */
    Fvid2Utils_Node        *tailNode;
    /**< Tail Node Node. */
    uint32_t                numElements;
    /**< Number of elements in the linked list. */
    uint32_t                priorityCnt;
    /**< Priority count of the linked list. */
} Fvid2UtilsLinkListObj;

/**
 *  struct Fvid2Utils_Handle
 *  \brief Typedef for FVID2 Utils handle.
 */
typedef Fvid2UtilsLinkListObj *Fvid2Utils_Handle;

/**
 *  struct Fvid2Utils_QHandle
 *  \brief Typedef for FVID2 Utils Queue Handle.
 */
typedef Fvid2Utils_Handle Fvid2Utils_QHandle;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  Fvid2Utils_init
 *  \brief Initializes the Util objects and create pool semaphore
 *
 *  \returns                Returns 0 on success else returns error value
 */
int32_t Fvid2Utils_init(void);

/**
 *  Fvid2Utils_deInit
 *  \brief De-Initializes the Util objects by removing pool semaphore
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t Fvid2Utils_deInit(void *arg);

/**
 *  Fvid2Utils_memset
 *  \brief Sets the memory with the given value. Access memory as byte.
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer.
 *  \param ch               Byte value to fill with.
 *  \param byteCount        Number of bytes to fill.
 *
 *  \return                 None.
 */
void Fvid2Utils_memset(void *mem, uint8_t ch, __size_t byteCount);

/**
 *  Fvid2Utils_memsetw
 *  \brief Sets the memory with the given value. Access memory as word.
 *  Hence memory pointer should be aligned to 4 byte boundary
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer.
 *  \param word             Word value to fill with.
 *  \param wordCount        Number of words to fill.
 *
 *  \return                 The destination memory pointer.
 */
void *Fvid2Utils_memsetw(void *mem, uint32_t word, uint32_t wordCount);

/**
 *  Fvid2Utils_memcpy
 *  \brief Copies source memory into destination memory. Access memory as byte.
 *  Returns the destination memory pointer.
 *
 *  \param dest             Destination memory pointer.
 *  \param src              Source memory pointer.
 *  \param byteCount        Number of bytes to copy.
 *
 *  \return                 None
 */
void Fvid2Utils_memcpy(void *dest, const void *src, __size_t byteCount);

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
                          uint32_t byteCount);

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
                                     Fvid2Utils_LinkAddMode  addMode);

/**
 *  Fvid2Utils_destructLinkList
 *  \brief Destructs a link list object.
 *
 *  \param llobj pointer to object of type Fvid2UtilsLinkListObj
 *
 *  \return                 None
 */
void Fvid2Utils_destructLinkList(Fvid2UtilsLinkListObj *llobj);

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
                            uint32_t          priority);

/**
 *  Fvid2Utils_linkUniqePriNode
 *  \brief Very similar to Fvid2Utils_linkNode, except that on equal priority
 *          nodes will not be inserted. An error (FVID2_EBADARGS) would be
 *          returned.
 *          Applicable for double linked list only.
 *  ToDo Update to handle circular list also.
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
                                    uint32_t          priority);

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
int32_t Fvid2Utils_unLinkAllNodes(Fvid2Utils_Handle handle);

/**
 *  Fvid2Utils_unLinkNodePri
 *  \brief Unlinks the node from the list. Used for the Priority linklists.
 *
 *  \param handle           Link list handle.
 *  \param node             Node pointer to be unlinked from the list.
 */
void Fvid2Utils_unLinkNodePri(Fvid2Utils_Handle handle, Fvid2Utils_Node *node);

/**
 *  Fvid2Utils_unLinkNode
 *  \brief Unlinks the node from the list. Used for Non-priority linked lists
 *
 *  \param handle           Link list handle.
 *  \param node             Node pointer to be unlinked from the list.
 */
void Fvid2Utils_unLinkNode(Fvid2Utils_Handle handle,
                           const Fvid2Utils_Node *node);

/**
 *  Fvid2Utils_linkNodeToHead
 *  \brief                  Link the node to the head of the double linked list.
 *                          No priority
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *
 */
void Fvid2Utils_linkNodeToHead(Fvid2Utils_Handle handle,
                               Fvid2Utils_Node  *node);

/**
 *  Fvid2Utils_linkNodeToTail
 *  \brief                  Link the node to the tail of the double linked list.
 *                          No priority
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 */
void Fvid2Utils_linkNodeToTail(Fvid2Utils_Handle handle,
                             Fvid2Utils_Node  *node);

/**
 *  Fvid2Utils_unLinkNodeFromHead
 *  \brief                  Returns the node from head. Removes the  node from
 *                          the list.
 *
 *  \param handle           Link list handle.
 *  \return                 Pointer to unlinked node.
 *
 */
Fvid2Utils_Node *Fvid2Utils_unLinkNodeFromHead(Fvid2Utils_Handle handle);

/**
 *  Fvid2Utils_unLinkNodeFromTail
 *  \brief                  Returns the node from tail. Removes the  node from
 *                          the list.
 *
 *  \param handle           Link list handle.
 *  \return                 Pointer to unlinked node.
 *
 */
Fvid2Utils_Node *Fvid2Utils_unLinkNodeFromTail(Fvid2Utils_Handle handle);

/**
 *  Fvid2Utils_getHeadNode
 *  \brief                  Returns the reference to the headNode. Does
 *                          not remove the node from the head.
 *
 *  \param handle           Link list handle.
 */
Fvid2Utils_Node *Fvid2Utils_getHeadNode(Fvid2Utils_Handle handle);

/**
 *  Fvid2Utils_getTailNode
 *  \brief                  Returns the reference to the TailNode. Does
 *                          not remove the node from the head.
 *
 *  \param handle           Link list handle.
 *  \return                 Reference  to tail node.  Acutally  node is not
 *                          unlinked from list.
 *
 */
Fvid2Utils_Node *Fvid2Utils_getTailNode(Fvid2Utils_Handle handle);

/**
 *  Fvid2Utils_isListEmpty
 *  \brief Checks whether a list is empty or not.
 *
 *  \param handle           List handle.
 *
 *  \return                 TRUE if List is empty else returns FALSE.
 */
uint32_t Fvid2Utils_isListEmpty(Fvid2Utils_Handle handle);

/**
 *  Fvid2Utils_getNumNodes
 *  \brief Returns the number of nodes present in a list.
 *
 *  \param handle           List handle.
 *
 *  \return                 Number of nodes present in a list.
 */
uint32_t Fvid2Utils_getNumNodes(Fvid2Utils_Handle handle);

/**
 *  Fvid2Utils_getNodeCnt
 *  \brief Returns the number of nodes in the link list
 *
 *  \param handle           Link list handle.
 *
 *
 *  \return                 Returns the number of nodes in the list.
 */
uint32_t Fvid2Utils_getNodeCnt(Fvid2Utils_Handle handle);

/**
 *  Fvid2Utils_constructQ
 *  \brief Constructs a Queue object.
 *
 * \param llobj pointer to object of type Fvid2UtilsLinkListObj
 *
 *  \return                 Returns FVID2_SOK on success else returns error value.
 */
int32_t Fvid2Utils_constructQ(Fvid2UtilsLinkListObj *llobj);

/**
 *  Fvid2Utils_destructQ
 *  \brief Destructs a Queue object.
 *
 * \param llobj pointer to object of type Fvid2UtilsLinkListObj
 *
 *  \return                 None
 */
void Fvid2Utils_destructQ(Fvid2UtilsLinkListObj *llobj);

/**
 *  Fvid2Utils_queue
 *  \brief Adds the data to the queue.
 *  The memory to the node object should be allocated by the caller.
 *
 *  \param handle           Queue handle.
 *  \param qElem            Queue Element object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 */
void Fvid2Utils_queue(Fvid2Utils_QHandle handle,
                      Fvid2Utils_QElem  *qElem,
                      void              *data);

/**
 *  Fvid2Utils_dequeue
 *  \brief Removes a element from the queue.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Returns the removed data pointer.
 */
void *Fvid2Utils_dequeue(Fvid2Utils_QHandle handle);

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
void *Fvid2Utils_peakHead(Fvid2Utils_QHandle handle);

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
void *Fvid2Utils_peakTail(Fvid2Utils_QHandle handle);

/**
 *  Fvid2Utils_queueBack
 *  \brief Adds the data to start of the queue.
 *  The memory to the node object should be allocated by the caller.
 *
 *  \param handle           Queue handle.
 *  \param qElem            Queue Element object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 */
void Fvid2Utils_queueBack(Fvid2Utils_QHandle handle,
                          Fvid2Utils_QElem  *qElem,
                          void              *data);

/**
 *  Fvid2Utils_isQEmpty
 *  \brief Checks whether a queue is empty or not.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 TRUE if queue is empty else returns FALSE.
 */
uint32_t Fvid2Utils_isQEmpty(Fvid2Utils_QHandle handle);

/**
 *  Fvid2Utils_getNumQElem
 *  \brief Returns the number of Queue Elements present in a Queue.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Number of Queue Elements present in a Queue.
 */
uint32_t Fvid2Utils_getNumQElem(Fvid2Utils_QHandle handle);

/**
 *  Fvid2Utils_floor
 *  \brief Floor a integer value.
 *
 *  \param val          [IN] Integer to floor.
 *  \param align        [IN] Alignment.
 *
 *  \return Returns the floored integer.
 */
static inline uint32_t Fvid2Utils_floor(uint32_t val, uint32_t align);

/**
 *  Fvid2Utils_align
 *  \brief Align a integer value.
 *
 *  \param val          [IN] Integer to align.
 *  \param align        [IN] Alignment.
 *
 *  \return Returns the aligned integer.
 */
static inline uint32_t Fvid2Utils_align(uint32_t val, uint32_t align);

/**
 *  Fvid2Utils_initPool
 *  \brief Initializes the pool object structure.
 *
 *  \param params           Pool parameters to be initialized.
 *  \param mem              Pointer to the pool memory.
 *  \param numElem          Number of elements in the pool.
 *  \param elemSize         Size of each element in bytes.
 *  \param flag             Array of flag variable used by pool manager to
 *                          indicate whether a pool element is allocated
 *                          or not. The size of this array should be
 *                          equal to the number of elements in this pool.
 *  \param traceMask        Trace mask used in trace prints.
 */
static inline void Fvid2Utils_initPool(Fvid2Utils_PoolParams *params,
                                       void                  *mem,
                                       uint32_t               numElem,
                                       uint32_t               elemSize,
                                       uint32_t              *flag,
                                       uint32_t               traceMask);

/**
 *  Fvid2Utils_alloc
 *  \brief Allocates one element from the pool.
 *
 *  \param params           Pool parameters.
 *  \param size             Size in bytes to allocate.
 *  \param traceMask        Trace mask used in trace prints.
 *
 *  \return                 Returns memory pointer on success else returns
 *                          NULL.
 */
static inline void *Fvid2Utils_alloc(Fvid2Utils_PoolParams *params,
                                   uint32_t               size,
                                   uint32_t               traceMask);

/**
 *  Fvid2Utils_free
 *  \brief Frees the element and returns to the pool.
 *
 *  \param params           Pool parameters.
 *  \param mem              Memory pointer to deallocate.
 *  \param traceMask        Trace mask used in trace prints.
 *
 *  \return                 Returns 0 on success else returns error value.
 */
static inline int32_t Fvid2Utils_free(Fvid2Utils_PoolParams *params,
                                      const void            *mem,
                                      uint32_t               traceMask);

/**
 *  Fvid2Utils_initTsPrfLog
 *  \brief Initializes the structure. This should be called once before
 *  calling any other performance functions.
 *
 *  \param tsPrf            Pointer to Fvid2Utils_TsPrfLog structure.
 *
 */
static inline void Fvid2Utils_initTsPrfLog(Fvid2Utils_TsPrfLog *tsPrf);

/**
 *  Fvid2Utils_startTsPrfLog
 *  \brief Log the start entry to the performance structure.
 *
 *  \param tsPrf            Pointer to Fvid2Utils_TsPrfLog structure.
 */
static inline void Fvid2Utils_startTsPrfLog(Fvid2Utils_TsPrfLog *tsPrf);

/**
 *  Fvid2Utils_endTsPrfLog
 *  \brief Log the entry to the performance structure. This uses the previous
 *  startTime stored when calling Fvid2Utils_startTsPrfLog() to calculate the
 *  difference.
 *
 *  \param tsPrf            Pointer to Fvid2Utils_TsPrfLog structure.
 */
static inline void Fvid2Utils_endTsPrfLog(Fvid2Utils_TsPrfLog *tsPrf);

/**
 *  Osal_getTimestamp64
 *  \brief This API gets the 64 bit time stamp.
 */
static inline uint64_t Osal_getTimestamp64(void);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline uint32_t Fvid2Utils_floor(uint32_t val, uint32_t align)
{
    return ((uint32_t) ((val / align) * align));
}

static inline uint32_t Fvid2Utils_align(uint32_t val, uint32_t align)
{
    return (Fvid2Utils_floor((uint32_t) (val + (align - 1U)), align));
}

static inline void Fvid2Utils_initPool(Fvid2Utils_PoolParams *params,
                                       void                  *mem,
                                       uint32_t               numElem,
                                       uint32_t               elemSize,
                                       uint32_t              *flag,
                                       uint32_t               traceMask)
{
    uint32_t cnt;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL_PTR != params));
    GT_assert(traceMask, (NULL_PTR != mem));
    GT_assert(traceMask, (NULL_PTR != flag));

    /* Init pool parameters */
    params->mem         = mem;
    params->numElem     = numElem;
    params->elemSize    = elemSize;
    params->flag        = flag;
    params->numFreeElem = numElem;

    /* Set pool flags as free */
    for (cnt = 0U; cnt < params->numElem; cnt++)
    {
        params->flag[cnt] = (uint32_t) FALSE;
    }

    return;
}

static inline void *Fvid2Utils_alloc(Fvid2Utils_PoolParams *params,
                                     uint32_t               size,
                                     uint32_t               traceMask)
{
    uint32_t cnt;
    uintptr_t cookie;
    uintptr_t tempVal;
    void  *allocMem = NULL;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL_PTR != params));
    /* Check if the requested size if within each fixed size element */
    GT_assert(traceMask, (size <= params->elemSize));
    GT_assert(traceMask, (0U != size));

    /* Disable global interrupts */
    cookie = HwiP_disable();

    for (cnt = 0U; cnt < params->numElem; cnt++)
    {
        if ((uint32_t) FALSE == params->flag[cnt])
        {
            tempVal = ((uintptr_t) params->mem) + (((uintptr_t) params->elemSize) * ((uintptr_t) cnt));
            allocMem          = (void *) (tempVal);
            params->flag[cnt] = (uint32_t) TRUE;

            /* Decrement free count.
             * Assert if it is zero as it can never happen. */
            GT_assert(traceMask, (0U != params->numFreeElem));
            params->numFreeElem--;
            break;
        }
    }

    /* Restore global interrupts */
    HwiP_restore(cookie);

    return (allocMem);
}

static inline int32_t Fvid2Utils_free(Fvid2Utils_PoolParams *params,
                                      const void            *mem,
                                      uint32_t               traceMask)
{
    uint32_t cnt;
    uintptr_t tempVal;
    int32_t  retVal = FVID2_EFAIL;
    uintptr_t cookie;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL_PTR != params));
    GT_assert(traceMask, (NULL_PTR != mem));

    /* Disable global interrupts */
    cookie = HwiP_disable();

    for (cnt = 0U; cnt < params->numElem; cnt++)
    {
        tempVal = ((uintptr_t) params->mem) + (((uintptr_t)params->elemSize) * ((uintptr_t)cnt));
        if ((void *) (tempVal) == mem)
        {
            /* Check if the memory is already allocated */
            GT_assert(traceMask, ((uint32_t) TRUE == params->flag[cnt]));
            params->flag[cnt] = (uint32_t) FALSE;

            /* Increment free count.
             * Assert if it is more than num elements as it can never happen. */
            params->numFreeElem++;
            GT_assert(traceMask, (params->numFreeElem <= params->numElem));

            retVal = FVID2_SOK;
            break;
        }
    }

    /* Restore global interrupts */
    HwiP_restore(cookie);

    return (retVal);
}

static inline void Fvid2Utils_initTsPrfLog(Fvid2Utils_TsPrfLog *tsPrf)
{
    /* NULL pointer check */
    GT_assert(GT_DEFAULT_MASK, (NULL_PTR != tsPrf));

    Fvid2Utils_memset(tsPrf, 0, sizeof (Fvid2Utils_TsPrfLog));
    /* Min can't be init to 0, set a higher value so that actual min gets
     * registered */
    tsPrf->min = 0xFFFFFFFFU;

    return;
}

static inline void Fvid2Utils_startTsPrfLog(Fvid2Utils_TsPrfLog *tsPrf)
{
    /* NULL pointer check */
    GT_assert(GT_DEFAULT_MASK, (NULL_PTR != tsPrf));

    tsPrf->startTime = Osal_getTimestamp64();

    return;
}

static inline void Fvid2Utils_endTsPrfLog(Fvid2Utils_TsPrfLog *tsPrf)
{
    uint64_t endTime, diff;

    /* NULL pointer check */
    GT_assert(GT_DEFAULT_MASK, (NULL_PTR != tsPrf));

    endTime = Osal_getTimestamp64();
    diff    = endTime - tsPrf->startTime;

    /* Log the difference */
    tsPrf->total += diff;
    tsPrf->totalCnt++;
    if (diff < tsPrf->min)
    {
        tsPrf->min = diff;
    }
    if (diff > tsPrf->max)
    {
        tsPrf->max = diff;
    }
    if (tsPrf->prfLogIndex >= FVID2UTILS_NUM_TIMESTAMP_LOG)
    {
        tsPrf->prfLogIndex = 0U;
    }
    tsPrf->prfLog[tsPrf->prfLogIndex] = diff;
    tsPrf->prfLogIndex++;

    return;
}

static inline uint64_t Osal_getTimestamp64(void)
{
    //TODO: Call OSAL API once implementation is done
    return (0U);
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FVID2_UTILS_H_ */
