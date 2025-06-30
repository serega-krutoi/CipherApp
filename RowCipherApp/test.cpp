#include <iostream>
#include <dlfcn.h>     // Для dlopen, dlsym, dlclose (на Linux)
#include "include/ICipherFactory.h"
#include "include/ICipher.h"

int main() {
    const char* path = "builded/plugins/codeword/libcodeword.so"; // Путь к твоему .so (уточни!)
    void* handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Ошибка dlopen: " << dlerror() << std::endl;
        return 1;
    }

    typedef ICipherFactory* (*CreateFactoryFunc)();
    CreateFactoryFunc createFactory = (CreateFactoryFunc)dlsym(handle, "createFactory");
    if (!createFactory) {
        std::cerr << "Ошибка dlsym: " << dlerror() << std::endl;
        dlclose(handle);
        return 2;
    }

    ICipherFactory* factory = createFactory();
    if (!factory) {
        std::cerr << "createFactory вернул nullptr\n";
        dlclose(handle);
        return 3;
    }

    try {
        factory->setParameter("codeword", "СЕКРТ");
        ICipher* cipher = factory->create();
        if (!cipher) {
            std::cerr << "create() вернул nullptr\n";
            delete factory;
            dlclose(handle);
            return 4;
        }

        std::string text = "ПРИВЕТ";
        std::string enc = cipher->encrypt(text);
        std::string dec = cipher->decrypt(enc);

        std::cout << "Оригинал:   " << text << std::endl;
        std::cout << "Шифр:       " << enc << std::endl;
        std::cout << "Расшифровка:" << dec << std::endl;

        delete cipher;
    } catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    delete factory;
    dlclose(handle);
    return 0;
}
