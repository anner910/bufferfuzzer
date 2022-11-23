



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

static void integration_copy(elementXmlContent *tree, elementXmlContent *ref)
{
    mlib_strcpy(tree->attribute_name, ref->attribute_name);
    mlib_strcpy(tree->attribute_size, ref->attribute_size);
    mlib_strcpy(tree->attribute_length, ref->attribute_length);
    mlib_strcpy(tree->attribute_alignment, ref->attribute_alignment);

    mlib_strcpy(tree->attribute_type, ref->attribute_type);
    mlib_strcpy(tree->attribute_valueType, ref->attribute_valueType);

    mlib_strcpy(tree->attribute_of, ref->attribute_of);
    mlib_strcpy(tree->attribute_token, ref->attribute_token);
    mlib_strcpy(tree->attribute_check, ref->attribute_check);
    mlib_strcpy(tree->attribute_position, ref->attribute_position);
    mlib_strcpy(tree->attribute_ref, ref->attribute_ref);

    mlib_strcpy(tree->attribute_refOK, ref->attribute_refOK);
    mlib_strcpy(tree->attribute_refOK1, ref->attribute_refOK1);
    mlib_strcpy(tree->attribute_refOK2, ref->attribute_refOK2);
    mlib_strcpy(tree->attribute_refOK3, ref->attribute_refOK3);

    mlib_strcpy(tree->attribute_endian, ref->attribute_endian);

    mlib_strcpy(tree->attribute_para1, ref->attribute_para1);
    mlib_strcpy(tree->attribute_para2, ref->attribute_para2);
    mlib_strcpy(tree->attribute_para3, ref->attribute_para3);
    mlib_strcpy(tree->attribute_para4, ref->attribute_para4);

    mlib_strcpy(tree->attribute_count, ref->attribute_count);
    mlib_strcpy(tree->attribute_minCount, ref->attribute_minCount);
    mlib_strcpy(tree->attribute_maxCount, ref->attribute_maxCount);

    mlib_strcpy(tree->attribute_mutator, ref->attribute_mutator);

    tree->type = ref->type;

    if (tree->attribute_value)
    {
        BF_free(tree->attribute_value);
        tree->attribute_value = NULL;
    }

    if (ref->attribute_value)
    {
        int length = mlib_strlen(ref->attribute_value);
        tree->attribute_value = BF_malloc(length + 1);
        BF_memset(tree->attribute_value, 0, length + 1);
        mlib_strcpy(tree->attribute_value, ref->attribute_value);
    }
}


static void integration_copy1(elementXmlContent *tree, elementXmlContent *ref)
{
    //mlib_strcpy(tree->attribute_name, ref->attribute_name);
    mlib_strcpy(tree->attribute_size, ref->attribute_size);
    mlib_strcpy(tree->attribute_length, ref->attribute_length);
    mlib_strcpy(tree->attribute_alignment, ref->attribute_alignment);

    mlib_strcpy(tree->attribute_type, ref->attribute_type);
    mlib_strcpy(tree->attribute_valueType, ref->attribute_valueType);


    mlib_strcpy(tree->attribute_of, ref->attribute_of);
    mlib_strcpy(tree->attribute_token, ref->attribute_token);
    mlib_strcpy(tree->attribute_check, ref->attribute_check);
    mlib_strcpy(tree->attribute_position, ref->attribute_position);
    mlib_strcpy(tree->attribute_ref, ref->attribute_ref);

    mlib_strcpy(tree->attribute_refOK, ref->attribute_refOK);
    mlib_strcpy(tree->attribute_refOK1, ref->attribute_refOK1);
    mlib_strcpy(tree->attribute_refOK2, ref->attribute_refOK2);
    mlib_strcpy(tree->attribute_refOK3, ref->attribute_refOK3);

    mlib_strcpy(tree->attribute_endian, ref->attribute_endian);

    mlib_strcpy(tree->attribute_para1, ref->attribute_para1);
    mlib_strcpy(tree->attribute_para2, ref->attribute_para2);
    mlib_strcpy(tree->attribute_para3, ref->attribute_para3);
    mlib_strcpy(tree->attribute_para4, ref->attribute_para4);

    mlib_strcpy(tree->attribute_count, ref->attribute_count);
    mlib_strcpy(tree->attribute_minCount, ref->attribute_minCount);
    mlib_strcpy(tree->attribute_maxCount, ref->attribute_maxCount);

    mlib_strcpy(tree->attribute_mutator, ref->attribute_mutator);

    tree->type = ref->type;

    if (tree->attribute_value)
    {
        BF_free(tree->attribute_value);
        tree->attribute_value = NULL;
    }

    if (ref->attribute_value)
    {
        int length = mlib_strlen(ref->attribute_value);
        tree->attribute_value = BF_malloc(length + 1);
        BF_memset(tree->attribute_value, 0, length + 1);
        mlib_strcpy(tree->attribute_value, ref->attribute_value);
    }
}


