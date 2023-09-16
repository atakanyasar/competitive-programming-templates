#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>

using namespace std;

class SuffixTree {

protected:
    friend struct TestSuffixTree;

    struct Node {
        unordered_map<char, Node*> edges;
        Node *suffix_link;
        Node *parent;
        int start;
        int depth;

        Node(int start, int depth, Node* parent) : start(start), depth(depth), parent(parent) {}

        bool exists(char c) {
            return edges.find(c) != edges.end();
        }

    };

private:

    Node* active_node;
    int active_length;

    Node* create_new_node(int start, int depth, Node* parent) {
        Node* new_node = new Node(start, depth, parent);
        all_nodes.push_back(new_node);
        if (depth == INT_MAX) {
            leaf_of_index[start] = new_node;
        }
        return new_node;
    }

    bool is_endpoint() {
        return active_node->depth == active_length;
    }

    char get_active_char() {
        if (is_endpoint()) {
            throw string("no active char");
        }
        return str[get_active_child_node()->start + active_length - 1];
    }

    char get_active_edge() {
        if (is_endpoint()) {
            throw string("no active edge");
        }
        return str[size - active_length + active_node->depth];
    }

    Node* get_active_child_node() {
        if (active_node->exists(get_active_edge())) {
            return active_node->edges[get_active_edge()];
        } else {
            return nullptr;
        }
    }

    void step_down_active_point() {
        while (!is_endpoint() && get_active_child_node() != nullptr && get_active_child_node()->depth < active_length) {
            active_node = get_active_child_node();
        }
    }

    void go_suffix_link() {
        active_length--;
        active_node = active_node->suffix_link;
    }

    Node* split_active_edge() {
        Node* new_node = create_new_node(get_active_child_node()->start, active_length - 1, active_node);
        new_node->edges[get_active_char()] = get_active_child_node();
        active_node->edges[get_active_edge()] = new_node;
        return new_node;
    }

    Node* iterate(char new_char) {
        Node* node = active_node;
        if (get_active_child_node() != nullptr && new_char == get_active_char()) {
            if (get_active_child_node()->depth == active_length) {
                active_node = get_active_child_node();
            }
        } else {
            if (active_node->exists(get_active_edge())) {
                node = split_active_edge();
            }
            node->edges[new_char] = create_new_node(size - active_length, INT_MAX, node);
            go_suffix_link();
            step_down_active_point();
            if (node != root) {
                node->suffix_link = iterate(new_char);
            }
        }
        return node;
    }

public:

    int size;
    string str;
    Node* root;
    vector<Node*> all_nodes = {};
    vector<Node*> leaf_of_index = {};

    SuffixTree() : size(0), active_length(0) {
        root = create_new_node(0, 0, nullptr);
        root->suffix_link = root;
        active_node = root;
    }

    SuffixTree(string s) : SuffixTree() {
        s += "$";
        for (int i = 0; i < s.size(); i++) {
            add_char(s[i]);
        }
    }

    ~SuffixTree() {
        for (auto node : all_nodes) {
            delete node;
        }
    }

    void add_char(char c) {
        leaf_of_index.push_back(nullptr);
        str += c;
        size++;
        active_length++;
        iterate(c);
    }

    bool is_substring(string& s) {
        Node* node = root;
        int i = 0;
        while (i < s.size()) {
            if (!node->exists(s[i])) {
                return false;
            }
            Node* next_node = node->edges[s[i]];
            while (i < s.size() && i < next_node->depth) {
                if (str[next_node->start + i] != s[i]) {
                    return false;
                }
                i++;
            }
            node = next_node;
        }
        return true;
    }

};

struct TestSuffixTree {
    
    TestSuffixTree() {
        run_all();
    }

