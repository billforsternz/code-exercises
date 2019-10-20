#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <memory>

template<class T>
class BinaryTreeNode
{
public:
    BinaryTreeNode(T x) : val(x) {}
    T val;
    std::shared_ptr<BinaryTreeNode> left;
    std::shared_ptr<BinaryTreeNode> right;
    bool find( const T &key );
    void insert( const T &key );
    void traverse( int depth );
    void traverse_read( std::vector<T> &keys )
    {
        keys.push_back(val);
        if( left )
            left->traverse_read(keys);
        if( right )
            right->traverse_read(keys);
    }
    bool validate( T &max, T &min );
    void breadth_first_dump( bool &hit, int depth, int target_depth );
};

template<class T>
class BinaryTree
{
public:
    std::shared_ptr<BinaryTreeNode<T>> data;
    bool find( const T &key )
    {
        if( data )
            return data->find(key);
        else
            return false;
    }
    void insert( const T &key )
    {
        if( data )
            data->insert(key);
        else
            data = std::make_shared<BinaryTreeNode<T>>(key);
    }
    void traverse()
    {
        if( data )
            data->traverse(1);
    }
    void clear()
    {
        data.reset();
    }
    std::vector<T> traverse_read()
    {
        std::vector<T> keys;
        if( data )
            data->traverse_read(keys);
        return keys;
    }
    bool validate()
    {
        bool ok=true;
        if( data )
        {
            T max=data->val, min=data->val;
            ok = data->validate( max, min );
        }
        return ok;
    }
    void breadth_first_dump()
    {
        if( data )
        {
            int depth = 0;
            bool hit=true;
            while(hit)
            {
                hit = false;
                data->breadth_first_dump(hit,0,depth++);
                std::cout << "\n";
            }
        }
    }
};


bool BinaryTree_test( BinaryTree<std::string> &dict );

#endif
