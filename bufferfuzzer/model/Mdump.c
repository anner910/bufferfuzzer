



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned char    cyg_uint8  ;
 typedef int64_t CYG_ADDRWORD;
 typedef int __printf_fun(const char *fmt, ...);
 void
 diag_vdump_buf_with_offset(__printf_fun *pf,
                            cyg_uint8     *p,
                            CYG_ADDRWORD   s,
                            cyg_uint8     *base)
 {
     int i, c;
     if ((CYG_ADDRWORD)s > (CYG_ADDRWORD)p) {
         s = (CYG_ADDRWORD)s - (CYG_ADDRWORD)p;
     }
     while ((int)s > 0) {
         if (base) {
             (*pf)("%08X: ", (CYG_ADDRWORD)p - (CYG_ADDRWORD)base);
         } else {
             (*pf)("%08X: ", p);
         }
         for (i = 0;  i < 16;  i++) {
             if (i < (int)s) {
                 (*pf)("%02X ", p[i] & 0xFF);
             } else {
                 (*pf)("   ");
             }
         if (i == 7) (*pf)(" ");
         }
         (*pf)(" |");
         for (i = 0;  i < 16;  i++) {
             if (i < (int)s) {
                 c = p[i] & 0xFF;
                 if ((c < 0x20) || (c >= 0x7F)) c = '.';
             } else {
                 c = ' ';
             }
             (*pf)("%c", c);
         }
         (*pf)("|\r\n");
         s -= 16;
         p += 16;
     }
 }
 
 void
 diag_dump_buf_with_offset(cyg_uint8     *p,
                           CYG_ADDRWORD   s,
                           cyg_uint8     *base)
 {
    diag_vdump_buf_with_offset(printf, p, s, base);
 }
 
 void diag_dump_buf(void *p, uint s)
 {
    diag_dump_buf_with_offset((cyg_uint8 *)p, s, 0);
 }


#ifdef __cplusplus
}
#endif