    void run_all() {
        test1();
        test2();
        test3();
        test4();
        test_string("a");
        test_string("ab");
        test_string("aba");
        test_string("abab");
        test_string("ababb");
        test_string("abcabdabb");
        test_string("aaaaaaaaaaaaaa");
        test_string("abcdeabcdfabdb");
        test_string("ababababbababaababababababababababababbababababababaabababaababababababaabbababa");
        test_string("aabcsdcasbchasbcjhabshcsjcnsajvbkjasdvnskjbvdskjnfsdkjbds");
        test_string("abacbacbabcbcacbabcbacbabcabcacadbcbacbabcbabcabbcabcbacbabbabcabcbdabcbabcabcbacbacbabcbacbac");
        test_string("aababababababacabbacbacbabcbabbababbacbabbabababababbbababbabcababbacbacbabacbabaababababa");
    }

    void test_string(string s) {
        s += "$";
        
        SuffixTree suffix_tree;
        for(int i = 0; i < s.size(); i++) {
            suffix_tree.add_char(s[i]);
            for (int j = 0; j < i; j++) {
                string suffix = s.substr(j, i - j + 1);
                SuffixTree::Node* node = suffix_tree.root;
                while (node->depth < suffix.size()) {
                    assert(node->exists(suffix[node->depth]));
                    node = node->edges[suffix[node->depth]];
                }
                if (i == s.size() - 1){
                    assert(suffix_tree.leaf_of_index[j] == node);
                }
            }
            
        }

        for (auto node : suffix_tree.all_nodes) {
            if (node == suffix_tree.root || node->depth == INT_MAX) continue;
            string suffix = s.substr(node->start, node->depth);
            string suffix_link = s.substr(node->suffix_link->start, node->suffix_link->depth);
            assert(suffix_link == suffix.substr(1));
        }


        cerr << "\033[1;32m" << "test_string(" << "\033[1;33m\"" << s << "\"\033[1;32m"<< ") passed" << "\033[0m" << endl;
    }

    void test1() {
        SuffixTree suffix_tree("a");
        assert(suffix_tree.root->exists('a'));
        assert(suffix_tree.root->exists('$'));

        assert(suffix_tree.root->start == 0);
        assert(suffix_tree.root->edges['a']->start == 0);
        assert(suffix_tree.root->edges['$']->start == 1);

        assert(suffix_tree.root->edges['a']->depth == INT_MAX);
        assert(suffix_tree.root->edges['$']->depth == INT_MAX);

        cerr << "\033[1;32m" << "test1 passed" << "\033[0m" << endl; 
    }

    void test2() {
        SuffixTree suffix_tree("ab");
        assert(suffix_tree.root->exists('a'));
        assert(suffix_tree.root->exists('b'));
        assert(suffix_tree.root->exists('$'));

        assert(suffix_tree.root->start == 0);
        assert(suffix_tree.root->edges['a']->start == 0);
        assert(suffix_tree.root->edges['b']->start == 1);
        assert(suffix_tree.root->edges['$']->start == 2);

        assert(suffix_tree.root->edges['a']->depth == INT_MAX);
        assert(suffix_tree.root->edges['b']->depth == INT_MAX);
        assert(suffix_tree.root->edges['$']->depth == INT_MAX);

        cerr << "\033[1;32m" << "test2 passed" << "\033[0m" << endl; 
    }

    void test3() {
        SuffixTree suffix_tree("aba");
        assert(suffix_tree.root->exists('a'));
        assert(suffix_tree.root->exists('b'));
        assert(suffix_tree.root->exists('$'));
        assert(suffix_tree.root->edges['a']->exists('b'));
        assert(suffix_tree.root->edges['a']->exists('$'));

        assert(suffix_tree.root->start == 0);
        assert(suffix_tree.root->edges['a']->start == 0);
        assert(suffix_tree.root->edges['b']->start == 1);
        assert(suffix_tree.root->edges['$']->start == 3);
        assert(suffix_tree.root->edges['a']->edges['b']->start == 0);
        assert(suffix_tree.root->edges['a']->edges['$']->start == 2);

        assert(suffix_tree.root->edges['a']->depth == 1);
        assert(suffix_tree.root->edges['b']->depth == INT_MAX);
        assert(suffix_tree.root->edges['$']->depth == INT_MAX);
        assert(suffix_tree.root->edges['a']->edges['b']->depth == INT_MAX);
        assert(suffix_tree.root->edges['a']->edges['$']->depth == INT_MAX);

        cerr << "\033[1;32m" << "test3 passed" << "\033[0m" << endl; 
    }

