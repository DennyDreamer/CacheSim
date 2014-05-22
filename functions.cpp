/*************************************************
// functions.cpp
// 1.Defination of almost all functions.
*************************************************/

#include "functions.h"

using namespace std;

bool GetHitNum(char *address)
{
    bool is_store = false;
    bool is_load = false;
    bool is_space = false;
    bool hit = false;
    switch(address[0])
    {
        case 's':is_store = true;break;
        case 'l':is_load = true;break;
        //case ' ':break; //Waring if a line has nothing,the first of it is a '\0' nor a ' '
        case '\0':is_space = true;break; //In case of space lines
        default:
            cout << "The address[0] is:" <<address[0] << endl;
            cout << "ERROR IN JUDGE!" << endl;return false;
    }
    temp = strtoul(address+2,NULL,16);
    bitset<32> flags(temp); // flags if the binary of address

    #ifndef NDEBUG
    cout << flags << endl;
    #endif // NDEBUG

    hit = IsHit(flags);

    if(hit && is_load) // ���У�������
    {
        i_num_access++;
        i_num_load++;
        i_num_load_hit++;
        i_num_hit++;

        #ifndef NDEBUG
        cout << "Loading" << endl;
        cout << "Hit" << endl;
        cout << "Read from Cache!" << endl;
        #endif // NDEBUG
        if(t_replace == LRU)
        {
            LruHitProcess();
        }

    }
    else if(hit && is_store) // ���У�д����
    {
        i_num_access++;
        i_num_store++;
        i_num_store_hit++;
        i_num_hit++;

        #ifndef NDEBUG
        cout << "Storing" << endl;
        cout << "Hit" << endl;
        cout << "Write to Cache" << endl;
        #endif // NDEBUG

        cache_item[current_line][29] = true; //����dirtyΪtrue
        if(t_replace == LRU)
        {
            LruHitProcess();
        }

    }
    else if((!hit) && is_load) // û���У�������
    {
        i_num_access++;
        i_num_load++;

        #ifndef NDEBUG
        cout << "Loading" << endl;
        cout << "Not Hit" << endl;
        #endif // NDEBUG

        GetRead(flags); // read data from memory

        #ifndef NDEBUG
        cout << "Read from Cache!" << endl;
        #endif // NDEBUG

        if(t_replace == LRU)
        {
            LruUnhitSpace();
        }

    }
    else if((!hit) && is_store) // û���У�д����
    {
        i_num_access++;
        i_num_store++;

        #ifndef NDEBUG
        cout << "Storing" << endl;
        cout << "Not Hit" << endl;
        #endif // NDEBUG

        GetRead(flags); // read data from memory

        #ifndef NDEBUG
        cout << "Write to Cache" << endl;
        #endif // NDEBUG

        cache_item[current_line][29] = true; //����dirtyΪtrue
        if(t_replace == LRU)
        {
            LruUnhitSpace();
        }
    }
    else if(is_space)
    {
        i_num_space++;
    }
    else
    {
        cerr << "Something ERROR" << endl;
        return false;
    }
    if(i_num_space != 0)
    {
        #ifndef NDEBUG
        cout << "There have " << i_num_space << " space lines" << endl;
        #endif // NDEBUG
    }

    return true;
}

bool IsHit(bitset<32> flags)
{
    bool ret = false;
    if(t_assoc == direct_mapped)
    {
        bitset<32> flags_line; // a temp variable
        for(j=0,i=(bit_block);i<(bit_block+bit_line);j++,i++) //�ж���cache������
        {
            flags_line[j] = flags[i];
        }
        current_line = flags_line.to_ulong();

        assert(cache_item[current_line][31] == true);

        if(cache_item[current_line][30]==true) //�ж�hitλ�Ƿ�Ϊ��
        {
            ret = true;
            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //�жϱ���Ƿ���ͬ,i:address,j:cache
            {
                if(flags[i] != cache_item[current_line][j])
                {
                    ret = false;
                    break;
                }
            }
        }
    }
	else if(t_assoc == full_associative)
    {
        for(temp=0;temp<i_num_line;temp++)
        {
            if(cache_item[temp][30]==true) //�ж�hitλ�Ƿ�Ϊ��
            {
                ret = true;
                for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //�жϱ���Ƿ���ͬ,i:address,j:cache
                {

                    if(flags[i] != cache_item[temp][j])
                    {
                        ret = false;
                        break;
                    }
                }
            }
            if(ret == true)
            {
                current_line = temp;
                break;
            }
        }

    }
    else if(t_assoc == set_associative)
    {
        bitset<32> flags_set;
        for(j=0,i=(bit_block);i<(bit_block+bit_set);j++,i++) //�ж���cache������
        {
            flags_set[j] = flags[i];
        }
        current_set = flags_set.to_ulong();
        for(temp=(current_set*i_cache_set);temp<((current_set+1)*i_cache_set);temp++)
        {
            if(cache_item[temp][30]==true) //�ж�hitλ�Ƿ�Ϊ��
            {
                ret = true;
                for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //�жϱ���Ƿ���ͬ,i:address,j:cache
                {

                    if(flags[i] != cache_item[temp][j])
                    {
                        ret = false;
                        break;
                    }
                }
            }
            if(ret == true)
            {
                current_line = temp;
                break;
            }
        }
    }
    return ret;
}

