#include <windows.h>
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
#include <memory>
#include <functional>
#include "util.h"
#include "bst.h"

bool map_test();
bool shared_ptr_test();
bool BinaryTree_test();

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    bool checked_get_min_max(TreeNode *node, int &min, int &max )
    {
        int val = node->val;
        min = val;
        max = val;
        int right_min=val, right_max=val;
        if( node->right )
        {
            if( !checked_get_min_max(node->right,right_min,right_max) )
                return false;
            if( ! (val < right_min) )
                return false;
            max = right_max;
        }
        int left_min=val, left_max=val;
        if( node->left )
        {
            if( !checked_get_min_max(node->left,left_min,left_max) )
                return false;
            if( !(left_max < val) )
                return false;
            min = left_min;
        }
        return true;
    }
public:
    bool isValidBST(TreeNode* root) {
        if(root)
        {
            int min = root->val;
            int max = root->val;
            return checked_get_min_max(root,min,max);
        }
        return true;
    }
};

void leet_test()
{
    TreeNode a(2);
    TreeNode b(1);
    TreeNode c(3);
    a.left = &b;
    a.right = &c;
    Solution s;
    bool ok = s.isValidBST(&a);
    printf( "leet_test() %s\n", ok?"PASS":"FAIL" );
}


// Forward declaration of isBadVersion API.
bool isBadVersion(int version) { return version>=4; }

class Solution2 {
public:
    int firstBadVersion(int n) {
        int hi = n;
        int lo = 1;
        int x;
        bool xIsBad;
        do
        {
            x = lo + (hi-lo)/2;
            xIsBad = isBadVersion(x);
            if( xIsBad )
                hi = x;
            else
                lo = x;
        } while( hi-lo > 1 );
        return xIsBad? x : x+1;
    }
};


void leet_test2()
{
    Solution2 s;
    int firstBadVersion = s.firstBadVersion(5);
    bool ok = (firstBadVersion==4);
    printf( "leet_test2() %s\n", ok?"PASS":"FAIL" );
}

class Solution3 {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        int *p1 = &nums1[0];
        int *p2 = &nums2[0];
        while(n)
        {
            int x = *p2++;
            n--;
            while( m && x>*p1 )
            {
                p1++;
                m--;
            }
            int *src = p1+m-1;
            int *dst = p1+m;
            for( int i=0; i<m; i++ )
            {
                *dst-- = *src--;
            }
            *p1++ = x;
        }
    }
};

void leet_test3()
{
    Solution3 s;
    std::vector<int> nums1;
    nums1.push_back(1);
    nums1.push_back(2);
    nums1.push_back(3);
    nums1.push_back(0);
    nums1.push_back(0);
    nums1.push_back(0);
    int m=3;
    std::vector<int> nums2;
    nums2.push_back(2);
    nums2.push_back(5);
    nums2.push_back(6);
    int n=3;
    s.merge(nums1,m,nums2,n);
    bool ok = (nums1.size()==6 && nums1[0]==1 && nums1[1]==2 && nums1[2]==2 && nums1[3]==3 && nums1[4]==5 && nums1[5]==6);
    printf( "leet_test3() %s\n", ok?"PASS":"FAIL" );
}


class Solution4 {
public:
    std::map<int,int> cache;
    int possible_ways_from_here(int step,int target)
    {
        auto it = cache.find(step);
        if( it != cache.end() )
            return it->second;
        else if( step == target )
            return 1;
        else if( step < target )
        {
            int result = possible_ways_from_here(step+1,target) + possible_ways_from_here(step+2,target);
            cache[step] = result;
            return result;
        }
        else
            return 0;
    }
    int climbStairs(int n) {
        cache.clear();
        return possible_ways_from_here(0,n);
    }
};

void leet_test4()
{
    Solution4 s;
    unsigned long numberWays = s.climbStairs(50);
    printf( "leet_test4(); climbStairs(50) returns %lu\n", numberWays );
    bool ok = (numberWays == 3185141890L);
    printf( "leet_test4() %s\n", ok?"PASS":"FAIL" );
}

