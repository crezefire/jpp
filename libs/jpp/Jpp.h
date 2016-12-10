/*
Ideas List:
- General objects packing / transferring
- Type injection through member overload
*/
#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <cstring>
#include <algorithm>

namespace jpp {

    class val {
    public:
        enum class type {
            NONE = 0,
            BOOL = sizeof(bool),
            NULLPTR = 2,
            INT = sizeof(unsigned long long),
            NUMBER  = sizeof(long double),
            STRING = 32,
            OTHER = 64,
        };

        val() = default;

        ~val(){
            if (CurrentType == type::STRING || CurrentType == type::OTHER) 
                delete static_cast<unsigned char*>(_other);
        };

        val(const val& rhs)
            : CurrentType (rhs.CurrentType),
            CurrentSize (rhs.CurrentSize) {
            
            copy(rhs.CurrentType, rhs._other, rhs.CurrentSize);
        }

        val(val&& rhs)
            : _number (rhs._number),
            CurrentType (rhs.CurrentType),
            CurrentSize (rhs.CurrentSize)
        {
            rhs._integer = 0;
            rhs.CurrentType = type::NONE,
            rhs.CurrentSize = 0;
        }

        explicit val(long double data)
            : _number (data),
            CurrentType (type::NUMBER),
            CurrentSize (sizeof(long double))
        {};

        explicit val(unsigned long long data)
            : _integer (data),
            CurrentType (type::INT),
            CurrentSize (sizeof(unsigned long long))
        {};

        explicit val(bool data)
            : _boolean (data),
            CurrentType (type::BOOL),
            CurrentSize (sizeof(bool))
        {};

        explicit val(const char* mem, std::size_t len)
            : val(static_cast<const void*>(mem), len) {
           
           CurrentType = type::STRING;
        };

        explicit val(const void* mem, std::size_t len)
            : CurrentType (type::OTHER),
            CurrentSize (len) {
            
            _other = new unsigned char [len];
            
            std::memcpy(_other, mem, len);
        };

        explicit val(std::nullptr_t)
            : val() {
            
            CurrentType = type::NULLPTR;
        }

        val& operator=(const val& rhs) {
            CurrentType = rhs.CurrentType;
            CurrentSize = rhs.CurrentSize;

            copy(rhs.CurrentType, rhs._other, rhs.CurrentSize);

            return *this;
        }

        val& operator=(val&& rhs) {
            _number = rhs._number;
            CurrentType = rhs.CurrentType;
            CurrentSize = rhs.CurrentSize;

            rhs._integer = 0;
            rhs.CurrentType = type::NONE,
            rhs.CurrentSize = 0;

            return *this;
        }

        auto GetCurrentType() const {
            return CurrentType;
        }

        auto GetCurrentSize() const {
            return CurrentSize;
        }

        auto HasType(type t) const {
            return t == CurrentType;
        }

        //TODO(vim): std::optional ???
        // Error if wrong type
        auto GetInteger() const {
            return _integer;
        }

        auto GetNumber() const {
            return _number;
        }

        auto GetBoolean() const {
            return _boolean;
        }

        auto GetNull() const {
            return nullptr;
        }

        template<typename T>
        auto GetOther() const {
            return reinterpret_cast<T*>(_other);
        }

    private:

        void copy(type t, const void* ptr, std::size_t len) {
            if ( t == type::OTHER || t == type::STRING) {
                _other = new unsigned char[len];

                std::memcpy(_other, ptr, len);
            }
        } 

        union {
            unsigned long long _integer = 0; // 8
            long double _number;             // 16
            bool _boolean;                   // 1
            void* _other;                    // word (8)   
        };

        type CurrentType { type::NONE };
        std::size_t CurrentSize { 0 };
    };

    template<typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    auto make_val(const T& data) {
        return val{static_cast<long double>(data)};
    }

    template<typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    auto make_val(const T& data) {
        return val{static_cast<unsigned long long>(data)};
    }

    template<typename T, std::enable_if_t<std::is_same<T, bool>::value> = true>
    auto make_val(const T& data) {
        return val{static_cast<bool>(data)};
    }

    auto make_val(std::nullptr_t) {
        return val{nullptr};
    }

    template<typename T, std::enable_if_t<
        !std::is_floating_point<T>::value
        && !std::is_integral<T>::value
        && !std::is_same<T, bool>::value
    >* = nullptr>
    val make_val(const T& data) {
        return val{reinterpret_cast<const void*>(std::addressof(data)), sizeof(T)};
    }

    struct str{};

    class field {
        std::string Name;
        val Value;
    public:
        field(std::string name)
            : Name(std::move(name))
        {}

        field(field&& rhs)
            :  Name(std::move(rhs.Name)),
            Value(std::move(rhs.Value))
        {}

        field(const field& rhs)
            : Name (rhs.Name),
            Value(rhs.Value)
        {}

        template<typename T>
        field& operator=(const T& rhs) {
            Value = make_val(rhs);
            return *this;
        }

        field& operator=(const char* rhs) {
            Value = val{rhs, std::strlen(rhs)};
            return *this;
        }

        field& operator=(field&& rhs) {
            Value = std::move(rhs.Value);
            Name = std::move(rhs.Name);
            return *this;
        }

        field& operator=(const field& rhs) {
            Value = rhs.Value;
            Name = rhs.Name;
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
        auto GetValue() const {
            return static_cast<T>(Value.GetNumber());
        }

        template<typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
        auto GetValue() const {
            return static_cast<T>(Value.GetInteger());
        }

        template<typename T, std::enable_if_t<std::is_same<T, bool>::value> = true>
        auto GetValue() const {
            return Value.GetBoolean();
        }

        template<typename T, std::enable_if_t<std::is_null_pointer<T>::value>* = nullptr>
        auto GetValue() const{
            return Value.GetNull();
        }

        template<typename T, std::enable_if_t<std::is_same<T, str>::value>* = nullptr>
        auto GetValue() const {
            return Value.GetOther<char>();
        }

        template<typename T, std::enable_if_t<
                !std::is_floating_point<T>::value
                && !std::is_integral<T>::value
                && !std::is_same<T, bool>::value
                && !std::is_null_pointer<T>::value
                && !std::is_same<T, str>::value
            >* = nullptr>
        auto GetValue() const {
            return Value.GetOther<T>();
        }

        auto GetRawValue() const {
            return Value;
        }

        decltype(auto) GetName() const {
            return Name;
        }

        static const field empty_field;
    };

    const field field::empty_field{""};

    class obj {
        std::vector<field> Fields;
    public:
        obj(std::initializer_list<field> list)
            : Fields(list)
        {}

        //TODO(vim): Maybe simplify with iterators..???
        const field& operator[](const std::string& name) const {

            auto result = std::find_if(std::begin(Fields), std::end(Fields),
                [&name](auto& element) {
                    if (element.GetName() == name) {
                        return true;
                    }

                    return false;
            });

            if (result != std::end(Fields)) {
                return *result;
            }

            return field::empty_field;
        }
    };

    class arr {

    };

    inline namespace literals {

        field operator""_f (const char* f, std::size_t length) {
                return { f };
        }
    }

}

