#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include "util.h"

using namespace std;

bool map_test();
bool shared_ptr_test();
bool set_test();
bool BinaryTree_test();

int main( int argc, char *argv[] )
{
    bool ok = set_test();
    if( !ok )
        cout << "Set test failed\n";        
    ok = map_test();
    if( !ok )
        cout << "Map test failed\n";        
    ok = shared_ptr_test();
    if( !ok )
        cout << "Shared ptr test failed\n";        
    ok = BinaryTree_test();
    if( !ok )
        cout << "BinaryTreeNode test failed\n";        
    return 0;
}

bool map_test()
{
    bool ok = true;
    map<string,string> m;
    m["John"] = "Pizza";
    m["Bill"] = "Cake";
    auto it = m.find("John");
    if( it == m.end() )
        ok = false;
    else
        ok = (it->second == "Pizza");
    if( ok )
    {
        it = m.find("Roger");
        ok = (it == m.end());
    }
    return ok;
}

bool shared_ptr_test()
{
    bool ok=true;
    shared_ptr<int> p = make_shared<int>(3);
    ok = (*p == 3);
    if( ok )
    {
        shared_ptr<int> q;
        q = make_shared<int>(4);
        ok = (*q == 4);
    }
    return ok;
}


template<class T>
class BinaryTreeNode
{
public:
    BinaryTreeNode(T x) : val(x) {}
    T val;
    shared_ptr<BinaryTreeNode> left;
    shared_ptr<BinaryTreeNode> right;
    bool find( const T &key );
    void insert( const T &key );
};

template<class T>
class BinaryTree
{
public:
    shared_ptr<BinaryTreeNode<T>> data;
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
            data = make_shared<BinaryTreeNode<T>>(key);
    }
};

template<class T> bool BinaryTreeNode<T>::find( const T &key )
{
    if( key == val )
        return true;
    else if( key<val && left)
        return left->find(key);
    else if( key>val && right)
        return right->find(key);
    else
        return false;
}

template<class T> void BinaryTreeNode<T>::insert( const T &key )
{
    if( key == val )
    {
        auto temp = make_shared<BinaryTreeNode<T>>(key);
        temp->left = left;
        left = temp;
    }
    else if( key < val )
    {
        if( left )
            left->insert(key);
        else
        {
#if 0
            BinaryTreeNode bt(key);
            *left = bt;
#else
            left = make_shared<BinaryTreeNode<T>>(key);
#endif
        }
    }
    else if( key > val )
    {
        if( right )
            right->insert(key);
        else
            right = make_shared<BinaryTreeNode<T>>(key);
    }
}

bool BinaryTree_test()
{
    bool ok = true;

    BinaryTree<int> bt2;
    bt2.insert(3);
    bt2.insert(4);
    bt2.insert(100);
    bt2.insert(1000);
    bt2.insert(2);
    bt2.insert(50);
    if( !bt2.find(2) )
        return false;
    if( !bt2.find(3) )
        return false;
    if( !bt2.find(4) )
        return false;
    if( !bt2.find(50) )
        return false;
    if( !bt2.find(100) )
        return false;
    if( !bt2.find(1000) )
        return false;
    if( bt2.find(5) )
        return false;

    BinaryTree<string> bt3;
    bt3.insert("Roger");
    bt3.insert("Rabbit");
    bt3.insert("Potter");
    if( !bt3.find("Roger") )
        return false;
    if( !bt3.find("Rabbit") )
        return false;
    if( !bt3.find("Potter") )
        return false;
    if( bt3.find("Steve") )
        return false;
    return ok;
}

bool set_test()
{
#if 1
    BinaryTree<string> dict;
#else
    set<string> dict;
#endif
    ifstream in("wlist_match12.txt");
    if( !in )
    {
        cout << "Cannot read wlist_match12.txt\n";        
        return false;
    }
    else
    {
        string s;
        printf( "Reading dictionary, begin\n" );
        int count=0;
        while( count++<100 && getline(in,s) )
        {
            util::rtrim(s);
            dict.insert(s);
        }
        printf( "Reading dictionary, end\n" );
#if 1
        if( !dict.find("absorb") )
            return false;
        if( !dict.find("absorbed") )
            return false;
        if( dict.find("absorbfla") )
            return false;
#else
        auto it = dict.find("book");
        if( it == dict.end() )
            return false;
        it = dict.find("engineer");
        if( it == dict.end() )
            return false;
        it = dict.find("hfkhasdhkdfla");
        if( it != dict.end() )
            return false;
#endif
    }
    return true;
}

