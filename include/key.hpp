#ifndef _HARDWATER_KEY_HPP
#define _HARDWATER_KEY_HPP
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <memory>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdint>

namespace Hardwater {
    class Key {
    public:
        enum class KeyType {
            Public,
            Private
        };
        
        struct ReadError : public std::runtime_error {
            ReadError(std::string err) : runtime_error(err) {}
        };
        
        Key(std::string pathname, KeyType type, const char *password);
        
        inline RSA* getKey() { return rsa.get(); }
        
        inline bool isPublic() const { return type == KeyType::Public; }
        
        inline bool isPrivate() const { return type == KeyType::Private; }
        
    protected:
        KeyType type;
        std::shared_ptr<RSA> rsa;
    };
}
#endif
