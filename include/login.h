#ifndef LOGIN_H
#define LOGIN_H
#include <string>

void menuLoginorRegister();

/* Login & Register */
bool login(const std::string& username, const std::string& password);
void createLoginSession(const std::string& username);
void registerUser(const std::string& username, const std::string& password);

/* Validation */
bool validationUsername(const std::string& username);
bool validationPassword(const std::string& password);
bool checkingUsername(const std::string& usernameToCheck);

#endif