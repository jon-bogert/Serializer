# Serializer - Readme

## Description
Simple compile-time object serialization library for C++. Currently supports the YAML file format. Objects you want to serialize should implement the `xe::ISerializable` interface. Base-types and `std::string` are implemented by default.

## Example
```cpp
#include <Serializer/ISerializable.h> // For ISerializable Interface
#include <Serializer/Serializer.h> // For Serializer
#include <iostream>

// Serializable Vector2
class Vector2 : public xe::ISerializable
{
public:
    float x = 0.f;
    float y = 0.f;

    Vector2() = default;
    constexpr Vector2(float x, float y) : x(x), y(y) {}

    SERIALIZE_METHOD // Define in public space
    {
        // Encapsulated serialize implementation via Macro (allows for use of variable name at compile-time)
        SERIALIZE(x); 
        SERIALIZE(y);
    }
};

// Serializable that also contains other serializable members
class GameObject : public xe::ISerializable
{
public:
    Vector2 position;
    float rotation;
    Vector2 rotation;

    SERIALIZE_METHOD
    {
        SERIALIZE(position); // ISerializable sub-ojects will be serialized recursively
        SERIALIZE(rotation);
        SERIALIZE(scale);
    }
}

// Usage
int main()
{
    xe::Serializer serializer;
    GameObject gameObject;

    // Add object with a root name (Vector2 members will use variable name)
    serializer.AddEntry(gameObject, "GameObject"); 

    // Load and populate existing data.
    serializer.LoadFrom("myFile.yaml");

    // Use/Change Data
    serializer.SaveTo("myFile.yaml");
}
```

## Repository
[yaml-cpp](https://github.com/jbeder/yaml-cpp) is required for this repository. MSVC static library included.

This repository uses the [premake5](https://premake.github.io/) build system. Run `generate-vs2022.bat` to generate a Visual Studio 2022 solution.