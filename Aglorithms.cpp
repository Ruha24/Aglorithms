#include <iostream>
#include <cstdio>
#include <cstdlib>   
#include <fstream>

#include "Gost34_2012.h"
#include <vector>
#include <string>



#define FILE_BUFFER_SIZE 40000

TGOSTHashContext CTX;

void HashPrint(TGOSTHashContext* CTX)
{
    printf("%d bit hash sum: \n", CTX->hash_size);
    int i;
    if (CTX->hash_size == 256)
        for (i = 32; i < 64; i++)
            printf("%02x", CTX->hash[i]);
    else
        for (i = 0; i < 64; i++)
            printf("%02x", CTX->hash[i]);
    printf("\n");
}
void GetHashFile(const std::string file_name, int hash_size)
{
    std::cout << "Открыт файл" << file_name;
    Gost34_2012 gost;
    TGOSTHashContext CTX;

    std::ifstream file(file_name, std::ios::binary);
    if (file.is_open())
    {
        std::vector<uint8_t> buffer(FILE_BUFFER_SIZE);
                           
        gost.GOSTHashInit(&CTX, hash_size);

        while (file.read(reinterpret_cast<char*>(buffer.data()), FILE_BUFFER_SIZE))
        {
            size_t len = file.gcount();
            gost.GOSTHashUpdate(&CTX, buffer.data(), len);
        }

        gost.GOSTHashFinal(&CTX);
        file.close();

        std::cout << "GOST 34.11-2012 \"Stribog\"\nFile name: " << file_name << std::endl;
        HashPrint(&CTX);
    }
    else
    {
        std::cout << "File error: " << file_name << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    GetHashFile("D:\\Euro Truck Simulator 2\\def.scs", 256);

    return 0;
}