class Solution5 {
public:
    std::map<int,int> cache;
    int min_price_from_here(int step, std::vector<int>& cost, int target)
    {
        auto it = cache.find(step);
        if( it != cache.end() )
            return it->second;
        else if( step == target-1 )
            return cost[step];
        else if( step == target-2 )
            return cost[step];
        else if( step < target-2 )
        {
            int poss1 = cost[step] + min_price_from_here(step+1, cost, target );
            int poss2 = cost[step] + min_price_from_here(step+2, cost, target );
            int result = poss1<poss2 ? poss1 : poss2;
            cache[step] = result;
            return result;
        }
        else
            return 0;
    }
    int minCostClimbingStairs(std::vector<int>& cost) {
        cache.clear();
        int poss1 = min_price_from_here( 0, cost, cost.size() );
        int poss2 = min_price_from_here( 1, cost, cost.size() );
        return poss1<poss2 ? poss1 : poss2;
    }
};

void leet_test5()
{
    Solution5 s;
    std::vector<int> cost;
    cost.push_back(1);
    cost.push_back(100);
    cost.push_back(1);
    cost.push_back(1);
    cost.push_back(1);
    cost.push_back(100);
    cost.push_back(1);
    cost.push_back(1);
    cost.push_back(100);
    cost.push_back(1);
    int price = s.minCostClimbingStairs(cost);
    printf( "leet_test5(); minCostClimbingStairs([1, 100, 1, 1, 1, 100, 1, 1, 100, 1]) returns %lu\n", price );
    bool ok = (price==6);
    printf( "leet_test5() %s\n", ok?"PASS":"FAIL" );
}

class Solution6 {
public:
    int lengthOfLongestSubstring(std::string s) {
        int longest_so_far = 0;
        int len = s.length();
        for( int i=0; i<len; i++ )
        {
            bool flags[256];
            memset(flags,0,sizeof(flags));
            for( int j=i; j<len; j++ )
            {
                int idx = 0xff & s[j];
                if( !flags[idx] )
                {
                    flags[idx] = true;
                }
                else
                {
                    if( j-i > longest_so_far )
                        longest_so_far = j-i;
                    break;
                }
            }
        }
        return longest_so_far;
    }
};

void leet_test6()
{
    Solution6 s;
    int len = s.lengthOfLongestSubstring(" ");
    printf( "leet_test6(); lengthOfLongestSubstring(\" \") returns %d\n", len );
    bool ok = (len==1);
    printf( "leet_test6() %s\n", ok?"PASS":"FAIL" );
}

class Solution7 {
public:
    bool isNumber(std::string s) {
        enum {init,trail,digits,pos,neg,exp_init,exp_init2,exp_digits,exp_dot_init,dot_init,init_dot_init,dot_digits,zeroes} state;
        state = init;
        bool positive=true;
        for( char c: s )
        {
            bool digit = ('0'<=c && c<= '9');
            switch( state )
            {
                case init:
                {
                    if( c==' ' )
                        break;
                    else if( c=='e' )
                        return false;
                    else if( c=='+')
                        state = pos;
                    else if( c=='-')
                        state = neg;
                    else if( c=='.')
                        state = init_dot_init;
                    else if( digit )
                        state = digits;
                    else
                        return false;
                    break;
                }

                case neg:
                    positive = false;
                case pos:
                {
                    if( c=='e' )
                        return false;
                    else if( c=='.')
                        state = init_dot_init;
                    else if( digit )
                        state = digits;
                    else
                        return false;
                    break;
                }

                case digits:
                {
                    if( c == ' ' )
                        state = trail;
                    else if( c=='e' )
                        state = exp_init;
                    else if ( c=='.' )
                        state = dot_init;
                    else if( !digit )
                        return false;
                    break;
                }

                case init_dot_init:
                {
                    if( digit )
                        state = dot_digits;
                    else
                        return false;
                    break;
                }

                case dot_init:
                {
                    if( c == ' ' )
                        state = trail;
                    else if( c=='e' )
                        state = exp_init;
                    else if( digit )
                        state = dot_digits;
                    else
                        return false;
                    break;
                }

                case exp_dot_init:
                {
                    if( c =='0' )
                        state = zeroes;
                    else
                        return false;
                    break;
                }

                case dot_digits:
                {
                    if( c == ' ' )
                        state = trail;
                    else if( c == 'e' )
                        state = exp_init;
                    else if( !digit )
                        return false;
                    break;
                }

                case zeroes:
                {
                    if( c == ' ' )
                        state = trail;
                    else if( c != '0' )
                        return false;
                    break;
                }

                case exp_init:
                {
                    if( c=='+' || c=='-' )
                        state = exp_init2;
                    else if( digit )
                        state = exp_digits;
                    else
                        return false;
                    break;
                }

                case exp_init2:
                {
                    if( digit )
                        state = exp_digits;
                    else
                        return false;
                    break;
                }

                case exp_digits:
                {
                    if( c=='.' )
                        state = exp_dot_init;
                    else if( !digit )
                        return false;
                    break;
                }

                case trail:
                {
                    if( c != ' ' )
                        return false;
                    break;
                }

            }
        }
        bool ok = (state==digits||state==trail||state==exp_digits||state==dot_init||state==dot_digits||state==zeroes);
        return ok;
    }
};
void leet_test7()
{
    Solution7 s;
    bool is_number = s.isNumber("1 ");
    printf( "leet_test7(); isNumber(\"1 \") returns %s\n", is_number?"true":"false" );
    bool ok = (is_number==true);
    printf( "leet_test7() %s\n", ok?"PASS":"FAIL" );
}


