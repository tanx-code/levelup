#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<cassert>

// Implementation:
// 1. could custom hash function by user
// 2. separate chaining with linked lists to handle collision

// It is helpful to have a list of prime numbers for the hash table size.
// e.g. 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289
// http://planetmath.org/goodhashtableprimes or "The Annotated STL Sources" P257

static const int TABLE_SIZE = 97;

template<typename K>
struct KeyHash {
    unsigned long operator() (const K& key) const{
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

template<>
struct KeyHash<std::string> {
    unsigned long operator() (const std::string& key) const{
        unsigned long val = 0;
        for(auto i : key) {
            val = val*5 + i; // 5 or other prime factors are both right
        }

        return val % TABLE_SIZE;
    }
};

template<typename K, typename V, typename F = KeyHash<K>>
class HashMap {
public:
    HashMap() : size_(0) , lists_(TABLE_SIZE) ,nullref_(V()) {}
    virtual ~HashMap() {}

public:
    void insert(const K& key, const V& value) {
        size_t keyHash = hashFunc_(key);

        if(find(key)) {
            (*this)[key] = value;
        }
        else {
            lists_[keyHash].push_back(std::pair<K,V>(key, value));
            size_++;
        }
    }

    void remove(const K& key) {
        if(!find(key))
            return ;

        size_t keyHash = hashFunc_(key);
        auto &list = lists_[keyHash];

        for(auto it = list.begin(); it != list.end(); it++) {
            if( it->first == key) {
                list.erase(it);
                size_--;
                break;
            }
        }
    }

    bool find(const K& key) {
        size_t keyHash = hashFunc_(key);

        if( lists_[keyHash].empty() )
            return false;

        for(auto i : lists_[keyHash]) {
            if( i.first == key)
                return true;
        }

        return false;
    }

    V& operator[] (const K& key) {
        size_t keyHash = hashFunc_(key);

        if(!find(key)) {
            insert(key, V());
            return (*this)[key];
        }

        // if forget &, here will make a copy which causes the modification useless
        auto &list = lists_[keyHash]; 
            for(auto it = list.begin(); it!=list.end(); it++ ) {
            if( it->first == key) 
                return it->second;
        }
        
        return nullref_;
    }

    size_t getSize() const {
        return size_;
    }
private:
    int size_;
    std::vector<std::list<std::pair<K,V>>> lists_;
    F hashFunc_;
    V nullref_;// for the return of empty reference
};





int main() {
    {
        HashMap<std::string,int> h;
        h["bob"] = 1234;
        h.insert("sam", 5678);

        assert( h["bob"] == 1234);
        assert( h["sam"] == 5678);

        assert(h.find("sam") == true);
        h.remove("sam");
        assert(h.find("sam") == false);

        // collision occured
        assert(h["ac"] == 0);
        assert(h["bb"] == 0);
        assert(h.find("ac") == true);
        assert(h.find("bb") == true);

        h["bb"]  = 131;
        assert(h["ac"] == 0);

        assert(h.getSize() == 3);
    }

    {
        // cunstom type 
        class User {
        public:
            User(int x) : v(x){}
            bool operator==( const User& src) {
                return src.v == v;
            }
            int v;
        };
        
        struct Myhashfunc {
            unsigned long operator() (const User& src) {
                return src.v % TABLE_SIZE;
            }
        };

        HashMap<User, int, Myhashfunc> m;
        User a(12);
        User b(13);
        m.insert(a, 1);
        m.insert(b, 2);

        assert(m.find(a) == true);
        assert(m.find(b) == true);

        // c,d  as a same key
        User c(12);
        User d(12);
        m.insert(c, 1);
        m.insert(d, 2);

        assert(m.find(c) == true);
        assert(m.find(d) == true);
        assert(m[c] == 2);
        assert(m[d] == 2);

        assert(m.getSize() == 2);
    }

    std::cout<<"All test cases pass";
    return 0;
}