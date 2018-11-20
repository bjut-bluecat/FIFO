//
//  main.cpp
//  Client
//
//  Created by 蓝猫 on 2018/11/16.
//  Copyright © 2018年 蓝猫. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <memory>
#include <string>
#define F_NAME "/Users/w/Desktop/unix_c/FIFO.txt"
using namespace std;
class Client
{
private:
    FILE *fp;
public:
    Client();
    ~Client(){cout<<"函数吸🐶"<<endl;};
    void SendStr();
};
Client::Client()
{
    fp=fopen(F_NAME, "w");
    if(fp==NULL)
    {
        cout<<"文件打开失败"<<endl;
        exit(1);
    }
    else
    {
        cout<<"文件打开成功"<<endl;
    }
};
void Client::SendStr()
{
    char *s="hello";
    cout<<"请在客户端输入你要发送到消息"<<endl;
    //scanf("%s",s);
    string temp;
    cin>>temp;
    s=(char*)temp.data();//string和char*转换
    if(temp=="quit")
    {
        fclose(fp);
        exit(1);
    }
    cout<<s<<endl;
    
    if(fputs(s,fp)==EOF)
    {
        cout<<"写fifo失败"<<endl;
        exit(1);
    }
   //fclose(fp);
};
int main(int argc, const char * argv[])
{
    cout<<"客户端发送程序"<<endl;
    shared_ptr<Client> ser=make_shared<Client>();
    while(1)
    {
        ser->SendStr();
    }
    
    return 0;
}
