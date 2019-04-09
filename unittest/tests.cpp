#include "catch.hpp"
#include "PreAllocString.h"
#include "string.h"

TEST_CASE("Functions", "[PreAllocString]")
{

    /* Teste ob die Methoden tun, was sie sollen, und nicht mehr */

    SECTION("index, size of, get length, empty")
    {
        CREATE(pas, 5);
        REQUIRE(pas.GetLength() == 0);
        REQUIRE(pas.SizeOf() == 5);
        pas = 'a';
        REQUIRE(pas[0] == 'a');
        REQUIRE(pas[1] == '\0');
        pas.Empty();
        REQUIRE(pas[0] == '\0');
    }

    SECTION("equal, plus equal")
    {
        CREATE(pas, 4);
        pas += "abc";
        REQUIRE(pas[1] == 'b');

        pas = "tooLong";
        REQUIRE(pas[3] == '\0');
    }

    SECTION("Printf")
    {
        CREATE(pas, 4);
        pas.AddFormat("%d%c%s", 1, '2', "3");
        REQUIRE(pas[0] == '1');
        REQUIRE(pas[1] == '2');
        REQUIRE(pas[2] == '3');
    }
}

TEST_CASE("Exceptions", "[PreAllocString]")
{

    /* Teste ungültige Argumente oder Aufrufe */

    SECTION("out of bounds")
    {
        CREATE(pas, 4);
        pas += "abc";
        REQUIRE(pas[3] == '\0');
        REQUIRE(pas[4] == 'a');
        REQUIRE(pas[-1] == '\0');
        REQUIRE(pas[-2] == 'c');
    }

    SECTION("nullptr")
    {
        CREATE(pas, 4);
        pas = "abc";

        pas += nullptr;
        REQUIRE(pas[1] == 'b');

        const char *np = nullptr;
        pas = np;
        REQUIRE(pas[1] == '\0');
    }

    SECTION("size = 1") {
        CREATE(pas, 1);
        pas += "abc";
        REQUIRE(pas[0] == '\0');
        pas = "abc";
        REQUIRE(pas[0] == '\0');
        pas.AddFormat("%d", 1);
        REQUIRE(pas[0] == '\0');
        REQUIRE(pas.GetLength() == 0);
        REQUIRE(pas.SizeOf() == 1);
    }
}

// d's tests
TEST_CASE("Truncate", "[PreAllocString]")
{
    CREATE(a, 6);
    REQUIRE(a.GetLength() == 0);
    REQUIRE(a.SizeOf() == 6);
    REQUIRE(strcmp(static_cast<const char *>(a), "") == 0);

    SECTION("Assign string")
    {
        a = "ABCDEFG";
        REQUIRE(a.GetLength() == 5);
        REQUIRE(a.SizeOf() == 6);
        REQUIRE(strcmp(static_cast<const char *>(a), "ABCDE") == 0);
    }

    SECTION("Add string")
    {
        for (size_t i = 0; i < 10; ++i)
        {
            a += "A";
        }
        REQUIRE(a.GetLength() == 5);
        REQUIRE(a.SizeOf() == 6);

        REQUIRE(strcmp(static_cast<const char *>(a), "AAAAA") == 0);
    }

    SECTION("Add char")
    {
        for (size_t i = 0; i < 10; ++i)
        {
            a += ('A' + i);
        }
        REQUIRE(a.GetLength() == 5);
        REQUIRE(a.SizeOf() == 6);
        REQUIRE(strcmp(static_cast<const char *>(a), "ABCDE") == 0);
    }

    SECTION("Add Format")
    {
        a = "AB";
        a.AddFormat("%d", 12345);
        REQUIRE(a.GetLength() == 5);
        REQUIRE(a.SizeOf() == 6);
        REQUIRE(strcmp(static_cast<const char *>(a), "AB123") == 0);
    }
}

// t's tests
TEST_CASE("Assign char", "[assign_char]")
{
    CREATE(s, 2);
    s = 'a';
    const char *chars = static_cast<const char *>(s);
    REQUIRE(chars[0] == 'a');
    REQUIRE(chars[1] == '\0');
}

