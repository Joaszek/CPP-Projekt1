#include <stdlib.h>
#include <string>

using namespace std;

struct RBTNode
    {
      RBTNode * father;
      RBTNode * left_son;
      RBTNode * right_son;
      int number;
      char color;
    };

class Tree{
public:
    

    RBTNode S;
    RBTNode *head;

    int size;
    int number;

    void add_element(int number); 
    void delete_element(int number);//
    void find_element(int number);
    void print_tree( string sp, string sn, RBTNode * p); //
    void tree_menu();//
    void rotation_to_the_left(RBTNode * node);//
    void rotation_to_the_right(RBTNode * node );//
    RBTNode * next(RBTNode *p);//
    RBTNode * minimum(RBTNode *p);
    void rebuilt_structure(RBTNode *node);
    void delete_root();
    void measure_time();

};

