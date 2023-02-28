#pragma once

#include <concepts>

/*
 * A singleton definition for self-initialized singletons
 */
template<typename T, bool Alloc_If_Not_Existent = false>
class Self_Init_Singleton {
	private:
		// singleton instance
		static T* mInstance;

	protected:
		// protected constructor - initializes the constructor (lazy init constructor)
		Self_Init_Singleton() noexcept {
			if constexpr (!Alloc_If_Not_Existent) {
				static_assert(std::is_base_of_v<Self_Init_Singleton<T>, T>, "T should derive from Self_Init_Singleton via CRTP");
			}
			mInstance = static_cast<T*>(this);
		}

	public:
		// retrieve the singleton instance
		static T* Instance() {
			if constexpr (Alloc_If_Not_Existent) {
				if (!mInstance)
					mInstance = new T;
			}

			return mInstance;
		}
};

template<class T, bool Alloc_If_Not_Existent> T* Self_Init_Singleton<T, Alloc_If_Not_Existent>::mInstance = nullptr;
