/*************************************************************************************

* Copyright (c) 2014, �������������о�Ժ

* All rights reserved.

* �ļ�����: treadcmd.cpp

* ��������: ��ȡXML�����ļ�

* ��ǰ�汾: 1.000

* ��	д: ������

* ��������: 2014.7.6

* ��	��:
**************************************************************************************/

#include "treadcmd.h"
#include "qa5driver.h"

#include <QFile>
#include <QDomDocument>


/*************************************************************************
* ��������: TReadCmd
* ��   ��: ���캯��
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
TReadCmd::TReadCmd()
{
}
/*************************************************************************
* ��������: ReadCmd
* ��   ��: ��ȡ������XML�ļ�
* �������:
* �������: ��
* �� �� ֵ: ��
*************************************************************************/
bool TReadCmd::ReadCmd()
{
    QDomDocument doc;
#ifdef EMBEDED_ARM
    QFile cf("/root/Config.xml"); //filepathΪxml�ļ�·��
#else
    QFile cf("Config.xml"); //filepathΪxml�ļ�·��
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

    QDomElement docElem = doc.documentElement();  //���ظ�Ԫ��
    QDomNode n = docElem.firstChild();   //���ظ��ڵ�ĵ�һ���ӽڵ�
    while(!n.isNull())
    {
        if (n.isElement())  //����ڵ���Ԫ��
        {
            QDomElement e1 = n.toElement();  //����ת��ΪԪ��
            QDomNodeList list1 = e1.childNodes(); //���Ԫ��e�������ӽڵ���б�
            for(int i=0; i<list1.count(); i++) //�������б�
            {
                QDomNode node1 = list1.at(i);
                if(node1.isElement()){
                    QDomElement e2 = node1.toElement();  //����ת��ΪԪ��
                    QDomNodeList list2 = e2.childNodes(); //���Ԫ��e�������ӽڵ���б�
                    for(int j=0; j<list2.count(); j++) //�������б�
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
        n = n.nextSibling();  //��һ���ֵܽڵ�
    }
}

TReadCmd    readCmd;    //��ȡ���������ļ�

//==========================================================================================
// End of file.
//==========================================================================================
