//
//  main.cpp
//  Server
//
//  Created by 蓝猫 on 2018/11/16.
//  Copyright © 2018年 蓝猫. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <memory>
#define F_NAME "/Users/w/Desktop/unix_c/FIFO.txt"
#define MAX 80
using namespace std;
class Server
{
private:
    FILE *fp;//命名管道
    char *readbuffer;// 读缓冲区
    string temp;//暂存到上一个字符串
public:
    Server();
    ~Server();
    void GetStr();
};
Server::Server()
{
    temp="";
    readbuffer=new char[MAX];
    fp=fopen(F_NAME, "r");//打开文件 读的方式
    cout<<"hello"<<endl;
    if((fp)==NULL)//管道不存在重新创建
    {
        cout<<"文件打开失败"<<endl;
        //设置默认权限 确保你创建的文件具有所希望的缺省权限，防止其他非同组用户对你的文件具有写权限
        umask(0);
        //生成设备节点/文件
        mknod(F_NAME, S_IFIFO|0666, 0);
    }
    else
    {
        cout<<"文件打开成功"<<endl;
        fclose(fp);
    }
}
Server::~Server()
{
    delete readbuffer;
    readbuffer=NULL;
}
void Server::GetStr()
{
    int a=0;
    while (a==0)
    {
        a++;
        //cout<<"getstr"<<endl;
        // 查看文件是否打开
        if((fp=fopen(F_NAME, "r"))==NULL)
        {
            cout<<"fifo文件打开失败"<<endl;
            exit(0);
        }
        //从命名管道读取数据
        if(fgets(readbuffer,MAX,fp)!=NULL)
        {
            string s;
            s=readbuffer;
            if(s!=temp)
            {
                cout<<"接受到字符串："<<s<<endl;
                temp=s;
            }
            
            fclose(fp);
        }
        else
        {
            if(ferror(fp))
            {
                perror(" 文件读取失败\n");
                exit(1);
            }
        }
    }
}
int main(int argc, const char * argv[])
{
    cout<<"服务器端接收程序"<<endl;
    shared_ptr<Server> ser=make_shared<Server>();
    while (1)
    {
        ser->GetStr();
    }
    
    return 0;
}
