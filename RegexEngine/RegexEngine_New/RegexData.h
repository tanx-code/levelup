#pragma once
#include<vector>
#include<map>
#include<algorithm>

namespace tl
{
	namespace regex_internal
	{
		class CharRange;

		template<typename T>
		class Sorted_vector
		{
		public:
			void push_back(CharRange r)
			{
				v.push_back(r);
				std::sort(v.begin(), v.end());
			}

			T& operator[](size_t i)
			{
				return v[i];
			}
			size_t size()
			{
				return v.size();
			}
			void clear()
			{
				v.clear();
			}
		private:
			typedef std::vector<T> vec;
			vec v;
		};
		 
		template<typename K, typename V>
		class Multimap
		{
		private:
			typedef std::vector<V> myvector;
			typedef std::map<K, myvector> mymap;

			mymap m_;
		public:
			// 局部特化，就要加typename
			// 两阶段名称查找，定义的时候找一次，找不到就会在实例化的时候再找一次
			// 这里::iterator是不知道的，所以要加
			typedef typename mymap::iterator myiterator;

			void insert(const K &first, const V & second)
			{
				if (m_.find(first) == m_.end())
				{
					myvector v;
					v.push_back(second);
					//m_.insert(std::pair<K, myvector>(first, v));
					m_.emplace(first, v);
				}
				else
				{
					m_[first].push_back(second);
				}
			}
			myvector& operator[](const K& e)
			{
				if (m_.find(e) == m_.end())
					return myvector();// 返回空的吧，返回null又不行= =
				return m_[e];
			}
			void clear()
			{
				m_.clear();
			}
			myiterator begin()
			{
				return m_.begin();
			}
			myiterator end()
			{
				return m_.end();
			}
			size_t size()
			{
				return m_.size();
			}
		};

		typedef Sorted_vector<CharRange> List;
		
		class CharRange
		{
		public:
			wchar_t begin;
			wchar_t end;
			
			CharRange();
			CharRange(wchar_t begin_, wchar_t end_);

			bool operator<(CharRange item)const;
			bool operator<=(CharRange item)const;
			bool operator>(CharRange item)const;
			bool operator>=(CharRange item)const;
			bool operator==(CharRange item)const;
			bool operator!=(CharRange item)const;

			bool operator<(wchar_t item)const;
			bool operator<=(wchar_t item)const;
			bool operator>(wchar_t item)const;
			bool operator>=(wchar_t item)const;
			bool operator==(wchar_t item)const;
			bool operator!=(wchar_t item)const;
		};
	}
}