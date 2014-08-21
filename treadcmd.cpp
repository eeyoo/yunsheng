/*************************************************************************************

* Copyright (c) 2014, 宁波韵升中央研究院

* All rights reserved.

* 文件名称: treadcmd.cpp

* 功能描述: 读取XML配置文件

* 当前版本: 1.000

* 编	写: 汤超阳

* 创建日期: 2014.7.6

* 修	改:
**************************************************************************************/

#include "treadcmd.h"
#include "qa5driver.h"

#include <QFile>
#include <QDomDocument>


/*************************************************************************
* 函数名称: TReadCmd
* 功   能: 构造函数
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
TReadCmd::TReadCmd()
{
}
/*************************************************************************
* 函数名称: ReadCmd
* 功   能: 读取、解析XML文件
* 输入参数:
* 输出参数: 无
* 返 回 值: 无
*************************************************************************/
bool TReadCmd::ReadCmd()
{
    QDomDocument doc;
#ifdef EMBEDED_ARM
    QFile cf("/root/Config.xml"); //filepath为xml文件路径
#else
    QFile cf("Config.xml"); //filepath为xml文件路径
#endif
    if (!cf.open(QIODevice::ReadOnly))
    {
        return false;
    }
    if (!doc.setContent(&cf))
    {
        cf.close();
        return false;
    }

    QDomElement docElem = doc.documentElement();  //返回根元素
    QDomNode n = docElem.firstChild();   //返回根节点的第一个子节点
    while(!n.isNull())
    {
        if (n.isElement())  //如果节点是元素
        {
            QDomElement e1 = n.toElement();  //将其转换为元素
            QDomNodeList list1 = e1.childNodes(); //获得元素e的所有子节点的列表
            for(int i=0; i<list1.count(); i++) //遍历该列表
            {
                QDomNode node1 = list1.at(i);
                if(node1.isElement()){
                    QDomElement e2 = node1.toElement();  //将其转换为元素
                    QDomNodeList list2 = e2.childNodes(); //获得元素e的所有子节点的列表
                    for(int j=0; j<list2.count(); j++) //遍历该列表
                    {
                        QDomNode node2 = list2.at(j);
                        if(node2.isElement()){
                            if(e1.tagName() == "CMD"){
                                CmdTil cmdt;
                                cmdt.cmdId  = node2.toElement().attribute("CmdId").toInt(NULL,16);
                                cmdt.cmdTil = node2.toElement().attribute("CmdTil");
                                //printf("%s\n",cmdt.cmdTil.toAscii().data());
                                if(e2.tagName() == "MOV"){
                                    CmdM.push_back(cmdt);
                                }else if(e2.tagName() == "INPUT"){
                                    CmdI.push_back(cmdt);
                                }else if(e2.tagName() == "OUTPUT"){
                                    CmdO.push_back(cmdt);
                                }else if(e2.tagName() == "STACK"){
                                    CmdS.push_back(cmdt);
                                }
                            }
                        }
                    }
                }
            }
        }
        n = n.nextSibling();  //下一个兄弟节点
    }
}

TReadCmd    readCmd;    //读取命令配置文件

//==========================================================================================
// End of file.
//==========================================================================================
