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
        cout << "BinaryTree test failed\n";        
    return 0;
}

bool set_test()
{
    set<string> dict;
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
        while( getline(in,s) )
        {
            util::rtrim(s);
            dict.insert(s);
        }
        printf( "Reading dictionary, end\n" );
        auto it = dict.find("book");
        if( it == dict.end() )
            return false;
        it = dict.find("engineer");
        if( it == dict.end() )
            return false;
        it = dict.find("hfkhasdhkdfla");
        if( it != dict.end() )
            return false;
    }
    return true;
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


class BinaryTree
{
public:
    BinaryTree(int x) : val(x) {}
    int val;
    shared_ptr<BinaryTree> left;
    shared_ptr<BinaryTree> right;
    bool find( int key );
    void insert( int key );
};

bool BinaryTree::find( int key )
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

void BinaryTree::insert( int key )
{
    if( key == val )
    {
        auto temp = make_shared<BinaryTree>(key);
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
            BinaryTree bt(key);
            *left = bt;
#else
            left = make_shared<BinaryTree>(key);
#endif
        }
    }
    else if( key > val )
    {
        if( right )
            right->insert(key);
        else
            right = make_shared<BinaryTree>(key);
    }
}

bool BinaryTree_test()
{
    bool ok = true;

    // Manually constructed binary tree
    BinaryTree bt(3);
    bt.left = make_shared<BinaryTree>(2);
    bt.right = make_shared<BinaryTree>(4);
    if( !bt.find(2) )
        return false;
    if( !bt.find(3) )
        return false;
    if( !bt.find(4) )
        return false;
    if( bt.find(5) )
        return false;

    // Programmatically constructed binary tree
    BinaryTree bt2(3);
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
    return ok;
}

