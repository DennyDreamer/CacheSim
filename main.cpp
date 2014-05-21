#include "functions.h"
#include "jiangxin.h"

using namespace std;

int main()
{
    #ifdef NDEBUG
    jx_PrintAuthorInfo();
    #endif // NDBUG

    char ch = '\0';
do
{
    InitVariables();
    GetInput(); // get input information
    CalcInfo();
    CreateCache();
    FileTest();
    PrintOutput(); // output the result
    cout << "Continue/Exit(C/E)" << endl;
    cin >> ch;
    ch = tolower(ch);
}while(ch != 'e');

    jx_PrintBye();
    return 0;
}
