#include "mpu.h"

MPUGET::MPUGET()
{
}

void MPUGET::MPU_get_value(QByteArray temp2)
{
    static int z=0,y=0;
    if((temp2[0]==0x55)&&(temp2[1]==0x53))
     {
        //温度提取
        MPU[0]=temp2[8];
        MPU[1]=temp2[9];
        if (MPU[0]>=0)
        {
             TL=MPU[0];
        }
        else
        {
            TL=256+MPU[0];
        }
        TH=MPU[1];
        TEM=(double) ( ( (short)TH<<8  )+TL )/100;
     }
     if((temp2[22]==0x55)&&(temp2[23]==0x53))
     {
        //x角度提取
        MPU[2]=temp2[24];
        MPU[3]=temp2[25];
        if (MPU[3]>=0)
        {
             RollH=MPU[3];
             if(MPU[2]>=0)
             {
                 RollL=MPU[2];
             }
             else
             {
                 RollL=256+MPU[2];
             }
        }
        else
        {
              RollH=MPU[3]+1;
              if(MPU[2]>=0)
              {
                  RollL=MPU[2]-256;
              }
              else
              {
                  RollL=MPU[2];
              }
        }
        Roll=(double)(RollH*256+RollL)/32768*180;
        if(Roll>180)  Roll=Roll-360;
        Roll=(double)((int)(Roll*100))/100;//保留两位小数

        //y角度提取
        MPU[4]=temp2[26];
        MPU[5]=temp2[27];
        if (MPU[5]>=0)
        {
             PitchH=MPU[5];
             if(MPU[4]>=0)
             {
                 PitchL=MPU[4];
             }
             else
             {
                 PitchL=256+MPU[4];
             }
        }
        else
        {
              PitchH=MPU[5]+1;
              if(MPU[4]>=0)
              {
                  PitchL=MPU[4]-256;
              }
              else
              {
                  PitchL=MPU[4];
              }
        }
        Pitch=(double)(PitchH*256+PitchL)/32768*180;
        if(Pitch>180)  Pitch=Pitch-360;
        Pitch=(double)((int)(Pitch*100))/100;//保留两位小数
        y=-(int)Pitch;

        //z角度提取
        MPU[6]=temp2[28];
        MPU[7]=temp2[29];
        if (MPU[7]>=0)
        {
             YawH=MPU[7];
             if(MPU[6]>=0)
             {
                 YawL=MPU[6];
             }
             else
             {
                 YawL=256+MPU[6];
             }
        }
        else
        {
              YawH=MPU[7]+1;
              if(MPU[6]>=0)
              {
                  YawL=MPU[6]-256;
              }
              else
              {
                  YawL=MPU[6];
              }
        }
        Yaw=(double)(YawH*256+YawL)/32768*180-90;
        if(Yaw>180)  Yaw=Yaw-360;
        Yaw=(double)((int)(Yaw*100))/100;//保留两位小数
        z=-(int)Yaw;
     }

     //气压提取
     if((temp2[11]==0x55)&&(temp2[12]==0x56))
     {
         MPU[8]=temp2[13];
         MPU[9]=temp2[14];
         MPU[10]=temp2[15];
         MPU[11]=temp2[16];
         p3=MPU[11];
         if (MPU[10]>=0)
         {
              p2=MPU[10];
         }
         else
         {
             p2=256+MPU[10];
         }
         if (MPU[9]>=0)
         {
              p1=MPU[9];
         }
         else
         {
             p1=256+MPU[9];
         }
         if (MPU[8]>=0)
         {
              p0=MPU[8];
         }
         else
         {
             p0=256+MPU[8];
         }
         Pa=256*256*256*p3+256*256*p2+256*p1+p0;
     }

     //高度提取
     if((temp2[11]==0x55)&&(temp2[12]==0x56))
     {
         MPU[12]=temp2[17];
         MPU[13]=temp2[18];
         MPU[14]=temp2[19];
         MPU[15]=temp2[20];
         if(MPU[15]>=0)
         {
                 h3=MPU[15];
                 if (MPU[14]>=0)
                 {
                      h2=MPU[14];
                 }
                 else
                 {
                     h2=256+MPU[14];
                 }
                 if (MPU[13]>=0)
                 {
                      h1=MPU[13];
                 }
                 else
                 {
                     h1=256+MPU[13];
                 }
                 if (MPU[12]>=0)
                 {
                      h0=MPU[12];
                 }
                 else
                 {
                     h0=256+MPU[12];
                 }
         }
         else
         {
                 h3=MPU[15]+1;
                 if (MPU[14]>=0)
                 {
                      h2=MPU[14]-256;
                 }
                 else
                 {
                     h2=MPU[14];
                 }
                 if (MPU[13]>=0)
                 {
                      h1=MPU[13]-256;
                 }
                 else
                 {
                     h1=MPU[13];
                 }
                 if (MPU[12]>=0)
                 {
                      h0=MPU[12]-256;
                 }
                 else
                 {
                     h0=MPU[12];
                 }
         }
         High=256*256*256*h3+256*256*h2+256*h1+h0;
     }
}
