
// *********************************************************************
// * Default Constructor                                               *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Previous List and Stack projects                      *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
BET<T>::BET():root{nullptr}{}

// *********************************************************************
// * 1 parameter constructor                                           *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Previous List and Stack projects                      *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
BET<T>::BET(const std::string & postfix):root {nullptr}
{
    buildFromPostfix(postfix);
}

// *********************************************************************
// * Copy constructor                                                  *
// * Last updated: 7/5/22                                              *
// * By: Harold Windham                                                * 
// * References: Previous List and Stack projects                      *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T> 
BET<T>::BET(const BET& b):root {nullptr}
{
    root = clone(b.root);
}

// *********************************************************************
// * Destructor                                                        *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Previous List and Stack projects                      *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
BET<T>::~BET()
{
    makeEmpty(root);
}

// *********************************************************************
// * Determine if input is operand                                     *
// * Last updated: 7/8/22                                              *
// * By: Harold Windham                                                * 
// * References:                                                       *
// * Code for buildFromPostfix function found on Michael Rand's        * 
// *     github account from 2015 cop4530 project.                     *
// * https://github.com/mrand13/COP4530/blob/master/Binary%20Expression*
// *     %20Tree/bet.cpp                                               *
// *********************************************************************

template <typename T>
bool BET<T>::buildFromPostfix(const std::string& postfix)
{
    if(!empty())
    {
        makeEmpty(root);
    }
    bool ret = true;
    std::string post = postfix, token;
    for(std::string::iterator it = post.begin(); it!= post.end(); ++it)
    {
        token += *it;   
        if(*it == ' ' || it == (post.end()- 1))
        {
            if(*it == ' ')
                token.pop_back();
            if(isOperand(token))
            {
                BinaryNode *n = new BinaryNode(token,nullptr,nullptr);
                Stack.push(n);
            }
            else if(isOperator(token))
            {
                BinaryNode *r, *l;    
                if(!Stack.empty())
                {
                    r = Stack.top();
                    Stack.pop();
                }
                else {ret = false;break;}
                if(!Stack.empty())
                {
                    l = Stack.top();
                    Stack.pop();
                }
                else {ret = false; break;}
                BinaryNode *op = new BinaryNode(token,l,r);
                Stack.push(op);
            }
            token = ""; 
        }
    }
    if(!Stack.empty())
    {
        root = Stack.top(); 
        if(Stack.size() > 1 && isOperand(root->element))
            ret = false;
    }
    else ret = false;
    return ret;
}

// *********************************************************************
// * Assignment operator overload                                      *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Previous List and Stack projects                      *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T> 
const BET<T>& BET<T>::operator=(const BET<T> &r)
{
  root = r.clone(r.root);
  return *this;
}

// *********************************************************************
// * Print infix                                                       *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Dr. Gaitros course videos                             *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
void BET<T>::printInfixExpression()
{
    printInfixExpression(root);
}

// *********************************************************************
// * Print postfix                                                     *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Dr. Gaitros course videos                             *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
void BET<T>::printPostfixExpression()
{
    printPostfixExpression(root);
}

// *********************************************************************
// * Return size of root                                               *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References:                                                       *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
size_t BET<T>::size()
{
    return size(root);
}

// *********************************************************************
// * Return number of leaf nodes                                       *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Previous List and Stack projects                      *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
size_t BET<T>::leaf_nodes()
{
    return leaf_nodes(root);
}

// *********************************************************************
// * Returns true if empty                                             *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Previous List and Stack projects                      *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
bool BET<T>::empty()
{
    if(root == nullptr)
        return true;
    else
        return false;
}

// *********************************************************************
// * Print the infix                                                   *
// * Last updated: 7/7/22                                              *
// * By: Harold Windham                                                * 
// * References: Previous List and Stack projects                      *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
void BET<T>::printInfixExpression(BinaryNode *n)
{
    if(n != nullptr)
    {
        printInfixExpression(n->left);
        printInfixExpression(n->right);
        std::cout << n->element << " ";
    }
}

// *********************************************************************
// * makeEmpty to delete elements                                      *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References:                                                       *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
void BET<T>::makeEmpty(BinaryNode* &t)
{
    if(t != nullptr) 
    {
        makeEmpty(t->left); 
        makeEmpty(t->right); 
        delete t;
    }
    t = nullptr;
}

// *********************************************************************
// * clone to create new node                                          *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References:                                                       *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
typename BET<T>::BinaryNode * BET<T>::clone(BinaryNode *t) const
{
    if(t == nullptr) 
        return nullptr; 
    else   
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

// *********************************************************************
// * Print the postfix                                                 *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Dr. Gaitros course videos                             *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
void BET<T>::printPostfixExpression(BinaryNode *n)
{
    if(n != nullptr)
    {
	    printPostfixExpression(n->left);
		printPostfixExpression(n->right);
		std::cout << n->element << " ";
    }
}

// *********************************************************************
// * Return size of root                                               *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Dr. Gaitros course videos                             *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
size_t BET<T>::size(BinaryNode *t)
{
    if(t == nullptr)
        return 0;
    else 
    {
        int _size = 1;
        _size += size(t->left);   
        _size += size(t->right);  
        return _size;
    }
}

// *********************************************************************
// * Return number of leaf nodes                                       *
// * Last updated: 7/4/22                                              *
// * By: Harold Windham                                                * 
// * References: Dr. Gaitros course videos                             *
// * Data Structures and Algorithm Analysis in C++ Fourth Edition Chp 4*
// *********************************************************************

template <typename T>
size_t BET<T>::leaf_nodes(BinaryNode *t)
{   
    int leaf = 0;
    if (t->left == nullptr && t->right == nullptr)
        leaf++;
    else 
    {
        if(t->left != nullptr)
            leaf += leaf_nodes(t->left);   
        if(t->right != nullptr)
            leaf += leaf_nodes(t->right);  
    }
    return leaf;
}

// *********************************************************************
// * Determine if input is operator                                    *
// * Last updated: 7/5/22                                              *
// * By: Harold Windham                                                * 
// * References:                                                       *
// * https://github.com/mrand13/COP4530/blob/master/Binary%20Expression*
// *     %20Tree/bet.cpp                                               *
// *********************************************************************

template <typename T>  
bool BET<T>::isOperator(const std::string &r)
{
    return(r == "+" || r == "-" || r == "/" ||
         r == "*");
}

// *********************************************************************
// * Determine if input is operand                                     *
// * Last updated: 7/5/22                                              *
// * By: Harold Windham                                                * 
// * References:                                                       *
// * https://github.com/mrand13/COP4530/blob/master/Binary%20Expression*
// *     %20Tree/bet.cpp                                               *
// *********************************************************************

template <typename T> 
bool BET<T>::isOperand(const std::string &nd)
{
    if(nd.length() == 1)
    {
        char c = nd[0];
        return((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9') || (c == '_'));
    }
    else return true;
}
