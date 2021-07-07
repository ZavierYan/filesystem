#include"common.hpp"

struct User{
    int uid;
    char username[USERNAME_SIZE];
    char password[PASSWD_SIZE];
    User(User&);
    User(
        char username[USERNAME_SIZE],
        char password[PASSWD_SIZE]
    );
    void set(
        char username[USERNAME_SIZE],
        char password[PASSWD_SIZE]
    );
};

void input_users();

//新增用户
void add_user(
    char username[USERNAME_SIZE],
    char password[PASSWD_SIZE]
);

//删除用户
void del_user(int uid);