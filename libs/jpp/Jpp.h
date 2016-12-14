#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <cstring>
#include <algorithm>

#ifdef NDEBUG
#include <cstdio>
#define JPP_ASSERT(condition, message)  {std::fprintf(stderr, message);\
                                        std::abort();}
#else
#include <cassert>
#define JPP_ASSERT(condition, message)  assert(condition && message)
#endif


namespace jpp {

    class val {
    public:
        enum class type {
            NONE = 0,
            BOOL,
            NULLPTR,
            INT,
            NUMBER,
            STRING,
            OTHER,
        };

        val() = default;

        ~val(){
            if (CurrentType == type::STRING || CurrentType == type::OTHER) 
                delete static_cast<unsigned char*>(_other);
        };

        val(const val& rhs)
            : _number(rhs._number),
            CurrentType (rhs.CurrentType),
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
            _number = rhs._number;
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

            //TODO(vim): Short opts for custom small types
            void* _other;                    // word (8)   
        };

        type CurrentType { type::NONE };
        std::size_t CurrentSize { 0 };
    };

    template<typename T, std::enable_if_t<std::is_floating_point<T>::value, bool> = false>
    auto make_val(const T& data) {
        return val{static_cast<long double>(data)};
    }

    template<typename T, std::enable_if_t<std::is_integral<T>::value
                                          && !std::is_same<T,bool>::value, bool> = false>
    auto make_val(const T& data) {
        return val{static_cast<unsigned long long>(data)};
    }

    template<typename T, std::enable_if_t<std::is_same<T, bool>::value, bool> = false>
    auto make_val(const T& data) {
        return val{data};
    }

    auto make_val(std::nullptr_t) {
        return val{nullptr};
    }

    template<typename T, std::enable_if_t<
        !std::is_floating_point<T>::value
        && !std::is_integral<T>::value
        && !std::is_same<T, bool>::value
        && !std::is_null_pointer<T>::value
        , bool> = true>
    val make_val(const T& data) {
        return val{reinterpret_cast<const void*>(std::addressof(data)), sizeof(T)};
    }

    struct str{};
    using null = std::nullptr_t;

    struct proxy {
        std::vector<val> Values;

        template<typename T>
        proxy& operator,(const T& rhs) {
            Values.emplace_back(make_val(rhs));
            return *this;
        }
    };

    struct arr_t {
        std::vector<val> Values;

        arr_t& operator[](proxy& rhs) {
            Values.clear();
            Values = std::move(rhs.Values);
            return *this;
        }
    };

    static arr_t arr;
    static proxy beg;

    class field {
        std::string Name;
        val Value;
        bool IsArray { false };
        std::vector<val> Values;
    public:
        field(std::string name)
            : Name(std::move(name))
        {}

        field(field&& rhs)
            :  Name(std::move(rhs.Name)),
            Value(std::move(rhs.Value)),
            Values(std::move(rhs.Values)),
            IsArray(rhs.IsArray)
        {}

        field(const field& rhs)
            : Name (rhs.Name),
            Value(rhs.Value),
            Values(rhs.Values),
            IsArray(rhs.IsArray)
        {}

        template<typename T>
        field& operator=(const T& rhs) {
            Value = make_val(rhs);
            return *this;
        }

        field& operator=(arr_t&& rhs) {
            Values = std::move(rhs.Values);
            IsArray = true;
            return *this;
        }

        field& operator=(arr_t& rhs) {
            Values = std::move(rhs.Values);
            IsArray = true;
            return *this;
        }

        field& operator=(const char* rhs) {
            Value = val{rhs, std::strlen(rhs) + 1};
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

        decltype(auto) GetRawValue() const {
            return (Value);
        }

        decltype(auto) GetName() const {
            return (Name);
        }

        decltype(auto) GetRawValues() const {
            return (Values);
        }

        auto GetIsArray() const {
            return IsArray;
        }

        static const field empty_field;
    };

    template<typename T, std::enable_if_t<std::is_floating_point<T>::value, bool> = false>
    auto Get(const field& f) {
        auto& Value = f.GetRawValue();
        
        auto CurrentType = Value.GetCurrentType();

        if (CurrentType == val::type::NONE)
            JPP_ASSERT(false, "field not found or contains an empty value");
        
        if(CurrentType != val::type::NUMBER)
            JPP_ASSERT(false, "Type Empty or not a floating point");

        return static_cast<T>(Value.GetNumber());
    }

    template<typename T, std::enable_if_t<std::is_integral<T>::value
                                        && !std::is_same<T, bool>::value, bool> = false>
    auto Get(const field& f) {
        auto& Value = f.GetRawValue();

        auto CurrentType = Value.GetCurrentType();

        if (CurrentType == val::type::NONE)
            JPP_ASSERT(false, "field not found or contains an empty value");
        
        if(CurrentType != val::type::INT)
            JPP_ASSERT(false, "Type Empty or not an integral");

        return static_cast<T>(Value.GetInteger());
    }

    template<typename T, std::enable_if_t<std::is_same<T, bool>::value, bool> = false>
    auto Get(const field& f) {
        auto& Value = f.GetRawValue();

        auto CurrentType = Value.GetCurrentType();

        if (CurrentType == val::type::NONE)
            JPP_ASSERT(false, "field not found or contains an empty value");
        
        if(CurrentType != val::type::BOOL)
            JPP_ASSERT(false, "Type Empty or not a boolean");

        return Value.GetBoolean();
    }

    template<typename T, std::enable_if_t<std::is_null_pointer<T>::value, bool> = false>
    auto Get(const field& f){
        auto& Value = f.GetRawValue();

        auto CurrentType = Value.GetCurrentType();
        
        if (CurrentType == val::type::NONE)
            JPP_ASSERT(false, "field not found or contains an empty value");
        
        if(CurrentType != val::type::NULLPTR)
            JPP_ASSERT(false, "Type Empty or not a null value");

        return Value.GetNull();
    }

    template<typename T, std::enable_if_t<std::is_same<T, str>::value, bool> = false>
    auto Get(const field& f) {
        auto& Value = f.GetRawValue();

        auto CurrentType = Value.GetCurrentType();

        //TODO(vim): Add call for this check and then check inliner
        if (CurrentType == val::type::NONE)
            JPP_ASSERT(false, "field not found or contains an empty value");
        
        if(CurrentType != val::type::STRING)
            JPP_ASSERT(false, "Not found or not a string");

        return Value.GetOther<char>();
    }


    template<typename T, std::enable_if_t<std::is_same<T, arr_t>::value, bool> = false>
    decltype(auto) Get(const field& f) {
        auto& Values = f.GetRawValues();

        if (!f.GetIsArray())
            JPP_ASSERT(false, "Not an array value");

        return (Values);
    }

    //TODO(vim): is_fundamental ...????
    template<typename T, std::enable_if_t<
            !std::is_fundamental<T>::value
            && !std::is_same<T, str>::value
            && !std::is_same<T, arr_t>::value
            , bool> = true>
    auto Get(const field& f) {
        auto& Value = f.GetRawValue();
        
        auto CurrentType = Value.GetCurrentType();

        if (CurrentType == val::type::NONE)
            JPP_ASSERT(false, "field not found or contains an empty value");
        
        if(CurrentType != val::type::OTHER)
            JPP_ASSERT(false, "Not found or not a non-fundamental type");

        return Value.GetOther<T>();
    }

    const field field::empty_field{""};

    class obj {
        std::vector<field> Fields;
    public:
        //TODO(vim): Unique fields
        //TODO(vim):  Move shit, prevent copying
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

    inline namespace literals {

        field operator""_f (const char* f, std::size_t) {
                return { f };
        }
    }

}

