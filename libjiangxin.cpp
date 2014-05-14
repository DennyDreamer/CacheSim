// libjiangxin.cpp

#include "stdio.h"
#include "ctype.h"
#include "jiangxin.h"

char jx_getchar(short option)
{
    char ch,temp;
    ch = getchar();
    if(ch == '\n') //ֱ������س�������'\n'
        return '\n';
    else if((temp=getchar())!='\n') //����һЩ�ַ�����ֹһ������Ȼ��س�����������ַ��󷵻�'\n'
    {
        while((temp=getchar())!='\n' && temp!=EOF);
        return '\n';
    }
    else //����һ���ַ������س��������������Сдת����ֱ�ӷ���
    {
        switch(option)
        {
            case 1:ch = tolower(ch);break;
            case 2:ch = toupper(ch);break;
            default:
                perror("Error Argument:option\n");
                break;
        }
        return ch;
    }
}
