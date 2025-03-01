#pragma once

// fix conflict between boost::python's and Qt's slots
#pragma push_macro("slots")
#undef slots
#include <boost/python.hpp>
#pragma pop_macro("slots")

namespace py = boost::python;

// a concept for any object that defines its interface to Python
template <typename T>
concept Self_Init_Python_Object =
    requires(T t, py::class_<T, boost::noncopyable> &&u) {
      T::Get_Class_Name();         // must define object/class name
      T::Define_Class_Contents(u); // must be able to define its contents
    };

// Python exported class definition wrapper
template <Self_Init_Python_Object TClass>
constexpr auto Define_Class(const char *name = nullptr) {
  return TClass::Define_Class_Contents(py::class_<TClass, boost::noncopyable>(
      name ? name : TClass::Get_Class_Name()));
}
