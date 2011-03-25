/*
 *  ASNode.cpp
 *  Translate AS1
 *
 *  Created by smackay on Tue Jun 15 2004.
 *  Copyright (c) 2004 Flagstone Software Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later 
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * For more information please contact:
 * 
 * Stuart MacKay
 * Flagstone Software Ltd
 * 92 High Street
 * Wick, Caithness KW1 4LY
 * Scotland
 * 
 * www.flagstonesoftware.com
 */

#include "ASNode.h"

#include <float.h>
#include <math.h>
#include <string>

using namespace std;
using namespace translate;

namespace translate {
    static const char* nodeNames[] = {
		"NoOp",
		"Array",
		"Button",
		"MovieClip",
		"List",
        "ExpressionList",
		"if",
		"for",
		"for..in",
		"while",
		"do..while",
		"With",
		"OnClipEvent",
		"On",
		"Break",
		"Return",
		"Continue",
		"Value",
        "Constant",
		"Number",
        "String",
		"Identifier",
		"Attribute",
		"Method",
		"Function",
		"NewObject",
		"Subscript",
        "Define Variable",
		"Define Array",
		"Define Function",
		"Define Attribute",
		"Define Method",
		"Define Object",
		"+",
		"-",
		"*",
		"/",
		"%",
		"<<",
		">>",
		">>>",
		"&",
		"|",
		"^",
		"&&",
		"||",
		"==",
		"!=",
		">",
		"<",
		">=",
		"<=",
		"?",
		"!",
		"~",
		"+x",
		"-x",
		"++x",
		"--x",
		"x++",
		"x--",
		"=",
		"+=",
		"-=",
		"*=",
		"/=",
		"%=",
		"<<=",
		">>=",
		">>>=",
		"&=",
		"|=",
		"^=",
        "delete",
        "instanceof"
    };
/*
 * Implementation of ASNode.
 */
class ASNodeImpl : public DLLImpl<ASNode>
{
public:
    ASNodeImpl(NodeType nodeType)
    {
        type = nodeType;
        status = 0;
        parent = 0;

        capacity = 4;
        size = 0;

        children = (ASNode**)malloc(sizeof(ASNode*)*capacity);

        for (unsigned int i=0; i<capacity; i++)
            *(children+i) = NULL;
    }

    ASNodeImpl(NodeType nodeType, const char* nodeValue)
    {
        type = nodeType;
        status = 0;
        value = nodeValue;
        parent = 0;

        capacity = 4;
        size = 0;

        children = (ASNode**)malloc(sizeof(ASNode*)*capacity);

        for (unsigned int i=0; i<capacity; i++)
            *(children+i) = NULL;
    }

    ~ASNodeImpl()
    {
        parent = NULL;

        if (children) 
        {
            for (unsigned int i=0; i<size; i++)
            {
                delete children[i];
                children[i] = NULL;
            }

            free(children); 
            children = 0;
            size = 0;
            capacity = 0;
        }
    }

    ASNode* CALL clone()
    {
        return ValueASNode(type, value.c_str());
    }

    ASNode* CALL cloneTree()
    {
        ASNode *root = clone();

        for (unsigned int i=0; i<size; i++)
            root->append(children[i]->cloneTree());

        return root;
    }

    NodeType CALL getType()
    {
        return type;
    }

    void CALL setType(NodeType nodeType)
    {
        type = nodeType;
    }

    int CALL getStatus()
    {
        return status;
    }
    void CALL setStatus(int state)
    {
        status = state;
    }
    const char* CALL getValue()
    {
        return value.c_str();
    }

    void CALL setValue(const char* nodeValue)
    {
	    value = nodeValue;
    }

    ASNode* CALL get(unsigned int index)
    {
        ASNode* node = NULL;

        if (index < size)
            node = children[index];

	    return node;
    }

    ASNode* CALL set(unsigned int index, ASNode* aNode) 
    {
        ASNode* node = NULL;

        if (index < size)
        {
            node = children[index];
            node->setParent(NULL);

            aNode->setParent(this);
            children[index] = aNode;
        }
	    return node;
    }

    void CALL append(ASNode* aNode) 
    {
        aNode->setParent(this);

        if (size == capacity)
            reserve(2*capacity+1);

        *(children+size++) = aNode;
    }

    bool CALL insert(unsigned int index, ASNode* aNode) 
    {
        bool inserted = false;

        if (index < size)
        {
            if (size == capacity)
                reserve(2*capacity+1);

            for (unsigned int i=size++; i>index; i--)
                children[i] = children[i-1];

            aNode->setParent(this);
            children[index] = aNode;

            inserted = true;
        }
        return inserted;
    }

    ASNode* CALL remove(unsigned int index) 
    {
        ASNode* node = NULL;

        if (index < size)
        {
            node = children[index];
            node->setParent(NULL);

            for (unsigned int i=index; i<size-1; i++)
                children[i] = children[i+1];

            children[size] = 0;
            size--;
        }
        return node;
    }

    int CALL indexOf(ASNode* aNode)
    {
	    int index = -1;

        for (unsigned int i=0; i<size; i++)
        {
            if (children[i] == aNode) index = i;
        }
	    return index;
    }

    ASNode* CALL getParent()
    {
        return parent;
    }
    void CALL setParent(ASNode* node)
    {
        parent = node;
    }
    unsigned int CALL count() 
    {
        return size;
    }
    ASNode** CALL getChildren()
    {
        return children;
    }
    const char* CALL toString()
    {
    	str = nodeNames[type];
    	
    	if (type == String)
		    str += " = \"" + value + "\"; ";
        else
        {
            if (value.length() > 0)
                str += " = " + value + "; ";\
        }

        return str.c_str();
    }

private:
    void reserve(unsigned int count)
    {
        capacity = count;

        ASNode** array = (ASNode**)malloc(sizeof(ASNode*)*capacity);

        for (unsigned int i=0; i<size; i++)
            array[i] = children[i];

        free(children);
        children = array;
    }

    NodeType type;
    int status;

    string value;
    string str;

    ASNode*  parent;
    ASNode** children;

    unsigned int size;
    unsigned int capacity;
};
/*
 * Factory functions for ASNode.
 */
ASNode* CALL NewASNode(ASNode::NodeType type)
{
    ASNode* node = new ASNodeImpl(type);

    return node;
}
ASNode* CALL ValueASNode(ASNode::NodeType type, const char* value)
{
    ASNode* node = new ASNodeImpl(type, value);

    return node;
}
ASNode* CALL BinaryASNode(ASNode::NodeType type, ASNode* a, ASNode* b)
{
    ASNode* node = new ASNodeImpl(type);

    node->append(a);
    node->append(b);

    return node;
}

}
