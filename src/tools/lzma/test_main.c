#if 0
#include <stdio.h>
#include "LzmaLib.h"

int main(int argc, char* argv[])
{
    FILE* pFile = fopen(argv[1], "rb");

    if (pFile == NULL)
    {
        printf("Error to Open the file!\n");
        return  - 1;
    }

    /*�ļ���С����*/
    fseek(pFile, 0, SEEK_END);
    size_t srcLen = ftell(pFile);
    //srcLenΪ�ļ����ֽ���
    rewind(pFile);//�����ļ�ָ��
    size_t destLen = srcLen * 2;

    unsigned char* psrcRead = new unsigned char[srcLen]; //ԭʼ�ļ�����
    unsigned char* pLzma = new unsigned char[destLen]; //���ѹ������
    unsigned char* pDecomress = new unsigned char[srcLen]; //��Ž�ѹ������

/******************************ѹ������*********************************/
    ///��ȡ�ļ�����
    fread(psrcRead, sizeof(char), srcLen, pFile);

    ///����prop����
    unsigned char prop[5] =
    {
        0
    };
    size_t sizeProp = 5;

    ///ѹ���ļ�����
    if (SZ_OK != LzmaCompress(pLzma, &destLen, psrcRead, srcLen, prop,
        &sizeProp, 9, (1 << 24), 3, 0, 2, 32, 2))
    {
        //������
        printf("ѹ��ʱ����\n");
        delete [] psrcRead;
        delete [] pDecomress;
        delete [] pLzma;
        fclose(pFile);
        return  - 1;
    }
    ///���ļ�

    FILE* pCompressFile = fopen("compress.dat", "wb");
    //д��ѹ���������
    if (pCompressFile == NULL)
    {
        printf("�����ļ�����!\n");
        delete [] psrcRead;
        delete [] pDecomress;
        delete [] pLzma;
        fclose(pFile);
        return  - 1;
    }

    ///д��ѹ��������ݵ��ļ�
    fwrite(pLzma, sizeof(char), destLen, pCompressFile);
    fclose(pCompressFile);

/***********************��ѹ����***********************************/
    FILE* pDecompressFile = fopen("decompress.dat", "wb");
    //д���ѹ������
    if (pDecompressFile == NULL)
    {
        printf("д�����ݳ���\n");
        delete [] psrcRead;
        delete [] pDecomress;
        delete [] pLzma;
        fclose(pFile);
        return  - 1;
    }

    //ע�⣺��ѹ��ʱprops����Ҫʹ��ѹ��ʱ���ɵ�outProps����������������ѹ��
    if (SZ_OK != LzmaUncompress(pDecomress, &srcLen, pLzma, &destLen, prop, 5))
    {
        delete [] psrcRead;
        delete [] pDecomress;
        delete [] pLzma;

        fclose(pDecompressFile);
        fclose(pFile);
        return  - 1;
    }
    //����ѹ����������д�뵽�ļ�
    fwrite(pDecomress, sizeof(char), srcLen, pDecompressFile);

    delete [] psrcRead;
    delete [] pDecomress;
    delete [] pLzma;

    fclose(pDecompressFile);
    fclose(pFile);

    return 0;
}

#end
