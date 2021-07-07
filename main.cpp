#include"header/common.hpp"
#include"header/User.hpp"
#include"header/Inode.hpp"
#include"header/Block.hpp"
#include"header/SuperBlock.hpp"
using namespace std;

unordered_map<string, void(*)(void)> func={
    {"info",info},
    {"login",login},
    {"dir",dir},
    {"create",create},
    {"delete",del},
    {"open",open},
    {"close",close},
    {"read",read},
    {"copy",copy},
    {"write",write},
    {"cd",cd}
};
char buffer[TOTAL_SPACE];   //缓冲区

SuperBlock *sblock;         //超级块
extern vector<User*> users;        //用户
extern vector<Inode*> inodes;      //文件信息
extern vector<Block*> blocks;      //文件数据

int cur_user;               //当前用户
int cur_dir;                //当前目录

//系统启动
void startup();
//初始化
void init();
//解析指令
void parseCmd();


int main(){
    startup();
    while(1){
        parseCmd();
    }
    return 0;
}

void startup(){
    ifstream fin("disk",ios::in|ios::binary);
    sblock = (SuperBlock*)buffer;
    if (!fin.is_open()){
        init();
    }
    else{
        fin.read(buffer, TOTAL_SPACE);
        input_users();
        input_inodes();
        input_blocks();
        /* users.reserve(sblock->unum);
        inodes.reserve(sblock->inum);
        char *p=buffer+USERTABLE_BEGIN;
        for (int i=0; i<sblock->unum; i++){
            users.push_back((User*)p);
            p+=sizeof(User);
        }
        p=buffer+INODETABLE_BEGIN;
        for (int i=0; i<sblock->inum; i++){
            inodes.push_back((Inode*)p);
            p+=sizeof(Inode);
        }
        for (int i=INODETABLE_END; i<TOTAL_SPACE; i+=sizeof(blocks)){
            blocks.push_back((Block*)(buffer+i));
        } */
    }
    cur_user=-1;
    cur_dir=0;
}

void init(){
    sblock->unum=0;
    sblock->inum=1;
    sblock->first_free_block=0;
    inodes.push_back((Inode*)(buffer+INODETABLE_BEGIN));
    inodes[0]->set("/",0,1,-1,-1,-1);
    for (int i=INODETABLE_END; i<TOTAL_SPACE; i+=sizeof(blocks)){
        blocks.push_back((Block*)(buffer+i));
    }
    for (int i=0; i<blocks.size(); i++){
        blocks[i]->bid  =i;
        blocks[i]->pre  =i-1;
        blocks[i]->next =i+1;
        blocks[i]->inode=-1;
    }
    blocks.back()->next =-1;
}

void parseCmd(){
    string cmd;//命令
    cin>>cmd;
    if (func.count(cmd)){
        func[cmd]();
    }
    else{
        printf("无效命令\n");
    }
}