/*********************************************
// base.h
// 1.declaration of almost all globle variables.
// 2.definition of almost all structures.
// 3.description of almost complier options.
*********************************************/

#define _windows_
#define NDEBUG
#define QUICK
//#define OUTPUT

#ifndef HEADFILES
#define HEADFILES
    #include <iostream>
    #include <fstream>
    #include <bitset>
    #include <cassert>
    #include <cstdio>
    #include <cstdlib>
    #include <cctype>
    #include <cmath>
#endif // HEADFILES

// The MaxValue of gcc ARRAY support 268435456(2^28)
#ifndef QUICK
#define MAX_CACHE_LINE 268435456
#endif

#define MAX_CACHE_LINE 65536


#ifndef STRUCT_TYPE
#define STRUCT_TYPE
    // �ڴ��ַ��Cache��ַ�Ĺ�����ʽ��ֱ��ӳ�䡢��������ȫ����
    enum associativity_way{direct_mapped=1,set_associative,full_associative};

    // �滻���ԣ�none��ֱ���滻����FIFO���Ƚ��ȳ��㷨����LRU������������㷨����LFU����������㷨����Random������滻�㷨��
    enum replacement_way{none,FIFO=1,LRU,LFU,Random};

    // д���ԣ�write_through��ȫд������write_back����д����
    enum write_way{write_through=1,write_back};
#endif // STRUCT_TYPE


typedef enum associativity_way ASSOC;
typedef enum replacement_way REPLACE;
typedef enum write_way WRITE;

/******************************************/
extern unsigned int i_cache_size; //cache size
extern unsigned int i_cache_line_size; //cacheline size
extern unsigned int i_num_line; //How many lines of the cache.

extern ASSOC t_assoc; //associativity method
extern REPLACE t_replace; //replacement policy
extern WRITE t_write; //write policy
/******************************************/

/******************************************/
extern short unsigned int bit_block; //How many bits of the block.
extern short unsigned int bit_line; //How many bits of the line.
extern short unsigned int bit_tag; //How many bits of the tag.
/******************************************/

/******************************************/
extern unsigned long int i_num_access; //Number of cache access
extern unsigned long int i_num_load; //Number of cache load
extern unsigned long int i_num_store; //Number of cache store
extern unsigned long int i_num_space; //Number of space line

extern unsigned long int i_num_hit; //Number of cache hit
extern unsigned long int i_num_load_hit; //Number of load hit
extern unsigned long int i_num_store_hit; //Number of store hit

extern float f_ave_rate; //Average cache hit rate
extern float f_load_rate; //Cache hit rate for loads
extern float f_store_rate; //Cache hit rate for stores
/******************************************/

extern std::bitset<32> cache_item[MAX_CACHE_LINE]; // [31]:valid,[30]:hit,[29]:dirty,[28]-[0]:data
extern unsigned long int line; // The line num which is processing
extern unsigned long int i,j; //For loop


