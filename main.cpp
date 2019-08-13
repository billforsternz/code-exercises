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
bool BinaryTree_test();

int main( int argc, char *argv[] )
{
    bool ok = map_test();
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
    void insert( const T &key );
    void traverse( int depth );
    void traverse_read( std::vector<T> &keys );
    bool validate( T &max, T &min );
};


#if 0
// Implement it using standard library
template<class T>
class BinaryTree
{
public:
    std::set<T> bt;
    bool find( const T &key )       { auto it=bt.find(key); return it!= bt.end(); }
    void insert( const T &key )     { bt.insert(key); }
    void traverse()                 {}
    void clear()                    { bt.clear(); }
    std::vector<T> traverse_read()  { std::vector<T> keys; for( auto T: bt ) keys.push_back(T); return keys; }
    bool validate()                 { return true; }
};

#else
// Implement it ourself
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
};
#endif

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

template<class T> void BinaryTreeNode<T>::traverse_read( std::vector<T> &keys )
{
    keys.push_back(val);
    if( left )
        left->traverse_read(keys);
    if( right )
        right->traverse_read(keys);
}

// Get the max and min of this node and all its decendents, returns
//  ok if no problem found
template<class T> bool BinaryTreeNode<T>::validate( T &max, T &min )
{
    bool ok = true;
    if( val >= max )
        max = val;
    if( val <= min )
        min = val;
    if( right )
    {
        T right_max=val, right_min=val;
        ok = right->validate( right_max, right_min );
        ok = ok && right_min>=val; // everything to the right should be >= val
        max = right_max;
    }
    if( ok && left )
    {
        T left_max=val, left_min=val;
        ok = left->validate( left_max, left_min );
        ok = ok && left_max<=val; // everything to the left should be <= val
        min = left_min;
    }
    return ok;
}

template<class T> void BinaryTreeNode<T>::insert( const T &key  )
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
            left = make_shared<BinaryTreeNode<T>>(key);
    }
    else if( key > val )
    {
        if( right )
            right->insert(key);
        else
            right = make_shared<BinaryTreeNode<T>>(key);
    }
}

void countdown_game( BinaryTree<string> &dict, std::string letters );
void countdown( BinaryTree<string> &dict )
{
    std::string games[] =
    {
        "nesoawmig",
        "lutrasihs",
        "oairnsnds",
        "eotlysuct",
        "lnteierha",
        "eapocmest",
        "oautgsmir",
        "brftogdue"
    };

    for( int i=0; i<sizeof(games)/sizeof(games[0]); i++ )
    {
        countdown_game( dict, games[i] );
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
    if( !bt2.validate() )
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
    if( !bt3.validate() )
        return false;

    BinaryTree<string> dict;
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
        //dict.traverse();
        //cout << "Max depth = " << max_depth << "\n";
        if( !dict.validate() )
            return false;
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
        cout << "Test passed\n";
        countdown(dict);
    }
    return true;

}


int algo( BinaryTree<string> &dict,  BinaryTree<string> &solutions, std::string letters, std::string word_so_far, unsigned int best_so_far )
{
    int len = letters.length();
    std::string word = word_so_far;
    for( int i=0; i<len; i++ )
    {
        word = word_so_far;
        char c = letters[i];
        word += c;
        if( dict.find(word) )
        {
            if( word.length() > best_so_far )
            {
                best_so_far = word.length();
                solutions.clear();
                solutions.insert(word);
            }
            else if( word.length() == best_so_far )
            {
                if( !solutions.find(word) )
                    solutions.insert(word);
            }
        }
        std::string t, t1, t2;
        if( i>0 )
            t1 = letters.substr(0,i);
        if( i<len-1 )
            t2 = letters.substr(i+1);
        t = t1+t2;
        if( t.length() > 0 )
            best_so_far = algo( dict, solutions, t, word, best_so_far );
    }
    return best_so_far;
}

void countdown_game( BinaryTree<string> &dict, std::string letters )
{
    printf( "Letters are;\n%s\n", letters.c_str() );
    BinaryTree<string> solutions;
    algo( dict, solutions, letters, "", 0 );
    std::vector<string> keys = solutions.traverse_read();
    printf( "Solutions are;\n" );
    for( auto s: keys )
        printf( "%s\n", s.c_str() );
    printf( "\n" );
}

