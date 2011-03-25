/*
 *  ASNode.h
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

#ifndef __ASNode_h__
#define __ASNode_h__ 1

#include "translate.h"

namespace translate {
/**
 * ASNode is the class used by the parser to construct a tree representation of
 * an ActionScript program.
 * 
 * Node trees can also be constructed 'manually' and then encoded to give the 
 * binary representation of the byte-codes and actions that will be executed 
 * by the Flash Player.
 * 
 * For example, the node tree for the ActionScript statement:
 * 
\verbatim
    c = a + b;
\endverbatim
 * 
 * Can be represented using the following code to build the tree.
 * 
\verbatim
    ASNode* a = ValueASNode(ASNode::Identifier, "a");
    ASNode* b = ValueASNode(ASNode::Identifier, "b");
    ASNode* c = ValueASNode(ASNode::Identifier, "c");

    ASNode* addNode = BinaryASNode(ASNode::Add, a, b);
    ASNode* assignNode = BinaryASNode(ASNode::Assign, c, add);
\endverbatim
 *
 * Three factory functions are used to create ASNode objects:
 *
\verbatim
    ASNode* node = ASNode(NodeType);
    ASNode* node = ValueASNode(NodeType, const char*);
    ASNode* node = BinaryASNode(NodeType, ASNode*, ASNode*);
\endverbatim
 *
 * The functions are provided to extend binary compatibility of the Translate
 * library across different compilers and should cover the majority the majority
 * of cases where nodes are created.
 * 
 * The ASNode class defines a full range of node types ranging from specifying 
 * literals through to complex structures such as iterative and conditional 
 * constructs such as for loops and if/else blocks.
 * 
 * The simplest method for determining the structure of the trees that represent
 * different structure in ActionScript is to use the Interpreter class provided 
 * in the example code hosted on Flagstone's web site dump out the structure of 
 * the parsed code.
 * 
 * When a node is deleted all its children are deleted also, freeing up the
 * entire tree.
 */
class ASNode : public DLLInterface
{
public:
    enum NodeType
    {
        NoOp = 0,         /**< No operation, no actions are generated. */

        Array,            /**< An array of nodes for FSDoAction, FSButtonEvent of FSClipEvent objects. */            
        Button,           /**< An array of On nodes for an FSDefineButton2 object. */
        MovieClip,        /**< An array of OnClipEvent objects for an FSPlaceObject2 object. */

        List,             /**< A list of zero or more statements, use with block statements. */
        ExpressionList,   /**< A list of one or more assignment statements. */
        If,               /**< if() statement */
        For,              /**< for(;;) statement */
        ForIn,            /**< for x in() statement */
        While,            /**< while() statement */
        Do,               /**< do..while() statement */
        With,             /**< with() statement */
        OnClipEvent,      /**< onClipEvent() statement */
        On,               /**< on() statement */
        Break,            /**< break statement */
        Return,           /**< return statement */
        Continue,         /**< continue statement */

        Value,            /**< Access complex values. */
        Constant,         /**< Used for constant values on the predefined Key, Number and Math objects. */
        Number,           /**< A numeric literal. */
        String,           /**< A string literal. */
        Identifier,       /**< Return the value assigned to a variable. */
        Attribute,        /**< Access an object attribute. */
        Method,           /**< Call a method on an object. */
        Function,         /**< Call of ActionScript's built-in functions, getUrl().  */
        
        NewObject,        /**< create instances of objects, new Object(). */
        Subscript,        /**< Array subscript, x[1]. */
        DefineVariable,   /**< variable definitions using the var keyword. */
        DefineArray,      /**< Anonyomus arrays, [a, b, c, d]. */
        DefineFunction,   /**< User defined functions. */
        DefineAttribute,  /**< Define an attribute on a user defined object. */
        DefineMethod,     /**< Define a method on a user defined object. */
        DefineObject,     /**< User defined objects. */

