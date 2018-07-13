#include "gps.h"

GPS::GPS()
{
}

void GPS::GPS_get_value(QByteArray temp)
{
    static int i =0;
    static int j =0;
    static int j_2=0;
    static int j_3=0;
    static int comma =0;
    static int point =0;

    if((temp[0]=='$')&&(temp[1]=='G')&&(temp[2]=='P')&&(temp[3]=='R')&&(temp[4]=='M')&&(temp[5]=='C'))
      {
            //纬度计算
             for(j=0;j<72;j++)
             {
                  if(temp[j]==',')
                  {    comma++;   }
                  if(comma==3)
                  {
                      Lat[j_2]=temp[j]-48;
                       j_2++;
                  }
              }
              j_2=0;
              comma=0;
              lat_1=Lat[1]*10+Lat[2];
              lat_2=Lat[3]*10+Lat[4]+(double)Lat[6]/10+(double)Lat[7]/100+(double)Lat[8]/1000+(double)Lat[9]/10000+(double)Lat[10]/100000;

              for(j=0;j<72;j++)
              {
                   if(temp[j]==',')
                   {    comma++;   }
                   if(comma==4)
                   {
                       Lat[j_2]=temp[j]-48;
                        j_2++;
                   }
               }
               j_2=0;
               comma=0;
               if(Lat[1]=='N'-48)
              {
                   N[0]='N';
                   //ui->N->setText(N);
               }
               else
               {
                   N[0]='S';
                   //ui->N->setText(N);
               }

             //经度计算
               for(j=0;j<72;j++)
               {
                    if(temp[j]==',')
                    {    comma++;   }
                    if(comma==5)
                    {
                        Lng[j_2]=temp[j]-48;
                         j_2++;
                    }
                }
                j_2=0;
                comma=0;
                lng_1=Lng[1]*100+Lng[2]*10+Lng[3];
                lng_2=Lng[4]*10+Lng[5]+(double)Lng[7]/10+(double)Lng[8]/100+(double)Lng[9]/1000+(double)Lng[10]/10000+(double)Lng[11]/100000;

                for(j=0;j<72;j++)
                {
                     if(temp[j]==',')
                     {    comma++;   }
                     if(comma==6)
                     {
                         Lng[j_2]=temp[j]-48;
                          j_2++;
                     }
                 }
                 j_2=0;
                 comma=0;
                 if(Lng[1]=='E'-48)
                {
                     E[0]='E';
                     //ui->E->setText(E);
                 }
                 else
                 {
                     E[0]='S';
                    // ui->E->setText(E);
                 }

             //地面速率
             for(j=0;j<72;j++)
             {
                  if(temp[j]==',')
                  {    comma++;   }
                  if(comma==7)
                  {
                      Groudrat[j_2]=temp[j]-48;
                       j_2++;
                  }
              }
              j_2=0;
              comma=0;

              for(j=0;j<7;j++)
               {
                        if(Groudrat[j]==254)
                        {   point=j;}
               }

              if(point==2)
              {
                     groudrat=Groudrat[1]+(double)Groudrat[3]/10+(double)Groudrat[4]/100+(double)Groudrat[5]/1000;
              }
              else if(point==3)
              {
                     groudrat=Groudrat[1]*10+Groudrat[2]+(double)Groudrat[4]/10+(double)Groudrat[5]/100;
              }
              else if(point==4)
              {
                     groudrat=Groudrat[1]*100+Groudrat[2]*10+Groudrat[4]+(double)Groudrat[5]/10;
              }
              groudrat=groudrat*1.852;

             //时间计算
              for(j=0;j<72;j++)
              {
                   if(temp[j]==',')
                   {    comma++;   }
                   if(comma==1)
                   {
                       time[j_2]=temp[j]-48;
                        j_2++;
                   }
               }
               j_2=0;
               comma=0;

               h=time[1]*10+time[2]+8;
               m=time[3]*10+time[4];
               s=time[5]*10+time[6]+(time[8]*10+time[9])/100;

               for(j=0;j<72;j++)
               {
                    if(temp[j]==',')
                    {    comma++;   }
                    if(comma==9)
                    {
                        time[j_2]=temp[j]-48;
                         j_2++;
                    }
                }
                j_2=0;
                comma=0;

                day=time[1]*10+time[2];
                month=time[3]*10+time[4];
                year=time[5]*10+time[6]+2000;
      }

    //find $GPGGA
        for(j=0;j<500;j++)
        {
             if(   (temp[j]=='$')&&(temp[j+1]=='G')&&(temp[j+2]=='P')&&(temp[j+3]=='G')&&(temp[j+4]=='G')&&(temp[j+5]=='A') )
             {
                 j_3=j;
             }
         }
        //海拔
       for(j=0;j<72;j++)
       {
            if(temp[j_3+j]==',')
            {    comma++;   }
            if(comma==9)
            {
                Altitude[j_2]=temp[j+j_3]-48;
                 j_2++;
            }
        }
        j_2=0;
        comma=0;

        for(j=0;j<7;j++)
         {
                  if(Altitude[j]==254)
                  {   point=j;}
         }
         if(point==4)
         {
             altitude=Altitude[1]*100+Altitude[2]*10+Altitude[3]+(double)Altitude[5]/10;
         }
         else if(point==5)
         {
             altitude=Altitude[1]*1000+Altitude[2]*100+Altitude[3]*10+Altitude[4]+(double)Altitude[6]/10;
         }
         else  if(point==3)
         {
             altitude=Altitude[1]*10+Altitude[2]+(double)Altitude[4]/10;
         }
         else  if(point==2)
         {
             altitude=Altitude[1]+(double)Altitude[3]/10;
         }
       //  altitude=Altitude[4];

         //大地水准面高度
         for(j=0;j<72;j++)
         {
              if(temp[j_3+j]==',')
              {    comma++;   }
              if(comma==11)
              {
                  Geoidalheight[j_2]=temp[j+103]-48;
                   j_2++;
              }
          }
          j_2=0;
          comma=0;
          for(j=0;j<7;j++)
           {
                    if(Geoidalheight[j]==254)
                    {   point=j;}
           }
       if(point==3)
       {
           if(Geoidalheight[1]=='-'-48)
           {
                 geoidalheight=-Geoidalheight[2]-(double)Geoidalheight[4]/10;
           }
           else
           {
                geoidalheight=Geoidalheight[1]*10+Geoidalheight[2]+(double)Geoidalheight[4]/10;
           }
       }
       else if(point==4)
       {
           if(Geoidalheight[1]=='-'-48)
           {
                 geoidalheight=-Geoidalheight[2]*10-Geoidalheight[3]-(double)Geoidalheight[5]/10;
           }
           else
           {
                geoidalheight=Geoidalheight[1]*100+Geoidalheight[2]*10+Geoidalheight[3]+(double)Geoidalheight[5]/10;
           }
       }
       else if(point==2)
       {
           geoidalheight=Geoidalheight[1]+(double)Geoidalheight[3]/10;
       }

}