    void test4() {
        SuffixTree suffix_tree("abab");
        assert(suffix_tree.root->exists('a'));
        assert(suffix_tree.root->exists('b'));
        assert(suffix_tree.root->exists('$'));
        assert(suffix_tree.root->edges['a']->exists('a'));
        assert(suffix_tree.root->edges['a']->exists('$'));
        assert(suffix_tree.root->edges['b']->exists('a'));
        assert(suffix_tree.root->edges['b']->exists('$'));

        assert(suffix_tree.root->start == 0);
        assert(suffix_tree.root->edges['a']->start == 0);
        assert(suffix_tree.root->edges['b']->start == 1);
        assert(suffix_tree.root->edges['$']->start == 4);
        assert(suffix_tree.root->edges['a']->edges['a']->start == 0);
        assert(suffix_tree.root->edges['a']->edges['$']->start == 2);
        assert(suffix_tree.root->edges['b']->edges['a']->start == 1);
        assert(suffix_tree.root->edges['b']->edges['$']->start == 3);

        assert(suffix_tree.root->edges['a']->depth == 2);
        assert(suffix_tree.root->edges['b']->depth == 1);
        assert(suffix_tree.root->edges['$']->depth == INT_MAX);
        assert(suffix_tree.root->edges['a']->edges['a']->depth == INT_MAX);
        assert(suffix_tree.root->edges['a']->edges['$']->depth == INT_MAX);
        assert(suffix_tree.root->edges['b']->edges['a']->depth == INT_MAX);
        assert(suffix_tree.root->edges['b']->edges['$']->depth == INT_MAX);

        cerr << "\033[1;32m" << "test4 passed" << "\033[0m" << endl; 

    }

    
    static void print(SuffixTree::Node* node, int depth = 0) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < depth; i++) {
            cerr << "  ";
        }
        cerr << "node: " << node << endl; 
        for (int i = 0; i < depth; i++) {
            cerr << "  ";
        }
        cerr << "start: " << node->start << endl;
        for (int i = 0; i < depth; i++) {
            cerr << "  ";
        }
        cerr << "depth: " << node->depth << endl;
        for (int i = 0; i < depth; i++) {
            cerr << "  ";
        }
        cerr << "link: " << node->suffix_link << endl;
        for (auto it: node->edges) {
            for (int i = 0; i <= depth; i++) {
                cerr << "  ";
            }
            cerr << "child: " << it.first << " {"<< endl;
            print(it.second, depth + 2);
            for (int i = 0; i <= depth; i++) {
                cerr << "  ";
            }
            cerr << "}" << endl;
        }
    }

    static void print(SuffixTree& suffix_tree) {
        cerr << "--------------------------" << endl;
        cerr << "-----------" << suffix_tree.size << "---------------" << endl;
        cerr << "--------------------------" << endl;
        
        print(suffix_tree.root);
        cerr << "active_node: " << suffix_tree.active_node << endl;
        cerr << "active_length: " << suffix_tree.active_length << endl;
        cerr << "active_node->start: " << suffix_tree.active_node->start << endl;
        cerr << "active_node->depth: " << suffix_tree.active_node->depth << endl;
        try {
            cerr << "active_edge: " << suffix_tree.get_active_edge() << endl;
        } catch(string e) {
            cerr << e << endl;
        }
        try {
            cerr << "active_char: " << suffix_tree.get_active_char() << endl;
        } catch(string e) {
            cerr << e << endl;
        }
        cerr << "--------------------------" << endl;
    }


} test_suffix_tree;

#endif