        Add,              /**< Arithmetic add, + */
        Sub,              /**< Subtract operation, - */
        Mul,              /**< Multiply operation, * */
        Div,              /**< Divide operation, / */
        Mod,              /**< Modulo operation, % */
        LSL,              /**< Logical Shift Left operation, &lt;&lt; */
        ASR,              /**< Arithmetic Shift Right operation, &gt;&gt; */
        LSR,              /**< Logical Shift Right operation, &gt;&gt;&gt; */
        BitAnd,           /**< Bitwise AND operation, & */
        BitOr,            /**< Bitwise OR operation, | */
        BitXOr,           /**< Bitwise Exclusive-OR operation, ^ */
        And,              /**< Logical AND operation, && */
        Or,               /**< Logical OR operation, || */
        Equal,            /**< Equal comparison, == */
        NotEqual,         /**< Not Equal comparison, != */
        GreaterThan,      /**< Greater Than comparison, &gt; */
        LessThan,         /**< Less Than comparison, &lt; */
        GreaterThanEqual, /**< Greater Than or Equal comparison. &gt;= */
        LessThanEqual,    /**< Less Than or Equal comparison. &gt;= */
        
        Select,           /**< Use to represent the ternary ?: operator. */

        Not,              /**< Unary not. !x */
        BitNot,           /**< Unary bit-not, ~x */
        Plus,             /**< Unary plus. +x */
        Minus,            /**< Unary minus, -x */
        PreInc,           /**< Pre-increment, ++x */
        PreDec,           /**< Pre-decrement, --x */
        PostInc,          /**< Post-increment, x++ */
        PostDec,          /**< Post-decrement, x-- */

        Assign,           /**< Assign, = */
        AssignAdd,        /**< Assign add, += */
        AssignSub,        /**< Assign subtract, -= */
        AssignMul,        /**< Assign multiply, *= */
        AssignDiv,        /**< Assign divide, /= */
        AssignMod,        /**< Assign modulo, %= */
        AssignLSL,        /**< Assign logical shift left, &lt;&lt;= */
        AssignASR,        /**< Assign arithmetic shift right, &gt;&gt;= */
        AssignLSR,        /**< Assign logical shift right, &lt;&lt;&lt;= */
        AssignBitAnd,     /**< Assign bitwise-AND, &= */
        AssignBitOr,      /**< Assign bitwise-OR, |= */
        AssignBitXOr,     /**< Assign bitwise-exclusive-OR, ^= */

        DeleteObject,     /**< Delete an object */
        InstanceOf,       /**< Identify the class an object belongs to */
    };

