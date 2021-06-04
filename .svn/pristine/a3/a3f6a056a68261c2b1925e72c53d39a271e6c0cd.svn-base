#include "huffman.h"

struct CustomTreeNodeCompare {
    bool operator() (const TreeNode* l, const TreeNode* r) {
        return l->get_count() > r->get_count() || 
            (l->get_count() == r->get_count() && l->get_value() < r->get_value());
    }
};

TaskInfo::TaskInfo(int real_, int archived_, int additional_) {
    real = real_;
    archived = archived_;
    additional = additional_;
}

TaskInfo::TaskInfo() {}

bool TreeNode::is_list() const {
	return is_list_;
}

int TreeNode::get_count() const {
	return count_;
}

char TreeNode::get_value() const {
	return value_;
}

TreeNode* TreeNode::get_left() const {
	return left;
}

TreeNode* TreeNode::get_right() const {
	return right;
}

TreeNode* HuffmanTree::get_current() const {
	return cur_;
}

TreeNode* HuffmanTree::get_root() const {
    return root_;
}

TreeNode::~TreeNode() {}

TreeNode::TreeNode(int count, char value) : is_list_(true), value_(value), count_(count), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(TreeNode* left, TreeNode* right) : is_list_(false), left(left), right(right) {
    count_ = 0;
    if (left != nullptr) {
        count_ += left->get_count();
    }
    if (right != nullptr) {
        count_ += right->get_count();
    }

    value_ = 0;
    if (left != nullptr) {
        value_ = std::max(value_, left->get_value());
    }
    if (right != nullptr) {
        value_ = std::max(value_, right->get_value());
    }
}

HuffmanTree::HuffmanTree() : root_(nullptr), cur_(nullptr) {}

HuffmanTree::HuffmanTree(TreeNode *root) : root_(root), cur_(root) {}

void HuffmanTree::clean_tree(TreeNode *v) {
    if (v == nullptr) {
        return;
    }

    if (v->get_left() != nullptr) {
        clean_tree(v->get_left());
        delete v->get_left();
    }
    if (v->get_right() != nullptr) {
        clean_tree(v->get_right());
        delete v->get_right();
    }
}

HuffmanTree::~HuffmanTree() {}

HuffmanTree::HuffmanTree(std::vector<std::pair<int, char> > &v) {
    if (!v.size()) {
        return;
    }

    if (v.size() == 1) {
        root_ = new TreeNode(new TreeNode(v[0].first, v[0].second), nullptr);
        cur_ = root_;
        return;
    }
	std::priority_queue<TreeNode*, std::vector<TreeNode*>, CustomTreeNodeCompare> q;

	for (std::size_t i = 0; i < v.size(); i++) {
        q.push(new TreeNode(v[i].first, v[i].second));
	}
	while (q.size() > 1) {
		TreeNode* left = q.top();
		q.pop();
		TreeNode* right = q.top();
		q.pop();

		TreeNode* nw = new TreeNode(left, right);
		q.push(nw);
	}

	root_ = cur_ = q.top();
    q.pop();
}

void HuffmanTree::get_codes(TreeNode* v, std::string &cur, std::map<char, std::string> &res) const {
	if (v == nullptr) {
		return;
	}
	cur.push_back('0');
	get_codes(v->get_left(), cur, res);
	cur.back() = '1';
	get_codes(v->get_right(), cur, res);
	cur.pop_back();
	if (v->is_list()) {
		res[v->get_value()] = cur;
	}
}


void HuffmanTree::add_byte(char c) {
    if (c == '0') {
        cur_ = cur_->get_left();
        return;
    }
    cur_ = cur_->get_right();
}

void HuffmanTree::reset() {
    cur_ = root_;
}

HuffmanArchiver::HuffmanArchiver(int mode_, std::string input_, std::string output_) : mode(mode), input(input_), output(output_) {}

