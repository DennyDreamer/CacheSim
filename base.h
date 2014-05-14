//base.h

#define _windows_
#define NDEBUG
//#define OUTPUT

#ifndef headfiles
#define headfiles
    #include <iostream>
    #include <fstream>
    #include <bitset>
    #include <cassert>
    #include <cstdio>
    #include <cstdlib>
    #include <cctype>
    #include <cmath>
#endif

#define MAX_CACHE_LINE 100000000

#ifndef types
#define types
    // �ڴ��ַ��Cache��ַ�Ĺ�����ʽ��ֱ��ӳ�䡢��������ȫ����
    enum associativity_way{direct_mapped=1,set_associative,full_associative};
    // �滻���ԣ�FIFO���Ƚ��ȳ��㷨����LRU������������㷨����LFU����������㷨����Random������滻�㷨��
    enum replacement_way{none,FIFO=1,LRU,LFU,Random};
    // д���ԣ�write_through��ȫд������write_back����д����
    enum write_way{write_through=1,write_back};

    typedef enum associativity_way ASSOC;
    typedef enum replacement_way REPLACE;
    typedef enum write_way WRITE;
#endif // types

    /******************************************/
    /* for input */
    extern unsigned int i_cache_size; //cache size
    extern unsigned int i_cache_line_size; //cacheline size

    extern ASSOC t_assoc; //associativity method
    extern REPLACE t_replace; //replacement policy
    extern WRITE t_write; //write policy
    /* for input */
    /******************************************/

    /******************************************/
    /* for temp */
    extern unsigned int i_num_line; //How many lines of the cache.
    extern short unsigned int bit_block; //How many bits of the block.
    extern short unsigned int bit_line; //How many bits of the line.
    extern short unsigned int bit_tag; //How many bits of the tag.
    /* for temp */
    /******************************************/

    /******************************************/
    /* for output */
    extern unsigned long int i_num_access; //Number of cache access
    extern unsigned long int i_num_load; //Number of cache load
    extern unsigned long int i_num_store; //Number of cache store

    extern unsigned long int i_num_hit; //Number of cache hit
    extern unsigned long int i_num_load_hit; //Number of load hit
    extern unsigned long int i_num_store_hit; //Number of store hit

    extern float f_ave_rate; //Average cache hit rate
    extern float f_load_rate; //Cache hit rate for loads
    extern float f_store_rate; //Cache hit rate for stores

    extern unsigned long int i_num_space; //Number of space line
    /* for output */
    /******************************************/
    extern std::bitset<32> cache_item[MAX_CACHE_LINE],*p_cache_item;
    extern unsigned long int line;
    extern unsigned long int i,j;
