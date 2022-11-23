
#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif


u32 mlib_strToIp(char* ipStr)
{
    int j =0,a=3;
    char str_ip_index[4]={'\0'};
    unsigned int ip_int,ip_add=0,ip_int_index[4],ip_temp_numbr=24; 
    for(unsigned int i =0;i<=mlib_strlen(ipStr);i++)//要用到''  
    {  
        if (ipStr[i]=='\0'||ipStr[i]=='.')  
        {             
            ip_int =mlib_atoi(str_ip_index);   
            if (ip_int<0||ip_int>255)  
            {  
                ASSERT("IP parse error\r\n");
                return 0;                 
            }  

            ip_add+=(ip_int*((unsigned int)pow(256.0,a)));            
            a--;  
            BF_memset(str_ip_index,0,sizeof(str_ip_index));  
            j=0;  
            continue;  
        }  

        str_ip_index[j]=ipStr[i];  
        j++;  
    }

    return ip_add;
}

static unsigned char unicode_number[22]={0x00,0x31,0x00,0x37,0x00,0x38,0x00,0x31,0x00,0x31,
                                0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x39,0x00,0x32,0x00,0x37};
static unsigned char consumer_number[100]={0}; 
/***********************************************************************
* 功能：将一个十六进制字节串转换成ASCII码表示的十六进制字符串
* 输入参数：pHex----十六进制数字节串首地址
*                   pAscii---转换后ASCII码表示的十六进制字符串首地址
*                   nLen---要转换的十六进制数长度（字节数）
* 注：转换后的结果全部是大写ASCII码表示的十六进制数
*此部分百度的
************************************************************************/
void mlib_hexToAscii(unsigned char *pHex, unsigned char *pAscii, int nLen)
{
    unsigned char Nibble[2];
    unsigned int i,j;
    for (i = 0; i < nLen; i++){
        Nibble[0] = (pHex[i] & 0xF0) >> 4;
        Nibble[1] = pHex[i] & 0x0F;
        for (j = 0; j < 2; j++){
            if (Nibble[j] < 10){            
                Nibble[j] += 0x30;
            }
            else{
                if (Nibble[j] < 16)
                    Nibble[j] = Nibble[j] - 10 + 'A';
            }
            *pAscii++ = Nibble[j];
        }               // for (int j = ...)
    }           // for (int i = ...)
}


int mlib_stringToHex(char *str, int inlen, unsigned char *out, unsigned int *outlen)
{
    char *p = str;
    char high = 0, low = 0;
    int  cnt = 0;

    while(inlen)
    {
        while(*p == ' ')
        {
            p ++;
            inlen--;
        }

        if (inlen == 0)
            break;

        high = ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;

        p ++;
        inlen--;

        while(*p == ' ')
        {
            p ++;
            inlen--;
        }

        if (inlen == 0)
        {
            ASSERT("mlib_stringToHex error\r\n");
        }

        low = (*(p) > '9' && ((*p <= 'F') || (*p <= 'f'))) ? *(p) - 48 - 7 : *(p) - 48;
        p ++;
        inlen--;

        out[cnt] = ((high & 0x0f) << 4 | (low & 0x0f));
        cnt ++;
    }

    if(outlen != NULL) 
        *outlen = cnt;

    return cnt;
}


int mlib_findFirstLetter(char *buf, char a)
{
    int i = 0;
    while(buf[i] != 0)
    {
        //
        if (buf[i] == a)
        {
            return i;
        }

        i++;
    }

    return i;
}


int mlib_findFirstSpace(char *buf)
{
    int i = 0;
    while(buf[i] != 0)
    {
        //
        if (buf[i] == ' ')
        {
            return i;
        }

        i++;
    }

    return i;
}

int mlib_findSecondQuotation(char *buf)
{
    int i = 0;

    int k =0;
    while(buf[i] != 0)
    {
        //
        if (buf[i] == '\"')
        {
            k++;
        }

        if (k == 2)
            return i;

        i++;
    }

    return -1;
}


void mlib_getLineBuf(char* buf, char** file, int* length)
{
    int i;
    int j = 0;

    for(i = 0; i < *length; i++)
    {
        buf[j++] = (*file)[i];

        if((*file)[i] == '\n')
        {
            buf[j] = 0;

            *length = *length - j;
            (*file) = (*file) + j;

            return;
        }
    }


    if (*length == 0)
        buf[0] = 0;

    return;
}

int mlib_searchMemory(char* mem, int lenmem, char* buf, int lenbuf)
{
    int length = lenbuf - lenmem;
    int i;

    if (length < 0)
        return length;

    for(i = 0;i < (length + 1); i++)
    {
        //BF_printf("mlib_searchMemory       %s          %s       %d\r\n",mem,buf +i, lenmem);
        if(mlib_memcmp(mem, buf + i, lenmem) == 0)
            return i;
    }

    return -1;
}