HuffmanArchiver::~HuffmanArchiver() {
    tree.clean_tree(tree.get_root());
    delete tree.get_root();
}

TaskInfo HuffmanArchiver::print_archived() {
    std::ifstream fin(input, std::ios::binary | std::ios::ate);
    std::ofstream fout(output, std::ios::binary);
    std::ifstream::pos_type pos = fin.tellg();
	std::map<char, std::string> codes;
    std::string tmp = "";

    if (!pos) {
        return TaskInfo(0, 0, 0);
    }

    std::vector<char> data(pos);

    fin.seekg(0, std::ios::beg);
    fin.read(&data[0], pos);

    std::map<char, int> table;

    for (auto v : data) {
        table[v]++;
    }

    std::vector<std::pair<int, char> > res;

    for (auto c : table) {
        res.push_back(std::make_pair(c.second, c.first));
    }

    tree = HuffmanTree(res);

    tree.get_codes(tree.get_current(), tmp, codes);

    int size = (int)res.size();

    fout.write((char*)&size, sizeof(int));

    for (auto c : table) {
    	fout.write((char*)&(c.first), sizeof(char));
    	fout.write((char*)&(c.second), sizeof(int));
    }

    std::string result = "";
    for (auto v : data) {
        result += codes[v];
    }
    int bits = result.size();
    fout.write((char*)&bits, sizeof(int));
    while (result.size() % TaskInfo::BYTE_SIZE != 0) {
    	result.push_back(0);
    }

    for (int i = 0; i < (int)result.size(); i += TaskInfo::BYTE_SIZE) {
    	char cur = 0;
    	for (int bit = 0; bit < TaskInfo::BYTE_SIZE; bit++) {
    		if (result[i + bit] == '1') {
    			cur |= (1 << bit);
    		}
    	}
    	fout.write((char*)&cur, sizeof(char));
    }
    fout.close();
    return TaskInfo(data.size(),
        result.size() / TaskInfo::BYTE_SIZE,
        table.size() * 5 + TaskInfo::BYTE_SIZE);
}

TaskInfo HuffmanArchiver::read_archived() {
    std::ifstream fin(input, std::ios::binary);
    std::ofstream fout(output, std::ios::binary);

    if (fin.peek() == std::ifstream::traits_type::eof()) {
        return TaskInfo(0, 0, 0);
    }

    int size = 0;
    fin.read((char*)&size, sizeof(int));

    std::vector<std::pair<int, char> > table;

    for (int i = 0; i < size; i++) {
        std::pair<int, char> c;
        fin.read((char*)&(c.second), sizeof(char));
        fin.read((char*)&(c.first), sizeof(int));
        table.push_back(c);
    }

    tree = HuffmanTree(table);

    std::string result = "";
    int bits = 0;
    fin.read((char*)&bits, sizeof(int));
    for (int i = 0; i < (bits + TaskInfo::BYTE_SIZE - 1) / TaskInfo::BYTE_SIZE; i++) {
        char cur = 0;
        fin.read((char*)&(cur), sizeof(char));

        for (int j = 0; j < TaskInfo::BYTE_SIZE; j++) {
            int index = i * TaskInfo::BYTE_SIZE + j;
            if (index < bits) {
                if (cur & (1 << j)) {
                    result.push_back('1');
                } else {
                    result.push_back('0');
                }
            }
        }
    }

    int byte_counter = 0;
    for (int i = 0; i < (int)result.size(); i++) {
        tree.add_byte(result[i]);
        if (tree.get_current()->is_list()) {
            char val = tree.get_current()->get_value();
            fout.write((char*)&val, sizeof(char));
            byte_counter++;
            tree.reset();
        }
    }

    return TaskInfo(byte_counter, 
        (result.size() + TaskInfo::BYTE_SIZE - 1) / TaskInfo::BYTE_SIZE, 
        table.size() * 5 + TaskInfo::BYTE_SIZE);
}