void quick_sort( std::vector<int> &v )
{
    void quick_sort_ptr( int *p, int count );
    quick_sort_ptr( &v[0], v.size() );
}


#define BILL_OPTIMISE 1
void quick_sort_ptr( int *p, int count )
{
    if( count <= 1 )
        return;
    else
    {
        int key = p[0];
        int front=0;
#if BILL_OPTIMISE == 1
        int previous = p[0];
        bool sorted = true;
        for( int i=0; i<count; i++ )
        {
            int dat = p[i];
            if( dat < previous )
                sorted = false;
            if( dat < key )
                front++;
            previous = dat;
        }
        if( sorted )
            return;
#else
        for( int i=0; i<count; i++ )
        {
            if( p[i] < key )
                front++;
        }
#endif
        int *lower = p;
        int *pivot = p + front;
        int *higher = pivot;
        int temp = *lower;
        *lower = *higher;
        *higher++ = temp;
        while( lower < pivot )
        {
            if( *lower >= key )
            {
                while( *higher >= key )
                    higher++;
                temp = *lower;
                *lower = *higher;
                *higher++ = temp;
            }
            lower++;
        }
        quick_sort_ptr( p, front+1 );
        quick_sort_ptr( p+front+1, count-front-1 );
    }
}

void merge_sort( std::vector<int> &v )
{
    void merge_sort_ptr( int *p, int count );
    merge_sort_ptr( &v[0], v.size() );
}

void merge_sort_ptr( int *p, int count )
{
    if( count <= 1 )
        return;
    else
    {
        int *save = p;
        std::vector<int> work;
        int half = count/2;
        int *q = p+half;
        int *end1 = q;
        int *end2 = q + count-half;
        merge_sort_ptr( p, half );
        merge_sort_ptr( q, count-half );
        while( p<end1 || q<end2 )
        {
            int n;
            if( p<end1 && q<end2 )
            {
                if( *p < *q )
                    n = *p++;
                else
                    n = *q++;
            }
            else if( p<end1 )
            {
                n = *p++;
            }
            else
            {
                n = *q++;
            }
            work.push_back(n);
        }
        std::copy( work.begin(), work.end(), save );
    }
}

void test_merge_sort()
{
    std::vector<int> v;
#if 1
    for( int i=0; i<101; i++ )
    {
        int n = rand();
        v.push_back(n);
    }
#else
    v.push_back( 3 );
    v.push_back( 6 );
    v.push_back( 5 );
    v.push_back( 2 );
    v.push_back( 4 );
#endif
    std::vector<int> w;
    w = v;
    std::sort( w.begin(), w.end() );
    merge_sort( v );
    bool ok = (v==w);
    printf( "merge_sort: %s\n", ok?"PASS":"FAIL");
}

void test_quick_sort()
{
    std::vector<int> v;
#if 1
    for( int i=0; i<101; i++ )
    {
        int n = rand();
        v.push_back(n);
    }
#else
    v.push_back( 3 );
    v.push_back( 6 );
    v.push_back( 5 );
    v.push_back( 2 );
    v.push_back( 4 );
#endif
    std::vector<int> w;
    w = v;
    std::sort( w.begin(), w.end() );
    quick_sort( v );
    bool ok = (v==w);
    printf( "quick_sort: %s\n", ok?"PASS":"FAIL");
}

void heap_insert( std::vector<int> &heap, int n )
{
    heap.push_back( n );
    int idx = heap.size()-1;
    while( idx > 0 )
    {
        int kdx = idx+1;
        int kdx_parent = kdx/2;
        if( n <= heap[kdx_parent-1] )
            break;
        int temp = heap[kdx_parent-1];
        heap[kdx_parent-1] = n;
        heap[idx] = temp;
        idx = kdx_parent-1;
    }
}

