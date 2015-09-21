#include <iostream>
#include "cpptest.h"
#include "include/hui.h"

class Tests : public Test::Suite {
    public:
        Tests(void) {
            TEST_ADD(Tests::testone);
        }

    protected:
        void setup(void) {
            //
        }

        void tear_down(void) {
            //
        }

    private:
        void testone(void) {
            TEST_ASSERT(1 + 1 == 2);
        }
};

int main(int argc, char **argv) {
    std::cout << "Testing..." << std::endl;

    Test::TextOutput output(Test::TextOutput::Verbose);
    Tests tests;

    return tests.run(output) ? EXIT_SUCCESS : EXIT_FAILURE;
}
