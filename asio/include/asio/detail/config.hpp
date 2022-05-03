//
// detail/config.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_CONFIG_HPP
#define ASIO_DETAIL_CONFIG_HPP

#if !defined(ASIO_STANDALONE)
# if (__cplusplus >= 201103)
#  define ASIO_STANDALONE 1
# elif defined(_MSC_VER) && defined(_MSVC_LANG)
#  if (_MSC_VER >= 1900) && (_MSVC_LANG >= 201103)
#   define ASIO_STANDALONE 1
#  endif // (_MSC_VER >= 1900) && (_MSVC_LANG >= 201103)
# endif // defined(_MSC_VER) && defined(_MSVC_LANG)
#endif // !defined(ASIO_STANDALONE)

#if !defined(ASIO_STANDALONE)
#error This file requires compiler and library support \
for the ISO C++ 2011 standard. This support must be enabled \
with the -std=c++11 or -std=gnu++11 compiler options.
#endif

#if defined(ASIO_STANDALONE)
# define ASIO_DISABLE_BOOST_REGEX 1
#endif // defined(ASIO_STANDALONE)

// Default to a header-only implementation. The user must specifically request
// separate compilation by defining either ASIO_SEPARATE_COMPILATION or
// ASIO_DYN_LINK (as a DLL/shared library implies separate compilation).
#if !defined(ASIO_HEADER_ONLY)
# if !defined(ASIO_SEPARATE_COMPILATION)
#  if !defined(ASIO_DYN_LINK)
#   define ASIO_HEADER_ONLY 1
#  endif // !defined(ASIO_DYN_LINK)
# endif // !defined(ASIO_SEPARATE_COMPILATION)
#endif // !defined(ASIO_HEADER_ONLY)

#if defined(ASIO_HEADER_ONLY)
# define ASIO_DECL inline
#else // defined(ASIO_HEADER_ONLY)
# if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__CODEGEARC__)
// We need to import/export our code only if the user has specifically asked
// for it by defining ASIO_DYN_LINK.
#  if defined(ASIO_DYN_LINK)
// Export if this is our own source, otherwise import.
#   if defined(ASIO_SOURCE)
#    define ASIO_DECL __declspec(dllexport)
#   else // defined(ASIO_SOURCE)
#    define ASIO_DECL __declspec(dllimport)
#   endif // defined(ASIO_SOURCE)
#  endif // defined(ASIO_DYN_LINK)
# endif // defined(_MSC_VER) || defined(__BORLANDC__) || defined(__CODEGEARC__)
#endif // defined(ASIO_HEADER_ONLY)

// If ASIO_DECL isn't defined yet define it now.
#if !defined(ASIO_DECL)
# define ASIO_DECL
#endif // !defined(ASIO_DECL)

// Helper macro for documentation.
#define ASIO_UNSPECIFIED(e) e

// Microsoft Visual C++ detection.
#if !defined(ASIO_MSVC)
# if defined(_MSC_VER) && (defined(__INTELLISENSE__) \
      || (!defined(__MWERKS__) && !defined(__EDG_VERSION__)))
#  define ASIO_MSVC _MSC_VER
# endif // defined(_MSC_VER) && (defined(__INTELLISENSE__)
        //   || (!defined(__MWERKS__) && !defined(__EDG_VERSION__)))
#endif // !defined(ASIO_MSVC)

// Clang / libc++ detection.
#if defined(__clang__)
# if (__cplusplus >= 201103)
#  if __has_include(<__config>)
#   include <__config>
#   if defined(_LIBCPP_VERSION)
#    define ASIO_HAS_CLANG_LIBCXX 1
#   endif // defined(_LIBCPP_VERSION)
#  endif // __has_include(<__config>)
# endif // (__cplusplus >= 201103)
#endif // defined(__clang__)

// Android platform detection.
#if defined(__ANDROID__)
# include <android/api-level.h>
#endif // defined(__ANDROID__)

// C++11: Support move construction and assignment on compilers known to allow it.
#define ASIO_HAS_MOVE 1

// Define
// * ASIO_MOVE_ARG,
// * ASIO_NONDEDUCED_MOVE_ARG, and
// * ASIO_MOVE_CAST
// to take advantage of rvalue references and perfect forwarding.
#define ASIO_MOVE_ARG(type) type&&
#define ASIO_MOVE_ARG2(type1, type2) type1, type2&&
#define ASIO_NONDEDUCED_MOVE_ARG(type) type&
#define ASIO_MOVE_CAST(type) static_cast<type&&>
#define ASIO_MOVE_CAST2(type1, type2) static_cast<type1, type2&&>
#define ASIO_MOVE_OR_LVALUE(type) static_cast<type&&>
#define ASIO_MOVE_OR_LVALUE_TYPE(type) type

// C++11: Support variadic templates on compilers known to allow it.
#define ASIO_HAS_VARIADIC_TEMPLATES 1

// C++11: Support constexpr on compilers known to allow it.
#define ASIO_HAS_CONSTEXPR 1
# define ASIO_STATIC_CONSTEXPR(type, assignment) \
    static constexpr type assignment
#if defined(ASIO_MSVC)
# define ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(type, name) \
     static const type name
#else // defined(ASIO_MSVC)
# define ASIO_STATIC_CONSTEXPR_DEFAULT_INIT(type, name) \
     static constexpr const type name{}
#endif // defined(ASIO_MSVC)

// C++11: Support noexcept on compilers known to allow it.
#define ASIO_HAS_NOEXCEPT 1

// Support noexcept on function types on compilers known to allow it.
#if !defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
# if !defined(ASIO_DISABLE_NOEXCEPT_FUNCTION_TYPE)
#  if defined(__clang__)
#   if (__cplusplus >= 202002)
#    define ASIO_HAS_NOEXCEPT_FUNCTION_TYPE 1
#   endif // (__cplusplus >= 202002)
#  elif defined(__GNUC__)
#   if (__cplusplus >= 202002)
#    define ASIO_HAS_NOEXCEPT_FUNCTION_TYPE 1
#   endif // (__cplusplus >= 202002)
#  elif defined(ASIO_MSVC)
#   if (_MSC_VER >= 1900 && _MSVC_LANG >= 202002)
#    define ASIO_HAS_NOEXCEPT_FUNCTION_TYPE 1
#   endif // (_MSC_VER >= 1900 && _MSVC_LANG >= 202002)
#  endif // defined(ASIO_MSVC)
# endif // !defined(ASIO_DISABLE_NOEXCEPT_FUNCTION_TYPE)
#endif // !defined(ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)

// C++11: Support automatic type deduction on compilers known to support it.
#define ASIO_HAS_DECLTYPE 1

