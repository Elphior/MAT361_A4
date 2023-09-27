#include <iostream>
#include <string>

int modInverse(int a, int m)
{
    for (int i = 0; i < m; i++)
    {
        if ((a * i) % m == 1)
        {
            return i;
        }
    }
    return -1; // Modular inverse doesn't exist
}

std::string affineDecrypt(std::string ciphertext, int a, int b)
{
    std::string plaintext = "";
    for (char c : ciphertext)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            int x = c - base;
            int x_inverse = modInverse(a, 26);
            int result = (x_inverse * (x - b + 26)) % 26;
            plaintext += char(result + base);
        }
        else
        {
            plaintext += c; // Preserve non-alphabetical characters
        }
    }
    return plaintext;
}

int main()
{
    std::cout << "MAT361 Fall 2023: Affine Code Decoder in C++ - Sungmin Moon" << std::endl;
    std::cout << "This program is uploaded in https://github.com/Elphior/MAT361_A4.git" << std::endl;
    std::string ciphertext;
    std::cout << "Enter the ciphertext: ";
    getline(std::cin, ciphertext);
    std::cout << "Enter value a, if available(0 to perform full brute force decryption): ";
    int value;
    std::cin >> value;
    if (value == 0)
    {
        std::cout << std::endl;
        std::cout << "Performing full brute force decryption..." << std::endl;
        for (int a = 1; a < 26; a += 2)
        {
            if (modInverse(a, 26) != -1)
            {
                for (int b = 0; b < 26; b++)
                {
                    std::string plaintext = affineDecrypt(ciphertext, a, b);
                    std::cout << "a = " << a << ", b = " << b << ": " << plaintext << std::endl;
                }
                std::cout << std::endl;
            }
        }
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Performing brute force decryption for a = " << value << "..." << std::endl;
        if (modInverse(value, 26) != -1)
        {
            for (int b = 0; b < 26; b++)
            {
                std::string plaintext = affineDecrypt(ciphertext, value, b);
                std::cout << "a = " << value << ", b = " << b << ": " << plaintext << std::endl;
            }
        }
    }

    return 0;
}
