#include "stdafx.h"

#include"../TextCore/Main.h"

using std::string;
using std::cout;


TEST(Core, getFile) {
    ASSERT_EQ(0, 0);// << "getFile wrong";
}

int _tmain(int argc, _TCHAR* argv[]){
    std::locale::global(std::locale(""));
    setlocale(LC_ALL, "Russian");
    ::testing::InitGoogleTest(&argc, argv);
    const int res = RUN_ALL_TESTS();
    if (res != 0)
        return res;

    if (argc < 2) {
        std::cerr << "WARNING: Missing arg";
        return -1;
    }
    
    boost::timer::cpu_timer bench_timer;
    bench_timer.stop();
    bench_timer.start( );
    cout << "\nBuild ...";
    getFile(argv[1]);
    //build(input_file_stream);
    bench_timer.stop( );
    cout << "\b\b\b\t" << format(bench_timer.elapsed( )) << "";

    view_table();

    getchar();
    return 0;
}