bool heap_remove( std::vector<int> &heap, int &n )
{
    int sz = heap.size();
    if( sz < 1 )
        return false;
    n = heap[0];

    // Replace root with last element in heap
    int x = heap[sz-1];
    heap[0] = x;
    heap.pop_back();
    sz--;
    if( sz == 0 )
        return true;

    // Rebalance by swapping the root down to its rightful place
    int idx = 0;
    int kdx = idx+1;
    while( kdx <= sz )
    {
        int kdx_child1 = kdx*2;
        int kdx_child2 = kdx_child1+1;
        int kdx_swap;
        if( kdx_child2 <= sz )
            kdx_swap = heap[kdx_child1-1] > heap[kdx_child2-1] ?  kdx_child1 : kdx_child2;  // swap must promote the larger of the two children up
        else if( kdx_child1 <= sz ) 
            kdx_swap = kdx_child1;
        else
            break;
        int temp = heap[kdx_swap-1];
        if( x >= temp )
            break;
        heap[kdx_swap-1] = x;
        heap[kdx-1] = temp;
        kdx = kdx_swap;
    }
    return true;
}

void heap_play()
{
    std::vector<int> heap;
    heap_insert( heap, 17 );
    heap_insert( heap, 12 );
    heap_insert( heap, 170 );
    heap_insert( heap, 7 );
    heap_insert( heap, 68 );
    heap_insert( heap, 3 );
    heap_insert( heap, 172 );
    for( unsigned int i=0; i<heap.size(); i++ )
        printf( "%s%d", i==0?"[":" ", heap[i] );
    printf( "]\n" );
    heap.clear();
    heap_insert( heap, 7 );
    heap_insert( heap, 170 );
    heap_insert( heap, 172 );
    heap_insert( heap, 12 );
    heap_insert( heap, 3 );
    heap_insert( heap, 68 );
    heap_insert( heap, 17 );
    for( unsigned int i=0; i<heap.size(); i++ )
        printf( "%s%d", i==0?"[":" ", heap[i] );
    printf( "]\n" );
    for( int i=0; i<20; i++ )
    {
        int n = rand();
        printf( "Inserting %d into heap\n", n );
        heap_insert( heap, n );
    }
    heap_insert( heap, 17 );
    heap_insert( heap, 12 );
    heap_insert( heap, 170 );
    heap_insert( heap, 7 );
    heap_insert( heap, 68 );
    heap_insert( heap, 3 );
    heap_insert( heap, 172 );
    for( unsigned int i=0; i<heap.size(); i++ )
        printf( "%s%d", i==0?"[":" ", heap[i] );
    printf( "]\n" );
    for(;;)
    {
        int n;
        bool ok = heap_remove( heap, n );
        if( !ok )
            break;
        printf( "Remove %d from heap\n", n );
    }
}

void heap_sort( std::vector<int> &v )
{
    int sz = v.size();
    std::vector<int> heap;
    for( int i=0; i<sz; i++ )
        heap_insert( heap, v[i] );
    for( int i=sz-1; i>=0; i-- )
        heap_remove( heap, v[i] );
}

void test_heap_sort()
{
    std::vector<int> v;
#if 1
    for( int i=0; i<101; i++ )
    {
        int n = rand();
        v.push_back(n);
    }
#else
    v.push_back( 3 );
    v.push_back( 6 );
    v.push_back( 5 );
    v.push_back( 2 );
    v.push_back( 4 );
#endif
    std::vector<int> w;
    w = v;
    std::sort( w.begin(), w.end() );
    heap_sort( v );
    bool ok = (v==w);
    printf( "heap_sort: %s\n", ok?"PASS":"FAIL");
}

