//functions.h

#ifndef headfiles
#define headfiles
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
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

void PrintAuthorInfo(void);
void GetInput(int& i_cache_size,int& i_cache_line_size,ASSOC& t_assoc,REPLACE& t_replace,WRITE& t_write);
void PrintOutput(int i_cache_size,int i_cache_line_size,
                 ASSOC t_assoc,REPLACE t_replace,WRITE t_write,
                 int i_num_access,int i_num_load,int i_num_store,
                 float f_ave_rate,float f_load_rate,float f_store_rate);
void PrintBye();