// C++11: Support alias templates on compilers known to allow it.
#define ASIO_HAS_ALIAS_TEMPLATES 1

// C++14: Support return type deduction on compilers known to allow it.
#define ASIO_HAS_RETURN_TYPE_DEDUCTION 1

// C++11: Support default function template arguments on compilers known to allow it.
#define ASIO_HAS_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS 1

// C++11: Support enum classes on compilers known to allow them.
#define ASIO_HAS_ENUM_CLASS 1

// Support concepts on compilers known to allow them.
#if !defined(ASIO_HAS_CONCEPTS)
# if !defined(ASIO_DISABLE_CONCEPTS)
#  if defined(__cpp_concepts)
#   define ASIO_HAS_CONCEPTS 1
#   if (__cpp_concepts >= 201707)
#    define ASIO_CONCEPT concept
#   else // (__cpp_concepts >= 201707)
#    define ASIO_CONCEPT concept bool
#   endif // (__cpp_concepts >= 201707)
#  endif // defined(__cpp_concepts)
# endif // !defined(ASIO_DISABLE_CONCEPTS)
#endif // !defined(ASIO_HAS_CONCEPTS)

// C++14: Support template variables on compilers known to allow it.
#define ASIO_HAS_VARIABLE_TEMPLATES 1

// Support SFINAEd template variables on compilers known to allow it.
#if !defined(ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
# if !defined(ASIO_DISABLE_SFINAE_VARIABLE_TEMPLATES)
#  if defined(__clang__)
#   if (__cplusplus >= 201703)
#    if __has_feature(__cxx_variable_templates__)
#     define ASIO_HAS_SFINAE_VARIABLE_TEMPLATES 1
#    endif // __has_feature(__cxx_variable_templates__)
#   endif // (__cplusplus >= 201703)
#  elif defined(__GNUC__)
#   if ((__GNUC__ == 8) && (__GNUC_MINOR__ >= 4)) || (__GNUC__ > 8)
#    if (__cplusplus >= 201402)
#     define ASIO_HAS_SFINAE_VARIABLE_TEMPLATES 1
#    endif // (__cplusplus >= 201402)
#   endif // ((__GNUC__ == 8) && (__GNUC_MINOR__ >= 4)) || (__GNUC__ > 8)
#  endif // defined(__GNUC__)
#  if defined(ASIO_MSVC)
#   if (_MSC_VER >= 1901)
#    define ASIO_HAS_SFINAE_VARIABLE_TEMPLATES 1
#   endif // (_MSC_VER >= 1901)
#  endif // defined(ASIO_MSVC)
# endif // !defined(ASIO_DISABLE_SFINAE_VARIABLE_TEMPLATES)
#endif // !defined(ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

// Support SFINAE use of constant expressions on compilers known to allow it.
#if !defined(ASIO_HAS_CONSTANT_EXPRESSION_SFINAE)
# if !defined(ASIO_DISABLE_CONSTANT_EXPRESSION_SFINAE)
#  if defined(__clang__)
#   if (__cplusplus >= 201402)
#    define ASIO_HAS_CONSTANT_EXPRESSION_SFINAE 1
#   endif // (__cplusplus >= 201402)
#  elif defined(__GNUC__) && !defined(__INTEL_COMPILER)
#   if (__GNUC__ >= 7)
#    if (__cplusplus >= 201402)
#     define ASIO_HAS_CONSTANT_EXPRESSION_SFINAE 1
#    endif // (__cplusplus >= 201402)
#   endif // (__GNUC__ >= 7)
#  endif // defined(__GNUC__) && !defined(__INTEL_COMPILER)
#  if defined(ASIO_MSVC)
#   if (_MSC_VER >= 1901)
#    define ASIO_HAS_CONSTANT_EXPRESSION_SFINAE 1
#   endif // (_MSC_VER >= 1901)
#  endif // defined(ASIO_MSVC)
# endif // !defined(ASIO_DISABLE_CONSTANT_EXPRESSION_SFINAE)
#endif // !defined(ASIO_HAS_CONSTANT_EXPRESSION_SFINAE)

// Enable workarounds for lack of working expression SFINAE.
#if !defined(ASIO_HAS_WORKING_EXPRESSION_SFINAE)
# if !defined(ASIO_DISABLE_WORKING_EXPRESSION_SFINAE)
#  if !defined(ASIO_MSVC) && !defined(__INTEL_COMPILER)
#   if (__cplusplus >= 201103)
#    define ASIO_HAS_WORKING_EXPRESSION_SFINAE 1
#   endif // (__cplusplus >= 201103)
#  elif defined(ASIO_MSVC) && (_MSC_VER >= 1929)
#   if (_MSVC_LANG >= 202000)
#    define ASIO_HAS_WORKING_EXPRESSION_SFINAE 1
#   endif // (_MSVC_LANG >= 202000)
#  endif // defined(ASIO_MSVC) && (_MSC_VER >= 1929)
# endif // !defined(ASIO_DISABLE_WORKING_EXPRESSION_SFINAE)
#endif // !defined(ASIO_HAS_WORKING_EXPRESSION_SFINAE)

// C++11: Support ref-qualified functions on compilers known to allow it.
#define ASIO_HAS_REF_QUALIFIED_FUNCTIONS 1

// C++11: Support for the alignof operator.
#define ASIO_HAS_ALIGNOF 1
#if defined(__STDCPP_DEFAULT_NEW_ALIGNMENT__)
# define ASIO_DEFAULT_ALIGN __STDCPP_DEFAULT_NEW_ALIGNMENT__
#else // defined(__STDCPP_DEFAULT_NEW_ALIGNMENT__)
# define ASIO_DEFAULT_ALIGN alignof(std::max_align_t)
#endif // defined(__STDCPP_DEFAULT_NEW_ALIGNMENT__)

// Standard library support for aligned allocation.
#if !defined(ASIO_HAS_STD_ALIGNED_ALLOC)
# if !defined(ASIO_DISABLE_STD_ALIGNED_ALLOC)
#  if (__cplusplus >= 201703)
#   if defined(__clang__)
#    if defined(ASIO_HAS_CLANG_LIBCXX)
#     if (_LIBCPP_STD_VER > 14) && defined(_LIBCPP_HAS_ALIGNED_ALLOC) \
        && !defined(_LIBCPP_MSVCRT) && !defined(__MINGW32__)
#      define ASIO_HAS_STD_ALIGNED_ALLOC 1
#     endif // (_LIBCPP_STD_VER > 14) && defined(_LIBCPP_HAS_ALIGNED_ALLOC)
            //   && !defined(_LIBCPP_MSVCRT) && !defined(__MINGW32__)
