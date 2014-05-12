//functions.h

#define _windows_

#ifndef headfiles
#define headfiles
    #include <iostream>
    #include <fstream>
    #include <cstdio>
    #include <cstdlib>
    #include <cctype>
#endif

#ifndef types
#define types
    // �ڴ��ַ��Cache��ַ�Ĺ�����ʽ��ֱ��ӳ�䡢��������ȫ����
    enum associativity_way{direct_mapped=1,set_associative,full_associative};
    // �滻���ԣ�FIFO���Ƚ��ȳ��㷨����LRU������������㷨����LFU����������㷨����Random������滻�㷨��
    enum replacement_way{FIFO=1,LRU,LFU,Random};
    // д���ԣ�write_through��ȫд������write_back����д����
    enum write_way{write_through=1,write_back};

    typedef enum associativity_way ASSOC;
    typedef enum replacement_way REPLACE;
    typedef enum write_way WRITE;
#endif // types

    /******************************************/
    /* for input */
    extern int i_cache_size; //cache size
    extern int i_cache_line_size; //cacheline size
    extern ASSOC t_assoc; //associativity method
    extern REPLACE t_replace; //replacement policy
    extern WRITE t_write; //write policy
    /* for input */
    /******************************************/

    /******************************************/
    /* for output */
    extern int i_num_access; //Number of cache access
    extern int i_num_load; //Number of cache load
    extern int i_num_store; //Number of cache store
    extern float f_ave_rate; //Average cache hit rate
    extern float f_load_rate; //Cache hit rate for loads
    extern float f_store_rate; //Cache hit rate for stores
    /* for output */
    /******************************************/

void PrintAuthorInfo(void);
void InitVariables(void);
void GetInput(void);
void FileTest(void);
void PrintOutput(void);
void PrintBye(void);
