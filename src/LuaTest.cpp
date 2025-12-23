#include <sol/sol.hpp>
#include <iostream>

void testLuaIntegration() {
    // Create Lua state
    sol::state lua;
    
    // Open standard Lua libraries
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string);
    
    // Execute simple Lua script
    lua.script("print('Hello from Lua!')");
    
    // Set a variable from C++
    lua["myNumber"] = 42;
    
    // Read it back from Lua
    int number = lua["myNumber"];
    std::cout << "Number from Lua: " << number << std::endl;
    
    // Call Lua function from C++
    lua.script("function add(a, b) return a + b end");
    sol::function add = lua["add"];
    int result = add(10, 20);
    std::cout << "10 + 20 = " << result << std::endl;
    
    // Expose C++ function to Lua
    lua["cpp_multiply"] = [](int a, int b) { return a * b; };
    lua.script("result = cpp_multiply(5, 6)");
    int multiply_result = lua["result"];
    std::cout << "5 * 6 = " << multiply_result << std::endl;
}
