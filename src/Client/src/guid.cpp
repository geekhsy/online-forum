#include "guid.h"
#include <objbase.h>
#include <string>

using namespace std;

string generateGuid() //产生全局唯一ID
{
    GUID guid;
    CoCreateGuid(&guid);
    char cBuffer[64] = {0};
    //将结构体转换为string
    sprintf_s(cBuffer, sizeof(cBuffer),
    "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
    guid.Data1, guid.Data2,
    guid.Data3, guid.Data4[0],
    guid.Data4[1], guid.Data4[2],
    guid.Data4[3], guid.Data4[4],
    guid.Data4[5], guid.Data4[6],
    guid.Data4[7]);
    return string(cBuffer);
}
