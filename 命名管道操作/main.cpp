//
//  main.cpp
//  命名管道操作
//
//  Created by 蓝猫 on 2018/11/15.
//  Copyright © 2018年 蓝猫. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;
/*
 命名管道打开操作和其他的文件打开有所区别;
 1.当打开命名管道是为了读操作时，只有出现有为了写操作打开命名管道
 的进程出现才可以。
 2.当打开命名管道是为了写操作时，只有出现有为了读操作打开命名管道
 的进程出现才可以。
 */
void fun1(int argc, const char * argv[])//使用mkfifo函数创建命名管道
{
    mode_t mode=0755;//文件权限设置
    if(argc!=2)
    {
       // cout<<"请输入正确的文件参数"<<endl;
        //exit(0);
    }
    //成功返回0 反之返回-1 第一个参数是命名管道的文件路径名字
    if(mkfifo("/Users/w/Desktop/unix_c/FIF.txt", mode)==0)
    {
        cout<<"命名管道创建成功"<<endl;
        //cout<<"创建失败"<<endl;
        //exit(1);
    }
    else
    {
        cout<<"创建失败"<<endl;
        exit(1);
    }
}
int main(int argc, const char * argv[])
{
    /*
     cout<<"argc:"<<argc<<endl;
     cout<<"argv:"<<endl;
     int a=argc;
     while (a)
     {
     cout<<argv[--a]<<endl;
     }
     cout<<endl;
     */
     fun1(argc,argv);
    return 0;
}