#    elif defined(_GLIBCXX_HAVE_ALIGNED_ALLOC)
#     define ASIO_HAS_STD_ALIGNED_ALLOC 1
#    endif // defined(_GLIBCXX_HAVE_ALIGNED_ALLOC)
#   elif defined(__GNUC__)
#    if defined(_GLIBCXX_HAVE_ALIGNED_ALLOC)
#     define ASIO_HAS_STD_ALIGNED_ALLOC 1
#    endif // defined(_GLIBCXX_HAVE_ALIGNED_ALLOC)
#   endif // defined(__GNUC__)
#  endif // (__cplusplus >= 201703)
# endif // !defined(ASIO_DISABLE_STD_ALIGNED_ALLOC)
#endif // !defined(ASIO_HAS_STD_ALIGNED_ALLOC)

// C++11: Standard library support for system errors.
#define ASIO_HAS_STD_SYSTEM_ERROR 1

// C++11: Standard library support for arrays.
#define ASIO_HAS_STD_ARRAY 1

// C++11: Standard library support for shared_ptr and weak_ptr.
#define ASIO_HAS_STD_SHARED_PTR 1

// C++11: Standard library support for allocator_arg_t.
#define ASIO_HAS_STD_ALLOCATOR_ARG 1

// C++11: Standard library support for atomic operations.
#define ASIO_HAS_STD_ATOMIC 1

// C++11: Standard library support for chrono.
#define ASIO_HAS_STD_CHRONO 1
#define ASIO_HAS_CHRONO 1

// C++11: Standard library support for addressof.
#define ASIO_HAS_STD_ADDRESSOF 1

// C++11: Standard library support for the function class.
#define ASIO_HAS_STD_FUNCTION 1

// C++11: Standard library support for the reference_wrapper class.
#define ASIO_HAS_STD_REFERENCE_WRAPPER 1

// C++11: Standard library support for type traits.
#define ASIO_HAS_STD_TYPE_TRAITS 1

// C++11: Standard library support for the nullptr_t type.
#define ASIO_HAS_NULLPTR 1

// C++11: Standard library support for the C++11 allocator additions.
#define ASIO_HAS_CXX11_ALLOCATORS 1

// C++11: Standard library support for the cstdint header.
#define ASIO_HAS_CSTDINT 1

// C++11: Standard library support for the thread class.
#define ASIO_HAS_STD_THREAD 1

// C++11: Standard library support for the mutex and condition variable classes.
#define ASIO_HAS_STD_MUTEX_AND_CONDVAR 1

// C++11: Standard library support for the call_once function.
#define ASIO_HAS_STD_CALL_ONCE 1

// C++11: Standard library support for futures.
#define ASIO_HAS_STD_FUTURE 1

// Standard library support for std::string_view.
#if !defined(ASIO_HAS_STD_STRING_VIEW)
# if !defined(ASIO_DISABLE_STD_STRING_VIEW)
#  if defined(__clang__)
#   if defined(ASIO_HAS_CLANG_LIBCXX)
#    if (__cplusplus >= 201402)
#     if __has_include(<string_view>)
#      define ASIO_HAS_STD_STRING_VIEW 1
#     endif // __has_include(<string_view>)
#    endif // (__cplusplus >= 201402)
#   else // defined(ASIO_HAS_CLANG_LIBCXX)
#    if (__cplusplus >= 201703)
#     if __has_include(<string_view>)
#      define ASIO_HAS_STD_STRING_VIEW 1
#     endif // __has_include(<string_view>)
#    endif // (__cplusplus >= 201703)
#   endif // defined(ASIO_HAS_CLANG_LIBCXX)
#  elif defined(__GNUC__)
#   if (__GNUC__ >= 7)
#    if (__cplusplus >= 201703)
#     define ASIO_HAS_STD_STRING_VIEW 1
#    endif // (__cplusplus >= 201703)
#   endif // (__GNUC__ >= 7)
#  elif defined(ASIO_MSVC)
#   if (_MSC_VER >= 1910 && _MSVC_LANG >= 201703)
#    define ASIO_HAS_STD_STRING_VIEW 1
#   endif // (_MSC_VER >= 1910 && _MSVC_LANG >= 201703)
#  endif // defined(ASIO_MSVC)
# endif // !defined(ASIO_DISABLE_STD_STRING_VIEW)
#endif // !defined(ASIO_HAS_STD_STRING_VIEW)

// Standard library support for std::experimental::string_view.
#if !defined(ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
# if !defined(ASIO_DISABLE_STD_EXPERIMENTAL_STRING_VIEW)
#  if defined(__clang__)
#   if defined(ASIO_HAS_CLANG_LIBCXX)
#    if (_LIBCPP_VERSION < 7000)
#     if (__cplusplus >= 201402)
#      if __has_include(<experimental/string_view>)
#       define ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW 1
#      endif // __has_include(<experimental/string_view>)
#     endif // (__cplusplus >= 201402)
#    endif // (_LIBCPP_VERSION < 7000)
#   else // defined(ASIO_HAS_CLANG_LIBCXX)
#    if (__cplusplus >= 201402)
#     if __has_include(<experimental/string_view>)
#      define ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW 1
#     endif // __has_include(<experimental/string_view>)
#    endif // (__cplusplus >= 201402)
#   endif // // defined(ASIO_HAS_CLANG_LIBCXX)
#  elif defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201402)
#     define ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW 1
#    endif // (__cplusplus >= 201402)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
# endif // !defined(ASIO_DISABLE_STD_EXPERIMENTAL_STRING_VIEW)
#endif // !defined(ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)

// Standard library has a string_view that we can use.
#if !defined(ASIO_HAS_STRING_VIEW)
# if !defined(ASIO_DISABLE_STRING_VIEW)
#  if defined(ASIO_HAS_STD_STRING_VIEW)
#   define ASIO_HAS_STRING_VIEW 1
#  elif defined(ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
#   define ASIO_HAS_STRING_VIEW 1
#  endif // defined(ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
# endif // !defined(ASIO_DISABLE_STRING_VIEW)
#endif // !defined(ASIO_HAS_STRING_VIEW)

// C++11: Standard library support for iostream move construction and assignment.
#define ASIO_HAS_STD_IOSTREAM_MOVE 1

