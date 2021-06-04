#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>

struct TaskInfo {
    int real;
    int archived;
    int additional;
    static const int BYTE_SIZE = 8;

    TaskInfo();
    TaskInfo(int real_, int archived_, int additional_);
};

class TreeNode {
public:
    TreeNode();
    ~TreeNode();
    TreeNode(int count, char value);
    TreeNode(TreeNode* left, TreeNode*right);
    bool is_list() const;
    int get_count() const;
    char get_value() const;
    TreeNode* get_left() const;
    TreeNode* get_right() const;
private:
    bool is_list_;
    char value_;
    int count_;
    TreeNode *left, *right;
};

class HuffmanTree {
public:
    HuffmanTree();
    HuffmanTree(TreeNode* root);
    HuffmanTree(std::vector<std::pair<int, char> > &v);
    ~HuffmanTree();
    TreeNode* get_current() const;
    TreeNode* get_root() const;
    void add_byte(char byte);
    void reset();
    void clean_tree(TreeNode *v);
    void get_codes(TreeNode* v, std::string &cur, std::map<char, std::string> &res) const;
private:
    TreeNode *root_;
    TreeNode *cur_;
};


class HuffmanArchiver {
public:
    HuffmanArchiver(int mode_, std::string input_, std::string output_);
    ~HuffmanArchiver();
    TaskInfo print_archived();
    TaskInfo read_archived();
private:
    int mode = 0;
    std::string input;
    std::string output;
    HuffmanTree tree;
};