static void integration_refChild(elementXmlContent *tree, elementXmlContent *ref)
{

    elementXmlContent *temp_tree = tree;
    elementXmlContent *ref_tree = ref->bigChild;

    if (ref_tree == NULL)
        return;

    elementXmlContent* temp_xml = (elementXmlContent *)BF_malloc(sizeof(elementXmlContent));
    BF_memset(temp_xml, 0, sizeof(elementXmlContent));

    temp_tree->bigChild = temp_xml;


    integration_copy(temp_xml, ref_tree);


    if(ref_tree->bigChild)
    {
        integration_refChild(temp_xml, ref_tree);
    }

    ref_tree = ref_tree->littleBrother;
    temp_tree = temp_xml;

    for(;ref_tree;)
    {
        elementXmlContent* temp_xml111 = (elementXmlContent *)BF_malloc(sizeof(elementXmlContent));
        BF_memset(temp_xml111, 0, sizeof(elementXmlContent));

        integration_copy(temp_xml111, ref_tree);

        if(ref_tree->bigChild)
        {
            integration_refChild(temp_xml111, ref_tree);
        }

        ref_tree = ref_tree->littleBrother;

        temp_tree->littleBrother= temp_xml111;
        temp_tree = temp_xml111;
    }

    return;
}


char* getFirstName(char* name, char** nameLeft)
{
    int pos = mlib_findFirstLetter(name, '.');

    if (name[pos] == '.')
    {
        name[pos] = 0;
        *nameLeft = name + pos + 1;
        return name;
    }

    *nameLeft = NULL;
    return name;
}

elementXmlContent* found_ref_element(elementXmlContent *tree_tree, char* name)
{
    char* nameLeft;
    char* ele_name = getFirstName(name, &nameLeft);

    for(;tree_tree;)
    {
        if (mlib_strcmp(tree_tree->attribute_name, ele_name) == 0)
        {
            if (nameLeft == NULL)
                return tree_tree;
            else
                return found_ref_element(tree_tree->bigChild, nameLeft);
        }
        tree_tree = tree_tree->littleBrother;
    }

    return NULL;
}

static void integration_selfChild(elementXmlContent *self, elementXmlContent *old_child)
{

    elementXmlContent *new_child = self->bigChild;

    for(;old_child;)
    {
        //相当于找不到了
        if (mlib_strlen(old_child->attribute_name) == 0)
            break;

        //从第一个依次查找  在自己(继承)哪里 自己的儿子还在不在
        elementXmlContent *temp_tree = found_ref_element(new_child, old_child->attribute_name);

        //找到替换成自己的
        if (temp_tree)
        {
            //自己原来有儿子也得释放啊
            if (temp_tree->bigChild)
                tree_free_xml(temp_tree->bigChild);

            integration_copy1(temp_tree, old_child);

            //儿子直接拷贝走
            temp_tree->bigChild = old_child->bigChild;
            old_child->bigChild = NULL;
        }

        //找不到都挂后边
        if (temp_tree == NULL)
            break;

        elementXmlContent *free_tree = old_child;
        old_child = old_child->littleBrother;

        free_xml(free_tree);
        BF_free(free_tree);
    }

    if (new_child == NULL)
        self->bigChild = old_child;

    for(;new_child;)
    {
        if (new_child->littleBrother == NULL)
        {
            new_child->littleBrother = old_child;
            break;
        }

        new_child = new_child->littleBrother;
    }

    return;
}


static void integration_ref(elementXmlContent *tree, elementXmlContent *root)
{
    elementXmlContent *temp_tree = root->bigChild;

    for(;temp_tree;)
    {

        if (mlib_strcmp(tree->attribute_ref, temp_tree->attribute_name) == 0)
        {
            if (g_bufferFuzz.onoffDebugXml)
            {
                BF_printf("     %s ref Buffer %s \r\n",tree->attribute_name, tree->attribute_ref);
            }

            elementXmlContent *temp_child = tree->bigChild;

            tree->bigChild = NULL;

            //拷贝别人儿子 
            integration_refChild(tree, temp_tree);

            //拷贝自己的儿子
            if (temp_child)
                integration_selfChild(tree, temp_child);



            mlib_strcpy(tree->attribute_refOK, temp_tree->attribute_refOK);
            mlib_strcpy(tree->attribute_refOK1, temp_tree->attribute_refOK1);
            mlib_strcpy(tree->attribute_refOK2, temp_tree->attribute_refOK2);
            mlib_strcpy(tree->attribute_refOK3, temp_tree->attribute_refOK3);

            //一个ref只生效依次
            if (mlib_strlen(tree->attribute_refOK) == 0)
                mlib_strcpy(tree->attribute_refOK,tree->attribute_ref);
            else if (mlib_strlen(tree->attribute_refOK1) == 0)
                mlib_strcpy(tree->attribute_refOK1,tree->attribute_ref);
            else if (mlib_strlen(tree->attribute_refOK2) == 0)
                mlib_strcpy(tree->attribute_refOK2,tree->attribute_ref);
            else if (mlib_strlen(tree->attribute_refOK3) == 0)
                mlib_strcpy(tree->attribute_refOK3,tree->attribute_ref);

            tree->attribute_ref[0] = 0;
        }

        temp_tree = temp_tree->littleBrother;
    }
}


void parseXmlRef(elementXmlContent *tree, elementXmlContent *root)
{
    elementXmlContent *temp_tree = tree;

    for(;temp_tree;)
    {
        if (mlib_strlen(temp_tree->attribute_ref) > 0)
        {
            integration_ref(temp_tree, root);
        }

        //不怕不怕
        if(temp_tree->bigChild)
        {
            parseXmlRef(temp_tree->bigChild, root);
        }

        temp_tree = temp_tree->littleBrother;
    }
}

#ifdef __cplusplus
}
#endif

