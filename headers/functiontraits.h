//
//  functiontraits.h
//  Practice Problems
//
//  Created by Sachit Vithaldas on 22/10/17.
//
//

#ifndef functiontraits_h
#define functiontraits_h

#pragma once

#include <cstddef>
#include <tuple>

namespace custom_traits
{
	template<class F>
	struct function_traits;

	// function pointer
	template<class R, class... Args>
	struct function_traits<R( * )( Args... )>
			: public function_traits<R( Args... )>
	{
	};

	template<class R, class... Args>
	struct function_traits<R( Args... )>
	{
		using return_type = R;

		static constexpr std::size_t arity = sizeof...( Args );

		template<std::size_t N>
		struct argument
		{
			static_assert( N < arity, "error: invalid parameter index." );
			using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
		};
	};

	// member function pointer
	template<class R, class C, class... Args>
	struct function_traits<R( C::* )( Args... )>
	{
		using return_type = R;

		static constexpr std::size_t arity = sizeof...( Args );

		template<std::size_t N>
		struct argument
		{
			static_assert( N < arity, "error: invalid parameter index." );
			using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
		};
	};

	// const member function pointer
	template<class R, class C, class... Args>
	struct function_traits<R( C::* )( Args... ) const>
			: public function_traits<R( C::* )( Args... )>
	{
	};

	// std::function
	template<class F>
	struct function_traits
	{
	private:
		using call_type = function_traits<decltype( &F::operator())>;
	public:
		using return_type = typename call_type::return_type;

		static constexpr std::size_t arity = call_type::arity;

		template<std::size_t N>
		struct argument
		{
			static_assert( N < arity, "error: invalid parameter index." );
			using type = typename call_type::template argument<N>::type;
		};
	};

	// Traits
	// constant member function
	template<class F>
	struct is_const_member_function;

	template<class R, class C, class... Args>
	struct is_const_member_function<R( C::* )( Args... ) const>
			: public std::true_type
	{
	};

	template<class R, class C, class... Args>
	struct is_const_member_function<R( C::* )( Args... )>
			: public std::false_type
	{
	};
}

#endif /* functiontraits_h */