// Standard library has invoke_result (which supersedes result_of).
#if !defined(ASIO_HAS_STD_INVOKE_RESULT)
# if !defined(ASIO_DISABLE_STD_INVOKE_RESULT)
#  if defined(ASIO_MSVC)
#   if (_MSC_VER >= 1911 && _MSVC_LANG >= 201703)
#    define ASIO_HAS_STD_INVOKE_RESULT 1
#   endif // (_MSC_VER >= 1911 && _MSVC_LANG >= 201703)
#  endif // defined(ASIO_MSVC)
#  if defined(ASIO_HAS_CLANG_LIBCXX)
#   if (_LIBCPP_VERSION >= 13000)
#    if (__cplusplus >= 202002)
#     define ASIO_HAS_STD_INVOKE_RESULT 1
#    endif // (__cplusplus >= 202002)
#   endif // (_LIBCPP_VERSION >= 13000)
#  endif // defined(ASIO_HAS_CLANG_LIBCXX)
# endif // !defined(ASIO_DISABLE_STD_INVOKE_RESULT)
#endif // !defined(ASIO_HAS_STD_INVOKE_RESULT)

// C++11: Standard library support for std::exception_ptr and std::current_exception.
#define ASIO_HAS_STD_EXCEPTION_PTR 1

// C++11: Standard library support for std::nested_exception.
#define ASIO_HAS_STD_NESTED_EXCEPTION 1

// Standard library support for std::any.
#if !defined(ASIO_HAS_STD_ANY)
# if !defined(ASIO_DISABLE_STD_ANY)
#  if defined(__clang__)
#   if (__cplusplus >= 201703)
#    if __has_include(<any>)
#     define ASIO_HAS_STD_ANY 1
#    endif // __has_include(<any>)
#   endif // (__cplusplus >= 201703)
#  elif defined(__GNUC__)
#   if (__GNUC__ >= 7)
#    if (__cplusplus >= 201703)
#     define ASIO_HAS_STD_ANY 1
#    endif // (__cplusplus >= 201703)
#   endif // (__GNUC__ >= 7)
#  endif // defined(__GNUC__)
#  if defined(ASIO_MSVC)
#   if (_MSC_VER >= 1910) && (_MSVC_LANG >= 201703)
#    define ASIO_HAS_STD_ANY 1
#   endif // (_MSC_VER >= 1910) && (_MSVC_LANG >= 201703)
#  endif // defined(ASIO_MSVC)
# endif // !defined(ASIO_DISABLE_STD_ANY)
#endif // !defined(ASIO_HAS_STD_ANY)

// Standard library support for std::source_location.
#if !defined(ASIO_HAS_STD_SOURCE_LOCATION)
# if !defined(ASIO_DISABLE_STD_SOURCE_LOCATION)
// ...
# endif // !defined(ASIO_DISABLE_STD_SOURCE_LOCATION)
#endif // !defined(ASIO_HAS_STD_SOURCE_LOCATION)

// Standard library support for std::experimental::source_location.
#if !defined(ASIO_HAS_STD_EXPERIMENTAL_SOURCE_LOCATION)
# if !defined(ASIO_DISABLE_STD_EXPERIMENTAL_SOURCE_LOCATION)
#  if defined(__GNUC__)
#   if (__cplusplus >= 201709)
#    if __has_include(<experimental/source_location>)
#     define ASIO_HAS_STD_EXPERIMENTAL_SOURCE_LOCATION 1
#    endif // __has_include(<experimental/source_location>)
#   endif // (__cplusplus >= 201709)
#  endif // defined(__GNUC__)
# endif // !defined(ASIO_DISABLE_STD_EXPERIMENTAL_SOURCE_LOCATION)
#endif // !defined(ASIO_HAS_STD_EXPERIMENTAL_SOURCE_LOCATION)

// Standard library has a source_location that we can use.
#if !defined(ASIO_HAS_SOURCE_LOCATION)
# if !defined(ASIO_DISABLE_SOURCE_LOCATION)
#  if defined(ASIO_HAS_STD_SOURCE_LOCATION)
#   define ASIO_HAS_SOURCE_LOCATION 1
#  elif defined(ASIO_HAS_STD_EXPERIMENTAL_SOURCE_LOCATION)
#   define ASIO_HAS_SOURCE_LOCATION 1
#  endif // defined(ASIO_HAS_STD_EXPERIMENTAL_SOURCE_LOCATION)
# endif // !defined(ASIO_DISABLE_SOURCE_LOCATION)
#endif // !defined(ASIO_HAS_SOURCE_LOCATION)

// Windows App target. Windows but with a limited API.
#if !defined(ASIO_WINDOWS_APP)
# if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0603)
#  include <winapifamily.h>
#  if (WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) \
       || WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_TV_TITLE)) \
   && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#   define ASIO_WINDOWS_APP 1
#  endif // WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
         // && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
# endif // defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0603)
#endif // !defined(ASIO_WINDOWS_APP)

// Legacy WinRT target. Windows App is preferred.
#if !defined(ASIO_WINDOWS_RUNTIME)
# if !defined(ASIO_WINDOWS_APP)
#  if defined(__cplusplus_winrt)
#   include <winapifamily.h>
#   if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) \
    && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#    define ASIO_WINDOWS_RUNTIME 1
#   endif // WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
          // && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#  endif // defined(__cplusplus_winrt)
# endif // !defined(ASIO_WINDOWS_APP)
#endif // !defined(ASIO_WINDOWS_RUNTIME)

// Windows target. Excludes WinRT but includes Windows App targets.
#if !defined(ASIO_WINDOWS)
# if !defined(ASIO_WINDOWS_RUNTIME)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   define ASIO_WINDOWS 1
#  elif defined(ASIO_WINDOWS_APP)
#   define ASIO_WINDOWS 1
#  endif // defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
# endif // !defined(ASIO_WINDOWS_RUNTIME)
#endif // !defined(ASIO_WINDOWS)

// Windows: target OS version.
#if defined(ASIO_WINDOWS) || defined(__CYGWIN__)
# if !defined(_WIN32_WINNT) && !defined(_WIN32_WINDOWS)
#  if defined(_MSC_VER) || (defined(__BORLANDC__) && !defined(__clang__))
#   pragma message( \
  "Please define _WIN32_WINNT or _WIN32_WINDOWS appropriately. For example:\n"\
  "- add -D_WIN32_WINNT=0x0601 to the compiler command line; or\n"\
  "- add _WIN32_WINNT=0x0601 to your project's Preprocessor Definitions.\n"\
  "Assuming _WIN32_WINNT=0x0601 (i.e. Windows 7 target).")
