/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include <cereal/types/map.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>
#include <array>
#include <memory>
#include "my_game.h"

class Test1
{
public:
    int a {};
    int b {};
    Test1 (void) { }
    Test1 (int a, int b) : a(a), b(b) { }

    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("a", a),
                cereal::make_nvp("b", b));
    }
};

class Test2
{
public:
    std::array<class Test1, 2> c;
    class Test1 d[2];
    class Test1 e[2][2];
    int f[2048][2048] = {{0}};
    std::shared_ptr<class Test1> u1;

    Test2 (void) { }

    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("c", c),
                cereal::make_nvp("d", d),
                cereal::make_nvp("e", e),
                cereal::make_nvp("f", f),
                cereal::make_nvp("u1", u1));
    }
};

static Test2 test2;
static Test2 test3;
int cereal_test (const std::string save_file)
{
    {
        std::ofstream os(save_file, std::ios::binary);
        cereal::JSONOutputArchive archive_out(os);

        test2.c[0] = Test1(1, 2);
        test2.c[1] = Test1(3, 4);
        test2.d[0] = Test1(5, 6);
        test2.d[1] = Test1(7, 8);
        test2.f[0][0] = 66;
        test2.f[1][1] = 67;
        test2.e[0][0] = Test1(1, 2);
        test2.e[1][1] = Test1(3, 4);

        auto p = std::make_unique<class Test1>(11, 12);
        test2.u1 = std::move(p);

        printf("json saving\n");
        system("date");
        archive_out(test2);
        system("date");
        printf("json saved\n");
    }

    {
        printf("create archive\n");
        std::ifstream is(save_file);
        cereal::JSONInputArchive archive_in(is);

        printf("json loading\n");
        system("date");
        archive_in(test3);
        system("date");
        printf("json loaded\n");

        //cereal::JSONOutputArchive archive_out(std::cout);
        //archive_out(test2);
    }

    {
        std::ofstream os(save_file, std::ios::binary);
        cereal::BinaryOutputArchive archive_out(os);

        test2.c[0] = Test1(1, 2);
        test2.c[1] = Test1(3, 4);
        test2.d[0] = Test1(5, 6);
        test2.d[1] = Test1(7, 8);
        test2.f[0][0] = 66;
        test2.f[1][1] = 67;
        test2.e[0][0] = Test1(1, 2);
        test2.e[1][1] = Test1(3, 4);

        auto p = std::make_unique<class Test1>(11, 12);
        test2.u1 = std::move(p);

        printf("binary saving\n");
        system("date");
        archive_out(test2);
        system("date");
        printf("binary saved\n");
    }

    {
        printf("create binary archive\n");
        std::ifstream is(save_file);
        cereal::BinaryInputArchive archive_in(is);

        printf("binary loading\n");
        system("date");
        archive_in(test3);
        system("date");
        printf("binary loaded\n");

        //cereal::BinaryOutputArchive archive_out(std::cout);
        //archive_out(test2);
    }

    exit(0);
//    return 0;
}
