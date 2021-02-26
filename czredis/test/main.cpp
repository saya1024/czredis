#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <thread>
#include <atomic>
#include "../include/czredis.h"

using namespace std;
using namespace chrono;
using namespace czredis;

void sleep(int millis)
{
    chrono::milliseconds dura(millis);
    this_thread::sleep_for(dura);
}

template<typename F, typename ...OBJECT>
void testTime(F func, OBJECT ...args)
{
    auto start = system_clock::now();
    func(args...);
    auto stop = system_clock::now();
    cout << duration_cast<milliseconds>(stop - start).count() << " ms" << endl;
}


void assert_equal(delay<string>& d, cref_string s)
{
    assert(d.get() == s);
}
void assert_equal(delay<reply>& d, cref_string s)
{
    assert(d.get().as_string() == s);
}

void testHost()
{
    redis rds;

    try
    {
        rds.connect();
        rds.auth("123456");
        cout << rds.call_command("get", { "name" }, true).as_string() << endl;
        auto p = rds.get_pipline();
        p.multi();
        auto v = p.set("name", "zhang");
        auto name1 =p.get("name");
        auto v2 = p.set("name", "wang");
        auto name2 = p.get("name");
        auto r = p.exec();
        p.multi();
        auto name3 = p.get("name");
        r = p.exec();
        p.sync();
        assert_equal(v, "OK");
        assert_equal(name1, "zhang");
        assert_equal(name2, "wang");
        assert_equal(name3, "wang");
        //cout << name.get().as_string() << name2.get().as_string() << endl;
        rds.disconnect();
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
}

int main()
{
#ifdef _WIN32
#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    testHost();
    system("pause");
    return 0;
}
