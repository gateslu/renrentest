#include <string>
#include <iostream>
#include "../include/RRAPI"
using namespace RRAPI;
using namespace std;

int main(int argc, char *argv[])
{
    RenRenAPI api;
    bool result;
    api.m_usersAPI->isAppUser("Session key here", result);

    std::cout << result << std::endl;

    return 0;
}