#include <iostream>
#include <string>

#include <Serializer/ISerializable.h>
#include <Serializer/Serializer.h>

class Vector2 : public xe::ISerializable
{
public:
    float x = 0.f;
    float y = 0.f;

    Vector2() = default;
    constexpr Vector2(float x, float y) : x(x), y(y) {}

    SERIALIZE_METHOD
    {
        SERIALIZE(x);
        SERIALIZE(y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v2)
    {
        os << v2.x << ", " << v2.y;
        return os;
    }
};

class GameObject : public xe::ISerializable
{
public:
    GameObject()
    {
        m_position.x = 0.f;
        m_position.y = 0.f;
        m_rotation = 0.f;
        m_scale.x = 1.f;
        m_scale.y = 1.f;
    }

    void SetPosition(const Vector2 position) { m_position = position; }
    void SetRotation(const float rotation) { m_rotation = rotation; }
    void SetScale(const Vector2 scale) { m_scale = scale; }

    Vector2 GetPosition() const { return m_position; }
    float GetRotation() const { return m_rotation; }
    Vector2 GetScale() const { return m_scale; }

    SERIALIZE_METHOD
    {
    SERIALIZE(m_position);
    SERIALIZE(m_rotation);
    SERIALIZE(m_scale);
    }

private:
    Vector2 m_position;
    float m_rotation;
    Vector2 m_scale;
};

int main (int argc, char* argv[])
{
    xe::Serializer serializer;
    
    GameObject objs[3];
    //objs[0].SetPosition({ 10.f, 15.f });
    //
    //objs[1].SetPosition({ 200.5f, -32.f });
    //objs[1].SetRotation(15.f);
    //
    //objs[2].SetRotation(15.f);
    //objs[2].SetScale({ 2.f, 3.f });

    for (int i = 0; i < 3; ++i)
    {
        serializer.AddEntry(objs[i], "GameObject_" + std::to_string(i));
    }

    //serializer.SaveTo("test.yaml");
    serializer.LoadFrom("test.yaml");

    for (int i = 0; i < 3; ++i)
    {
        std::cout << objs[i].GetPosition() << std::endl;
        std::cout << objs[i].GetRotation() << std::endl;
        std::cout << objs[i].GetScale() << std::endl << std::endl;
    }

    return 0;
}
