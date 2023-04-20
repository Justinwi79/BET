#ifndef BET_H    
#define BET_H

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

template <typename T>
    class BET{
        public: 
            BET();
            BET(const string& postfix);
            BET(const BET&);
            ~BET();
            bool buildFromPostfix(const string& postfix);
            const BET & operator= (const BET &);
            void printInfixExpression();
            void printPostfixExpression();
            size_t size();
            size_t leaf_nodes();
            bool empty();

    

        private: 
            struct BinaryNode{
                T element;
                BinaryNode *left;
                BinaryNode *right;
                
                BinaryNode(const T & e = T{}, BinaryNode *l = nullptr,
                    BinaryNode *r = nullptr)
                    : element{e}, left{l}, right{r}{}
                BinaryNode(std::string && e, BinaryNode *l = nullptr,
                    BinaryNode *r = nullptr)
                    : element{std::move(e)}, left{l}, right{r}{}
                //^^copied from List project
            };
        BinaryNode *root;
        stack<BinaryNode*> Stack;
        void printInfixExpression(BinaryNode *n);
        void makeEmpty(BinaryNode* &t);
        BinaryNode * clone(BinaryNode *t) const;
        void printPostfixExpression(BinaryNode *n);
        size_t size(BinaryNode *t);
        size_t leaf_nodes(BinaryNode *t);
        bool isOperator(const std::string &r);
        bool isOperand(const std::string &nd);

    
    };

#include "bet.hpp"
#endif