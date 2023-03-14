#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <chrono>
using namespace std;

struct Red_Black_Node
{
  Red_Black_Node *father;
  Red_Black_Node *left_son;
  Red_Black_Node *right_son;
  int number;
  char color;
};

class Tree
{
public:
  Red_Black_Node sentinel_node;
  Red_Black_Node *head;

  int size;
  int number;

  void add_element(int number);
  void delete_element(int number); //
  void find_element(int number);
  void print_tree(string sp, string sn, Red_Black_Node *p);
  void tree_menu();
  void rotation_to_the_left(Red_Black_Node *node);
  void rotation_to_the_right(Red_Black_Node *node);
  Red_Black_Node *next_node(Red_Black_Node *p);
  Red_Black_Node *minimum(Red_Black_Node *p);
  void rebuilt_structure(Red_Black_Node *node);
  void delete_root();
  void measure_time();
};