#  else // defined(_MSC_VER) || (defined(__BORLANDC__) && !defined(__clang__))
#   warning Please define _WIN32_WINNT or _WIN32_WINDOWS appropriately.
#   warning For example, add -D_WIN32_WINNT=0x0601 to the compiler command line.
#   warning Assuming _WIN32_WINNT=0x0601 (i.e. Windows 7 target).
#  endif // defined(_MSC_VER) || (defined(__BORLANDC__) && !defined(__clang__))
#  define _WIN32_WINNT 0x0601
# endif // !defined(_WIN32_WINNT) && !defined(_WIN32_WINDOWS)
# if defined(_MSC_VER)
#  if defined(_WIN32) && !defined(WIN32)
#   if !defined(_WINSOCK2API_)
#    define WIN32 // Needed for correct types in winsock2.h
#   else // !defined(_WINSOCK2API_)
#    error Please define the macro WIN32 in your compiler options
#   endif // !defined(_WINSOCK2API_)
#  endif // defined(_WIN32) && !defined(WIN32)
# endif // defined(_MSC_VER)
# if defined(__BORLANDC__)
#  if defined(__WIN32__) && !defined(WIN32)
#   if !defined(_WINSOCK2API_)
#    define WIN32 // Needed for correct types in winsock2.h
#   else // !defined(_WINSOCK2API_)
#    error Please define the macro WIN32 in your compiler options
#   endif // !defined(_WINSOCK2API_)
#  endif // defined(__WIN32__) && !defined(WIN32)
# endif // defined(__BORLANDC__)
# if defined(__CYGWIN__)
#  if !defined(__USE_W32_SOCKETS)
#   error You must add -D__USE_W32_SOCKETS to your compiler options.
#  endif // !defined(__USE_W32_SOCKETS)
# endif // defined(__CYGWIN__)
#endif // defined(ASIO_WINDOWS) || defined(__CYGWIN__)

// Windows: minimise header inclusion.
#if defined(ASIO_WINDOWS) || defined(__CYGWIN__)
# if !defined(ASIO_NO_WIN32_LEAN_AND_MEAN)
#  if !defined(WIN32_LEAN_AND_MEAN)
#   define WIN32_LEAN_AND_MEAN
#  endif // !defined(WIN32_LEAN_AND_MEAN)
# endif // !defined(ASIO_NO_WIN32_LEAN_AND_MEAN)
#endif // defined(ASIO_WINDOWS) || defined(__CYGWIN__)

// Windows: suppress definition of "min" and "max" macros.
#if defined(ASIO_WINDOWS) || defined(__CYGWIN__)
# if !defined(ASIO_NO_NOMINMAX)
#  if !defined(NOMINMAX)
#   define NOMINMAX 1
#  endif // !defined(NOMINMAX)
# endif // !defined(ASIO_NO_NOMINMAX)
#endif // defined(ASIO_WINDOWS) || defined(__CYGWIN__)

// Windows: IO Completion Ports.
#if !defined(ASIO_HAS_IOCP)
# if defined(ASIO_WINDOWS) || defined(__CYGWIN__)
#  if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400)
#   if !defined(UNDER_CE) && !defined(ASIO_WINDOWS_APP)
#    if !defined(ASIO_DISABLE_IOCP)
#     define ASIO_HAS_IOCP 1
#    endif // !defined(ASIO_DISABLE_IOCP)
#   endif // !defined(UNDER_CE) && !defined(ASIO_WINDOWS_APP)
#  endif // defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400)
# endif // defined(ASIO_WINDOWS) || defined(__CYGWIN__)
#endif // !defined(ASIO_HAS_IOCP)

// On POSIX (and POSIX-like) platforms we need to include unistd.h in order to
// get access to the various platform feature macros, e.g. to be able to test
// for threads support.
#if !defined(ASIO_HAS_UNISTD_H)
# if defined(unix) \
  || defined(__unix) \
  || defined(_XOPEN_SOURCE) \
  || defined(_POSIX_SOURCE) \
  || (defined(__MACH__) && defined(__APPLE__)) \
  || defined(__FreeBSD__) \
  || defined(__NetBSD__) \
  || defined(__OpenBSD__) \
  || defined(__linux__) \
  || defined(__HAIKU__)
#  define ASIO_HAS_UNISTD_H 1
# endif
#endif // !defined(ASIO_HAS_UNISTD_H)
#if defined(ASIO_HAS_UNISTD_H)
# include <unistd.h>
#endif // defined(ASIO_HAS_UNISTD_H)

// Linux: epoll, eventfd and timerfd.
#if defined(__linux__)
# include <linux/version.h>
# if !defined(ASIO_HAS_EPOLL)
#  if !defined(ASIO_DISABLE_EPOLL)
#   if LINUX_VERSION_CODE >= KERNEL_VERSION(2,5,45)
#    define ASIO_HAS_EPOLL 1
#   endif // LINUX_VERSION_CODE >= KERNEL_VERSION(2,5,45)
#  endif // !defined(ASIO_DISABLE_EPOLL)
# endif // !defined(ASIO_HAS_EPOLL)
# if !defined(ASIO_HAS_EVENTFD)
#  if !defined(ASIO_DISABLE_EVENTFD)
#   if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
#    define ASIO_HAS_EVENTFD 1
#   endif // LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
#  endif // !defined(ASIO_DISABLE_EVENTFD)
# endif // !defined(ASIO_HAS_EVENTFD)
# if !defined(ASIO_HAS_TIMERFD)
#  if defined(ASIO_HAS_EPOLL)
#   if (__GLIBC__ > 2) || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 8)
#    define ASIO_HAS_TIMERFD 1
#   endif // (__GLIBC__ > 2) || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 8)
#  endif // defined(ASIO_HAS_EPOLL)
# endif // !defined(ASIO_HAS_TIMERFD)
#endif // defined(__linux__)

// Linux: io_uring is used instead of epoll.
#if !defined(ASIO_HAS_IO_URING_AS_DEFAULT)
# if !defined(ASIO_HAS_EPOLL) && defined(ASIO_HAS_IO_URING)
#  define ASIO_HAS_IO_URING_AS_DEFAULT 1
# endif // !defined(ASIO_HAS_EPOLL) && defined(ASIO_HAS_IO_URING)
#endif // !defined(ASIO_HAS_IO_URING_AS_DEFAULT)

// Mac OS X, FreeBSD, NetBSD, OpenBSD: kqueue.
#if (defined(__MACH__) && defined(__APPLE__)) \
  || defined(__FreeBSD__) \
  || defined(__NetBSD__) \
  || defined(__OpenBSD__)
# if !defined(ASIO_HAS_KQUEUE)
#  if !defined(ASIO_DISABLE_KQUEUE)
#   define ASIO_HAS_KQUEUE 1
#  endif // !defined(ASIO_DISABLE_KQUEUE)
# endif // !defined(ASIO_HAS_KQUEUE)
#endif // (defined(__MACH__) && defined(__APPLE__))
       //   || defined(__FreeBSD__)
       //   || defined(__NetBSD__)
       //   || defined(__OpenBSD__)

