#include <iostream>
#include "mapped_file.hpp"
#include "ion.hpp"
#include <iostream>
#include "key.hpp"
#include "openssl/rsa.h"
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>


int main(int argc, const char ** argv) {
    using std::cerr;
    using std::cout;
    using std::endl;
    OpenSSL_add_all_algorithms();
    Hardwater::MappedFile f("wow");
    Hardwater::Key key("test_files/keys/generic.pem",
                       Hardwater::Key::KeyType::Private,
                       "passphrase");
    RSA *r = key.getKey();
    auto res = RSA_size(r);
    std::cout << "Rsa size is " << res << std::endl;
    return 0;
    /*
    auto m = std::make_unique<Hardwater::MappedFile>("kobold.png");
    Hardwater::Ion i(std::move(m));
    i.generate();
    cout << "File has " << i.getNumChunks() << " chunks with a size of " << i.getChunkSize() << "bytes" << endl;
    cout << "Overall hash: " << i.getOverallHash().getDigest() << endl;
    auto c = i.getChunks();
    for(int i = 0; i < c.size(); ++i) {
        cout << "Chunk " << i << ": " << c.at(i).getHash().getDigest() << endl;
    }

    Hardwater::Ion other;
    auto size = i.getFile().getSize();
    std::vector<Hardwater::FragmentHash> frags;
    for(auto f : i.getChunks()) {
        frags.emplace_back(f.getHash());
    }
    
    auto op = std::make_unique<Hardwater::MappedFile>("kobold_alt.png", size);
    other.setFile(std::move(op));
    other.setChunkSize(i.getChunkSize());
    other.setOverallHash(i.getOverallHash());
    other.createChunks(frags);
    std::cout << "Check validity overall: " << other.checkValidity() << endl;
    checkHashes(other.getChunks());
    auto ourChunks = other.getChunks();
    const auto &iChunks = i.getChunks();
    for(int i = 0; i < iChunks.size(); ++i) {
        ourChunks.at(i).writeOut(iChunks.at(i).getData());
    }
    std::cout << "Check validty again: " << other.checkValidity() << endl;
    checkHashes(other.getChunks());
    return 0;
    */
}
