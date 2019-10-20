#include "bst.h"
#include "util.h"

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

/*
template<class T> void BinaryTreeNode<T>::traverse_read( std::vector<T> &keys )
{
    keys.push_back(val);
    if( left )
        left->traverse_read(keys);
    if( right )
        right->traverse_read(keys);
}
  */

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

template<class T> void BinaryTreeNode<T>::breadth_first_dump( bool &hit, int depth, int target_depth  )
{
    if( depth == target_depth )
    {
        hit = true;
        std::cout << (left?left->val:"NULL");
        std::cout << " (" << val << ") ";
        std::cout << (right?right->val:"NULL") << ", ";
    }
    else
    {
        if( left )
            left->breadth_first_dump( hit, depth+1, target_depth );
        if( right )
            right->breadth_first_dump( hit, depth+1, target_depth );
    }
}

template<class T> void BinaryTreeNode<T>::insert( const T &key  )
{
    if( key == val )
    {
        auto temp = std::make_shared<BinaryTreeNode<T>>(key);
        temp->left = left;
        left = temp;
    }
    else if( key < val )
    {
        if( left )
            left->insert(key);
        else
            left = std::make_shared<BinaryTreeNode<T>>(key);
    }
    else if( key > val )
    {
        if( right )
            right->insert(key);
        else
            right = std::make_shared<BinaryTreeNode<T>>(key);
    }
}

bool BinaryTree_test( BinaryTree<std::string> &dict )
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

    BinaryTree<std::string> bt3;
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

    std::ifstream in("wlist_match12.txt");
    if( !in )
    {
        std::cout << "Cannot read wlist_match12.txt\n";        
        return false;
    }
    else
    {
        std::string s;
        std::cerr << "Reading dictionary, begin\n";
        std::vector<std::string> v;
        std::vector<bool> flags;
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
        std::cerr << util::sprintf( "Reading dictionary(%d,%d), end\n", rands++, len-1000 );
        //dict.breadth_first_dump();
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
        std::cout << "Test passed\n";
    }
    return true;
}

