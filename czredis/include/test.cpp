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
#include "czredis.h"

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

//static void testRedis()
//{
//    try
//    {
//        RedisObject redis;
//        redis.Connect("127.0.0.1", 6379, 1000);
//        assert(redis.AUTH("12345678"));
//        assert(redis.SELECT(1));
//        assert(redis.PING());
//
//        redis.DEL({ "name", "age", "user" });
//        //test String
//        assert(redis.SET("name", "zhou"));
//        assert(redis.GETSET("name", "wang") == "zhou");
//        assert(redis.GET("name") == "wang");
//        assert(!redis.SETNX("name", "zhang"));
//        assert(redis.SETNX("age", "18"));
//        assert(!redis.SETNX("age", "20"));
//        assert(redis.INCR("age") == 19);
//        assert(redis.INCRBY("age", 2) == 21);
//        assert(redis.DECR("age") == 20);
//        assert(redis.DECRBY("age", 2) == 18);
//        assert(redis.SETEX("age", 1, "20"));
//        assert(redis.GET("age") == "20");
//        sleep(1100);
//        assert(redis.GET("age").IsNull());
//        assert(redis.EXPIRE("name", 1));
//        assert(redis.EXISTS("name"));
//        sleep(1100);
//        assert(!redis.EXISTS("name"));
//
//        cout << "test String success" << endl;
//
//        assert(redis.HSET("user", "name", "zhao"));
//        assert(!redis.HSET("user", "name", "zhang"));
//        assert(redis.HSETNX("user", "age", "18"));
//        assert(!redis.HSETNX("user", "age", "20"));
//        auto hash = StringMap();
//        hash["name"] = "zhou";
//        hash["age"] = "20";
//        assert(redis.HMSET("user", hash));
//        auto rp = redis.HMGET("user", { "name", "age" });
//        assert(rp[0] == "zhou");
//        assert(rp[1] == "20");
//        assert(redis.HINCRBY("user", "age", -2) == 18);
//        assert(redis.HGET("user", "name") == "zhou");
//        hash = redis.HGETALL("user");
//        assert(hash["name"] == "zhou" && hash["age"] == "18");
//        assert(redis.HEXISTS("user", "name"));
//        assert(redis.HDEL("user", { "name", "age" }) == 2);
//        assert(redis.HGET("user", "name").IsNull());
//        assert(redis.HSET("user", "name", "zhang"));
//        assert(redis.EXPIREAT("user", time(nullptr) + 1));
//        sleep(1100);
//        assert(!redis.EXISTS("user"));
//
//        cout << "test Hash and Key success" << endl;
//
//        StringArray arr =
//        {
//            "set name zhang",
//            "set age 22",
//            "get name",
//            "get age",
//            "get user"
//        };
//        auto replys = redis.Pipline(arr);
//        assert(replys[0].ToString() == "OK" && replys[1].ToString() == "OK");
//        assert(replys[2].ToString() == "zhang" && replys[3].ToString() == "22" && replys[4].ToString().IsNull());
//        cout << "test Pipline success" << endl;
//    }
//    catch (exception &e)
//    {
//        cout << e.what() << endl;
//    }
//}
//
//
static redis_pool *pool = nullptr;

static void threadFunc1(int num)
{
    try
    {
        //Redis redis("47.100.250.142", 6379);
        //redis.Connect();
        for (int i = 0; i < 100; i++)
        {
            auto redis = pool->get_redis();
            //redis.SendCommand({ "SET", "name", "zyc" });
        }
    }
    catch (exception &e)
    {
        printf("thread %d err: %s\n", num, e.what());
    }
    //printf("thread %d end\n", num);
}
//void testRedisPool()
//{
//    redis_pool_config config;
//    config.max_size = 10000;
//    pool = new redis_pool("47.100.250.142", 6379, config);
//
//    const int threadMax = 100;
//    thread tarr[threadMax];
//    auto start = system_clock::now();
//    for (int i = 0; i < threadMax; i++)
//    {
//        tarr[i] = thread(threadFunc1, i);
//    }
//    for (int i = 0; i < threadMax; i++)
//    {
//        tarr[i].join();
//    }
//    //cout << "pool size: " << pool->size() << endl;
//    delete pool;
//    auto stop = system_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//    cout << "pool cost " << duration.count() << " ms" << endl;
//}
//
//void testBinary()
//{
//    auto c = redisConnectWithTimeout("127.0.0.1", 6379, {1, 0});
//    freeReplyObject(redisCommand(c, "AUTH 12345678"));
//    //vector<vector<char>> argvs{ {'s', 'e', 't'}, {'n', 'a', 'm', 'e'}, { 0, 20, 13 } };
//    //vector<const char*> argv{ &(argvs[0][0]), &(argvs[1][0]), &(argvs[2][0]) };
//    //vector<size_t> argvlen{ 3, 4, 3 };
//    //auto reply = (redisReply*)redisCommandArgv(c, 3, &(argv[0]), &(argvlen[0]));
//    //freeReplyObject(reply);
//    auto reply = (redisReply*)redisCommand(c, "get name");
//    freeReplyObject(reply);
//}
//
//void testCmd()
//{
//    RedisObject obj;
//    obj.Connect("127.0.0.1", 6379, 1000);
//    obj.AUTH("12345678");
//
//    for (int i=0; i<10000; i++)
//    {
//        obj.RedisCommand("setex name %d zhang", 10);
//    }
//}
//
//void testCmdArgv()
//{
//    RedisObject obj;
//    obj.Connect("127.0.0.1", 6379, 1000);
//    obj.AUTH("12345678");
//
//    for (int i = 0; i < 10000; i++)
//    {
//        obj.RedisCommandArgv({"setex", "name", to_string(10), "zhang"});
//    }
//}
//
void testHost()
{
    redis rds("192.168.1.209", "10068");

    try
    {
        rds.connect();
        //cout << obj.SendCommand({ "AUTH", "ldadgf4g65hh10068" }).as_string() << endl;
        auto b = rds.auth("ldadgf4g65hh10068");
        rds.disconnect();
        //cout << rds.SendCommand({ "get", "name" }).as_string() << endl;
        //cout << obj.SendCommand({ "AUTH", "12345678" }).as_string() << endl;
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
    //_CrtSetBreakAlloc(287);
    testHost();
    //testRedisPool();
    //testBinary();
    //testTime(testCmd);
    //testTime(testCmdArgv);
    system("pause");
    return 0;
}
