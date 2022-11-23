



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif


//补偿失败的时候以后再考虑
static int resolvedNoLengthElement(char* bin, int pos, int length, elementBinContent *resolvedlTree)
{
	resolvedlTree->resolvedlTree = g_bufferFuzz.nolength_tree;
		
	g_bufferFuzz.nolength_tree->value_length = length;

	if (g_bufferFuzz.nolength_tree->value)
		BF_free(g_bufferFuzz.nolength_tree->value);

	g_bufferFuzz.nolength_tree->value = BF_malloc(g_bufferFuzz.nolength_tree->value_length + 1);
	BF_memset(g_bufferFuzz.nolength_tree->value, 0, g_bufferFuzz.nolength_tree->value_length + 1);
	BF_memcpy(g_bufferFuzz.nolength_tree->value, bin + pos, length);

	if (g_bufferFuzz.onoffDebugXml)
	{
		BF_printf("\r\n\r\nThe length is resolved------%s  length %d\r\n",g_bufferFuzz.nolength_tree->xml->attribute_name, g_bufferFuzz.nolength_tree->value_length);
		mlib_printfData(g_bufferFuzz.nolength_tree->value, g_bufferFuzz.nolength_tree->value_length);
	}

	//感觉应该提前
	if (mlib_strlen(g_bufferFuzz.nolength_tree->xml->attribute_check) > 0)
	{
		int ret = do_check_value(g_bufferFuzz.nolength_tree, g_bufferFuzz.nolength_tree->value, g_bufferFuzz.nolength_tree->value_length);
		if (ret < 0)
			return ret;
	}

	elementBinContent *tree = g_bufferFuzz.nolength_tree;
	g_bufferFuzz.nolength_tree = NULL;
	
	//ElementType_BufferFuzzer 值解决了，用自己的value解决儿子的
	//这里边返回 失败怎么办?????????
	if(tree->xml->type == ElementType_Transform)
	{
		//的用加解密之后的
		do_transform_before(tree);
		int temp_length = parse_struct_child(tree->xml, tree->value, tree->value_length, tree);

		if (temp_length < 0)
		{
			g_bufferFuzz.nolength_tree = tree;
			return temp_length;
		}

		if (tree->value_length > temp_length)
		{
			if(g_bufferFuzz.nolength_tree != NULL)
			{
				int ret = resolvedNoLengthElement(bin, temp_length, tree->value_length - temp_length, tree);
				if (ret < 0)
				{
					g_bufferFuzz.nolength_tree = tree;
					return ret;
				}

				temp_length = tree->value_length;
			}
			else
			{
				g_bufferFuzz.nolength_tree = tree;
				return -1;//-1
			}

		}

		if ((tree->value_length > 0) && (tree->value_length < temp_length))
		{
			g_bufferFuzz.nolength_tree = tree;
			return -1;//-1
		}

		return length;//temp_length
	}

	return length;

}