// Solaris: /dev/poll.
#if defined(__sun)
# if !defined(ASIO_HAS_DEV_POLL)
#  if !defined(ASIO_DISABLE_DEV_POLL)
#   define ASIO_HAS_DEV_POLL 1
#  endif // !defined(ASIO_DISABLE_DEV_POLL)
# endif // !defined(ASIO_HAS_DEV_POLL)
#endif // defined(__sun)

// Serial ports.
#if !defined(ASIO_HAS_SERIAL_PORT)
# if defined(ASIO_HAS_IOCP) \
  || !defined(ASIO_WINDOWS) \
  && !defined(ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
#  if !defined(__SYMBIAN32__)
#   if !defined(ASIO_DISABLE_SERIAL_PORT)
#    define ASIO_HAS_SERIAL_PORT 1
#   endif // !defined(ASIO_DISABLE_SERIAL_PORT)
#  endif // !defined(__SYMBIAN32__)
# endif // defined(ASIO_HAS_IOCP)
        //   || !defined(ASIO_WINDOWS)
        //   && !defined(ASIO_WINDOWS_RUNTIME)
        //   && !defined(__CYGWIN__)
#endif // !defined(ASIO_HAS_SERIAL_PORT)

// Windows: stream handles.
#if !defined(ASIO_HAS_WINDOWS_STREAM_HANDLE)
# if !defined(ASIO_DISABLE_WINDOWS_STREAM_HANDLE)
#  if defined(ASIO_HAS_IOCP)
#   define ASIO_HAS_WINDOWS_STREAM_HANDLE 1
#  endif // defined(ASIO_HAS_IOCP)
# endif // !defined(ASIO_DISABLE_WINDOWS_STREAM_HANDLE)
#endif // !defined(ASIO_HAS_WINDOWS_STREAM_HANDLE)

// Windows: random access handles.
#if !defined(ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
# if !defined(ASIO_DISABLE_WINDOWS_RANDOM_ACCESS_HANDLE)
#  if defined(ASIO_HAS_IOCP)
#   define ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE 1
#  endif // defined(ASIO_HAS_IOCP)
# endif // !defined(ASIO_DISABLE_WINDOWS_RANDOM_ACCESS_HANDLE)
#endif // !defined(ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)

// Windows: object handles.
#if !defined(ASIO_HAS_WINDOWS_OBJECT_HANDLE)
# if !defined(ASIO_DISABLE_WINDOWS_OBJECT_HANDLE)
#  if defined(ASIO_WINDOWS) || defined(__CYGWIN__)
#   if !defined(UNDER_CE) && !defined(ASIO_WINDOWS_APP)
#    define ASIO_HAS_WINDOWS_OBJECT_HANDLE 1
#   endif // !defined(UNDER_CE) && !defined(ASIO_WINDOWS_APP)
#  endif // defined(ASIO_WINDOWS) || defined(__CYGWIN__)
# endif // !defined(ASIO_DISABLE_WINDOWS_OBJECT_HANDLE)
#endif // !defined(ASIO_HAS_WINDOWS_OBJECT_HANDLE)

// Windows: OVERLAPPED wrapper.
#if !defined(ASIO_HAS_WINDOWS_OVERLAPPED_PTR)
# if !defined(ASIO_DISABLE_WINDOWS_OVERLAPPED_PTR)
#  if defined(ASIO_HAS_IOCP)
#   define ASIO_HAS_WINDOWS_OVERLAPPED_PTR 1
#  endif // defined(ASIO_HAS_IOCP)
# endif // !defined(ASIO_DISABLE_WINDOWS_OVERLAPPED_PTR)
#endif // !defined(ASIO_HAS_WINDOWS_OVERLAPPED_PTR)

// POSIX: stream-oriented file descriptors.
#if !defined(ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
# if !defined(ASIO_DISABLE_POSIX_STREAM_DESCRIPTOR)
#  if !defined(ASIO_WINDOWS) \
  && !defined(ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
#   define ASIO_HAS_POSIX_STREAM_DESCRIPTOR 1
#  endif // !defined(ASIO_WINDOWS)
         //   && !defined(ASIO_WINDOWS_RUNTIME)
         //   && !defined(__CYGWIN__)
# endif // !defined(ASIO_DISABLE_POSIX_STREAM_DESCRIPTOR)
#endif // !defined(ASIO_HAS_POSIX_STREAM_DESCRIPTOR)

// UNIX domain sockets.
#if !defined(ASIO_HAS_LOCAL_SOCKETS)
# if !defined(ASIO_DISABLE_LOCAL_SOCKETS)
#  if !defined(ASIO_WINDOWS_RUNTIME)
#   define ASIO_HAS_LOCAL_SOCKETS 1
#  endif // !defined(ASIO_WINDOWS_RUNTIME)
# endif // !defined(ASIO_DISABLE_LOCAL_SOCKETS)
#endif // !defined(ASIO_HAS_LOCAL_SOCKETS)

// Files.
#if !defined(ASIO_HAS_FILE)
# if !defined(ASIO_DISABLE_FILE)
#  if defined(ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
#   define ASIO_HAS_FILE 1
#  elif defined(ASIO_HAS_IO_URING)
#   define ASIO_HAS_FILE 1
#  endif // defined(ASIO_HAS_IO_URING)
# endif // !defined(ASIO_DISABLE_FILE)
#endif // !defined(ASIO_HAS_FILE)

// Pipes.
#if !defined(ASIO_HAS_PIPE)
# if defined(ASIO_HAS_IOCP) \
  || !defined(ASIO_WINDOWS) \
  && !defined(ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
#  if !defined(__SYMBIAN32__)
#   if !defined(ASIO_DISABLE_PIPE)
#    define ASIO_HAS_PIPE 1
#   endif // !defined(ASIO_DISABLE_PIPE)
#  endif // !defined(__SYMBIAN32__)
# endif // defined(ASIO_HAS_IOCP)
        //   || !defined(ASIO_WINDOWS)
        //   && !defined(ASIO_WINDOWS_RUNTIME)
        //   && !defined(__CYGWIN__)
#endif // !defined(ASIO_HAS_PIPE)

// Can use sigaction() instead of signal().
#if !defined(ASIO_HAS_SIGACTION)
# if !defined(ASIO_DISABLE_SIGACTION)
#  if !defined(ASIO_WINDOWS) \
  && !defined(ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
#   define ASIO_HAS_SIGACTION 1
#  endif // !defined(ASIO_WINDOWS)
         //   && !defined(ASIO_WINDOWS_RUNTIME)
         //   && !defined(__CYGWIN__)
# endif // !defined(ASIO_DISABLE_SIGACTION)
#endif // !defined(ASIO_HAS_SIGACTION)

// Can use signal().
#if !defined(ASIO_HAS_SIGNAL)
# if !defined(ASIO_DISABLE_SIGNAL)
#  if !defined(UNDER_CE)
#   define ASIO_HAS_SIGNAL 1
#  endif // !defined(UNDER_CE)
# endif // !defined(ASIO_DISABLE_SIGNAL)
#endif // !defined(ASIO_HAS_SIGNAL)

// Can use getaddrinfo() and getnameinfo().
#if !defined(ASIO_HAS_GETADDRINFO)
# if !defined(ASIO_DISABLE_GETADDRINFO)
#  if defined(ASIO_WINDOWS) || defined(__CYGWIN__)
#   if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0501)
#    define ASIO_HAS_GETADDRINFO 1
#   elif defined(UNDER_CE)
#    define ASIO_HAS_GETADDRINFO 1
#   endif // defined(UNDER_CE)
#  elif defined(__MACH__) && defined(__APPLE__)
#   if defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#    if (__MAC_OS_X_VERSION_MIN_REQUIRED >= 1050)
#     define ASIO_HAS_GETADDRINFO 1
#    endif // (__MAC_OS_X_VERSION_MIN_REQUIRED >= 1050)
#   else // defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#    define ASIO_HAS_GETADDRINFO 1
#   endif // defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#  else // defined(__MACH__) && defined(__APPLE__)
#   define ASIO_HAS_GETADDRINFO 1
#  endif // defined(__MACH__) && defined(__APPLE__)
# endif // !defined(ASIO_DISABLE_GETADDRINFO)
#endif // !defined(ASIO_HAS_GETADDRINFO)

// Whether standard iostreams are disabled.
//#define ASIO_NO_IOSTREAM 1

// Whether exception handling is disabled.
//#define ASIO_NO_EXCEPTIONS 1

// Threads.
#if !defined(ASIO_HAS_THREADS)
# if !defined(ASIO_DISABLE_THREADS)
#  if defined(__GNUC__) && !defined(__MINGW32__) \
     && !defined(linux) && !defined(__linux) && !defined(__linux__)
#   define ASIO_HAS_THREADS 1
#  elif defined(_MT) || defined(__MT__)
#   define ASIO_HAS_THREADS 1
#  elif defined(_REENTRANT)
#   define ASIO_HAS_THREADS 1
#  elif defined(__APPLE__)
#   define ASIO_HAS_THREADS 1
#  elif defined(__HAIKU__)
#   define ASIO_HAS_THREADS 1
#  elif defined(_POSIX_THREADS) && (_POSIX_THREADS + 0 >= 0)
#   define ASIO_HAS_THREADS 1
#  elif defined(_PTHREADS)
#   define ASIO_HAS_THREADS 1
#  endif // defined(__GNUC__) && !defined(__MINGW32__)
         //   && !defined(linux) && !defined(__linux) && !defined(__linux__)
# endif // !defined(ASIO_DISABLE_THREADS)
#endif // !defined(ASIO_HAS_THREADS)

// POSIX threads.
#if !defined(ASIO_HAS_PTHREADS)
# if defined(ASIO_HAS_THREADS)
#  if defined(_POSIX_THREADS) && (_POSIX_THREADS + 0 >= 0)
#   define ASIO_HAS_PTHREADS 1
#  elif defined(__HAIKU__)
#   define ASIO_HAS_PTHREADS 1
#  endif // defined(_POSIX_THREADS) && (_POSIX_THREADS + 0 >= 0)
# endif // defined(ASIO_HAS_THREADS)
#endif // !defined(ASIO_HAS_PTHREADS)

// Helper to prevent macro expansion.
#define ASIO_PREVENT_MACRO_SUBSTITUTION

// Helper to define in-class constants.
#define ASIO_STATIC_CONSTANT(type, assignment) \
    static const type assignment

// Boost regex library.
#if !defined(ASIO_HAS_BOOST_REGEX)
# if !defined(ASIO_DISABLE_BOOST_REGEX)
#  define ASIO_HAS_BOOST_REGEX 1
# endif // !defined(ASIO_DISABLE_BOOST_REGEX)
#endif // !defined(ASIO_HAS_BOOST_REGEX)

// Microsoft Visual C++'s secure C runtime library.
#if !defined(ASIO_HAS_SECURE_RTL)
# if !defined(ASIO_DISABLE_SECURE_RTL)
#  if defined(ASIO_MSVC) \
    && (ASIO_MSVC >= 1400) \
    && !defined(UNDER_CE)
#   define ASIO_HAS_SECURE_RTL 1
#  endif // defined(ASIO_MSVC)
         // && (ASIO_MSVC >= 1400)
         // && !defined(UNDER_CE)
# endif // !defined(ASIO_DISABLE_SECURE_RTL)
#endif // !defined(ASIO_HAS_SECURE_RTL)

// Handler hooking. Disabled for ancient Borland C++ and gcc compilers.
#if !defined(ASIO_HAS_HANDLER_HOOKS)
# if !defined(ASIO_DISABLE_HANDLER_HOOKS)
#  if defined(__GNUC__)
#   if (__GNUC__ >= 3)
#    define ASIO_HAS_HANDLER_HOOKS 1
#   endif // (__GNUC__ >= 3)
#  elif !defined(__BORLANDC__) || defined(__clang__)
#   define ASIO_HAS_HANDLER_HOOKS 1
#  endif // !defined(__BORLANDC__) || defined(__clang__)
# endif // !defined(ASIO_DISABLE_HANDLER_HOOKS)
#endif // !defined(ASIO_HAS_HANDLER_HOOKS)

// Support for the __thread keyword extension.
#if !defined(ASIO_DISABLE_THREAD_KEYWORD_EXTENSION)
# if defined(__linux__)
#  if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#   if ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 3)
#    if !defined(__INTEL_COMPILER) && !defined(__ICL) \
       && !(defined(__clang__) && defined(__ANDROID__))
#     define ASIO_HAS_THREAD_KEYWORD_EXTENSION 1
#     define ASIO_THREAD_KEYWORD __thread
#    elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1100)
#     define ASIO_HAS_THREAD_KEYWORD_EXTENSION 1
#    endif // defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1100)
           // && !(defined(__clang__) && defined(__ANDROID__))
#   endif // ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 3)
#  endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
# endif // defined(__linux__)
# if defined(ASIO_MSVC) && defined(ASIO_WINDOWS_RUNTIME)
#  if (_MSC_VER >= 1700)
#   define ASIO_HAS_THREAD_KEYWORD_EXTENSION 1
#   define ASIO_THREAD_KEYWORD __declspec(thread)
#  endif // (_MSC_VER >= 1700)
# endif // defined(ASIO_MSVC) && defined(ASIO_WINDOWS_RUNTIME)
#endif // !defined(ASIO_DISABLE_THREAD_KEYWORD_EXTENSION)
#if !defined(ASIO_THREAD_KEYWORD)
# define ASIO_THREAD_KEYWORD __thread
#endif // !defined(ASIO_THREAD_KEYWORD)

// Support for POSIX ssize_t typedef.
#if !defined(ASIO_DISABLE_SSIZE_T)
# if defined(__linux__) \
   || (defined(__MACH__) && defined(__APPLE__))
#  define ASIO_HAS_SSIZE_T 1
# endif // defined(__linux__)
        //   || (defined(__MACH__) && defined(__APPLE__))
#endif // !defined(ASIO_DISABLE_SSIZE_T)

// Helper macros to manage transition away from error_code return values.
#define ASIO_NO_DEPRECATED 1
#define ASIO_SYNC_OP_VOID void
#define ASIO_SYNC_OP_VOID_RETURN(e) return

// Newer gcc, clang need special treatment to suppress unused typedef warnings.
#if defined(__clang__)
# if defined(__apple_build_version__)
#  if (__clang_major__ >= 7)
#   define ASIO_UNUSED_TYPEDEF __attribute__((__unused__))
#  endif // (__clang_major__ >= 7)
# elif ((__clang_major__ == 3) && (__clang_minor__ >= 6)) \
    || (__clang_major__ > 3)
#  define ASIO_UNUSED_TYPEDEF __attribute__((__unused__))
# endif // ((__clang_major__ == 3) && (__clang_minor__ >= 6))
        //   || (__clang_major__ > 3)
#elif defined(__GNUC__)
# if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4)
#  define ASIO_UNUSED_TYPEDEF __attribute__((__unused__))
# endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4)
#endif // defined(__GNUC__)
#if !defined(ASIO_UNUSED_TYPEDEF)
# define ASIO_UNUSED_TYPEDEF
#endif // !defined(ASIO_UNUSED_TYPEDEF)

// Some versions of gcc generate spurious warnings about unused variables.
#if defined(__GNUC__)
# if (__GNUC__ >= 4)
#  define ASIO_UNUSED_VARIABLE __attribute__((__unused__))
# endif // (__GNUC__ >= 4)
#endif // defined(__GNUC__)
#if !defined(ASIO_UNUSED_VARIABLE)
# define ASIO_UNUSED_VARIABLE
#endif // !defined(ASIO_UNUSED_VARIABLE)

// Support the co_await keyword on compilers known to allow it.
#if !defined(ASIO_HAS_CO_AWAIT)
# if !defined(ASIO_DISABLE_CO_AWAIT)
#  if defined(ASIO_MSVC)
#   if (_MSC_VER >= 1928) && (_MSVC_LANG >= 201705) && !defined(__clang__)
#    define ASIO_HAS_CO_AWAIT 1
#   elif (_MSC_FULL_VER >= 190023506)
#    if defined(_RESUMABLE_FUNCTIONS_SUPPORTED)
#     define ASIO_HAS_CO_AWAIT 1
#    endif // defined(_RESUMABLE_FUNCTIONS_SUPPORTED)
#   endif // (_MSC_FULL_VER >= 190023506)
#  elif defined(__clang__)
#   if (__cplusplus >= 201703) && (__cpp_coroutines >= 201703)
#    if __has_include(<experimental/coroutine>)
#     define ASIO_HAS_CO_AWAIT 1
#    endif // __has_include(<experimental/coroutine>)
#   endif // (__cplusplus >= 201703) && (__cpp_coroutines >= 201703)
#  elif defined(__GNUC__)
#   if (__cplusplus >= 201709) && (__cpp_impl_coroutine >= 201902)
#    if __has_include(<coroutine>)
#     define ASIO_HAS_CO_AWAIT 1
#    endif // __has_include(<coroutine>)
#   endif // (__cplusplus >= 201709) && (__cpp_impl_coroutine >= 201902)
#  endif // defined(__GNUC__)
# endif // !defined(ASIO_DISABLE_CO_AWAIT)
#endif // !defined(ASIO_HAS_CO_AWAIT)

// Standard library support for coroutines.
#if !defined(ASIO_HAS_STD_COROUTINE)
# if !defined(ASIO_DISABLE_STD_COROUTINE)
#  if defined(ASIO_MSVC)
#   if (_MSC_VER >= 1928) && (_MSVC_LANG >= 201705)
#    define ASIO_HAS_STD_COROUTINE 1
#   endif // (_MSC_VER >= 1928) && (_MSVC_LANG >= 201705)
#  endif // defined(ASIO_MSVC)
#  if defined(__GNUC__)
#   if (__cplusplus >= 201709) && (__cpp_impl_coroutine >= 201902)
#    if __has_include(<coroutine>)
#     define ASIO_HAS_STD_COROUTINE 1
#    endif // __has_include(<coroutine>)
#   endif // (__cplusplus >= 201709) && (__cpp_impl_coroutine >= 201902)
#  endif // defined(__GNUC__)
# endif // !defined(ASIO_DISABLE_STD_COROUTINE)
#endif // !defined(ASIO_HAS_STD_COROUTINE)

// Compiler support for the the [[nodiscard]] attribute.
#if !defined(ASIO_NODISCARD)
# if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(nodiscard)
#   if (__cplusplus >= 201703)
#    define ASIO_NODISCARD [[nodiscard]]
#   endif // (__cplusplus >= 201703)
#  endif // __has_cpp_attribute(nodiscard)
# endif // defined(__has_cpp_attribute)
#endif // !defined(ASIO_NODISCARD)
#if !defined(ASIO_NODISCARD)
# define ASIO_NODISCARD
#endif // !defined(ASIO_NODISCARD)

// Kernel support for MSG_NOSIGNAL.
#if !defined(ASIO_HAS_MSG_NOSIGNAL)
# if defined(__linux__)
#  define ASIO_HAS_MSG_NOSIGNAL 1
# elif defined(_POSIX_VERSION)
#  if (_POSIX_VERSION >= 200809L)
#   define ASIO_HAS_MSG_NOSIGNAL 1
#  endif // _POSIX_VERSION >= 200809L
# endif // defined(_POSIX_VERSION)
#endif // !defined(ASIO_HAS_MSG_NOSIGNAL)

// C++11: Standard library support for std::hash.
#define ASIO_HAS_STD_HASH 1

#endif // ASIO_DETAIL_CONFIG_HPP
