#include"header/common.hpp"
#include"header/User.hpp"
#include"SuperBlock.hpp"
using namespace std;

extern SuperBlock *sblock;
extern char buffer[TOTAL_SPACE];
vector<User*> users;

User::User(User &src){
    strcpy(username, src.username);
    strcpy(password, src.password);
}

User::User(
    char username_[USERNAME_SIZE],
    char password_[PASSWD_SIZE]
){
    strncpy(username, username_, USERNAME_SIZE);
    strncpy(password, password_, PASSWD_SIZE);
}

void User::set(
    char username_[USERNAME_SIZE],
    char password_[PASSWD_SIZE]
){
    strncpy(username, username_, USERNAME_SIZE);
    strncpy(password, password_, PASSWD_SIZE);
}

void input_users(){
    users.reserve(sblock->unum);
    char *p=buffer+USERTABLE_BEGIN;
    for (int i=0; i<sblock->unum; i++){
        users.push_back((User*)p);
        p+=sizeof(User);
    }
}

//新增用户
void add_user(
    char username[USERNAME_SIZE],
    char password[PASSWD_SIZE]
){
    int pos = USERTABLE_BEGIN + sizeof(User)*users.size();
    if (pos+sizeof(User)>=USERTABLE_SIZE){
        printf("用户数量已达上限！\n");
        return;
    }
    users.push_back((User*)(buffer + pos));
    users.back()->set(username,password);
}