int parse_element(elementXmlContent *tree, char* bin, int length, elementBinContent *treeBin)
{
	if (g_bufferFuzz.onoffDebugXml)
	{
		BF_printf("-------------------------------------------------------\r\n");
		BF_printf("parse_element %12s\r\n",tree->attribute_name);

		BF_printf("                              type      is %s\r\n", mlib_getTypeName(tree->type));
		BF_printf("                              bin       is %p\r\n", bin);
		BF_printf("                              binlength is %d\r\n", length);
		BF_printf("                              xmllength is %d\r\n", tree->xml_length);
		BF_printf("                              xml_size  is %d\r\n", tree->xml_size);
		BF_printf("                              fixLength is %d\r\n", tree->fixLength);
		BF_printf("                              istoken   is %d\r\n", tree->istoken);

		BF_printf("-----------bin left is :\r\n");
		mlib_printfData(bin, length);
	}

	//不是解析bin文件的场景,有数据拷贝完直接结束
	if (bin == NULL)
	{
		if((tree->xml_length > 0) && (tree->type != ElementType_Bits))
		{
			treeBin->value_length = tree->xml_length;
			treeBin->value = BF_malloc(treeBin->value_length + 1);
			BF_memset(treeBin->value, 0, treeBin->value_length + 1);
			BF_memcpy(treeBin->value, tree->xml_value, tree->xml_length);
			

			if (g_bufferFuzz.onoffDebugXml)
			{
				mlib_printfData(treeBin->value, treeBin->value_length);
			}
		
			return treeBin->value_length;
		}
		//有儿子就解析儿子
		else if ((tree->type == ElementType_Bits) || (tree->type == ElementType_Transform))
		{
			int temp_length = parse_struct_child(tree, bin, length, treeBin);
			return temp_length;
		}

		//ElementType_Transform   不用管他，直接解析儿子就行
	}

	if((tree->type == ElementType_Relation)
		||(tree->type == ElementType_Fixup)
		||(tree->type == ElementType_Param)
		||(tree->type == ElementType_Analyzer)
		||(tree->type == ElementType_Unknown))
	{
		return 0;
	}

	int binLength = tree->fixLength;

	int isRalationResolved = 0;

	//可以先找到长度  还要判断是size类型的，以后加count的时候再加
	if((bin != NULL) 
		&& ((tree->isRelationBlob == 1) && (tree->isRelationParent == 0)))
	{
		int temp_length = do_relation_get(treeBin);

		if (treeBin->typeRelation == 3)
		{
			//有可能为0，必须标记一下
			treeBin->relationCount = temp_length;
			treeBin->isRelationCount = 1; 

			if (g_bufferFuzz.onoffDebugXml)
				BF_printf("get relation count %d(Parent==0)\r\n", temp_length);
		}
		else
		{
			if ((binLength > 0) && (binLength != temp_length))
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***relation blob(%s) get length is %d, != fixLength %d\r\n",
					tree->attribute_name,temp_length, binLength);
				
				return -1;
			}

			binLength = temp_length;

			isRalationResolved = 1;

			if (g_bufferFuzz.onoffDebugXml)
				BF_printf("get relation length %d(Parent==0)\r\n", temp_length);
		}
 
 		
	}

	if (g_bufferFuzz.onoffDebugXml)
		BF_printf("                              binLength is %d\r\n", binLength);

	//属于成功搞定，长度都为0了，就不往下走了
	if ((bin != NULL) 
		&& (binLength == 0
		&& (isRalationResolved == 1)))
	{
		return 0;
	}

	if ((bin != NULL) 
		&& (binLength > length))
	{
		if (g_bufferFuzz.onoffDebugXml)
			BF_printf("failed***binLength is %d > bin left length %d)\r\n", binLength, length);
		
		return -1;
	}

	if(tree->type == ElementType_Padding)
	{
		treeBin->value_length = do_padding_get(treeBin);
		
		treeBin->value = BF_malloc(treeBin->value_length + 1);
		BF_memset(treeBin->value, 0, treeBin->value_length + 1);

		if (bin)
		{
			if (treeBin->value_length <= length)
				BF_memcpy(treeBin->value, bin, treeBin->value_length);
			else
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Padding(%s) get length is %d, > bin left length %d\r\n",
					tree->attribute_name, treeBin->value_length, length);
				
				return -1;
			}
		}

		if (g_bufferFuzz.onoffDebugXml)
		{
			mlib_printfData(treeBin->value, treeBin->value_length);
		}

		return treeBin->value_length;
	}

	
	if(tree->type == ElementType_Buffer)
	{
		int temp_length = parse_struct_child(tree, bin, length, treeBin);

		if (temp_length < 0)
		{
			return temp_length;
		}

		if (length > temp_length)
		{
			if(g_bufferFuzz.nolength_tree != NULL)
			{
				int ret = resolvedNoLengthElement(bin, temp_length, length - temp_length, treeBin);
				if (ret < 0)
					return ret;

				temp_length = length;
			}
			else
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Buffer(%s) get length is %d, < bin left length %d\r\n",
					tree->attribute_name, temp_length, length);
				
				return -1;
			}
		}
	
		return temp_length;
	}

	if(tree->type == ElementType_Struct)
	{
		int use_length = length;
		if (binLength > 0)
			use_length = binLength;
		int temp_length = parse_struct_child(tree, bin, use_length, treeBin);

		if (temp_length < 0)
		{
			return temp_length;
		}

		if (binLength >= temp_length)
		{
			if(g_bufferFuzz.nolength_tree != NULL)
			{
				int ret = resolvedNoLengthElement(bin, temp_length, binLength - temp_length, treeBin);
				if (ret < 0)
					return ret;

				temp_length = binLength;
			}
			else if (binLength > temp_length)
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Struct(%s) get length is %d, > return length %d\r\n",
					tree->attribute_name, binLength, temp_length);
				return -1;
			}
		}

		//=号为了最后一个元素长度为0
		if (treeBin->value_length >= temp_length)
		{
			if(g_bufferFuzz.nolength_tree != NULL)
			{
				int ret = resolvedNoLengthElement(bin, temp_length, treeBin->value_length - temp_length, treeBin);
				if (ret < 0)
					return ret;

				temp_length = treeBin->value_length;
			}
			else  if (treeBin->value_length > temp_length)
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Struct(%s) value_length is %d, > return length %d\r\n",
					tree->attribute_name, treeBin->value_length, temp_length);
				return -1;
			}

		}

		if ((treeBin->value_length > 0) && (treeBin->value_length < temp_length))
		{
			if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Struct(%s) value_length is %d, < return length %d\r\n",
					tree->attribute_name, treeBin->value_length, temp_length);
			
			return -1;
		}

		return temp_length;
	}

	
	if(tree->type == ElementType_Array)
	{
		int use_length = length;
		if (binLength > 0)
			use_length = binLength;
		
		int temp_length = parse_array_child(tree, bin, use_length, treeBin);

		if (temp_length < 0)
		{
			return temp_length;
		}

		if (binLength >= temp_length)
		{
			if(g_bufferFuzz.nolength_tree != NULL)
			{
				int ret = resolvedNoLengthElement(bin, temp_length, binLength - temp_length, treeBin);
				if (ret < 0)
					return ret;

				temp_length = binLength;
			}
			else if (binLength > temp_length)
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Array(%s) get length is %d, > return length %d\r\n",
					tree->attribute_name, binLength, temp_length);
				
				return -1;
			}
		}

		if (treeBin->value_length >= temp_length)
		{
			if(g_bufferFuzz.nolength_tree != NULL)
			{
				int ret = resolvedNoLengthElement(bin, temp_length, treeBin->value_length - temp_length, treeBin);
				if (ret < 0)
					return ret;

				temp_length = treeBin->value_length;
			}
			else if (treeBin->value_length > temp_length)
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Array(%s) value_length is %d, > return length %d\r\n",
					tree->attribute_name, treeBin->value_length, temp_length);
				return -1;
			}

		}

		if ((treeBin->value_length > 0) && (treeBin->value_length < temp_length))
		{
			if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Array(%s) value_length is %d, < return length %d\r\n",
					tree->attribute_name, treeBin->value_length, temp_length);
			
			return -1;
		}

		return temp_length;
	}

	if(tree->type == ElementType_Union)
	{
		int use_length = length;
		if (binLength > 0)
			use_length = binLength;
		
		int temp_length = parse_union_child(tree, bin, use_length, treeBin);

		if (temp_length < 0)
		{
			return temp_length;
		}

		if (binLength >= temp_length)
		{
			if(g_bufferFuzz.nolength_tree != NULL)
			{
				int ret = resolvedNoLengthElement(bin, temp_length, binLength - temp_length, treeBin);
				if (ret < 0)
					return ret;

				temp_length = binLength;
			}
			else if (binLength > temp_length)
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Union(%s) get length is %d, > return length %d\r\n",
					tree->attribute_name, binLength, temp_length);
				
				return -1;
			}
		}

		if (treeBin->value_length >= temp_length)
		{
			if(g_bufferFuzz.nolength_tree != NULL)
			{
				int ret = resolvedNoLengthElement(bin, temp_length, treeBin->value_length - temp_length, treeBin);
				if (ret < 0)
					return ret;

				temp_length = treeBin->value_length;
			}
			else if (treeBin->value_length > temp_length)
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Union(%s) value_length is %d, > return length %d\r\n", 
					tree->attribute_name, treeBin->value_length, temp_length);
				return -1;
			}

		}

		if ((treeBin->value_length > 0) && (treeBin->value_length < temp_length))
		{
			if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Union(%s) value_length is %d, < return length %d\r\n", 
					tree->attribute_name, treeBin->value_length, temp_length);
			return -1;
		}

		return temp_length;
	}

	//按理说就不应该到这里
	if (bin == NULL)
	{
		ASSERT("parse_element error\r\n");
		return 0;
	}

	
	//ElementType_String
	//ElementType_Buf
	//ElementType_Number
	//... ...

	//Transform 目前不支持整体token

	//token匹配，必须成功
	if((tree->istoken)&&(g_bufferFuzz.nolength_tree == NULL))
	{
		//匹配失败
		if(tree->type == ElementType_Bit)
		{
			treeBin->value_length = tree->xml_length;
			treeBin->value = BF_malloc(treeBin->value_length + 1);
			BF_memset(treeBin->value, 0, treeBin->value_length + 1);

			if (length == 1)
			{
				s8 aaa = tree_getValue(treeBin->parent);
				mlib_copyBitsValue(treeBin->value, (char*)&aaa,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size,tree->xml_length);
			}
			else if (length == 2)
			{
				s16 aaa = tree_getValue(treeBin->parent);
				mlib_copyBitsValue(treeBin->value, (char*)&aaa,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size,tree->xml_length);
			}
			else if (length == 4)
			{
				s32 aaa = tree_getValue(treeBin->parent);
				mlib_copyBitsValue(treeBin->value, (char*)&aaa,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size,tree->xml_length);
			}
			else
			{
				s64 aaa = tree_getValue(treeBin->parent);
				mlib_copyBitsValue(treeBin->value, (char*)&aaa,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size,tree->xml_length);
			}
			
			if(mlib_memcmp(tree->xml_value, treeBin->value, treeBin->value_length) != 0)
			{
				if (g_bufferFuzz.onoffDebugXml)
				{
					BF_printf("failed***Bit token(%s) check failed, length is %d\r\n", tree->attribute_name, treeBin->value_length);
					
					BF_printf("xml data is: \r\n");
					diag_dump_buf(tree->xml_value, treeBin->value_length);

					BF_printf("bin data is: \r\n");
					diag_dump_buf(treeBin->value, treeBin->value_length);
					BF_printf("failed***End\r\n");
				}
				
				//释放内存 
				return -1;
			}

		}
		else
		{
			if(mlib_memcmp(tree->xml_value, bin, binLength) != 0)
			{
				if (g_bufferFuzz.onoffDebugXml)
				{
					BF_printf("failed***token(%s) check failed, length is %d\r\n", tree->attribute_name, binLength);

					BF_printf("xml data is: \r\n");
					diag_dump_buf(tree->xml_value, binLength);

					BF_printf("bin data is: \r\n");
					diag_dump_buf(bin, binLength);
					BF_printf("failed***End\r\n");
				}
				
				//释放内存 
				return -1;
			}

			treeBin->value_length = binLength;

			treeBin->value = BF_malloc(treeBin->value_length + 1);
			BF_memset(treeBin->value, 0, treeBin->value_length + 1);
			BF_memcpy(treeBin->value, bin, treeBin->value_length);
		}

		

		if (g_bufferFuzz.onoffDebugXml)
		{
			mlib_printfData(treeBin->value, treeBin->value_length);
		}

		if(tree->type == ElementType_Bit)
		{
			return 0;
		}
		
		return treeBin->value_length;

	}

	//寻找token,
	if((tree->istoken)&&(g_bufferFuzz.nolength_tree != NULL))
	{
		int pos = mlib_searchMemory(tree->xml_value, binLength, bin, length);
		
		if(pos < 0)
		{
			if (g_bufferFuzz.onoffDebugXml)
			{
				BF_printf("failed***token(%s) check failed, data is not found\r\n", tree->attribute_name);

				BF_printf("xml length is %d, data is:\r\n",binLength);
				diag_dump_buf(tree->xml_value, binLength);
				BF_printf("failed***End\r\n");
			}
			return -1;
		}

		treeBin->value_length = binLength;
		treeBin->value = BF_malloc(treeBin->value_length + 1);
		BF_memset(treeBin->value, 0, treeBin->value_length + 1);
		BF_memcpy(treeBin->value, bin + pos, treeBin->value_length);

		if (g_bufferFuzz.onoffDebugXml)
		{
			mlib_printfData(treeBin->value, treeBin->value_length);
		}

		//补偿未知长度元素

		int ret = resolvedNoLengthElement(bin, 0, pos, treeBin);
		if (ret < 0)
			return ret;

		return treeBin->value_length + pos;

	}

	//位置元素不接token，严重错误
	if(g_bufferFuzz.nolength_tree != NULL)
	{
		if (g_bufferFuzz.onoffDebugXml)
			BF_printf("failed***(%s)no lenght is unable to resolve\r\n",g_bufferFuzz.nolength_tree->xml->attribute_name);
		return -1;
	}

	if (mlib_strlen(tree->attribute_check) > 0)
	{
		int ret = do_check_bin(treeBin, bin, length);
		if (ret < 0)
			return ret;
	}
	

	if(binLength > 0)
	{
		treeBin->value_length = binLength;

		if(tree->type == ElementType_Bit)
		{
			treeBin->value_length = tree->xml_length;
			treeBin->value = BF_malloc(treeBin->value_length + 1);
			BF_memset(treeBin->value, 0, treeBin->value_length + 1);

			if (length == 1)
			{
				s8 aaa = tree_getValue(treeBin->parent);
				mlib_copyBitsValue(treeBin->value, (char*)&aaa,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size,tree->xml_length);
			}
			else if (length == 2)
			{
				s16 aaa = tree_getValue(treeBin->parent);
				mlib_copyBitsValue(treeBin->value, (char*)&aaa,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size,tree->xml_length);
			}
			else if (length == 4)
			{
				s32 aaa = tree_getValue(treeBin->parent);
				mlib_copyBitsValue(treeBin->value, (char*)&aaa,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size,tree->xml_length);
			}
			else
			{
				s64 aaa = tree_getValue(treeBin->parent);
				mlib_copyBitsValue(treeBin->value, (char*)&aaa,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size,tree->xml_length);
			}

			//mlib_copyBitsValue(treeBin->value,bin,mlib_atoi(treeBin->xml->attribute_position), treeBin->xml->xml_size);
		}
		else
		{
			treeBin->value = BF_malloc(treeBin->value_length + 1);
			BF_memset(treeBin->value, 0, treeBin->value_length + 1);
			BF_memcpy(treeBin->value, bin, treeBin->value_length);
		}

		if (g_bufferFuzz.onoffDebugXml)
		{
			mlib_printfData(treeBin->value, treeBin->value_length);
		}

		if (mlib_strlen(tree->attribute_check) > 0)
		{
			int ret = do_check_value(treeBin, bin, length);
			if (ret < 0)
				return ret;
		}

		//祖先relation,给他赋值
		if((tree->isRelationValue == 1) && (tree->isRelationParent == 1))
		{
			//elementBinContent* temp_bin1 = tree_relation_parent(treeBin, tree->relationBlob);
			elementBinContent* temp_bin1 = found_relationOfBinBlob(treeBin, tree->relationBlob->attribute_name, 0);

			//int temp_length = *(int*)treeBin->value;

			int temp_length = do_relation_get(temp_bin1);
	 
	 		if ((temp_bin1->value_length > 0) && (temp_bin1->value_length != temp_length))
	 		{
	 			if (g_bufferFuzz.onoffDebugXml)
	 			{
					BF_printf("failed***Relation get length is %d, != value length %d\r\n", temp_length, temp_bin1->value_length);
					BF_printf("relation value is %s, blob is %s\r\n", tree->attribute_name, temp_bin1->xml->attribute_name);
					BF_printf("failed***End\r\n");
	 			}
				return -1;
	 		}

			temp_bin1->value_length = temp_length;

			if (g_bufferFuzz.onoffDebugXml)
				BF_printf("%s get relation length %d(Parent==1)\r\n", temp_bin1->xml->attribute_name, temp_length);
		}

		//ElementType_BufferFuzzer 值解决了，用自己的value解决儿子的
		if(tree->type == ElementType_Transform)
		{
			//得用加解密之后的
			do_transform_before(treeBin);
			int temp_length = parse_struct_child(tree, treeBin->value, treeBin->value_length, treeBin);

			if (temp_length < 0)
			{
				return temp_length;
			}

			if (treeBin->value_length > temp_length)
			{
				if(g_bufferFuzz.nolength_tree != NULL)
				{
					int ret = resolvedNoLengthElement(bin, temp_length, treeBin->value_length - temp_length, treeBin);
					if (ret < 0)
						return ret;

					temp_length = treeBin->value_length;
				}
				else
				{
					if (g_bufferFuzz.onoffDebugXml)
						BF_printf("failed***Transform(%s) value_length is %d, > return length %d\r\n", 
						tree->attribute_name, treeBin->value_length, temp_length);
					
					return -1;
				}

			}

			if ((treeBin->value_length > 0) && (treeBin->value_length < temp_length))
			{
				if (g_bufferFuzz.onoffDebugXml)
						BF_printf("failed***Transform(%s) value_length is %d, < return length %d\r\n", 
						tree->attribute_name, treeBin->value_length, temp_length);
				
				return -1;
			}

			return temp_length;
		}


		if(tree->type == ElementType_Bits)
		{
			//这东东是定长的
			int temp_length = parse_struct_child(tree, treeBin->value, treeBin->value_length, treeBin);

			//只管token匹配
			if (temp_length == -1)
			{
				if (g_bufferFuzz.onoffDebugXml)
					BF_printf("failed***Bits(%s) parse error\r\n",tree->attribute_name);
				
				return -1;
			}
		}


		if(tree->type == ElementType_Bit)
		{
			return 0;
		}
		
		return treeBin->value_length;
	}

	//没有长度，直接往下找，得到长度
	if((tree->type == ElementType_String)
		||(tree->type == ElementType_Buf))
	{
		if (g_bufferFuzz.onoffDebugXml)
			BF_printf("data is none, The length is not resolved\r\n");
		g_bufferFuzz.nolength_tree = treeBin;
		return 0;
	}
	
	return 0;

}

#ifdef __cplusplus
}
#endif