char* mlib_getTypeName(int type)
{
    if (type == ElementType_Buf)
        return "Buf(Blob)";

    if (type == ElementType_String)
        return "String";

    if (type == ElementType_Number)
        return "Number";

    if (type == ElementType_Padding)
        return "Padding";

    if (type == ElementType_Bit)
        return "Bit(Flag)";

    if (type == ElementType_S8)
        return "S8";

    if (type == ElementType_S16)
        return "S16";

    if (type == ElementType_S32)
        return "S32";

    if (type == ElementType_S64)
        return "S64";

    if (type == ElementType_U8)
        return "U8";

    if (type == ElementType_U16)
        return "U16";

    if (type == ElementType_U32)
        return "U32";

    if (type == ElementType_U64)
        return "U64";

    if (type == ElementType_Float)
        return "Float";

    if (type == ElementType_Double)
        return "Double";

    if (type == ElementType_Struct)
        return "Struct(Block)";

    if (type == ElementType_Bits)
        return "Bits(Flags)";

    if (type == ElementType_Array)
        return "Array";

    if (type == ElementType_Union)
        return "Union(Choice)";

    if (type == ElementType_Relation)
        return "Relation";

    if (type == ElementType_Fixup)
        return "Fixup";

    if (type == ElementType_Param)
        return "Param";

    if (type == ElementType_Transform)
        return "Transform";

    if (type == ElementType_Analyzer)
        return "Analyzer";

    if (type == ElementType_Buffer)
        return "Buffer(DataModel)";

    if (type == ElementType_BufferFuzzer)
        return "BufferFuzzer";

    if (type == ElementType_Defaults)
        return "Defaults";

    if (type == ElementType_Configure)
        return "Configure";

    return "Unknown";

}

#define BitFill(_a,_b)    \
		do{\
		char* _bf = (char*)(_a);\
		u32 _pos = (_b);\
		_bf[_pos>>3] |= (128 >> (_pos & 7));\
		}while(0);

#define BitZero(_a,_b)    \
		do{\
		char* _bf = (char*)(_a);\
		u32 _pos = (_b);\
		_bf[_pos>>3] &= ~(128 >> (_pos & 7));\
		}while(0);


int mlib_fromSizeToLength(int size)
{
    if (size <= 8)
        return 1;
    else if (size <= 16)
        return 2;
    else if (size <= 32)
        return 4;
    else if (size <= 64)
        return 8;

    return 0;
}


//内存mem2的pos位置为size比特拷贝给mem1的0位置
void mlib_copyBitsValue(char* mem1, char* mem2, int pos, int size, int length)
{
    int i;
    for (i = 0; i< size; i++)
    {
        if ( mem2[(pos + i)>> 3 ] & (128 >> ((pos + i) & 7)))
        {
            BitFill(mem1, length*8 -(size - i) );
        }
    }
}

//内存mem2的0位置为size比特拷贝给mem1的pos位置

void mlib_copyValueBits(char* mem1, char* mem2, int pos, int size)
{
    int i;
    int count = mlib_fromSizeToLength(size) * 8;

    for (i = 0; i< size; i++)
    {
        if ( mem2[(count  + i - size)>> 3 ] & (128 >> ((count  + i - size) & 7)))
        {
            BitFill(mem1, pos + i);
        }
    }
}

void mlib_printfData(void *p, uint s)
{

    if (s == 0)
        return;

    BF_printf("data is length %10d-----------\r\n\r\n",s);
    if ((p) && (s < Max_Buf_Prinf_Length))
        diag_dump_buf(p, s);
    else if (p)
    {
        diag_dump_buf(p, Max_Buf_Prinf_Length);
        BF_printf("\r\n... ... %d byte not display\r\n", s - Max_Buf_Prinf_Length);
        diag_dump_buf(p + s - 16, 16);
    }
    BF_printf("data over                -----------\r\n");

}




int mlib_isprint(u8 v)
{
    if ((0x20 <= v) && (v <= 0x7e))
        return 1;
    return 0;
}

int mlib_isspace(u8 v)
{
    if ((v == ' ') 
        || (v == '\t')
        || (v == '\n')
        || (v == '\v')
        || (v == '\f')
        || (v == '\r'))
        return 1;
    return 0;
}

int mlib_isxdigit(u8 v)
{
    if (('0' <= v) && (v <= '9'))
        return 1;
    if (('a' <= v) && (v <= 'f'))
        return 1;
    if (('A' <= v) && (v <= 'F'))
        return 1;
    return 0;
}

int mlib_isdigit(u8 v)
{
    if (('0' <= v) && (v <= '9'))
        return 1;

    return 0;
}


#define LONG_MIN (-2147483647 - 1)
#define LONG_MAX (2147483647)

#define ERANGE 111
#define EINVAL 222


int errno222;

