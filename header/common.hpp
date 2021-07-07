#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<cstring>

int const USERNAME_SIZE     =20;                //用户名长度
int const PASSWD_SIZE       =20;                //密码长度
int const FILENAME_SIZE     =20;                //文件名长度
int const TOTAL_SPACE       =100<<20;           //缓冲区大小
int const BLOCK_SIZE        =4<<10;             //块大小

//int const METADATA_SIZE     =4<<10;         //元数据大小
int const SUPERBLOCK_SIZE   =sizeof(int)*2;     //超级块大小
int const USERTABLE_SIZE    =4000;              //用户表大小
int const INODETABLE_SIZE   =100000;            //文件表大小

int const USERTABLE_BEGIN   =SUPERBLOCK_SIZE;
int const USERTABLE_END     =USERTABLE_BEGIN+USERTABLE_SIZE;
int const INODETABLE_BEGIN  =USERTABLE_END;
int const INODETABLE_END    =INODETABLE_BEGIN+INODETABLE_SIZE;



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