void GetRead(bitset<32> flags)
{
    if(t_assoc == direct_mapped)
    {
        if(cache_item[current_line][30] == false) //hit is false
        {
            #ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
            #endif // NDEBUG
            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //���ñ��
            {
                cache_item[current_line][j] = flags[i];
                assert(j>0);
            }
            cache_item[current_line][30] = true; //����hitλΪtrue
        }
        else
        {
            GetReplace(flags);
        }
    }
	else if(t_assoc == full_associative)
    {
        bool space = false;
        for(temp=0;temp<i_num_line;temp++)
        {
            if(cache_item[temp][30] == false) //find a space line
            {
                space = true;
                break;
            }
        }

        if(space == true)
        {
            current_line = temp; // �˴���temp�����1����Ϊһ�����ֿ��У�����forѭ����break����ʱtemp��δ++
            #ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
            #endif // NDEBUG

            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //���ñ��
            {
                cache_item[current_line][j] = flags[i];
                assert(j>0);
            }
            cache_item[current_line][30] = true; //����hitλΪtrue.
            if(t_replace == LRU)
            {
                LruUnhitSpace();
            }

        }
        else
        {
            GetReplace(flags);
        }
    }
    else if(t_assoc == set_associative)
    {
        bool space = false;
        for(temp=(current_set*i_cache_set);temp<((current_set+1)*i_cache_set);temp++)
        {
            if(cache_item[temp][30] == false) //find a space line
            {
                space = true;
                break;
            }
        }
        if(space == true)
        {
            current_line = temp; // �˴���temp�����1����Ϊһ�����ֿ��У�����forѭ����break����ʱtemp��δ++
            #ifndef NDEBUG
            cout << "Read from Main Memory to Cache!" << endl;
            #endif // NDEBUG

            for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //���ñ��
            {
                cache_item[current_line][j] = flags[i];
                assert(j>0);
            }
            cache_item[current_line][30] = true; //����hitλΪtrue.
            if(t_replace == LRU)
            {
                LruUnhitSpace();
            }
        }
        else
        {
            GetReplace(flags);
        }
    }
}

void GetReplace(bitset<32> flags)
{
    if(t_assoc == direct_mapped)
    {
    }
	else if(t_assoc == full_associative)
    {
    	if(t_replace == Random)
        {
            current_line = rand()/(RAND_MAX/i_num_line+1); // a random line in(0,i_num_line-1)
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
            temp = rand()/(RAND_MAX/i_cache_set+1); // a random line in(0,i_cache_set-1)
            current_line = current_set*i_cache_set+temp; // a random line in current_set
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
	cout << "Read from Main Memory to Cache: " << endl;
	#endif // NDEBUG

    for(i=31,j=28;i>(31ul-bit_tag);i--,j--) //���ñ��
    {
        cache_item[current_line][j] = flags[i];
        assert(j>0);
    }
    cache_item[current_line][30] = true; //����hitλΪtrue
}

void GetWrite() //д���ڴ�
{
    #ifndef NDEBUG
    cout << "Writing to the Main Memory!" <<endl;
    #endif
    cache_item[current_line][29] = false; //����dirtyΪfalse
    cache_item[current_line][30] = false; //����hitΪfalse
}

void GetHitRate()
{
    assert(i_num_access != 0);
    assert(i_num_load != 0);
    assert(i_num_store != 0);
    f_ave_rate = ((double)i_num_hit)/i_num_access; //Average cache hit rate
    f_load_rate = ((double)i_num_load_hit)/i_num_load; //Cache hit rate for loads
    f_store_rate = ((double)i_num_store_hit)/i_num_store; //Cache hit rate for stores
}

