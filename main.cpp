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

static int max_depth;

template<class T> class BinaryTree;

template<class T>
class BinaryTreeNode
{
public:
    BinaryTreeNode(T x) : val(x) {}
    T val;
    shared_ptr<BinaryTreeNode> left;
    shared_ptr<BinaryTreeNode> right;
    bool find( const T &key );
    void insert( const T &key, BinaryTree<T> *root, int count );
    void traverse( int depth );
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
            data->insert(key,this,0);
        else
            data = make_shared<BinaryTreeNode<T>>(key);
    }
    void traverse()
    {
        if( data )
            data->traverse(1);
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

template<class T> void BinaryTreeNode<T>::traverse( int depth )
{
    if( depth > max_depth )
        max_depth = depth;
    cout << depth << " ";
    cout << val << "\n";
    if( left )
    {
        cout << "L";
        left->traverse(++depth);
    }
    if( right )
    {
        cout << "R";
        right->traverse(++depth);
    }
}

template<class T> void BinaryTreeNode<T>::insert( const T &key, BinaryTree<T> *root, int count  )
{
    if( key == val )
    {
        auto temp = make_shared<BinaryTreeNode<T>>(key);
        temp->left = left;
        left = temp;
    }
 /*  else if( count > 5 )
    {
        auto temp = make_shared<BinaryTreeNode<T>>(key);
        if( key < root->data->val )
            temp->right = root->data;
        else
            temp->left = root->data;
        root->data = temp;
    } */
    else if( key < val )
    {
        if( left )
            left->insert(key,root,count+1);
        else
            left = make_shared<BinaryTreeNode<T>>(key);
    }
    else if( key > val )
    {
        if( right )
            right->insert(key,root,count+1);
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
        cerr << "Reading dictionary, begin\n";
        vector<string> v;
        vector<bool> flags;
        while( getline(in,s) )
        {
            util::rtrim(s);
            v.push_back(s);
            flags.push_back(false);
        }
        int len = v.size();
        int count = 0, rands=0;
        while( count < len-1000 )
        {
            int idx = rand();
            rands++;
            idx = idx%len;
            if( !flags[idx] )
            {
                flags[idx] = true;
                dict.insert( v[idx] );
                count++;
            }
        }
        for( int idx=0; idx<len; idx++ )
        {
            if( !flags[idx] )
            {
                flags[idx] = true;
                dict.insert( v[idx] );
            }
        }
        cerr << util::sprintf( "Reading dictionary(%d,%d), end\n", rands++, len-1000 );
#if 1
        dict.traverse();
        cout << max_depth;
        cerr << "Max depth = " << max_depth;
        if( !dict.find("absorb") )
            return false;
        if( !dict.find("absorbed") )
            return false;
        if( dict.find("absorbfla") )
            return false;
        if( !dict.find("random") )
            return false;
        if( !dict.find("good") )
            return false;
        if( dict.find("hfdkjhafd") )
            return false;
        if( !dict.find("book") )
            return false;
        if( !dict.find("engineer") )
            return false;
        if( dict.find("hfkhasdhkdfla") )
            return false;
        cerr << "Test passed";
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


