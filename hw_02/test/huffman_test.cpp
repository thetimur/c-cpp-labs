#define DOCTEST_CONFIG_IMPLEMENT
#include "autotest.h"
#include "huffman.h"
#include <algorithm>

TEST_CASE("Test huffman nodes") {
    TreeNode *l = new TreeNode(10, 'a');
    TreeNode *r = new TreeNode(20, 'b');

    TreeNode *uq = new TreeNode(l, r);

    SUBCASE("Test node created by TreeNode(val, ch)/TreeNode(l, r) constructors") {

        SUBCASE("Test get_count()") {
            CHECK(uq->get_count() == 30);
            CHECK(l->get_count() == 10);
            CHECK(r->get_count() == 20);
        }

        SUBCASE("Test get_value()") {
            CHECK(l->get_value() == 'a');
            CHECK(r->get_value() == 'b');
            CHECK(uq->get_value() == 'b');
        }

        SUBCASE("Test is_list()") {
            CHECK(l->is_list() == true);
            CHECK(r->is_list() == true);
            CHECK(uq->is_list() == false);
        }

        SUBCASE("Test get_left/right()") {
            CHECK(l->get_left() == nullptr);
            CHECK(l->get_right() == nullptr);

            CHECK(r->get_left() == nullptr);
            CHECK(r->get_right() == nullptr);

            CHECK(uq->get_left() == l);
            CHECK(uq->get_right() == r);
        }
    }
}


TEST_CASE("Test huffman tree") {

    SUBCASE("Test small tree") {
        TreeNode *root = new TreeNode(10, 'a');

        HuffmanTree small_tree(root);

        CHECK(small_tree.get_current() == root);
        CHECK(small_tree.get_current()->get_value() == 'a');
        CHECK(small_tree.get_current()->is_list() == true);
    }

    SUBCASE("Test built tree") {

        SUBCASE("Test HuffmanTree(data)") {
            std::vector<std::pair<int, char> > v;
            v.push_back(std::make_pair(3, 'b'));
            v.push_back(std::make_pair(4, 'e'));
            v.push_back(std::make_pair(2, 'p'));
            v.push_back(std::make_pair(2, ' '));
            v.push_back(std::make_pair(2, 'o'));
            v.push_back(std::make_pair(1, 'r'));
            v.push_back(std::make_pair(1, '!'));

            HuffmanTree tree(v);

            CHECK(tree.get_current() == tree.get_root());
            CHECK(tree.get_current()->get_count() == 15);
            CHECK(tree.get_current()->is_list() == false);
           
            SUBCASE("Test add_byte(byte)") {
                tree.add_byte('0');
                CHECK(tree.get_current() == tree.get_root()->get_left());

                SUBCASE("Test reset()") {
                    tree.reset();
                    CHECK(tree.get_current() == tree.get_root());   
                }

                tree.add_byte('1');
                CHECK(tree.get_current() == tree.get_root()->get_right());
                tree.reset();
            }


            SUBCASE("Test get_codes(v, s, codes)") {
                std::map<char, std::string> codes;
                std::string tmp = "";

                tree.get_codes(tree.get_current(), tmp, codes);
                CHECK((int)codes['b'].size() == 2);
                CHECK((int)codes['e'].size() == 2);
                CHECK((int)codes['!'].size() == 4);
            }
        }
    }
}

// Generated real-case tests
//
//  This part generates real-case files (or gets it from /resourses 
//    folder) and checks that results are equal and contets in both files is the same.
//

#define DOCTEST_VALUE_PARAMETERIZED_DATA(names)                                  \
    std::for_each(names.begin(), names.end(), [&](const auto& in) {           \
        DOCTEST_SUBCASE((std::string(#names ": \'") +                                     \
                        in + "\'").c_str()) { test_real(in); }  \
    });

void test_real(std::string prefix) {

    TaskInfo result;
    SUBCASE("Check code on") {
        std::string text_in = "test/resourses/" + prefix + ".txt";
        std::string text_out = "test/resourses/" + prefix + ".bin";
        std::cerr << text_in << std::endl;

        HuffmanArchiver arc = HuffmanArchiver(1, text_in, text_out);

        result = arc.print_archived();
    }

    SUBCASE("Check decode") {
        std::string text_in = "test/resourses/" + prefix + ".bin";
        std::string text_out = "test/resourses/out_" + prefix + ".txt";
        std::cerr << text_in << std::endl;

        HuffmanArchiver arc = HuffmanArchiver(2, text_in, text_out);

        auto out_result = arc.read_archived();

        CHECK(out_result.real == result.real);
        CHECK(out_result.archived == result.archived);
        CHECK(out_result.additional == result.additional);
    }

    SUBCASE("Test that files has same content") {
        std::ifstream before_in("test/resourses/" + prefix + ".txt", std::ios::binary | std::ios::ate);
        std::ifstream::pos_type pos_before = before_in.tellg();

        std::vector<char> data_before(pos_before);

        before_in.seekg(0, std::ios::beg);
        before_in.read(&data_before[0], pos_before);
        std::ifstream after_out("test/resourses/out_" + prefix + ".txt", std::ios::binary | std::ios::ate);
        std::ifstream::pos_type pos_after = after_out.tellg();

        std::vector<char> data_after(pos_after);

        after_out.seekg(0, std::ios::beg);
        after_out.read(&data_after[0], pos_after);

        CHECK(data_before == data_after);
    }
}

TEST_CASE("Checking real cases") {

    std::vector<std::string> names = {"lots_of_a", "one_a", "simple_data", "random_data", "empty", "one_million_symbol"};
    
    DOCTEST_VALUE_PARAMETERIZED_DATA(names);
}

//
//
// Useless main part copied from DOCTEST tutorial
//
//

int main(int argc, char** argv) {
	doctest::Context context;
    std::string text_in = "test/resourses/one_million_symbol.txt";

    std::ofstream prepare(text_in, std::ios::binary);

    for (int i = 0; i < 1e6; i++) {
        std::vector<char> tmp = {'a', 'b', 'c', 'd', 'e', 'f'};
        int c = rand() % 6;
        prepare.write((char*)&tmp[c], sizeof(char));
    }

    prepare.close();


	 // defaults
    context.setOption("order-by", "name");            // sort the test cases by their name

    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

    int res = context.run(); // run

    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests
    
    int client_stuff_return_code = 0;
    // your program - if the testing framework is integrated in your production code
    
    return res + client_stuff_return_code; // the result from doctest is propagated here as well
}