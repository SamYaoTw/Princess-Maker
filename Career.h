#ifndef CAREER_H
    #define CAREER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "Attribute.h"

    struct AttributeCompare
    {
        char Name[30] = {}; // �����O�W�r
        char CS; // Compare symbol �j��Τp��
        bool Type; //Type = 0 Compare Condition ����ƭ�, Type = 1 CAName ����ݩʭ�
        int Condition = 0; // ����ƭ�
        char CAName[30] = {}; // CompareAttribute name ����ݩʭȪ��W�r
    };
    /// �ھڤ���ݩʭ� �M�w��������¾�~
    struct Career
    {
        char Name[30] = {};         // ¾�~�W��
        AttributeCompare At[12];    // ¾�~�ݨD
        int size = 0;
    };
    /// ¾�~�W�ٻP¾�~����

    struct CareerDB
    {
        Career C[12];
        int size = 0;
    };
    /// ¾�~��Ʈw
    /// �Ĩ���ʫᦩ���� �P ��o���ݩʭ�

    bool ReadCareer(FILE * fp, Career * c);             //�q titlerules.txt ���o¾�~��T
    bool AddCareer(CareerDB * PDB, const Career * p);         //�N¾�~�[�J¾�~��Ʈw
    ///�O�o�^�Ǧ������\

    int SearchCareerMatch(const CareerDB * PDB, const Player * p);  // �d�߸�Ʈw���O�_���ŦX�n�D��¾�~ �Y���h�^�Ǹ�¾�~�b�Ӹ�Ʈw��������Index
    /// ��X-1��ܬƻ򳣤��ŦX

#endif
