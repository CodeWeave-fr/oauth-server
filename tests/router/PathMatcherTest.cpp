/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <catch2/catch_test_macros.hpp>
#include "router/PathMatcher.hpp"

using namespace Lattice;

TEST_CASE("PathMatcher") {
    SECTION("matches") {
        PathMatcher matcher("/test");
        REQUIRE(matcher.matches("/test"));
        REQUIRE(matcher.matches("/test?type=1"));
        REQUIRE(matcher.matches("/test/"));
        REQUIRE_FALSE(matcher.matches("/test2"));
        REQUIRE_FALSE(matcher.matches("/test/2"));
        REQUIRE_FALSE(matcher.matches("/test/2/"));
        REQUIRE_FALSE(matcher.matches("test"));
        REQUIRE_FALSE(matcher.matches("test/"));
    }

    SECTION("path parameters") {
        PathMatcher matcher("/test/[param]");
        REQUIRE(matcher.matches("/test/0"));
        REQUIRE(matcher.matches("/test/1"));
        REQUIRE(matcher.matches("/test/1?type=1"));
        REQUIRE(matcher.matches("/test/hello-world"));
        REQUIRE(matcher.matches("/test/hello-world?type=1"));
        REQUIRE(matcher.matches("/test/2/"));
        REQUIRE_FALSE(matcher.matches("/test"));
        REQUIRE_FALSE(matcher.matches("/test/"));
        REQUIRE_FALSE(matcher.matches("/test//"));

        matcher = PathMatcher("/test/hello-[param]/[param2]");
        REQUIRE(matcher.matches("/test/hello-world/0"));
        REQUIRE(matcher.matches("/test/hello-world/1"));
        REQUIRE(matcher.matches("/test/hello-world/1?type=1"));
        REQUIRE_FALSE(matcher.matches("/test/hello-/hello-world"));
        REQUIRE_FALSE(matcher.matches("/test/hello-world"));
    }

    SECTION("path validation") {
        REQUIRE_THROWS_AS(PathMatcher("test"), std::runtime_error);
        REQUIRE_THROWS_AS(PathMatcher("test/"), std::runtime_error);
        REQUIRE_THROWS_AS(PathMatcher("/test/"), std::runtime_error);
        REQUIRE_NOTHROW(PathMatcher("/test"));
        REQUIRE_NOTHROW(PathMatcher("/test/[param]"));
        REQUIRE_NOTHROW(PathMatcher("/test/[param]/[param2]"));
        REQUIRE_NOTHROW(PathMatcher("/test/hello-[param]"));
        REQUIRE_THROWS_AS(PathMatcher("/test/hello-[param"), std::runtime_error);
        REQUIRE_THROWS_AS(PathMatcher("/*/test"), std::runtime_error);
        REQUIRE_NOTHROW(PathMatcher("/test/*"));
        REQUIRE_THROWS_AS(PathMatcher("/test/*/*"), std::runtime_error);
        REQUIRE_THROWS_AS(PathMatcher("/test/*/[param]"), std::runtime_error);
        REQUIRE_THROWS_AS(PathMatcher("/test/[param ]"), std::runtime_error);
        REQUIRE_THROWS_AS(PathMatcher("/test/[param]/hello?test=test"), std::runtime_error);
    }

    SECTION("process") {
        PathMatcher matcher("/test/[param]");
        auto processed = matcher.process("/test/0");
        REQUIRE(processed.path_params.size() == 1);
        REQUIRE(processed.path_params["param"] == "0");

        processed = matcher.process("/test/1");
        REQUIRE(processed.path_params.size() == 1);
        REQUIRE(processed.path_params["param"] == "1");

        processed = matcher.process("/test/1?type=1");
        REQUIRE(processed.path_params.size() == 1);
        REQUIRE(processed.path_params["param"] == "1");
        REQUIRE(processed.query_params.size() == 1);
        REQUIRE(processed.query_params[0].name == "type");
        REQUIRE(processed.query_params[0].value == "1");

        processed = matcher.process("/test/hello-world");
        REQUIRE(processed.path_params.size() == 1);
        REQUIRE(processed.path_params["param"] == "hello-world");

        processed = matcher.process("/test/hello-world?type=1");
        REQUIRE(processed.path_params.size() == 1);
        REQUIRE(processed.path_params["param"] == "hello-world");
        REQUIRE(processed.query_params.size() == 1);
        REQUIRE(processed.query_params[0].name == "type");

        processed = matcher.process("/test/2/");
        REQUIRE(processed.path_params.size() == 1);
        REQUIRE(processed.path_params["param"] == "2");

        matcher = PathMatcher("/test/hello-[param]/[param2]");
        processed = matcher.process("/test/hello-world/0");

        REQUIRE(processed.path_params.size() == 2);
        REQUIRE(processed.path_params["param"] == "world");
        REQUIRE(processed.path_params["param2"] == "0");

        processed = matcher.process("/test/hello-world/1");
        REQUIRE(processed.path_params.size() == 2);
        REQUIRE(processed.path_params["param"] == "world");
        REQUIRE(processed.path_params["param2"] == "1");

        processed = matcher.process("/test/hello-world/1?hello-world=test%20test");
        REQUIRE(processed.path_params.size() == 2);
        REQUIRE(processed.path_params["param"] == "world");
        REQUIRE(processed.path_params["param2"] == "1");
        REQUIRE(processed.query_params.size() == 1);
        REQUIRE(processed.query_params[0].name == "hello-world");
        REQUIRE(processed.query_params[0].value == "test test");

        processed = matcher.process("/test/hello-world/1?hello-world=test%20test&test=1");
        REQUIRE(processed.path_params.size() == 2);
        REQUIRE(processed.path_params["param"] == "world");
        REQUIRE(processed.path_params["param2"] == "1");
        REQUIRE(processed.query_params.size() == 2);
        REQUIRE(processed.query_params[0].name == "hello-world");
        REQUIRE(processed.query_params[0].value == "test test");
        REQUIRE(processed.query_params[1].name == "test");
        REQUIRE(processed.query_params[1].value == "1");
    }

    SECTION("wildcard") {
        PathMatcher matcher("/test/*");
        REQUIRE(matcher.matches("/test/0"));
        REQUIRE(matcher.matches("/test/1"));
        REQUIRE(matcher.matches("/test/1?type=1"));
        REQUIRE(matcher.matches("/test/hello-world"));
        REQUIRE(matcher.matches("/test/hello-world?type=1"));
        REQUIRE(matcher.matches("/test/2/"));
        REQUIRE_FALSE(matcher.matches("/test"));
        REQUIRE_FALSE(matcher.matches("/test/"));
        REQUIRE_FALSE(matcher.matches("/test//"));
    }
}