TEST_CASE("Size 1 null character", "[size_1_null_char]")
{
    CREATE(s, 1);
    s = 'x';
    const char *chars = static_cast<const char *>(s);
    REQUIRE(chars[0] == '\0');
}

TEST_CASE("Assign char array", "[assign_char_array]")
{
    CREATE(s, 7);
    const char *expected = "foobar";
    s = expected;
    const char *result = static_cast<const char *>(s);
    REQUIRE(strcmp(expected, result) == 0);
    REQUIRE(s.SizeOf() == 7);
    REQUIRE(s.GetLength() == 6);
}

TEST_CASE("Assign char* const", "[assign_char_ptr_const]")
{
    CREATE(s, 7);
    const char *orginial = "foobar";
    char *expected = const_cast<char *>(orginial);
    s = expected;
    const char *result = static_cast<const char *>(s);
    REQUIRE(strcmp(expected, result) == 0);
    REQUIRE(s.SizeOf() == 7);
    REQUIRE(s.GetLength() == 6);
}

TEST_CASE("Add char", "[add_char]")
{
    CREATE(s, 7);
    const char *expected = "foobar";
    s = "foo";
    s += 'b';
    s += 'a';
    s += 'r';
    s += 'x'; // should be ignored
    const char *result = static_cast<const char *>(s);
    REQUIRE(strcmp(expected, result) == 0);
    REQUIRE(s.SizeOf() == 7);
    REQUIRE(s.GetLength() == 6);
}

TEST_CASE("Add char array", "[add_char_array]")
{
    CREATE(s, 8);
    const char *expected = "abc";
    s += "ab";
    s += "c";
    const char *result = static_cast<const char *>(s);
    REQUIRE(strcmp(expected, result) == 0);
    REQUIRE(s.SizeOf() == 8);
    REQUIRE(s.GetLength() == 3);
}

TEST_CASE("Add char array full", "[add_char_array_full]")
{
    CREATE(s, 16);
    const char *expected = "abcdefghijlmnop";
    s = "abcdefghij";
    s += "lmnop";
    s += "xxx"; // should be ignored
    const char *result = static_cast<const char *>(s);
    REQUIRE(strcmp(expected, result) == 0);
    REQUIRE(s.SizeOf() == 16);
    REQUIRE(s.GetLength() == 15);
}

TEST_CASE("Add format", "[add_format]")
{
    const char *fmt = "%b whatever %% this %d that %u %c %s %x";
    const char *expected = "0b101010 whatever % this 42 that 777 ! meow 0x2a";
    constexpr size_t buff_len = 48 + 1;

    CREATE(s, buff_len);
    s.AddFormat(fmt, 42, 42, 777, '!', "meow", 42);
    const char *result = static_cast<const char *>(s);
    REQUIRE(strcmp(expected, result) == 0);
    REQUIRE(s.SizeOf() == 49);
    REQUIRE(s.GetLength() == 48);
}

TEST_CASE("Add whitespace", "[add_whitespace]")
{
    CREATE(s, 5);
    const char *expected = "abc ";
    s = "abc";
    s.AddWhiteSpace();
    s += "xxx"; // should be ignored
    const char *result = static_cast<const char *>(s);
    REQUIRE(strcmp(expected, result) == 0);
    REQUIRE(s.SizeOf() == 5);
    REQUIRE(s.GetLength() == 4);
}

TEST_CASE("Add empty", "[add_empty]")
{
    CREATE(s, 16);
    const char *expected = "foo";
    s = "foo";
    s += "";
    s += "";
    const char *result = static_cast<const char *>(s);
    REQUIRE(strcmp(expected, result) == 0);
    REQUIRE(s.SizeOf() == 16);
    REQUIRE(s.GetLength() == 3);
}

TEST_CASE("Assign nullptr", "[assign_nullptr]")
{
    CREATE(s, 8);
    const char *foo = nullptr;
    s = foo;
    REQUIRE(s.SizeOf() == 8);
    REQUIRE(s.GetLength() == 0);
}
