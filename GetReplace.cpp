#include "functions.h"

using namespace std;

void GetReplace(bitset<32> flags,unsigned long int& current_line)
{
    if(t_assoc == direct_mapped)
    {
    }
	else if(t_assoc == full_associative)
    {
    	if(t_replace == Random)
        {
            current_line = rand()/(RAND_MAX/i_num_line+1); // ������������ѡһ�У������滻
        }
        else if(t_replace == LRU)
        {
            LruUnhitUnspace();
        }
    }
    else if(t_assoc == set_associative) // �ӱ�������ѡһ�У������滻
    {
        if(t_replace == Random)
        {
            temp = rand()/(RAND_MAX/i_cache_set);
            current_line = current_set*i_cache_set+temp;
        }
        else if(t_replace == LRU)
        {
            LruUnhitUnspace();
        }
    }
    if(cache_item[current_line][29] == true) //dirtyλ����Ϊ1��д��
    {
        GetWrite(); //д���ڴ�
    }
	#ifndef NDEBUG
	cout << "Update the Content of Cache: " << current_line << endl;
	#endif // NDEBUG
    for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //���ñ��
    {
        cache_item[current_line][j] = flags[i];
    }
    cache_item[current_line][30] = true; //����hitλΪtrue
}
