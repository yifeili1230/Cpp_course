#ifndef NAMED_VECTOR_HPP
#define NAMED_VECTOR_HPP

#include <vector>
#include <string>

namespace ipb {
    template <typename T>
    class named_vector : public std::vector <T> {
    private:
        std::string name_;
    public:
        named_vector() : std::vector<T>(), name_("") {}
        named_vector(const std::string& name) : std::vector<T>(), name_(name){};
        named_vector(const std::string& name, const std::vector<T>& vec) : std::vector<T>(vec), name_(name) {};


        std::string name() const { return name_; }
        std::vector<T> vector() const {return std::vector<T>(*this); }

  
        size_t size() const {
            return std::vector<T>::size() + name_.length();
        }

        
        bool empty() const {
            return std::vector<T>::empty() || name_.empty();
        }

        
    };
}


#endif // NAMED_VECTOR_HPP