const int BENCH_SZ=100000;
const int BENCH_REPEAT=40;
void sort_speed_test()
{
    std::vector<int> v;
    printf( "Speed tests, sz=%d, loops=%d, version %d\n", BENCH_SZ, BENCH_REPEAT, BILL_OPTIMISE );
    for( int t=0; t<3; t++ )
    {
        switch( t )
        {
            case 0:
            {
                // Random
                printf( "Random\n" );
                for( int i=0; i<BENCH_SZ; i++ )
                {
                    int n = rand();
                    v.push_back(n);
                }
                break;
            }

            case 1:
            {
                // Increasing
                printf( "Increasing\n" );
                for( int i=0; i<BENCH_SZ; i++ )
                {
                    v.push_back(i);
                }
                break;
            }

            case 2:
            {
                // Decreasing
                printf( "Decreasing\n" );
                for( int i=0; i<BENCH_SZ; i++ )
                {
                    v.push_back(BENCH_SZ-i);
                }
                break;
            }

        }

        // Overhead
        std::vector<int> w1, w2, w3, w4;
        std::string empty;
        unsigned long n1 = GetTickCount();
        for( int i=0; i<BENCH_REPEAT; i++ )
        {
            w1=v;
            util::kill_unwanted_optimisation(&w1[0]);  // ensures w1=v not optimised out
        }
        unsigned long n2 = GetTickCount();
        unsigned long overhead = n2-n1;
        //printf( "Overhead: %lu milliseconds elapsed\n", overhead );

        // System
        printf( "System begin\n" );
        n1 = GetTickCount();
        for( int i=0; i<BENCH_REPEAT; i++ )
        {
            w1=v;
            std::sort( w1.begin(), w1.end() );
        }
        n2 = GetTickCount();
        printf( "System end: %lu milliseconds elapsed\n", n2-n1-overhead );

        // Merge
        printf( "Merge begin\n" );
        n1 = GetTickCount();
        for( int i=0; i<BENCH_REPEAT; i++ )
        {
            w2=v;
            merge_sort( w2 );
        }
        n2 = GetTickCount();
        printf( "Merge end: %lu milliseconds elapsed\n", n2-n1-overhead );

        // Quick
        printf( "Quick begin\n" );
        n1 = GetTickCount();
        for( int i=0; i<BENCH_REPEAT; i++ )
        {
            w3=v;
            quick_sort( w3 );
        }
        n2 = GetTickCount();
        printf( "Quick end: %lu milliseconds elapsed\n", n2-n1-overhead );

        // Heap
        printf( "Heap begin\n" );
        n1 = GetTickCount();
        for( int i=0; i<BENCH_REPEAT; i++ )
        {
            w4=v;
            heap_sort( w4 );
        }
        n2 = GetTickCount();
        printf( "Heap end: %lu milliseconds elapsed\n", n2-n1-overhead );

        // Check
        bool merge_ok = (w2==w1);
        bool quick_ok = (w3==w1);
        bool heap_ok  = (w4==w1);
        printf( "Merge: %s, Quick: %s, Heap: %s\n", merge_ok?"PASS":"FAIL", quick_ok?"PASS":"FAIL", heap_ok?"PASS":"FAIL" );
        printf("\n");
    }
}


int main( int argc, char *argv[] )
{
    std::string s1("House");
    std::size_t x1 = std::hash<std::string> ()(s1);
    printf( "x1=%u\n", x1 );
    std::string s2("H0use");
    std::size_t x2 = std::hash<std::string> ()(s2);
    printf( "x2=%u\n", x2 );
    //heap_play();
    //test_heap_sort();
    //test_merge_sort();
    //test_quick_sort();
    //sort_speed_test();
    //return 0;
    bool ok = map_test();
    if( !ok )
        std::cout << "Map test failed\n";        
    ok = shared_ptr_test();
    if( !ok )
        std::cout << "Shared ptr test failed\n";
    BinaryTree<std::string> dictionary;
    ok = BinaryTree_test(dictionary);
    if( !ok )
        std::cout << "BinaryTreeNode test failed\n";        
    void countdown( BinaryTree<std::string> &dict );
    countdown( dictionary );
    return 0;
}

bool map_test()
{
    bool ok = true;
    std::map<std::string,std::string> m;
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
    std::shared_ptr<int> p = std::make_shared<int>(3);
    ok = (*p == 3);
    if( ok )
    {
        std::shared_ptr<int> q;
        q = std::make_shared<int>(4);
        ok = (*q == 4);
    }
    return ok;
}

// Implement stub BinaryTree with using standard library
#if 0
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

#endif

void countdown_game( BinaryTree<std::string> &dict, std::string letters );
void countdown( BinaryTree<std::string> &dict )
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

void TestFixLater()
{
    std::cout << "Test passed\n";
    //countdown(dict);
}


int algo( BinaryTree<std::string> &dict,  BinaryTree<std::string> &solutions, std::string letters, std::string word_so_far, unsigned int best_so_far )
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

void countdown_game( BinaryTree<std::string> &dict, std::string letters )
{
    printf( "Letters are;\n%s\n", letters.c_str() );
    BinaryTree<std::string> solutions;
    algo( dict, solutions, letters, "", 0 );
    std::vector<std::string> keys = solutions.traverse_read();
    printf( "Solutions are;\n" );
    for( auto s: keys )
        printf( "%s\n", s.c_str() );
    printf( "\n" );
}

