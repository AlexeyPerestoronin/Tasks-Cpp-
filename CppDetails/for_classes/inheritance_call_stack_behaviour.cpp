#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

#include <format>
#include <ostream>
#include <sstream>

namespace {

std::stringstream output;

TEST(Inheritance, Test1) {

    struct G1_1
    {
        int value;

        G1_1(int val)
            : value{val} {
            output << std::format("G1_1::G1_1({})", value) << std::endl;
        }

        ~G1_1() {
            output << std::format("~G1_1::G1_1({})", value) << std::endl;
        }
    };

    struct G2_1 : G1_1
    {
        int value;

        G2_1(int val)
            : G1_1(11)
            , value{val} {
            output << std::format("G2_1::G2_1({})", value) << std::endl;
        }

        ~G2_1() {
            output << std::format("~G2_1::G2_1({})", value) << std::endl;
        }
    };

    struct G2_2 : G1_1
    {
        int value;

        G2_2(int val)
            : G1_1(12)
            , value{val} {
            output << std::format("G2_2::G2_2({})", value) << std::endl;
        }

        ~G2_2() {
            output << std::format("~G2_2::G2_2({})", value) << std::endl;
        }
    };

    struct G3_1 : G2_1, G2_2
    {
        int value;

        G3_1(int val)
            : G2_1(21)
            , G2_2{22}
            , value{val} {
            output << std::format("G3_1::G3_1({})", value) << std::endl;
        }

        ~G3_1() {
            output << std::format("~G3_1::G3_1({})", value) << std::endl;
        }
    };

    G3_1(31);
    ASSERT_EQ(output.str(),
              "G1_1::G1_1(11)\n"
              "G2_1::G2_1(21)\n"
              "G1_1::G1_1(12)\n"
              "G2_2::G2_2(22)\n"
              "G3_1::G3_1(31)\n"
              "~G3_1::G3_1(31)\n"
              "~G2_2::G2_2(22)\n"
              "~G1_1::G1_1(12)\n"
              "~G2_1::G2_1(21)\n"
              "~G1_1::G1_1(11)\n");
}

TEST(VirtualInheritance, Test1) {

    struct G1_1
    {
        int value;

        G1_1(int val)
            : value{val} {
            output << std::format("G1_1::G1_1({})", value) << std::endl;
        }

        ~G1_1() {
            output << std::format("~G1_1::G1_1({})", value) << std::endl;
        }
    };

    struct G2_1 : virtual G1_1
    {
        int value;

        G2_1(int val)
            : G1_1(1) // 1
            , value{val} {
            output << std::format("G2_1::G2_1({})", value) << std::endl;
        }

        ~G2_1() {
            output << std::format("~G2_1::G2_1({})", value) << std::endl;
        }
    };

    struct G2_2 : virtual G1_1
    {
        int value;

        G2_2(int val)
            : G1_1(2) // 2
            , value{val} {
            output << std::format("G2_2::G2_2({})", value) << std::endl;
        }

        ~G2_2() {
            output << std::format("~G2_2::G2_2({})", value) << std::endl;
        }
    };

    struct G3_1 : G2_1, G2_2
    {
        int value;

        G3_1(int val)
            : G1_1(11) // 1
            , G2_1(21) // 1
            , G2_2{22} // 2
            , value{val} {
            output << std::format("G3_1::G3_1({})", value) << std::endl;
        }

        ~G3_1() {
            output << std::format("~G3_1::G3_1({})", value) << std::endl;
        }
    };

    G3_1(31);
    ASSERT_EQ(output.str(),
              "G1_1::G1_1(11)\n"
              "G2_1::G2_1(21)\n"
              "G2_2::G2_2(22)\n"
              "G3_1::G3_1(31)\n"
              "~G3_1::G3_1(31)\n"
              "~G2_2::G2_2(22)\n"
              "~G2_1::G2_1(21)\n"
              "~G1_1::G1_1(11)\n");
}
} // namespace
