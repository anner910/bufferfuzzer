
#include "../../model/Model.h"


#ifdef __cplusplus
extern "C"{
#endif

#ifdef BF_Mode_AnalyzerJson

#include "../../otherLib/cJSON.h"


void do_json_free(cJSON *json2)
{
    cJSON *temp_tree2 = json2;

    if(temp_tree2->type == cJSON_String)
    {
        if(temp_tree2->valuestring)
        {
            BF_free(temp_tree2->valuestring);
            temp_tree2->valuestring = 0;
        }
    }

    if(temp_tree2->child)
    {
        do_json_free(temp_tree2->child);
    }


    temp_tree2 = temp_tree2->next;

    for(;temp_tree2;)
    {
        if(temp_tree2->type == cJSON_String)
        {
            if(temp_tree2->valuestring)
            {
                BF_free(temp_tree2->valuestring);
                temp_tree2->valuestring = 0;
            }
        }

        if(temp_tree2->child)
        {
            do_json_free(temp_tree2->child);
        }

        temp_tree2 = temp_tree2->next;
    }
}


void do_json_before(elementBinContent *tree)
{
    tree->p1 = (char*)cJSON_Parse(tree->value);
    tree->p2 = (char*)cJSON_Parse(tree->value);

    if(tree->p1 == NULL)
        BF_printf("json prase error, must assert\r\n");

    //先把p2free了，要不内存泄漏
    do_json_free((cJSON *)tree->p2);
}


void do_json_call_fuzz(cJSON *json1, cJSON *json2)
{
    //其他类型以后再加
    if(json1->type == cJSON_String)
    {
        json2->valuestring = CF_GetString(g_paraNo++, json1->valuestring, mlib_strlen(json1->valuestring) + 1, 1, 1000);
    }

    if(json1->type == cJSON_Number)
    {
        int temp = *(s32*)CF_GetS32(g_paraNo++, json1->valueint);
        json2->valuedouble = temp;
    }
}


void do_json_fuzz(cJSON *json1, cJSON *json2)
{

    cJSON *temp_tree = json1;
    cJSON *temp_tree2 = json2;

    do_json_call_fuzz(temp_tree, temp_tree2);


    if(temp_tree->child)
    {
        do_json_fuzz(temp_tree->child, temp_tree2->child);
    }

    temp_tree = temp_tree->next;
    temp_tree2 = temp_tree2->next;

    for(;temp_tree;)
    {
        do_json_call_fuzz(temp_tree, temp_tree2);

        if(temp_tree->child)
        {
            do_json_fuzz(temp_tree->child, temp_tree2->child);
        }

        temp_tree = temp_tree->next;
        temp_tree2 = temp_tree2->next;
    }

}

int do_json(elementBinContent *tree)
{
    do_json_fuzz((cJSON *)tree->p1, (cJSON *)tree->p2);

    if(tree->after_buf)
        BF_free(tree->after_buf);

    tree->after_buf = cJSON_Print((cJSON *)tree->p2);
    tree->after_lenght = mlib_strlen(tree->after_buf); //减一，以后再改
    return 1;
}

void do_json_after_free(elementBinContent *tree)
{
    if(tree->p1)
        cJSON_Delete((cJSON *)tree->p1);

    if(tree->p2)
        cJSON_Delete((cJSON *)tree->p2);
}


#else

void do_json_before(elementBinContent *tree)
{


}

int do_json(elementBinContent *tree)
{
    return 0;
}

void do_json_after_free(elementBinContent *tree)
{


}


#endif


#ifdef __cplusplus
}
#endif

