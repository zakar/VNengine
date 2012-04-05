#include <cstdlib>

#define _INLINE 

template<typename type, int blockSize>
class BlockAllocator {
 public:
  BlockAllocator(void);
  ~BlockAllocator(void);
  void Init(void);
  void Shutdown(void);
  
  type* Allocate(void);
  void Free(type*);

 private:
  
  typedef struct single_member {
    single_member* next;
    type member;
  } single_member;

  typedef struct block_header {
    block_header* next;
  } block_header;

  block_header* firstBlock;
  single_member* freeMember;

  int total;
  int active;
};

template<typename type, int blockSize>
_INLINE BlockAllocator<type, blockSize>::BlockAllocator(void)
{
  firstBlock = NULL;
  freeMember = NULL;
  total = 0;
  active = 0;
}

template<typename type, int blockSize>
_INLINE BlockAllocator<type, blockSize>::~BlockAllocator(void)
{
  void* cur;
  while (firstBlock != NULL) {
    cur = (void*)firstBlock;
    firstBlock = firstBlock->next;
    std::free(cur);
  }
}

template<typename type, int blockSize>
_INLINE void BlockAllocator<type, blockSize>::Init(void)
{
  
}

template<typename type, int blockSize>
_INLINE void BlockAllocator<type, blockSize>::Shutdown(void)
{
  
}

template<typename type, int blockSize>
_INLINE type* BlockAllocator<type, blockSize>::Allocate()
{
  if (freeMember == NULL) {
    block_header* block = (block_header*)std::malloc(sizeof(block_header) + blockSize * sizeof(single_member));
    block->next = firstBlock;
    firstBlock = block;

    single_member* cur = (single_member*)((char*)block + sizeof(block_header*));
    int i;
    for (i = 0; i < blockSize; ++i, ++cur) {
      cur->next = freeMember;
      freeMember = cur;
    }

    ++total;
  }

  type* cur = (type*)((char*)freeMember + sizeof(single_member*));
  freeMember = freeMember->next;
  ++active;
  return cur;
}

template<typename type, int blockSize>
_INLINE void BlockAllocator<type, blockSize>::Free(type* member)
{
  single_member* cur = (single_member*)((char*)member - sizeof(single_member*));
  cur->next = freeMember;
  freeMember = cur;
  --active;
}
