#include "stdafx.h"
#include <gtest\gtest.h>

TEST(test_case_name, test_name) {
    ASSERT_EQ(1, 0) << "1 is not equal 0";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    const int res = RUN_ALL_TESTS();
    getchar();
    return res;
}

//int _tmain(int argc, _TCHAR* argv[]){
//	return 0;
//}

