#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

#define self_over 				1
#define parent_over 			2
#define all_over 				4


int parseXmlModel(elementXmlContent **tree, char** file, int* length)
{
    char tempbuf[1024];
    int type;
    int type2;

    *tree = (elementXmlContent *)BF_malloc(sizeof(elementXmlContent));
    BF_memset(*tree, 0, sizeof(elementXmlContent));


    //����
    for(;;)
    {
        if (*length == 0)
        {
            BF_free(*tree);
            *tree = NULL;
            return all_over;
        }

        mlib_getLineBuf(tempbuf,file, length);

        //֧��xmlע��
        {

            int k;

            //�ҿ�ͷ
            k = mlib_findFirstLetter(tempbuf, '<');


            if ((tempbuf[k] == '<')
                &&(tempbuf[k + 1] == '?'))
            {
                continue;
            }

            if ((tempbuf[k] == '<')
                &&(tempbuf[k + 1] == '!')
                &&(tempbuf[k + 2] == '-')
                &&(tempbuf[k + 3] == '-'))
            {
                int pos = mlib_searchMemory("-->", 3, tempbuf, mlib_strlen(tempbuf));

                if (pos > 0)
                    continue;

                pos = mlib_searchMemory("-->", 3, *file, *length);

                if (pos > 0)
                {
                    *file = *file + pos + 3;
                    *length = *length - pos - 3;
                    continue;
                }
            }
        }


        type = parseXmlLine(tempbuf,*tree);

        if(type == Pc_tail)
        {
            BF_free(*tree);
            *tree = NULL;

            return parent_over;
        }

        if((type == Pc_notail)||(type == Pc_oneline))
            break;
        else//Pc_no
            continue;
    }


    //ֻ��һ�У�ֱ�ӽ�����
    if (type == Pc_oneline)
        return self_over;

    elementXmlContent **temp_tree = &(*tree)->bigChild;

    //
    for(;;)
    {
        if (*length == 0)
            return all_over;

        type2 = parseXmlModel( temp_tree,file,length);

        if(type2 == all_over)
            return all_over;

        if(type2 == parent_over)
        {
            return self_over;
        }

        if(type2 == self_over)
        {
            temp_tree = &(*temp_tree)->littleBrother;
            continue;
        }
    }

    return all_over;
}


#ifdef __cplusplus
}
#endif

