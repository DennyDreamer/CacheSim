#include "functions.h"

using namespace std;


void CalcInfo()
{
    assert(i_cache_line_size != 0);
    i_num_line = (i_cache_size<<10)/i_cache_line_size;

    temp = i_cache_line_size;
    while(temp)
    {
        temp >>= 1;
        bit_block++;
    }
    bit_block--; //warning
    if(t_assoc == direct_mapped)
    {
        bit_set = 0; // for direct_mapped,the bit_set is 0
        temp = i_num_line;
        while(temp)
        {
            temp >>= 1;
            bit_line++;
        }
        bit_line--; //warning
    }
    else if(t_assoc == full_associative)
    {
        bit_line = 0; // for full_associative,the bit_line is 0
        bit_set = 0; // for full_associative,the bit_set is 0
    }
    else if(t_assoc == set_associative)
    {
        bit_line = 0; // for set_associative,the bit_line is 0
        assert(i_cache_set != 0);
        assert(i_num_line > i_cache_set);
        i_num_set = i_num_line/i_cache_set;
        temp = i_num_set;
        while(temp)
        {
            temp >>= 1;
            bit_set++;
        }
        bit_set--;
    }

    bit_tag = 32ul - bit_block - bit_line - bit_set;
    assert(bit_tag <= 29); //32-valid-hit-dirty
    cout << "i_cache_line_size: " << i_cache_line_size << "B" << endl; // ��ʾ���С
    cout << "i_cache_size: " << i_cache_size << "KB" << endl; // ��ʾcache������������
    if(t_assoc == set_associative) // ���Ϊ����������ʾ�Ǽ�·������
    {
        cout << "i_cache_set: " << i_cache_set << " lines each set" << endl;
    }
    cout << "i_num_line: " << i_num_line << endl; // ��ʾ���ж�����
    if(t_assoc == set_associative) // ���Ϊ����������ʾ���м���
    {
        cout << "i_num_set: " << i_num_set << endl;
    }
    cout << "bit_block: " << bit_block << endl; // ��ʾ���ڵ�ַ����λ��
    if(t_assoc == direct_mapped) // ���Ϊֱ��ӳ�䣬��ʾ�к�����λ��
    {
        cout << "bit_line: " << bit_line << endl;
    }
    if(t_assoc == set_associative) // ���Ϊ����������ʾ�������λ��
    {
        cout << "bit_set: " << bit_set << endl;
    }
    cout << "bit_tag: " << bit_tag << endl; // ��ʾ��־λ����λ��
}