    /**
     * Gets the type of the node.
     *
     * @return the type assigned to the node.
     */
    virtual NodeType CALL getType() = 0;
    /**
     * Sets the type of the node. Changing the type of a node after it has 
     * been assigned a value or child nodes can lead to unpredictable results.
     *
     * @param type the type assigned to the node.
     */
    virtual void CALL setType(NodeType type) = 0;
    /**
     * Get the value assigned to a node.
     *
     * @return a string representing the value assigned to a node.
     */
    virtual const char* CALL getValue() = 0;
    /**
     * Set the string representation of the value assigned to a node.
     *
     * @param val a string that will be assigned to the node.
     */
    virtual void CALL setValue(const char* val) = 0;
    /**
     * Gets the status of the node.
     *
     * @return the status assigned to the node.
     */
    virtual int CALL getStatus() = 0;
    /**
     * Sets the status of the node. This is used solely to pass information 
     * between nodes when the ASParser compiles the node into the byte-codes
     * or actions it represents.
     *
     * @param state the status assigned to the node.
     */
    virtual void CALL setStatus(int state) = 0;
    /**
     * Returns the node at the specified index from the array of child nodes. 
     * If the index is outside the range of the array then 0 is returned. It
     * should not be used directly.
     * 
     * @param index the index of the child node to return.
     * @return the child node at the specified index. Returns 0 if the 
     * node does not have a child at the specified index.
     */
    virtual ASNode* CALL get(unsigned int index) = 0;
    /**
     * Replaces the node at specified index in the array of child nodes. Returns
     * the replaced node or 0 if the node does not contain a child at the 
     * specified index.
     *  
     * @param index the index of the child node to replace.
     * @param aNode the node to replace the child node with.
     * @return the node being replaced or 0 if the node does not contain
     * a child at the specified index.
     */
    virtual ASNode* CALL set(unsigned int index, ASNode* aNode) = 0;
    /**
     * Appends a node to the array of children.
     * 
     * @param aNode the node to be added.
     */
    virtual void CALL append(ASNode* aNode) = 0;
    /**
     * Inserts a node at specified index in the array of children. The size of the 
     * array is increased by one and the nodes from the insertion point onwards
     * are moved to the right.
     *
     * If the node is successfully inserted the method returns true. If the position 
     * is beyond the last child node then node is not added and the method returns 
     * false.
     *  
     * @param index the index of the child node to replace.
     * @param aNode the node to replace the ith node.
     * @return true if the node was inserted successfully, false otherwise.
     */
    virtual bool CALL insert(unsigned int index, ASNode* aNode) = 0;
    /**
     * Removes the node at specified index in the array of child nodes. The size 
     * of the array is decreased by one and the nodes from the deletion point onwards
     * are moved to the left.
     *
     * The method returns the child node. If the position is beyond the last child 
     * node then 0 is returned.
     *
     * @param index the index of the child node to remove.
     * @return the node removed from the array of child nodes or 0 if there is 
     * no node at the specified index.
     */
    virtual ASNode* CALL remove(unsigned int index) = 0;
    /**
      * Returns the index of a node in the array of child nodes or -1 if the node 
      * was not found.
      *
      * @param aNode the node to search the array of children for.
      * 
      * @return the index of the node in the array of children or -1 if the 
      * node is not a child of this node.
      */
    virtual int CALL indexOf(ASNode* aNode) = 0;
    /**
     * Gets the parent node of this one. If the node is at the root of a tree then 
     * 0 is returned.
     *
     * @return the parent node of this one or 0 if the node is at the root of
     * a tree.
     */
    virtual ASNode* CALL getParent() = 0;
    /**
     * Sets the parent node of this node.
     *
     * @param aNode the parent node of this one or 0 if the node is at the root of
     * a tree.
     */
    virtual void CALL setParent(ASNode* aNode) = 0;
    /** 
     * Return the number of child nodes contained by this node.
     * 
     * @return the number of child nodes.
     */
    virtual unsigned int CALL count() = 0;
    /**
     * Returns a pointer to the array of child nodes.
     *
     * @return a pointer to the table of pointers referencing the child nodes.
     */
    virtual ASNode** CALL getChildren() = 0;
    /**
     * displays the type of node, any associated value.
     *
     * @return a string representation of the node.
     */
    virtual const char* CALL toString() = 0;
    /**
     * Returns a copy of this node initialized with the node type and 
     * value. No child nodes are copied.
     *
     * @return a shallow copy of this node.
     */
    virtual ASNode* CALL clone() = 0;
    /**
     * Returns a complete copy of the node tree. 
     *
     * @return a deep copy of this node.
     */
    virtual ASNode* CALL cloneTree() = 0;
};

/**
 * Factory method to create an instance of an ASNode object with the specified 
 * NodeType.
 *
 * @param nodeType the type of node to create.
 * @return an ASNode object.
 */
extern "C" ASNode* CALL NewASNode(ASNode::NodeType nodeType);
/**
 * Factory method to create an instance of an ASNode object with the specified 
 * NodeType and value.
 *
 * Strings are used to represent integer and string literals. The NodeType
 * specified is used to differentiate the types.
 *
 * @param nodeType the type of node to create.
 * @param nodeValue a string representation of the value assigned to the node.
 * @return an ASNode object.
 */
extern "C" ASNode* CALL ValueASNode(ASNode::NodeType nodeType, const char* nodeValue);
/**
 * Factory method to create an instance of an ASNode object with the specified 
 * NodeType and two child nodes.
 *
 * For all nodes the order in which child nodes are added is important.
 *
 * @param nodeType the type of node to create.
 * @param a the first child noded added.
 * @param b the second child node added.
 * @return an ASNode object.
 */
extern "C" ASNode* CALL BinaryASNode(ASNode::NodeType nodeType, ASNode* a, ASNode* b);

}

#endif