long mlib_strtol(const char * nptr, char ** endptr, int base) 
{ 
    const char *s; 
    unsigned long acc; 
    char c; 
    unsigned long cutoff; 
    int neg, any, cutlim; 
        s = nptr; 
    do { 
        c = *s++; 
    } while (mlib_isspace((unsigned char)c)); 
    if (c == '-') { 
        neg = 1; 
        c = *s++;         //去掉前导空格和+ - 符号 
    } else { 
        neg = 0; 
        if (c == '+') 
            c = *s++; 
    } 
    //判断进制,并去除前导0x或者0 
    if ((base == 0 || base == 16) && 
        c == '0' && (*s == 'x' || *s == 'X') && 
        ((s[1] >= '0' && s[1] <= '9') || 
        (s[1] >= 'A' && s[1] <= 'F') || 
        (s[1] >= 'a' && s[1] <= 'f'))) { 
        c = s[1]; 
        s += 2; 
        base = 16; 
    } 
    if (base == 0) 
        base = c == '0' ? 8 : 10; 
    acc = any = 0; 
    if (base < 2 || base > 36) 
        goto noconv; 
    
 /*判断溢出的方法:
 cutoff为系统能够表示的最大数除以base的结果，也就是当前进制能够表示的最大有效的数。
例如32为系统下长整形的范围是[-2147483648..2147483647]，如果base是10的话，则cutoff就是
214748364，而cutlim就是7(正整数)或者8(负整数)。如果当前算得的值大于cutoff就溢出了，或者等于cutoff但是下一位大于cutlim也就溢出了
*/
       cutoff = neg ? (unsigned long)-(LONG_MIN + LONG_MAX) + LONG_MAX 
        : LONG_MAX; 
    cutlim = cutoff % base; 
    cutoff /= base; 
    for ( ; ; c = *s++) { 
        if (c >= '0' && c <= '9') 
            c -= '0'; 
        else if (c >= 'A' && c <= 'Z') 
            c -= 'A' - 10; 
        else if (c >= 'a' && c <= 'z') 
            c -= 'a' - 10; 
        else 
            break; 
        if (c >= base) 
            break;                       
        //如果溢出则设置any为负数
        
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim)) 
            any = -1; 
        else { 
            any = 1; 
            acc *= base; 
            acc += c; 
        } 
    } 
    if (any < 0) {         //如果溢出就返回最大能表示的值
        acc = neg ? LONG_MIN : LONG_MAX; 
        errno222 = ERANGE; 
    } else if (!any) { 
noconv: 
        errno222 = EINVAL; 
    } else if (neg) 
        acc = -acc; 
    if (endptr != NULL)   
        *endptr = (char *)(any ? s - 1 : nptr); 
    return (acc); 
}


char* mlib_itoa(int num,char* str,int radix)
{/*索引表*/
    char index[]="0123456789ABCDEF";
    unsigned unum;/*中间变量*/
    int i=0,j,k;
    /*确定unum的值*/
    if(radix==10&&num<0)/*十进制负数*/
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num;/*其他情况*/
    /*转换*/
    do{
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
       }while(unum);
    str[i]='\0';
    /*逆序*/
    if(str[0]=='-')
        k=1;/*十进制负数*/
    else
        k=0;
     
    for(j=k;j<=(i-1)/2;j++)
    {       char temp;
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }
    return str;
}



int mlib_memcmp(void *d,void *s,size_t n)
{
    int i;
    char* dd = (char*)d;
    char* ss = (char*)s;
    for(i = 0; i < n; i++)
    {
        if(dd[i] != ss[i])
        return 1;
    }

    return 0;
}

char* mlib_strcpy(char *dst,char *src)
{
    return strcpy(dst,src);


    if (dst == NULL || src == NULL)
    {
        return NULL;
    }
    if (dst == src)
    {
        return dst;
    }

    char* ret = dst;

    while ((*dst++ = *src++) != '\0')

    return ret;
}


int mlib_strcmp(void *d,void *s)
{
    int i;
    char* dd = (char*)d;
    char* ss = (char*)s;
    for(i = 0;; i++)
    {
        if (dd[i] == 0)
            if (ss[i] != 0)
                return 1;

        if (ss[i] == 0)
            if (dd[i] != 0)
                return 1;

        if (ss[i] == 0)
            if (dd[i] == 0)
                return 0;

        if(dd[i] != ss[i])
            return 1;
    }

    return 0;
}


int mlib_strnlen(const char* s, int len)
{
    int i;
    for (i = 0; (i < len) && s[i]; i++);

    return i;
}



int mlib_strlen(const char* s)
{
    int i;
    for (i = 0; s[i]; i++);

    return i;
}



int mlib_atoi(const char *nptr)
{
    int c;              /* current char */
    int total;         /* current total */
    int sign;           /* if '-', then negative, otherwise positive */

    /* skip whitespace */
    while ( mlib_isspace((int)(unsigned char)*nptr) )
        ++nptr;

    c = (int)(unsigned char)*nptr++;
    sign = c;           /* save sign indication */
    if (c == '-' || c == '+')
        c = (int)(unsigned char)*nptr++;    /* skip sign */

    total = 0;

    while (mlib_isdigit(c)) {
        total = 10 * total + (c - '0');     /* accumulate digit */
        c = (int)(unsigned char)*nptr++;    /* get next char */
    }

    if (sign == '-')
        return -total;
    else
        return total;   /* return result, negated if necessary */
}



#ifdef __cplusplus
}
#endif

