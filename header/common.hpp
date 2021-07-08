#pragma once

int const USERNAME_SIZE     =20;                //用户名长度
int const PASSWD_SIZE       =20;                //密码长度
int const FILENAME_SIZE     =20;                //文件名长度
int const TOTAL_SPACE       =100<<20;           //缓冲区大小
int const BLOCK_SIZE        =4<<10;             //块大小
int const BITMAP_SIZE       =BLOCK_SIZE;//TOTAL_SPACE/BLOCK_SIZE/sizeof(char);

//实验要求功能
void info();
void login();
void dir();
void create();
void del();
void open();
void close();
void read();
void copy();
void write();
void cd();

//系统内部功能
void save();