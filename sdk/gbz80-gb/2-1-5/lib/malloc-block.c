/** @name malloc-block
    Implementation of malloc() and free() where all block
*/
#include <config.h>

#if USE_BLOCK_BASED_MALLOC

#include <stdlib.h>

extern BYTE malloc_heap_start[];

/* Currently uses 4k */
#define NUM_TYPES	4

#define NUM_TYPE_0	32
#define SIZE_TYPE_0	32

#define NUM_TYPE_1	16
#define SIZE_TYPE_1	64

#define NUM_TYPE_2	8
#define SIZE_TYPE_2	128

#define NUM_TYPE_3	4
#define SIZE_TYPE_3	256

#define TOTAL_SIZE 	((NUM_TYPE_0*SIZE_TYPE_0) + \
 			 (NUM_TYPE_1*SIZE_TYPE_1) + \
			 (NUM_TYPE_2*SIZE_TYPE_2) + \
			 (NUM_TYPE_3*SIZE_TYPE_3))

typedef struct _MALLOC_HUNK MALLOC_HUNK;
  
struct _MALLOC_HUNK {
    MALLOC_HUNK *pNext;
    BYTE bFlags;
};

typedef struct {
    MALLOC_HUNK *pFirst;
} MALLOC_SECTION;

/** Array of all sections */
static MALLOC_SECTION _aSections[NUM_TYPES];

/** Size of the header on each hunk */
#define HEADER_OVERHEAD sizeof(MALLOC_HUNK)

/** Used in malloc_init() */
static const UWORD _awSizes[NUM_TYPES] = {
    SIZE_TYPE_0, SIZE_TYPE_1, SIZE_TYPE_2, SIZE_TYPE_3
};

/** Used in malloc_init() */
static const UBYTE _abNums[NUM_TYPES] = {
    NUM_TYPE_0, NUM_TYPE_1, NUM_TYPE_2, NUM_TYPE_3
};

/** Initialise all the secions and hunks */
void malloc_init_region(BYTE *pBase)
{
    MALLOC_HUNK *pLast;
    MALLOC_SECTION *pSect;
    UWORD wSize;
    UBYTE b;
    UBYTE bType;

    for (bType = 0; bType != NUM_TYPES; bType++) {
	wSize = _awSizes[bType];
	pLast = NULL;
	for (b = _abNums[bType]; b; --b) {
	    ((MALLOC_HUNK *)pBase)->bFlags = bType;
	    ((MALLOC_HUNK *)pBase)->pNext = pLast;
	    pLast = (MALLOC_HUNK *)pBase;
	    pBase += wSize;
	}
	_aSections[bType].pFirst = pLast;
    }
}

BYTE malloc_init(void)
{
    malloc_init_region(malloc_heap_start+1);
    *malloc_heap_start = 1;
    return 0;
}

/** Allocate memory.
 */
void *malloc(UWORD wSize)
{
    MALLOC_SECTION *pSect = NULL;
    MALLOC_HUNK *pRet;

    wSize += HEADER_OVERHEAD;

    if (wSize <= SIZE_TYPE_0) {
	pSect = &_aSections[0];
    }
    else if (wSize <= SIZE_TYPE_1) {
	pSect = &_aSections[1];
    }
    else if (wSize <= SIZE_TYPE_2) {
	pSect = &_aSections[2];
    }
    else if (wSize <= SIZE_TYPE_3) {
	pSect = &_aSections[3];
    }
    else {
	/* Wont fit into any of the blocks */
	return NULL;
    }
    if ((pRet = pSect->pFirst)) {
	/* There's at least one block free.  Return the one from
	   the top of the list. */
	pSect->pFirst = pRet->pNext;
	return (void *)((BYTE *)pRet + HEADER_OVERHEAD);
    }
    /* No free blocks in this class */
    return NULL;
}

BYTE free(void *pToFree)
{
    MALLOC_HUNK *pHunk;
    MALLOC_SECTION *pSect;

    if (pToFree) {
	/* Adjust the pointer so we get ahold of the header */
	pHunk = (MALLOC_HUNK *)((BYTE *)pToFree - HEADER_OVERHEAD);
	pSect = &_aSections[pHunk->bFlags&3];
	pHunk->pNext = pSect->pFirst;
	pSect->pFirst = pHunk;
    }
    return 0;
}

void *calloc(UWORD nmemb, UWORD size)
{
    BYTE *pRet;
    pRet = (BYTE *)malloc(nmemb*size);
    if (pRet) {
	memset(pRet, 0, nmemb*size);
    }
    return pRet;
}

void *realloc(void *p, UWORD wLen)
{
    BYTE *pNew;
    pNew = malloc(wLen);
    if (pNew) {
	memcpy(pNew, (BYTE *)p, wLen);
	free(p);
    }
    return pNew;
}
#endif
